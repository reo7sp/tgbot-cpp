from __future__ import annotations

import re
import textwrap
from collections.abc import Iterable
from dataclasses import dataclass
from pathlib import Path
from typing import Any

import yaml
from jinja2 import Environment, FileSystemLoader, StrictUndefined

Schema = dict[str, Any]
TEMPLATE_DIR = Path(__file__).with_name("templates")
ROOT = Path(__file__).resolve().parents[1]
DEFAULT_CONFIG = ROOT / "api" / "codegen.yaml"
TEMPLATES = Environment(
    loader=FileSystemLoader(TEMPLATE_DIR),
    undefined=StrictUndefined,
    autoescape=False,
    keep_trailing_newline=True,
    trim_blocks=True,
    lstrip_blocks=True,
)
CONFIG = yaml.safe_load(DEFAULT_CONFIG.read_text(encoding="utf-8"))
TYPE_CONFIG = CONFIG.get("types", {})
API_CONFIG = CONFIG.get("api", {})
ATTACH_REFERENCES_DESCRIPTION = (
    "Files uploaded as named multipart parts. Reference each file from a composite "
    "Telegram API argument as attach://<name> and use the same name in InputFileAttachment."
)


def run(schema_path: Path, root: Path) -> None:
    generated = _OpenApiGenerator(schema_path, root).generate()
    print(f"Generated {generated.types} types and {generated.methods} API methods")


@dataclass(frozen=True)
class _GeneratedCount:
    types: int
    methods: int


@dataclass(frozen=True)
class _ConstantModel:
    name: str
    value: str


@dataclass(frozen=True)
class _FieldModel:
    wire_name: str
    cpp_name: str
    cpp_type: str
    required: bool
    description: tuple[str, ...]
    constant: _ConstantModel | None
    enum: _EnumModel | None
    accepts_integer_string: bool


@dataclass(frozen=True)
class _EnumValueModel:
    name: str
    value: str


@dataclass(frozen=True)
class _EnumModel:
    name: str
    values: tuple[_EnumValueModel, ...]


@dataclass(frozen=True)
class _TypeModel:
    name: str
    aliases: tuple[str, ...]
    description: tuple[str, ...]
    constants: tuple[_ConstantModel, ...]
    enums: tuple[_EnumModel, ...]
    fields: tuple[_FieldModel, ...]
    union_members: tuple[str, ...]
    dependencies: tuple[str, ...]
    standard_headers: tuple[str, ...]


@dataclass(frozen=True)
class _ArgModel:
    wire_name: str
    cpp_name: str
    cpp_type: str
    declaration_type: str
    required: bool
    always_send: bool
    default_value: str | None
    wire_default_value: str | None
    description: tuple[str, ...]


@dataclass(frozen=True)
class _MethodModel:
    name: str
    return_type: str
    response_type: str
    return_description: str
    description: tuple[str, ...]
    args: tuple[_ArgModel, ...]
    direct_args: tuple[_ArgModel, ...]
    struct_args: tuple[_ArgModel, ...]
    compatibility_args: tuple[_ArgModel, ...]
    legacy_ephemeral_parameters: bool
    args_name: str | None


