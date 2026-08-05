from pathlib import Path

import pytest
import yaml

from api_codegen.generate import (
    API_CONFIG,
    TYPE_CONFIG,
    _build_field,
    _build_parameter,
    _cpp_type,
    _field_constant,
    _object_standard_headers,
    _ordered_parameter_names,
    _parameter_default,
    _snake_to_camel,
    generate_openapi,
)


def test_snake_to_camel_converts_telegram_names() -> None:
    assert _snake_to_camel("id") == "id"
    assert _snake_to_camel("file_unique_id") == "fileUniqueId"


def test_direct_api_keeps_legacy_parameter_order_and_defaults() -> None:
    properties = {
        "audio": {},
        "business_connection_id": {},
        "caption": {},
        "chat_id": {},
        "duration": {},
    }

    assert _ordered_parameter_names("sendAudio", properties, {"audio", "chat_id"}) == [
        "chat_id",
        "audio",
        "caption",
        "duration",
        "business_connection_id",
    ]
    assert _parameter_default("std::int32_t", "setWebhook", "max_connections") == "40"
    assert (
        _parameter_default("InputFile::Ptr", "setWebhook", "certificate") == "nullptr"
    )


def test_compatibility_config_is_grouped_by_telegram_entity() -> None:
    assert API_CONFIG["setStickerSetTitle"]["parameter_order"] == ["name", "title"]
    assert API_CONFIG["editMessageText"]["return_type"] == "std::shared_ptr<Message>"
    assert API_CONFIG["getUpdates"]["parameters"]["limit"]["default"] == 100
    assert (
        TYPE_CONFIG["BotCommandScopeChatMember"]["fields"]["user_id"]["type"]
        == "std::int64_t"
    )
    assert TYPE_CONFIG["Chat"]["fields"]["type"]["enum"]["Private"] == "private"


