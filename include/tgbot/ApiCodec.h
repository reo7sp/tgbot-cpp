#pragma once

#include "tgbot/HttpFormField.h"
#include "tgbot/InputFile.h"
#include "tgbot/Json.h"
#include "tgbot/export.h"

#include <nlohmann/json.hpp>

#include <memory>
#include <optional>
#include <stdexcept>
#include <string>
#include <string_view>
#include <type_traits>
#include <unordered_set>
#include <variant>
#include <vector>

/** @cond */

namespace TgBot::ApiRequest {

TGBOT_API void appendField(std::vector<HttpFormField>& fields, std::string_view name, std::string_view value);
TGBOT_API void appendField(std::vector<HttpFormField>& fields, std::string_view name,
                           const std::shared_ptr<InputFile>& value);

template<typename T>
requires(!std::is_convertible_v<const T&, std::string_view>)
void appendField(std::vector<HttpFormField>& fields, std::string_view name, const T& value) {
    if constexpr (std::is_arithmetic_v<T>) {
        fields.push_back({ std::string(name), std::to_string(value) });
    } else {
        fields.push_back({ std::string(name), Json::encode(value).dump() });
    }
}

template<typename T>
void appendField(std::vector<HttpFormField>& fields, std::string_view name, const std::optional<T>& value) {
    if (value) {
        appendField(fields, name, *value);
    }
}

template<typename T>
void appendField(std::vector<HttpFormField>& fields, std::string_view name, const std::shared_ptr<T>& value) {
    if (value) {
        fields.push_back({ std::string(name), Json::encode(value).dump() });
    }
}

template<typename... T>
void appendField(std::vector<HttpFormField>& fields, std::string_view name, const std::variant<T...>& value) {
    std::visit(
        [&](const auto& item) {
            appendField(fields, name, item);
        },
        value);
}

template<typename T>
requires std::is_arithmetic_v<T>
void appendOptionalField(std::vector<HttpFormField>& fields, std::string_view name, T value) {
    if (value != 0) {
        appendField(fields, name, value);
    }
}

TGBOT_API void appendOptionalField(std::vector<HttpFormField>& fields, std::string_view name, std::string_view value);
TGBOT_API void appendOptionalField(std::vector<HttpFormField>& fields, std::string_view name, const std::string& value);

TGBOT_API void appendOptionalField(std::vector<HttpFormField>& fields, std::string_view name,
                                   const nlohmann::json& value);
TGBOT_API void appendOptionalField(std::vector<HttpFormField>& fields, std::string_view name,
                                   const std::vector<InputFileAttachment>& value);

template<typename T>
void appendOptionalField(std::vector<HttpFormField>& fields, std::string_view name, const std::shared_ptr<T>& value) {
    if (value) {
        appendField(fields, name, value);
    }
}

template<typename T>
void appendOptionalField(std::vector<HttpFormField>& fields, std::string_view name, const std::vector<T>& value) {
    if (!value.empty()) {
        appendField(fields, name, value);
    }
}

template<typename... T>
void appendOptionalField(std::vector<HttpFormField>& fields, std::string_view name, const std::variant<T...>& value) {
    std::visit(
        [&](const auto& item) {
            appendOptionalField(fields, name, item);
        },
        value);
}

/**
 * @brief Internal non-owning parameter proxy for immediate use with makeFields().
 *
 * Do not store this object. The referenced name and value must remain valid until
 * makeFields() returns.
 */
template<bool Required, typename T>
struct Parameter {
    static constexpr bool isRequired = Required;

    std::string_view name;
    const T& value;
};

/**
 * @brief Internal non-owning parameter proxy with a default value.
 *
 * Do not store this object. The referenced name and value must remain valid until
 * makeFields() returns.
 */
template<typename T>
struct ParameterWithDefault {
    static constexpr bool isRequired = false;

    std::string_view name;
    const T& value;
    T defaultValue;
};

template<typename T>
Parameter<true, T> required(std::string_view name, const T& value) {
    return { name, value };
}

template<typename T>
Parameter<false, T> optional(std::string_view name, const T& value) {
    return { name, value };
}

template<typename T>
ParameterWithDefault<T> optional(std::string_view name, const T& value, T defaultValue) {
    return { name, value, std::move(defaultValue) };
}

template<typename... Parameters>
std::vector<HttpFormField> makeFields(const Parameters&... parameters) {
    std::vector<HttpFormField> result;
    result.reserve(sizeof...(Parameters));
    (
        [&] {
            if constexpr (Parameters::isRequired) {
                appendField(result, parameters.name, parameters.value);
            } else if constexpr (requires { parameters.defaultValue; }) {
                if (parameters.value != parameters.defaultValue) {
                    appendField(result, parameters.name, parameters.value);
                }
            } else {
                appendOptionalField(result, parameters.name, parameters.value);
            }
        }(),
        ...);

    std::unordered_set<std::string_view> names;
    for (const auto& field : result) {
        if (!names.emplace(field.name).second) {
            throw std::invalid_argument("Duplicate multipart field name: " + field.name);
        }
    }

    return result;
}

} // namespace TgBot::ApiRequest

namespace TgBot::ApiResponse {

template<typename T>
T decode(const nlohmann::json& json) {
    T result { };
    Json::decode(json, result);

    return result;
}

template<typename T>
std::shared_ptr<T> decodeObjectOrTrue(const nlohmann::json& json) {
    auto result = decode<std::variant<std::shared_ptr<T>, bool>>(json);
    if (auto object = std::get_if<std::shared_ptr<T>>(&result)) {
        return *object;
    }

    return nullptr;
}

} // namespace TgBot::ApiResponse

/** @endcond */