class _OpenApiGenerator:
    def __init__(self, schema_path: Path, root: Path, config: Schema = CONFIG) -> None:
        self._schema_path = schema_path
        self._root = root
        self._config = config

    def generate(self) -> _GeneratedCount:
        document = yaml.safe_load(self._schema_path.read_text(encoding="utf-8"))
        components = {name: schema for name, schema in document["components"]["schemas"].items() if "x-tags" in schema}
        types = _TypeModelBuilder(components, self._config.get("types", {})).build()
        methods = _MethodModelBuilder(document["paths"], self._config.get("api", {})).build()
        self._validate_config(components, types, methods)

        for path, content in self._outputs(types, methods).items():
            self._write(path, content)

        return _GeneratedCount(len(types), len(methods))

    def _validate_config(
        self,
        components: dict[str, Schema],
        types: tuple[_TypeModel, ...],
        methods: tuple[_MethodModel, ...],
    ) -> None:
        self._validate_names("codegen", self._config, {"types", "api"})
        type_config = self._config.get("types", {})
        type_models = {model.name: model for model in types}
        self._validate_names("types", type_config, components)
        for name, config in type_config.items():
            path = f"types.{name}"
            self._validate_names(path, config, {"aliases", "fields", "extra_union_types", "append_union_types"})
            fields = config.get("fields", {})
            self._validate_names(f"{path}.fields", fields, components[name].get("properties", {}))
            for field_name, field_config in fields.items():
                self._validate_names(f"{path}.fields.{field_name}", field_config, {"type", "enum"})
            self._validate_names(
                f"{path}.append_union_types", config.get("append_union_types", ()), type_models[name].union_members
            )

        api_config = self._config.get("api", {})
        method_models = {model.name: model for model in methods}
        self._validate_names("api", api_config, method_models)
        for name, config in api_config.items():
            path = f"api.{name}"
            self._validate_names(
                path,
                config,
                {
                    "args_order",
                    "args",
                    "return_type",
                    "supports_attach_references",
                    "legacy_ephemeral_parameters",
                    "direct_exclude",
                    "extra_args",
                    "compatibility_overload_without",
                },
            )
            method = method_models[name]
            wire_names = {arg.wire_name for arg in method.args}
            direct_names = {arg.wire_name for arg in method.direct_args}
            # Legacy arguments and named attachments are also valid public arguments.
            for key in ("args_order", "args"):
                self._validate_names(f"{path}.{key}", config.get(key, ()), wire_names | direct_names)
            self._validate_names(f"{path}.direct_exclude", config.get("direct_exclude", ()), wire_names)
            self._validate_names(
                f"{path}.compatibility_overload_without", config.get("compatibility_overload_without", ()), direct_names
            )
            for arg_name, arg_config in config.get("args", {}).items():
                self._validate_names(
                    f"{path}.args.{arg_name}", arg_config, {"type", "default", "declaration_required", "always_send"}
                )

    @staticmethod
    def _validate_names(path: str, names: Iterable[str], allowed: Iterable[str]) -> None:
        unknown = set(names) - set(allowed)
        if unknown:
            raise ValueError(f"Unknown entries in {path}: {', '.join(sorted(unknown))}")

    def _outputs(
        self,
        types: tuple[_TypeModel, ...],
        methods: tuple[_MethodModel, ...],
    ) -> dict[Path, str]:
        return {
            self._root / "include" / "tgbot" / "Types.h": self._render("types.h.j2", types=types, methods=methods),
            self._root / "src" / "Types.cpp": self._render("types.cpp.j2", types=types),
            self._root / "include" / "tgbot" / "ApiMethods.inc.h": self._render(
                "api_methods.inc.h.j2", methods=methods
            ),
            self._root / "src" / "ApiMethods.cpp": self._render("api_methods.cpp.j2", methods=methods),
        }

    @staticmethod
    def _render(name: str, **context: Any) -> str:
        return TEMPLATES.get_template(name).render(**context)

    @staticmethod
    def _write(path: Path, content: str) -> None:
        path.parent.mkdir(parents=True, exist_ok=True)
        path.write_text(content, encoding="utf-8")


