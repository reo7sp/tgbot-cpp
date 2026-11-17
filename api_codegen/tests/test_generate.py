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
        "editEphemeralMessageMedia",
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
    scope_user_id = type_builder._build_field(
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

    assert user_id.cpp_type == "std::uint64_t"
    assert limit.cpp_type == "std::uint32_t"
    assert chat_id.cpp_type == "std::variant<std::int64_t, std::string>"
    assert direct_messages_topic_id.cpp_type == "std::uint64_t"
    assert scope_user_id.cpp_type == "std::uint64_t"
    assert shared_user_id.cpp_type == "std::uint64_t"
    assert message_id.cpp_type == "std::uint32_t"


@pytest.mark.parametrize(
    ("owner", "name", "expected"),
    [
        ("User", "id", "std::uint64_t"),
        ("Chat", "id", "std::int64_t"),
        ("Community", "id", "std::uint64_t"),
        ("DirectMessagesTopic", "topic_id", "std::uint64_t"),
        ("Story", "id", "std::uint32_t"),
        ("InputChecklistTask", "id", "std::uint32_t"),
        ("Update", "update_id", "std::uint32_t"),
        ("Message", "ephemeral_message_id", "std::uint32_t"),
        ("Message", "reply_to_checklist_task_id", "std::uint32_t"),
        ("ChatFullInfo", "accent_color_id", "std::uint32_t"),
        ("ChatFullInfo", "profile_accent_color_id", "std::uint32_t"),
        ("KeyboardButtonRequestUsers", "request_id", "std::int32_t"),
        ("MessageGenerationStopped", "draft_id", "std::int64_t"),
        ("Message", "migrate_to_chat_id", "std::int64_t"),
        ("BusinessConnection", "user_chat_id", "std::uint64_t"),
        ("ChatJoinRequest", "user_chat_id", "std::uint64_t"),
        ("ChatShared", "chat_id", "std::int64_t"),
        ("BotCommandScopeChat", "chat_id", "std::variant<std::int64_t, std::string>"),
        ("BotCommandScopeChatAdministrators", "chat_id", "std::variant<std::int64_t, std::string>"),
        ("BotCommandScopeChatMember", "chat_id", "std::variant<std::int64_t, std::string>"),
        ("ReplyParameters", "chat_id", "std::variant<std::int64_t, std::string>"),
    ],
)
def test_id_signedness_depends_on_semantics(owner: str, name: str, expected: str) -> None:
    schema = {"type": "integer"}
    if owner in {"User", "Chat", "Community", "DirectMessagesTopic"}:
        schema["format"] = "int64"
    assert _CppTypeResolver.field_type(name, schema, True, owner) == expected
    assert _CppTypeResolver.field_type(name, schema, False, owner) == f"std::optional<{expected}>"


@pytest.mark.parametrize(
    ("name", "expected"),
    [
        ("added_user_ids", "std::uint64_t"),
        ("message_ids", "std::uint32_t"),
        ("correct_option_ids", "std::uint32_t"),
        ("option_ids", "std::uint32_t"),
        ("marked_as_done_task_ids", "std::uint32_t"),
    ],
)
def test_id_arrays_use_the_same_type_as_scalar_ids(name: str, expected: str) -> None:
    schema = {"type": "array", "items": {"type": "integer"}}
    assert _CppTypeResolver.field_type(name, schema, True) == f"std::vector<{expected}>"
    arg = _MethodModelBuilder({})._build_arg("method", name, schema, True, False)
    assert arg.cpp_type == f"std::vector<{expected}>"


def test_string_identifiers_and_signed_offsets_keep_their_types() -> None:
    assert _CppTypeResolver.field_type("id", {"type": "string"}, True, "Poll") == "std::string"
    assert _CppTypeResolver.api_type({"type": "string"}, "callback_query_id") == "std::string"
    assert _CppTypeResolver.api_type({"type": "integer"}, "offset") == "std::int32_t"


@pytest.mark.parametrize(
    ("owner", "name", "expected"),
    [
        ("MessageEntity", "offset", "std::uint32_t"),
        ("getUpdates", "offset", "std::int32_t"),
        ("getUpdates", "limit", "std::uint32_t"),
        ("getUpdates", "timeout", "std::uint32_t"),
        ("getStarTransactions", "offset", "std::uint32_t"),
        ("getUserProfilePhotos", "offset", "std::uint32_t"),
        ("getUserProfileAudios", "offset", "std::uint32_t"),
        ("StarTransaction", "amount", "std::uint64_t"),
        ("StarTransaction", "nanostar_amount", "std::uint32_t"),
        ("StarAmount", "amount", "std::int64_t"),
        ("StarAmount", "nanostar_amount", "std::int32_t"),
        ("AffiliateInfo", "amount", "std::int64_t"),
        ("AffiliateInfo", "nanostar_amount", "std::int32_t"),
        ("LabeledPrice", "amount", "std::int64_t"),
        ("SuggestedPostPrice", "amount", "std::uint64_t"),
        ("SuggestedPostPaid", "amount", "std::uint64_t"),
        ("UniqueGiftInfo", "last_resale_amount", "std::uint64_t"),
        ("SuccessfulPayment", "total_amount", "std::uint64_t"),
        ("sendInvoice", "max_tip_amount", "std::uint64_t"),
        ("Video", "duration", "std::uint32_t"),
        ("InputMediaVideo", "height", "std::uint32_t"),
        ("StoryAreaTypeWeather", "background_color", "std::uint32_t"),
        ("GiveawayWinners", "winner_count", "std::uint32_t"),
        ("Dice", "value", "std::uint32_t"),
        ("InputRichBlockListItem", "value", "std::int32_t"),
        ("RichBlockListItem", "value", "std::int32_t"),
        ("UserRating", "level", "std::int32_t"),
        ("UserRating", "rating", "std::int32_t"),
        ("UserRating", "current_level_rating", "std::int32_t"),
        ("UserRating", "next_level_rating", "std::int32_t"),
        ("Message", "date", "std::uint32_t"),
        ("InaccessibleMessage", "date", "std::uint32_t"),
        ("RichTextDateTime", "unix_time", "std::int32_t"),
        ("banChatMember", "until_date", "std::int32_t"),
        ("getChatMemberCount", "result", "std::uint32_t"),
    ],
)
def test_integer_domains_follow_documented_context(owner: str, name: str, expected: str) -> None:
    schema = {"type": "integer"}
    if owner[0].isupper():
        assert _CppTypeResolver.field_type(name, schema, True, owner) == expected
        assert _CppTypeResolver.field_type(name, schema, False, owner) == f"std::optional<{expected}>"
    elif name == "result":
        assert _CppTypeResolver.api_type(schema, name, owner) == expected
    else:
        arg = _MethodModelBuilder({})._build_arg(owner, name, schema, False, False)
        assert arg.cpp_type == expected


def test_unsigned_sizes_and_arrays_preserve_their_widths() -> None:
    assert (
        _CppTypeResolver.field_type("file_size", {"type": "integer", "format": "int64"}, True, "File")
        == "std::uint64_t"
    )
    schema = {"type": "array", "items": {"type": "integer"}}
    assert (
        _CppTypeResolver.field_type("colors", schema, True, "BackgroundFillFreeformGradient")
        == "std::vector<std::uint32_t>"
    )
    arg = _MethodModelBuilder({})._build_arg("sendInvoice", "suggested_tip_amounts", schema, False, False)
    assert arg.cpp_type == "std::vector<std::uint64_t>"
    assert (
        _CppTypeResolver.field_type("suggested_tip_amounts", schema, False, "InputInvoiceMessageContent")
        == "std::optional<std::vector<std::uint64_t>>"
    )


@pytest.mark.parametrize(
    "method_name", ["getChatMenuButton", "setChatMenuButton", "sendMessageDraft", "sendRichMessageDraft"]
)
def test_private_chat_method_arguments_use_unsigned_ids(method_name: str) -> None:
    arg = _MethodModelBuilder({})._build_arg(
        method_name, "chat_id", {"type": "integer", "format": "int64"}, False, False
    )
    assert arg.cpp_type == "std::variant<std::uint64_t, std::string>"
    assert arg.default_value == "{ }"


@pytest.mark.parametrize("method_name", ["sendMessageDraft", "sendRichMessageDraft"])
def test_draft_method_arguments_use_signed_64_bit_ids(method_name: str) -> None:
    arg = _MethodModelBuilder({})._build_arg(method_name, "draft_id", {"type": "integer"}, True, False)
    assert arg.cpp_type == "std::int64_t"


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


def test_bot_api_10_3_keeps_legacy_ephemeral_arguments() -> None:
    schema_path = Path(__file__).parents[2] / "api" / "telegram-bot-api.yaml"
    document = yaml.safe_load(schema_path.read_text(encoding="utf-8"))
    methods = {method.name: method for method in _MethodModelBuilder(document["paths"]).build()}
    legacy_methods = {
        "sendAnimation",
        "sendAudio",
        "sendContact",
        "sendDocument",
        "sendLivePhoto",
        "sendLocation",
        "sendMessage",
        "sendPhoto",
        "sendSticker",
        "sendVenue",
        "sendVideo",
        "sendVideoNote",
        "sendVoice",
    }

    assert {name for name, config in API_CONFIG.items() if config.get("legacy_ephemeral_parameters")} == legacy_methods
    for name in legacy_methods:
        method = methods[name]
        direct_names = [arg.wire_name for arg in method.direct_args]
        struct_names = [arg.wire_name for arg in method.struct_args]
        wire_names = [arg.wire_name for arg in method.args]
        assert direct_names == API_CONFIG[name]["args_order"]
        assert struct_names == [*direct_names, "ephemeral_message_parameters"]
        assert "callback_query_id" in direct_names
        assert "receiver_user_id" in direct_names
        assert "ephemeral_message_parameters" not in direct_names
        assert "callback_query_id" not in wire_names
        assert "receiver_user_id" not in wire_names
        assert "ephemeral_message_parameters" in wire_names
        assert method.direct_args[0].wire_name == "chat_id"
        assert method.direct_args[0].default_value is None
        chat_arg = next(arg for arg in method.args if arg.wire_name == "chat_id")
        assert not chat_arg.required


def test_bot_api_10_3_appends_new_direct_arguments() -> None:
    schema_path = Path(__file__).parents[2] / "api" / "telegram-bot-api.yaml"
    document = yaml.safe_load(schema_path.read_text(encoding="utf-8"))
    methods = {method.name: method for method in _MethodModelBuilder(document["paths"]).build()}
    legacy_prefixes = {
        "editEphemeralMessageText": [
            "chat_id",
            "ephemeral_message_id",
            "receiver_user_id",
            "text",
            "entities",
            "link_preview_options",
            "parse_mode",
            "reply_markup",
        ],
        "sendMessageDraft": ["chat_id", "draft_id", "entities", "message_thread_id", "parse_mode", "text"],
        "sendRichMessageDraft": ["chat_id", "draft_id", "rich_message", "message_thread_id"],
    }

    for name, legacy_prefix in legacy_prefixes.items():
        direct_names = [arg.wire_name for arg in methods[name].direct_args]
        assert direct_names[: len(legacy_prefix)] == legacy_prefix

    assert [arg.wire_name for arg in methods["sendRichMessage"].direct_args] == [
        "chat_id",
        "rich_message",
        "allow_paid_broadcast",
        "business_connection_id",
        "direct_messages_topic_id",
        "disable_notification",
        "message_effect_id",
        "message_thread_id",
        "protect_content",
        "reply_markup",
        "reply_parameters",
        "suggested_post_parameters",
        "attachments",
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


def test_rich_text_union_appends_plain_text_and_recursive_array() -> None:
    components = {
        "RichText": {"description": "String or Array of RichText, or:\nRichTextBold\nRichTextItalic"},
        "RichTextBold": {},
        "RichTextItalic": {},
    }
    rich_text = next(model for model in _TypeModelBuilder(components).build() if model.name == "RichText")

    assert rich_text.union_members == (
        "std::shared_ptr<RichTextBold>",
        "std::shared_ptr<RichTextItalic>",
        "std::string",
        "std::vector<std::shared_ptr<RichText>>",
    )
    assert rich_text.dependencies == ("RichTextBold", "RichTextItalic")
    assert {"string", "vector", "variant"} <= set(rich_text.standard_headers)
    header = _OpenApiGenerator._render("types.h.j2", types=(rich_text,), methods=())
    assert "std::vector<std::shared_ptr<RichText>>" in header
    assert "std::shared_ptr<std::string>" not in header


def test_generator_renders_types_methods_and_documentation(
    tmp_path: Path,
) -> None:
    schema_path = tmp_path / "schema.yaml"
    schema_path.write_text(yaml.safe_dump(_schema()), encoding="utf-8")
    source_dir = tmp_path / "src"
    source_dir.mkdir()
    source_dir.joinpath("Api.cpp").write_text("", encoding="utf-8")

    config = {
        "api": {
            "setWebhook": {
                "args_order": ["url", "certificate", "max_connections", "allowed_updates"],
                "args": {"max_connections": {"default": 40}},
            }
        }
    }
    generated = _OpenApiGenerator(schema_path, tmp_path, config).generate()

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
    assert "std::uint32_t maxConnections = 40" in methods
    assert 'ApiRequest::required("url", url)' in api_source
    assert 'ApiRequest::optional("certificate", certificate)' in api_source
    assert 'ApiRequest::optional("allowed_updates", allowedUpdates)' in api_source
    assert "struct SetWebhookArgs" in types
    assert "std::string url { };" in types
    assert "std::uint32_t maxConnections = 40;" in types
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

    generated_again = _OpenApiGenerator(schema_path, tmp_path, config).generate()

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
    assert method.compatibility_args == method.direct_args


@pytest.mark.parametrize(
    ("config", "error"),
    [
        ({"typo": {}}, "Unknown entries in codegen: typo"),
        ({"types": {"Missing": {}}}, "Unknown entries in types: Missing"),
        ({"types": {"User": {"field": {}}}}, "Unknown entries in types.User: field"),
        (
            {"types": {"User": {"fields": {"missing": {"type": "std::int64_t"}}}}},
            "Unknown entries in types.User.fields: missing",
        ),
        (
            {"types": {"User": {"fields": {"id": {"typo": True}}}}},
            "Unknown entries in types.User.fields.id: typo",
        ),
        (
            {"types": {"User": {"append_union_types": ["std::shared_ptr<Missing>"]}}},
            "Unknown entries in types.User.append_union_types: std::shared_ptr<Missing>",
        ),
        ({"api": {"missingMethod": {}}}, "Unknown entries in api: missingMethod"),
        ({"api": {"setWebhook": {"arg_order": ["url"]}}}, "Unknown entries in api.setWebhook: arg_order"),
        (
            {"api": {"setWebhook": {"args_order": ["url", "removed_argument"]}}},
            "Unknown entries in api.setWebhook.args_order: removed_argument",
        ),
        (
            {"api": {"setWebhook": {"args": {"missing": {"default": 1}}}}},
            "Unknown entries in api.setWebhook.args: missing",
        ),
        (
            {"api": {"setWebhook": {"args": {"url": {"typo": True}}}}},
            "Unknown entries in api.setWebhook.args.url: typo",
        ),
        (
            {"api": {"setWebhook": {"direct_exclude": ["missing"]}}},
            "Unknown entries in api.setWebhook.direct_exclude: missing",
        ),
        (
            {"api": {"setWebhook": {"compatibility_overload_without": ["missing"]}}},
            "Unknown entries in api.setWebhook.compatibility_overload_without: missing",
        ),
    ],
)
def test_invalid_config_preserves_generated_files(tmp_path: Path, config: dict, error: str) -> None:
    schema_path = tmp_path / "schema.yaml"
    schema_path.write_text(yaml.safe_dump(_schema()), encoding="utf-8")
    output = tmp_path / "include/tgbot/Types.h"
    output.parent.mkdir(parents=True)
    output.write_text("existing generated file\n", encoding="utf-8")

    with pytest.raises(ValueError, match=re.escape(error)):
        _OpenApiGenerator(schema_path, tmp_path, config).generate()

    assert output.read_text(encoding="utf-8") == "existing generated file\n"
    assert not tmp_path.joinpath("src").exists()


def test_config_accepts_multipart_and_synthetic_arguments(tmp_path: Path) -> None:
    schema_path = tmp_path / "schema.yaml"
    schema_path.write_text(yaml.safe_dump(_schema()), encoding="utf-8")
    config = {
        "api": {
            "setWebhook": {
                "supports_attach_references": True,
                "extra_args": {"extra": {"type": "string"}},
                "args_order": ["url", "certificate", "extra", "attachments"],
                "args": {"certificate": {"type": "std::shared_ptr<InputFile>"}},
                "direct_exclude": ["extra"],
            }
        }
    }

    _OpenApiGenerator(schema_path, tmp_path, config).generate()

    source = tmp_path.joinpath("src/ApiMethods.cpp").read_text(encoding="utf-8")
    assert 'ApiRequest::optional("certificate", args.certificate)' in source
    assert 'ApiRequest::optional("extra", args.extra)' in source
    assert 'ApiRequest::optional("attachments", args.attachments)' in source


def test_generator_rejects_method_without_result_schema(tmp_path: Path) -> None:
    schema = _schema()
    response_parts = schema["paths"]["/getMe"]["post"]["responses"]["200"]["content"]["application/json"]["schema"][
        "allOf"
    ]
    response_parts[1]["properties"].clear()
    schema_path = tmp_path / "schema.yaml"
    schema_path.write_text(yaml.safe_dump(schema), encoding="utf-8")

    with pytest.raises(ValueError, match="Response type is missing for getMe"):
        _OpenApiGenerator(schema_path, tmp_path, {}).generate()


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
        args_signature = re.search(
            rf"Api::{method.name}\(\s*const {expected_args_name}& args\s*\) const \{{",
            definitions,
        )
        assert args_signature is not None
        args_start = args_signature.start()
        args_end = definitions.index("\n}", args_start)
        args_body = definitions[args_start:args_end]
        if method.direct_args == method.args:
            request_body = classic_body
            assert f"return {method.name}(" in args_body
            positions = [args_body.index(f"args.{arg.cpp_name}") for arg in method.args]
            assert positions == sorted(positions)
        else:
            request_body = args_body
            assert f"return {method.name}(args);" in classic_body
            positions = [classic_body.index(f"args.{arg.cpp_name}") for arg in method.direct_args]
            assert positions == sorted(positions)

        normalized_request_body = " ".join(request_body.split())
        assert f'sendRequest( "{method.name}", ApiRequest::makeFields(' in normalized_request_body
        for arg in method.args:
            field_factory = "required" if arg.required or arg.always_send else "optional"
            assert f'ApiRequest::{field_factory}("{arg.wire_name}",' in request_body


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
