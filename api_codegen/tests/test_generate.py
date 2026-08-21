import re
from pathlib import Path

import pytest
import yaml

from api_codegen.generate import (
    API_CONFIG,
    TYPE_CONFIG,
    _BaseModelBuilder,
    _CppTypeResolver,
    _MethodModelBuilder,
    _OpenApiGenerator,
    _TypeModelBuilder,
)


def test_snake_to_camel_converts_telegram_names() -> None:
    assert _BaseModelBuilder._cpp_name("id") == "id"
    assert _BaseModelBuilder._cpp_name("file_unique_id") == "fileUniqueId"


def test_direct_api_keeps_legacy_args_order_and_defaults() -> None:
    builder = _MethodModelBuilder({})
    properties = {
        "audio": {},
        "business_connection_id": {},
        "caption": {},
        "chat_id": {},
        "duration": {},
    }

    assert builder._ordered_arg_names("sendAudio", properties, {"audio", "chat_id"}) == [
        "chat_id",
        "audio",
        "caption",
        "duration",
        "business_connection_id",
    ]
    assert builder._arg_default("std::int32_t", "setWebhook", "max_connections") == "40"
    assert builder._arg_default("std::shared_ptr<InputFile>", "setWebhook", "certificate") == "nullptr"
    assert builder._arg_declaration_type("std::string") == "std::string_view"


def test_compatibility_config_is_grouped_by_telegram_entity() -> None:
    assert API_CONFIG["setStickerSetTitle"]["args_order"] == ["name", "title"]
    assert API_CONFIG["editMessageText"]["return_type"] == "std::shared_ptr<Message>"
    assert API_CONFIG["getUpdates"]["args"]["limit"]["default"] == 100
    assert API_CONFIG["sendMediaGroup"]["supports_attach_references"] is True
    assert {name for name, config in API_CONFIG.items() if config.get("supports_attach_references")} == {
        "addStickerToSet",
        "createNewStickerSet",
        "editMessageMedia",
        "editMessageText",
        "editStory",
        "postStory",
        "replaceStickerInSet",
        "sendMediaGroup",
        "sendPaidMedia",
        "sendRichMessage",
        "setBusinessAccountProfilePhoto",
        "setMyProfilePhoto",
    }
    assert TYPE_CONFIG["BotCommandScopeChatMember"]["fields"]["user_id"]["type"] == "std::int64_t"
    assert TYPE_CONFIG["Chat"]["fields"]["type"]["enum"]["Private"] == "private"


def test_integer_widths_follow_schema_and_telegram_id_rules() -> None:
    method_builder = _MethodModelBuilder({})
    type_builder = _TypeModelBuilder({})
    assert _CppTypeResolver.type({"type": "integer", "format": "int64"}) == "std::int64_t"
    assert _CppTypeResolver.type({"type": "integer", "format": "int32"}) == "std::int32_t"
    assert _CppTypeResolver.type({"type": "integer"}) == "std::int32_t"

    user_id = method_builder._build_arg(
        "giftPremiumSubscription",
        "receiver_user_id",
        {"type": "integer", "format": "int32"},
        True,
        False,
    )
    limit = method_builder._build_arg(
        "getUpdates",
        "limit",
        {"type": "integer", "format": "int32"},
        False,
        False,
    )
    chat_id = method_builder._build_arg(
        "sendMessage",
        "chat_id",
        {"type": "integer", "format": "int64"},
        True,
        False,
    )
    direct_messages_topic_id = method_builder._build_arg(
        "sendMessage",
        "direct_messages_topic_id",
        {"type": "integer", "format": "int32"},
        False,
        False,
    )
    configured_user_id = type_builder._build_field(
        "BotCommandScopeChatMember",
        "user_id",
        {"type": "integer", "format": "int32"},
        True,
    )
    shared_user_id = type_builder._build_field(
        "SharedUser",
        "user_id",
        {"type": "integer", "format": "int32"},
        True,
    )
    message_id = type_builder._build_field(
        "Message",
        "message_id",
        {"type": "integer", "format": "int32"},
        True,
    )

    assert user_id.cpp_type == "std::int64_t"
    assert limit.cpp_type == "std::int32_t"
    assert chat_id.cpp_type == "std::variant<std::int64_t, std::string>"
    assert direct_messages_topic_id.cpp_type == "std::int64_t"
    assert configured_user_id.cpp_type == "std::int64_t"
    assert shared_user_id.cpp_type == "std::int64_t"
    assert message_id.cpp_type == "std::int32_t"