class _CppTypeResolver:
    @classmethod
    def api_type(cls, schema: Schema, name: str = "", owner: str = "") -> str:
        return cls.type(schema, name, owner)

    @classmethod
    def type(cls, schema: Schema, name: str = "", owner: str = "") -> str:
        if ref := cls.ref_name(schema):
            return f"std::shared_ptr<{ref}>"
        if choices := schema.get("oneOf"):
            return f"std::variant<{', '.join(cls.type(item, name, owner) for item in choices)}>"
        schema_type = schema.get("type")
        if schema_type == "array":
            item_name = name[:-1] if name.endswith("_ids") else name
            return f"std::vector<{cls.type(schema['items'], item_name, owner)}>"
        if schema_type == "boolean":
            return "bool"
        if schema_type == "integer":
            cpp_type = "std::int64_t" if schema.get("format") == "int64" else "std::int32_t"
            return cls.telegram_integer(name, cpp_type, owner)
        if schema_type == "number":
            return "double"
        if schema_type == "string":
            return "std::string"

        return "nlohmann::json"

    @staticmethod
    def telegram_integer(name: str, cpp_type: str, owner: str = "") -> str:
        # user_chat_id identifies a private chat with a user, so it is also nonnegative.
        if (
            name in {"user_id", "user_chat_id"}
            or name.endswith("_user_id")
            or (owner in {"User", "Community"} and name == "id")
        ):
            return "std::uint64_t"
        if name == "direct_messages_topic_id" or (owner == "DirectMessagesTopic" and name == "topic_id"):
            return "std::uint64_t"
        if name == "chat_id" or name.endswith("_chat_id"):
            return "std::int64_t"
        if name == "draft_id":
            return "std::int64_t"
        # request_id can be negative. A bare id depends on its owning type.
        unsigned_id = (
            name
            in {
                "message_id",
                "message_thread_id",
                "story_id",
                "update_id",
                "option_id",
                "correct_option_id",
                "accent_color_id",
                "profile_accent_color_id",
            }
            or name.endswith(("_message_id", "_story_id", "_task_id"))
            or (name == "id" and owner in {"Story", "ChecklistTask", "InputChecklistTask"})
        )
        if unsigned_id:
            return cpp_type.replace("std::int", "std::uint")

        # Payments allow 12-digit amounts; TON prices can reach 10^13 nanograms.
        # Labeled prices include discounts, and Stars balances/refunds can be negative.
        if name == "amount" and owner in {"LabeledPrice", "StarAmount", "AffiliateInfo"}:
            return "std::int64_t"
        if (name == "amount" and owner in {"StarTransaction", "SuggestedPostPrice", "SuggestedPostPaid"}) or name in {
            "total_amount",
            "max_tip_amount",
            "suggested_tip_amounts",
            "last_resale_amount",
        }:
            return "std::uint64_t"

        # Identically named fields can have different domains. In particular,
        # getUpdates supports negative offsets; other pagination offsets do not.
        unsigned_context = (
            (
                name == "offset"
                and owner in {"MessageEntity", "getStarTransactions", "getUserProfilePhotos", "getUserProfileAudios"}
            )
            or (name == "nanostar_amount" and owner == "StarTransaction")
            or (name == "value" and owner == "Dice")
            or (name == "date" and owner in {"Message", "InaccessibleMessage"})
            or (name == "result" and owner == "getChatMemberCount")
        )
        # Nonnegative quantities and RGB/ARGB colors from the Bot API field
        # descriptions. Unlisted integers (including general Unix timestamps,
        # ratings and ordered-list labels) retain their signed schema type.
        unsigned_quantity = name.endswith(
            ("_count", "_width", "_height", "_duration", "_color", "_colors")
        ) or name in {
            "active_period",
            "cache_time",
            "closing_minute",
            "color",
            "colors",
            "colspan",
            "commission_per_mille",
            "dark_theme_dimming",
            "day",
            "distance",
            "duration",
            "file_size",
            "heading",
            "height",
            "intensity",
            "length",
            "limit",
            "live_period",
            "max_connections",
            "max_quantity",
            "member_limit",
            "message_auto_delete_time",
            "month",
            "number",
            "open_period",
            "opening_minute",
            "photo_size",
            "position",
            "proximity_alert_radius",
            "quote_position",
            "rarity_per_mille",
            "retry_after",
            "rotation_angle",
            "rowspan",
            "score",
            "size",
            "slow_mode_delay",
            "start_timestamp",
            "subscription_period",
            "subscription_price",
            "timeout",
            "unique_gift_number",
            "video_start_timestamp",
            "width",
            "year",
            "zoom",
        }
        if unsigned_context or unsigned_quantity:
            return cpp_type.replace("std::int", "std::uint")

        return cpp_type

    @classmethod
    def field_type(cls, name: str, schema: Schema, required: bool, owner: str = "") -> str:
        # These chat identifiers also accept @username, which tgbotspec currently loses.
        if name == "chat_id" and owner in {
            "BotCommandScopeChat",
            "BotCommandScopeChatAdministrators",
            "BotCommandScopeChatMember",
            "ReplyParameters",
        }:
            result = "std::variant<std::int64_t, std::string>"
        else:
            result = cls.type(schema, name, owner)
        if required or result.startswith("std::shared_ptr<"):
            return result

        return f"std::optional<{result}>"

    @classmethod
    def ref_name(cls, schema: Schema) -> str | None:
        if ref := schema.get("$ref"):
            return str(ref).rsplit("/", 1)[-1]
        for item in schema.get("allOf", []):
            if name := cls.ref_name(item):
                return name

        return None