def test_integer_widths_follow_schema_and_telegram_id_rules() -> None:
    assert _cpp_type({"type": "integer", "format": "int64"}) == "std::int64_t"
    assert _cpp_type({"type": "integer", "format": "int32"}) == "std::int32_t"
    assert _cpp_type({"type": "integer"}) == "std::int32_t"

    user_id = _build_parameter(
        "giftPremiumSubscription",
        "receiver_user_id",
        {"type": "integer", "format": "int32"},
        True,
        False,
    )
    limit = _build_parameter(
        "getUpdates",
        "limit",
        {"type": "integer", "format": "int32"},
        False,
        False,
    )
    chat_id = _build_parameter(
        "sendMessage",
        "chat_id",
        {"type": "integer", "format": "int64"},
        True,
        False,
    )
    direct_messages_topic_id = _build_parameter(
        "sendMessage",
        "direct_messages_topic_id",
        {"type": "integer", "format": "int32"},
        False,
        False,
    )
    configured_user_id = _build_field(
        "BotCommandScopeChatMember",
        "user_id",
        {"type": "integer", "format": "int32"},
        True,
    )
    shared_user_id = _build_field(
        "SharedUser",
        "user_id",
        {"type": "integer", "format": "int32"},
        True,
    )
    message_id = _build_field(
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


def test_high_risk_methods_keep_legacy_parameter_order() -> None:
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

    assert _ordered_parameter_names(
        "promoteChatMember", properties, {"chat_id", "user_id"}
    ) == [
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
    constant = _field_constant(
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
        _field_constant(
            "type",
            {
                "type": "string",
                "description": "Type of the chat, can be either private or group",
            },
            True,
        )
        is None
    )


def test_union_header_includes_variant() -> None:
    assert "variant" in _object_standard_headers((), ("Message",))


def test_generate_openapi_renders_types_methods_and_documentation(
    tmp_path: Path,
) -> None:
    schema_path = tmp_path / "schema.yaml"
    schema_path.write_text(yaml.safe_dump(_schema()), encoding="utf-8")
    source_dir = tmp_path / "src"
    source_dir.mkdir()
    source_dir.joinpath("Api.cpp").write_text("", encoding="utf-8")

    generated = generate_openapi(schema_path, tmp_path)

    types = tmp_path.joinpath("include/tgbot/types/types.h").read_text()
    user = tmp_path.joinpath("include/tgbot/types/User.h").read_text()
    cached_audio = tmp_path.joinpath(
        "include/tgbot/types/InlineQueryResultCachedAudio.h"
    ).read_text()
    user_source = tmp_path.joinpath("src/types/User.cpp").read_text()
    cached_audio_source = tmp_path.joinpath(
        "src/types/InlineQueryResultCachedAudio.cpp"
    ).read_text()
    api_source = tmp_path.joinpath("src/ApiMethods.cpp").read_text()
    methods = tmp_path.joinpath("include/tgbot/ApiMethods.inc.h").read_text()
    assert generated.objects == 2
    assert generated.methods == 2
    assert user.startswith(
        "// Generated by `make api-generate`. Do not edit.\n\n#pragma once"
    )
    assert '#include "tgbot/types/User.h"' in types
    assert "struct User" not in types
    assert "struct User" in user
    assert "This object represents a Telegram user." in user
    assert "Unique identifier for this user." in user
    assert "@brief This object represents a Telegram user." in user
    assert "@brief Unique identifier for this user." in user
    assert "static TGBOT_API const std::string TYPE;" in cached_audio
    assert "TGBOT_API void from_json" in cached_audio
    assert "TGBOT_API void to_json" in cached_audio
    assert "std::string type { TYPE };" in cached_audio
    assert "std::string id { };\n\n    /**" in cached_audio
    assert (
        'const std::string InlineQueryResultCachedAudio::TYPE = "audio";'
        in cached_audio_source
    )
    assert '#include "tgbot/Json.h"' in user_source
    assert '#include "tgbot/types/User.h"' in cached_audio_source
    assert 'Json::readRequiredField(json, "id", value.id);' in user_source
    assert not tmp_path.joinpath("src/Types.cpp").exists()
    assert "\n    /**\n     * @brief Returns information about the bot.\n" in methods
    assert "\n    std::shared_ptr<User> getMe() const" in methods
    assert "Returns information about the bot." in methods
    assert '#include "tgbot/ApiCodec.h"' in api_source
    assert "ApiRequest::makeFields(" in api_source
    assert "ApiResponse::decode<std::shared_ptr<User>>" in api_source
    assert "HttpReqArg" not in api_source
    assert "InputFile::Ptr certificate = nullptr" in methods
    assert "std::int32_t maxConnections = 40" in methods
    assert 'ApiRequest::required("url", url)' in api_source
    assert 'ApiRequest::optional("certificate", certificate)' in api_source
    assert 'ApiRequest::optional("allowed_updates", allowedUpdates)' in api_source

    generated_again = generate_openapi(schema_path, tmp_path)

    assert generated_again == generated
    assert tmp_path.joinpath("include/tgbot/types/User.h").read_text() == user
    assert tmp_path.joinpath("src/ApiMethods.cpp").read_text() == api_source


def test_generate_openapi_removes_only_stale_generated_type_files(
    tmp_path: Path,
) -> None:
    schema_path = tmp_path / "schema.yaml"
    schema_path.write_text(yaml.safe_dump(_schema()), encoding="utf-8")
    types_dir = tmp_path / "include" / "tgbot" / "types"
    types_dir.mkdir(parents=True)
    stale = types_dir / "OldType.h"
    stale.write_text(
        "// Generated by `make api-generate`. Do not edit.\n", encoding="utf-8"
    )
    manual = types_dir / "InputFile.h"
    manual.write_text("// Hand-written.\n", encoding="utf-8")
    type_sources_dir = tmp_path / "src" / "types"
    type_sources_dir.mkdir(parents=True)
    stale_source = type_sources_dir / "OldType.cpp"
    stale_source.write_text(
        "// Generated by `make api-generate`. Do not edit.\n", encoding="utf-8"
    )
    manual_source = type_sources_dir / "InputFile.cpp"
    manual_source.write_text("// Hand-written.\n", encoding="utf-8")

    generate_openapi(schema_path, tmp_path)

    assert not stale.exists()
    assert manual.read_text(encoding="utf-8") == "// Hand-written.\n"
    assert not stale_source.exists()
    assert manual_source.read_text(encoding="utf-8") == "// Hand-written.\n"


def test_generate_openapi_rejects_method_without_result_schema(tmp_path: Path) -> None:
    schema = _schema()
    response_parts = schema["paths"]["/getMe"]["post"]["responses"]["200"]["content"][
        "application/json"
    ]["schema"]["allOf"]
    response_parts[1]["properties"].clear()
    schema_path = tmp_path / "schema.yaml"
    schema_path.write_text(yaml.safe_dump(schema), encoding="utf-8")

    with pytest.raises(ValueError, match="Response type is missing for getMe"):
        generate_openapi(schema_path, tmp_path)


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
                                                "properties": {
                                                    "result": {
                                                        "$ref": "#/components/schemas/User"
                                                    }
                                                },
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
                                        "url": {"type": "string"},
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
                                                "properties": {
                                                    "result": {"type": "boolean"}
                                                },
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