def test_type_resolver_handles_json_fallback_and_later_all_of_reference() -> None:
    assert _CppTypeResolver.type({}) == "nlohmann::json"
    assert (
        _CppTypeResolver.ref_name(
            {
                "allOf": [
                    {"type": "object"},
                    {"$ref": "#/components/schemas/Message"},
                ]
            }
        )
        == "Message"
    )


def test_high_risk_methods_keep_legacy_args_order() -> None:
    builder = _MethodModelBuilder({})
    properties = {
        "chat_id": {},
        "user_id": {},
        "can_change_info": {},
        "can_post_messages": {},
        "can_edit_messages": {},
        "can_delete_messages": {},
        "can_manage_chat": {},
        "can_manage_tags": {},
    }

    assert builder._ordered_arg_names("promoteChatMember", properties, {"chat_id", "user_id"}) == [
        "chat_id",
        "user_id",
        "can_change_info",
        "can_post_messages",
        "can_edit_messages",
        "can_delete_messages",
        "can_manage_chat",
        "can_manage_tags",
    ]


def test_field_constant_recognizes_only_fixed_discriminators() -> None:
    constant = _TypeModelBuilder._field_constant(
        "status",
        {
            "type": "string",
            "description": "The member's status in the chat, always “creator”",
        },
        True,
    )

    assert constant is not None
    assert constant.name == "STATUS"
    assert constant.value == "creator"
    assert (
        _TypeModelBuilder._field_constant(
            "type",
            {
                "type": "string",
                "description": "Type of the chat, can be either private or group",
            },
            True,
        )
        is None
    )


def test_field_constant_uses_single_enum_value() -> None:
    constant = _TypeModelBuilder._field_constant(
        "type",
        {
            "type": "string",
            "enum": ["audio"],
        },
        True,
    )

    assert constant is not None
    assert constant.name == "TYPE"
    assert constant.value == "audio"


def test_union_header_includes_variant() -> None:
    assert "variant" in _TypeModelBuilder._standard_headers((), ("Message",))


def test_generator_renders_types_methods_and_documentation(
    tmp_path: Path,
) -> None:
    schema_path = tmp_path / "schema.yaml"
    schema_path.write_text(yaml.safe_dump(_schema()), encoding="utf-8")
    source_dir = tmp_path / "src"
    source_dir.mkdir()
    source_dir.joinpath("Api.cpp").write_text("", encoding="utf-8")

    generated = _OpenApiGenerator(schema_path, tmp_path).generate()

    types = tmp_path.joinpath("include/tgbot/Types.h").read_text(encoding="utf-8")
    types_source = tmp_path.joinpath("src/Types.cpp").read_text(encoding="utf-8")
    api_source = tmp_path.joinpath("src/ApiMethods.cpp").read_text(encoding="utf-8")
    methods = tmp_path.joinpath("include/tgbot/ApiMethods.inc.h").read_text(encoding="utf-8")
    normalized_methods = " ".join(methods.split())
    assert generated.types == 2
    assert generated.methods == 2
    assert types.startswith("// Generated by `make api-generate`. Do not edit.\n\n#pragma once")
    assert "struct User;" in types
    assert "struct InlineQueryResultCachedAudio;" in types
    assert "struct User {" in types
    assert "This object represents a Telegram user." in types
    assert "Unique identifier for this user." in types
    assert "@brief This object represents a Telegram user." in types
    assert "@brief Unique identifier for this user." in types
    assert "@ingroup api" in types
    assert "static TGBOT_API const std::string TYPE;" in types
    assert "TGBOT_API void from_json" in types
    assert "TGBOT_API void to_json" in types
    assert "std::string type { TYPE };" in types
    assert "std::string id" in types
    assert 'const std::string InlineQueryResultCachedAudio::TYPE = "audio";' in types_source
    assert '#include "tgbot/Json.h"' in types_source
    assert '#include "tgbot/Types.h"' in types_source
    assert 'Json::readRequiredField(json, "id", value.id);' in types_source
    assert not tmp_path.joinpath("include/tgbot/types").exists()
    assert not tmp_path.joinpath("src/types").exists()
    assert "@brief Returns information about the bot." in normalized_methods
    assert "std::shared_ptr<User> getMe( ) const;" in normalized_methods
    assert "Returns information about the bot." in methods
    assert "@param url HTTPS URL for incoming updates." in methods
    assert '#include "tgbot/ApiCodec.h"' in api_source
    assert "ApiRequest::makeFields(" in api_source
    assert "ApiResponse::decode<std::shared_ptr<User>>" in api_source
    assert "std::shared_ptr<InputFile> certificate = nullptr" in methods
    assert "std::string_view url" in methods
    assert "std::int32_t maxConnections = 40" in methods
    assert 'ApiRequest::required("url", url)' in api_source
    assert 'ApiRequest::optional("certificate", certificate)' in api_source
    assert 'ApiRequest::optional("allowed_updates", allowedUpdates)' in api_source
    assert "struct SetWebhookArgs" in types
    assert "std::string url { };" in types
    assert "std::int32_t maxConnections = 40;" in types
    assert "std::shared_ptr<InputFile> certificate = nullptr;" in types
    assert "setWebhook( const SetWebhookArgs& args ) const;" in normalized_methods
    assert methods.count("@brief Specify a URL and receive incoming updates.") == 2
    assert "@return True on success." in methods
    assert "@return The resulting User object." in methods
    assert "return setWebhook(" in api_source
    assert "args.url" in api_source
    assert "args.certificate" in api_source
    assert "args.maxConnections" in api_source
    assert "args.allowedUpdates" in api_source

    generated_again = _OpenApiGenerator(schema_path, tmp_path).generate()

    assert generated_again == generated
    assert tmp_path.joinpath("include/tgbot/Types.h").read_text(encoding="utf-8") == types
    assert tmp_path.joinpath("src/Types.cpp").read_text(encoding="utf-8") == types_source
    assert tmp_path.joinpath("src/ApiMethods.cpp").read_text(encoding="utf-8") == api_source