class _BaseModelBuilder:
    @staticmethod
    def _comment_lines(text: str, width: int) -> tuple[str, ...]:
        normalized = " ".join(text.replace("*/", "* /").split())
        if not normalized:
            return ()

        return tuple(textwrap.wrap(normalized, width=width, break_long_words=False))

    @staticmethod
    def _cpp_name(value: str) -> str:
        first, *rest = value.split("_")

        return first + "".join(part[:1].upper() + part[1:] for part in rest)


class _TypeModelBuilder(_BaseModelBuilder):
    def __init__(self, components: dict[str, Schema], type_config: Schema = TYPE_CONFIG) -> None:
        self._components = components
        self._type_config = type_config
        self._names = set(components)

    def build(self) -> tuple[_TypeModel, ...]:
        types = []
        for name in sorted(self._names):
            schema = self._components[name]
            required = set(schema.get("required", []))
            union_members = self._union_members(name, schema)
            fields = tuple(
                self._build_field(name, field_name, field, field_name in required)
                for field_name, field in schema.get("properties", {}).items()
            )
            types.append(
                _TypeModel(
                    name=name,
                    aliases=tuple(self._type_config.get(name, {}).get("aliases", ())),
                    description=self._comment_lines(schema.get("description", ""), 92),
                    constants=self._constants(fields),
                    enums=tuple(field.enum for field in fields if field.enum),
                    fields=fields,
                    union_members=union_members,
                    dependencies=self._dependencies(name, fields, union_members),
                    standard_headers=self._standard_headers(fields, union_members),
                )
            )

        return tuple(types)

    def _build_field(self, type_name: str, name: str, schema: Schema, required: bool) -> _FieldModel:
        enum = self._field_enum(type_name, name)
        field_config = self._type_config.get(type_name, {}).get("fields", {}).get(name, {})
        cpp_type = field_config.get(
            "type", enum.name if enum else _CppTypeResolver.field_type(name, schema, required, type_name)
        )
        return _FieldModel(
            wire_name=name,
            cpp_name=self._cpp_name(name),
            cpp_type=cpp_type,
            required=required,
            description=self._comment_lines(schema.get("description", ""), 88),
            constant=self._field_constant(name, schema, required),
            enum=enum,
            accepts_integer_string=type_name == "MessageGenerationStopped" and name == "draft_id",
        )

    def _field_enum(self, type_name: str, field_name: str) -> _EnumModel | None:
        values = self._type_config.get(type_name, {}).get("fields", {}).get(field_name, {}).get("enum")
        if not values:
            return None

        return _EnumModel(
            name="Type",
            values=tuple(_EnumValueModel(name=name, value=value) for name, value in values.items()),
        )

    @staticmethod
    def _constants(fields: tuple[_FieldModel, ...]) -> tuple[_ConstantModel, ...]:
        return tuple(field.constant for field in fields if field.constant)

    def _dependencies(
        self,
        name: str,
        fields: tuple[_FieldModel, ...],
        union_members: tuple[str, ...],
    ) -> tuple[str, ...]:
        cpp_types = [field.cpp_type for field in fields]
        cpp_types.extend(union_members)
        dependencies = {
            token
            for cpp_type in cpp_types
            for token in re.findall(r"\b[A-Z][A-Za-z0-9]*\b", cpp_type)
            if token in self._names and token != name
        }

        return tuple(sorted(dependencies))

    @staticmethod
    def _standard_headers(fields: tuple[_FieldModel, ...], union_members: tuple[str, ...]) -> tuple[str, ...]:
        cpp_types = " ".join([field.cpp_type for field in fields] + list(union_members))
        headers = {"memory"}
        for cpp_type, header in (
            ("std::int", "cstdint"),
            ("std::optional", "optional"),
            ("std::string", "string"),
            ("std::variant", "variant"),
            ("std::vector", "vector"),
        ):
            if cpp_type in cpp_types:
                headers.add(header)
        if union_members:
            headers.add("variant")

        return tuple(sorted(headers))

    @staticmethod
    def _field_constant(name: str, schema: Schema, required: bool) -> _ConstantModel | None:
        if not required or name not in {"source", "status", "type"}:
            return None
        if schema.get("type") != "string":
            return None

        values = schema.get("enum", [])
        if len(values) == 1:
            return _ConstantModel(name.upper(), str(values[0]))

        description = schema.get("description", "")
        for pattern in (
            r"\bmust be ([a-z0-9_]+)(?:[.,]|$)",
            r'\balways ["“]([a-z0-9_]+)["”]',
        ):
            if match := re.search(pattern, description):
                return _ConstantModel(name.upper(), match.group(1))

        return None

    def _union_members(self, name: str, schema: Schema) -> tuple[str, ...]:
        if schema.get("properties"):
            return ()

        members = tuple(
            dict.fromkeys(
                f"std::shared_ptr<{line.strip()}>"
                for line in schema.get("description", "").splitlines()
                if line.strip() in self._names and line.strip() != name
            )
        )
        config = self._type_config.get(name, {})
        appended = tuple(member for member in config.get("append_union_types", ()) if member in members)
        # Preserve existing variant indices when Telegram inserts a new union member.
        return (
            tuple(member for member in members if member not in appended)
            + tuple(config.get("extra_union_types", ()))
            + appended
        )


class _MethodModelBuilder(_BaseModelBuilder):
    def __init__(self, paths: dict[str, Schema], api_config: Schema = API_CONFIG) -> None:
        self._paths = paths
        self._api_config = api_config

    def build(self) -> tuple[_MethodModel, ...]:
        return tuple(self._build_method(self._paths[path]["post"]) for path in sorted(self._paths))

    def _build_method(self, operation: Schema) -> _MethodModel:
        name = operation["operationId"]
        request = self._request_schema(operation)
        multipart = self._multipart_schema(operation)
        properties = dict(request.get("properties", {}))
        for arg_name, arg in multipart.get("properties", {}).items():
            properties.setdefault(arg_name, arg)
        method_config = self._api_config.get(name, {})
        if method_config.get("supports_attach_references"):
            properties["attachments"] = {"description": ATTACH_REFERENCES_DESCRIPTION}
        properties.update(method_config.get("extra_args", {}))
        required = set(request.get("required", [])) | set(multipart.get("required", []))
        binary = self._binary_args(operation)
        arg_names = self._ordered_arg_names(name, properties, required)
        response_type = _CppTypeResolver.api_type(self._response_schema(operation), "result", name)
        return_type = method_config.get("return_type", response_type)
        args = tuple(
            self._build_arg(
                name,
                arg_name,
                properties[arg_name],
                arg_name in required,
                arg_name in binary,
            )
            for arg_name in arg_names
        )
        legacy_ephemeral_parameters = bool(method_config.get("legacy_ephemeral_parameters"))
        direct_properties = {
            arg_name: schema
            for arg_name, schema in properties.items()
            if arg_name not in method_config.get("direct_exclude", ())
        }
        if legacy_ephemeral_parameters:
            direct_properties.pop("ephemeral_message_parameters", None)
            direct_properties.update(
                {
                    "callback_query_id": {
                        "type": "string",
                        "description": "Identifier of the callback query which triggered the ephemeral message",
                    },
                    "receiver_user_id": {
                        "type": "integer",
                        "format": "int64",
                        "description": "Identifier of the user who will receive the ephemeral message",
                    },
                }
            )
        direct_required = required & direct_properties.keys()
        if legacy_ephemeral_parameters:
            direct_required = direct_required | {"chat_id"}
        direct_arg_names = self._ordered_arg_names(name, direct_properties, direct_required)
        direct_args = tuple(
            self._build_arg(
                name,
                arg_name,
                direct_properties[arg_name],
                arg_name in direct_required,
                arg_name in binary,
            )
            for arg_name in direct_arg_names
        )
        direct_arg_wire_names = {arg.wire_name for arg in direct_args}
        struct_args = direct_args + tuple(arg for arg in args if arg.wire_name not in direct_arg_wire_names)
        compatibility_without = set(method_config.get("compatibility_overload_without", ()))
        return _MethodModel(
            name=name,
            return_type=return_type,
            response_type=response_type,
            return_description=self._return_description(return_type, response_type),
            description=self._comment_lines(operation.get("description", ""), 88),
            args=args,
            direct_args=direct_args,
            struct_args=struct_args,
            compatibility_args=tuple(arg for arg in direct_args if arg.wire_name not in compatibility_without),
            legacy_ephemeral_parameters=legacy_ephemeral_parameters,
            args_name=f"{name[0].upper()}{name[1:]}Args" if args else None,
        )

    def _ordered_arg_names(
        self,
        method_name: str,
        properties: dict[str, Schema],
        required: set[str],
    ) -> list[str]:
        method_config = self._api_config.get(method_name, {})
        preferred = method_config.get("args_order", ())
        args_order = {name: index for index, name in enumerate(preferred)}
        declaration_required = required | {
            name for name in properties if method_config.get("args", {}).get(name, {}).get("declaration_required")
        }
        if method_config.get("legacy_ephemeral_parameters"):
            declaration_required |= {"chat_id"}
        required_names = sorted(
            (name for name in properties if name in declaration_required),
            key=lambda name: (
                name != "chat_id",
                args_order.get(name, len(args_order)),
                name,
            ),
        )
        optional_names = [name for name in properties if name not in declaration_required]
        optional_names.sort(
            key=lambda name: (
                name == "attachments" and method_config.get("supports_attach_references"),
                args_order.get(name, len(args_order)),
                name,
            )
        )

        return required_names + optional_names

    def _build_arg(
        self,
        method_name: str,
        name: str,
        schema: Schema,
        required: bool,
        binary: bool,
    ) -> _ArgModel:
        arg_config = self._api_config.get(method_name, {}).get("args", {}).get(name, {})
        method_config = self._api_config.get(method_name, {})
        attach_references_arg = name == "attachments" and method_config.get("supports_attach_references")
        override = "std::vector<InputFileAttachment>" if attach_references_arg else arg_config.get("type")
        if override:
            cpp_type = override
        elif name in {"chat_id", "from_chat_id"}:
            private_chat = name == "chat_id" and method_name in {
                "getChatMenuButton",
                "setChatMenuButton",
                "sendMessageDraft",
                "sendRichMessageDraft",
            }
            integer_type = "std::uint64_t" if private_chat else "std::int64_t"
            cpp_type = f"std::variant<{integer_type}, std::string>"
        elif name == "certificate" and binary:
            cpp_type = "std::shared_ptr<InputFile>"
        elif binary:
            cpp_type = "std::variant<std::shared_ptr<InputFile>, std::string>"
        else:
            cpp_type = _CppTypeResolver.api_type(schema, name, method_name)
        return _ArgModel(
            wire_name=name,
            cpp_name=self._cpp_name(name),
            cpp_type=cpp_type,
            declaration_type=self._arg_declaration_type(cpp_type),
            required=required,
            always_send=bool(arg_config.get("always_send")),
            default_value=(
                None
                if required or arg_config.get("declaration_required")
                else self._arg_default(cpp_type, method_name, name)
            ),
            wire_default_value=(
                None if arg_config.get("always_send") else self._configured_arg_default(method_name, name)
            ),
            description=self._comment_lines(schema.get("description", ""), 72),
        )

    def _arg_default(self, cpp_type: str, method_name: str, arg_name: str) -> str:
        if (default := self._configured_arg_default(method_name, arg_name)) is not None:
            return default
        if cpp_type == "bool":
            return "false"
        if cpp_type in {"std::int32_t", "std::int64_t", "std::uint32_t", "std::uint64_t", "double"}:
            return "0"
        if cpp_type == "std::string":
            return '""'
        if cpp_type.startswith("std::shared_ptr<"):
            return "nullptr"
        if cpp_type == "nlohmann::json":
            return "nullptr"

        return "{ }"

    def _configured_arg_default(self, method_name: str, arg_name: str) -> str | None:
        arg_config = self._api_config.get(method_name, {}).get("args", {}).get(arg_name, {})
        default = arg_config.get("default")
        if default is None:
            return None
        if isinstance(default, bool):
            return str(default).lower()

        return str(default)

    @staticmethod
    def _return_description(return_type: str, response_type: str) -> str:
        if return_type == "bool":
            return "True on success."
        if return_type in {"std::int32_t", "std::uint32_t", "std::int64_t", "std::uint64_t"}:
            return "The resulting integer."
        if return_type == "std::string":
            return "The resulting string."
        if match := re.fullmatch(r"std::shared_ptr<([A-Za-z0-9]+)>", return_type):
            type_name = match.group(1)
            if return_type != response_type:
                return f"The resulting {type_name} object, or nullptr if Telegram returns True."
            return f"The resulting {type_name} object."
        if match := re.fullmatch(r"std::vector<std::shared_ptr<([A-Za-z0-9]+)>>", return_type):
            return f"The resulting list of {match.group(1)} objects."

        raise ValueError(f"Unsupported API return type: {return_type}")

    @staticmethod
    def _arg_declaration_type(cpp_type: str) -> str:
        if cpp_type == "std::string":
            return "std::string_view"
        if cpp_type.startswith("std::vector<"):
            return f"const {cpp_type}&"
        if cpp_type == "nlohmann::json":
            return "const nlohmann::json&"

        return cpp_type

    @staticmethod
    def _request_schema(operation: Schema) -> Schema:
        return (
            operation.get("requestBody", {})
            .get("content", {})
            .get("application/json", {"schema": {"type": "object", "properties": {}}})["schema"]
        )

    @staticmethod
    def _multipart_schema(operation: Schema) -> Schema:
        return operation.get("requestBody", {}).get("content", {}).get("multipart/form-data", {"schema": {}})["schema"]

    @staticmethod
    def _binary_args(operation: Schema) -> set[str]:
        multipart = operation.get("requestBody", {}).get("content", {}).get("multipart/form-data", {})

        return {
            name
            for name, schema in multipart.get("schema", {}).get("properties", {}).items()
            if schema.get("format") == "binary"
        }

    @staticmethod
    def _response_schema(operation: Schema) -> Schema:
        response = operation["responses"]["200"]["content"]["application/json"]["schema"]
        for part in response.get("allOf", []):
            if result := part.get("properties", {}).get("result"):
                return result

        raise ValueError(f"Response type is missing for {operation['operationId']}")