@pytest.mark.parametrize(
    "method_name",
    [name for name, config in API_CONFIG.items() if config.get("supports_attach_references")],
)
def test_generator_renders_optional_attach_reference_argument(method_name: str) -> None:
    document = yaml.safe_load((Path(__file__).parents[2] / "api/telegram-bot-api.yaml").read_text(encoding="utf-8"))
    methods = _MethodModelBuilder(document["paths"]).build()
    method = next(method for method in methods if method.name == method_name)

    attachment = next(arg for arg in method.args if arg.wire_name == "attachments")
    assert attachment.cpp_type == "std::vector<InputFileAttachment>"
    assert attachment.default_value == "{ }"
    assert method.args[-1] == attachment
    assert method.compatibility_args == method.args


def test_generator_rejects_method_without_result_schema(tmp_path: Path) -> None:
    schema = _schema()
    response_parts = schema["paths"]["/getMe"]["post"]["responses"]["200"]["content"]["application/json"]["schema"][
        "allOf"
    ]
    response_parts[1]["properties"].clear()
    schema_path = tmp_path / "schema.yaml"
    schema_path.write_text(yaml.safe_dump(schema), encoding="utf-8")

    with pytest.raises(ValueError, match="Response type is missing for getMe"):
        _OpenApiGenerator(schema_path, tmp_path).generate()


def test_json_argument_defaults_and_unsupported_return_type() -> None:
    builder = _MethodModelBuilder({})

    assert builder._arg_default("nlohmann::json", "method", "argument") == "nullptr"
    assert builder._arg_declaration_type("nlohmann::json") == "const nlohmann::json&"
    with pytest.raises(ValueError, match="Unsupported API return type: double"):
        builder._return_description("double", "double")


def test_every_method_with_args_generates_ordered_argument_object_delegation(tmp_path: Path) -> None:
    schema_path = Path(__file__).parents[2] / "api" / "telegram-bot-api.yaml"
    document = yaml.safe_load(schema_path.read_text(encoding="utf-8"))
    methods = _MethodModelBuilder(document["paths"]).build()

    _OpenApiGenerator(schema_path, tmp_path).generate()

    types = tmp_path.joinpath("include/tgbot/Types.h").read_text(encoding="utf-8")
    declarations = tmp_path.joinpath("include/tgbot/ApiMethods.inc.h").read_text(encoding="utf-8")
    normalized_declarations = " ".join(declarations.split())
    definitions = tmp_path.joinpath("src/ApiMethods.cpp").read_text(encoding="utf-8")

    for method in methods:
        if not method.args:
            assert method.args_name is None
            continue

        expected_args_name = f"{method.name[0].upper()}{method.name[1:]}Args"
        assert method.args_name == expected_args_name
        assert f"struct {expected_args_name} {{" in types
        assert f"{method.name}( const {expected_args_name}& args ) const;" in normalized_declarations

        classic_start = definitions.index(f"Api::{method.name}(")
        classic_end = definitions.index("\n}", classic_start)
        classic_body = definitions[classic_start:classic_end]
        normalized_classic_body = " ".join(classic_body.split())
        assert f'sendRequest( "{method.name}", ApiRequest::makeFields(' in normalized_classic_body
        for arg in method.args:
            field_factory = "required" if arg.required or arg.always_send else "optional"
            assert f'ApiRequest::{field_factory}("{arg.wire_name}", {arg.cpp_name}' in classic_body

        args_signature = re.search(
            rf"Api::{method.name}\(\s*const {expected_args_name}& args\s*\) const \{{",
            definitions,
        )
        assert args_signature is not None
        args_start = args_signature.start()
        args_end = definitions.index("\n}", args_start)
        args_body = definitions[args_start:args_end]
        assert f"return {method.name}(" in args_body
        positions = [args_body.index(f"args.{arg.cpp_name}") for arg in method.args]
        assert positions == sorted(positions)


def _schema() -> dict:
    return {
        "openapi": "3.0.0",
        "components": {
            "schemas": {
                "OkResponse": {"type": "object"},
                "InlineQueryResultCachedAudio": {
                    "type": "object",
                    "x-tags": ["Available types"],
                    "description": "Represents a cached audio result.",
                    "properties": {
                        "type": {
                            "type": "string",
                            "description": "Type of the result, must be audio",
                        },
                        "id": {"type": "string"},
                        "user": {"$ref": "#/components/schemas/User"},
                    },
                    "required": ["type", "id"],
                },
                "User": {
                    "type": "object",
                    "x-tags": ["Available types"],
                    "description": "This object represents a Telegram user.",
                    "properties": {
                        "id": {
                            "type": "integer",
                            "format": "int64",
                            "description": "Unique identifier for this user.",
                        }
                    },
                    "required": ["id"],
                },
            }
        },
        "paths": {
            "/getMe": {
                "post": {
                    "operationId": "getMe",
                    "description": "Returns information about the bot.",
                    "responses": {
                        "200": {
                            "content": {
                                "application/json": {
                                    "schema": {
                                        "allOf": [
                                            {"$ref": "#/components/schemas/OkResponse"},
                                            {
                                                "type": "object",
                                                "properties": {"result": {"$ref": "#/components/schemas/User"}},
                                            },
                                        ]
                                    }
                                }
                            }
                        }
                    },
                }
            },
            "/setWebhook": {
                "post": {
                    "operationId": "setWebhook",
                    "description": "Specify a URL and receive incoming updates.",
                    "requestBody": {
                        "content": {
                            "application/json": {
                                "schema": {
                                    "type": "object",
                                    "properties": {
                                        "url": {
                                            "type": "string",
                                            "description": "HTTPS URL for incoming updates.",
                                        },
                                        "max_connections": {"type": "integer"},
                                        "allowed_updates": {
                                            "type": "array",
                                            "items": {"type": "string"},
                                        },
                                    },
                                    "required": ["url"],
                                }
                            },
                            "multipart/form-data": {
                                "schema": {
                                    "type": "object",
                                    "properties": {
                                        "certificate": {
                                            "type": "string",
                                            "format": "binary",
                                        }
                                    },
                                }
                            },
                        }
                    },
                    "responses": {
                        "200": {
                            "content": {
                                "application/json": {
                                    "schema": {
                                        "allOf": [
                                            {"$ref": "#/components/schemas/OkResponse"},
                                            {
                                                "type": "object",
                                                "properties": {"result": {"type": "boolean"}},
                                            },
                                        ]
                                    }
                                }
                            }
                        }
                    },
                }
            },
        },
    }
