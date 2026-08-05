#pragma once

#include "tgbot/HttpFormField.h"
#include "tgbot/InputFile.h"
#include "tgbot/Json.h"

#include <nlohmann/json.hpp>

#include <memory>
#include <optional>
#include <string>
#include <type_traits>
#include <variant>
#include <vector>

/** @cond */

namespace TgBot::ApiRequest {

void appendField(std::vector<HttpFormField>& fields, const char* name, const std::string& value);
void appendField(std::vector<HttpFormField>& fields, const char* name, const InputFile::Ptr& value);

template<typename T>
void appendField(std::vector<HttpFormField>& fields, const char* name, const T& value) {
    if constexpr (std::is_arithmetic_v<T>) {
        fields.push_back({ name, std::to_string(value) });
    } else {
        fields.push_back({ name, Json::encode(value).dump() });
    }
}

template<typename T>
void appendField(std::vector<HttpFormField>& fields, const char* name, const std::optional<T>& value) {
    if (value) {
        appendField(fields, name, *value);
    }
}

template<typename T>
void appendField(std::vector<HttpFormField>& fields, const char* name, const std::shared_ptr<T>& value) {
    if (value) {
        fields.push_back({ name, Json::encode(value).dump() });
    }
}

template<typename... T>
void appendField(std::vector<HttpFormField>& fields, const char* name, const std::variant<T...>& value) {
    std::visit([&](const auto& item) { appendField(fields, name, item); }, value);
}

template<typename T>
requires std::is_arithmetic_v<T> void appendOptionalField(std::vector<HttpFormField>& fields, const char* name,
                                                          T value) {
    if (value != 0) {
        appendField(fields, name, value);
    }
}

void appendOptionalField(std::vector<HttpFormField>& fields, const char* name, const std::string& value);
void appendOptionalField(std::vector<HttpFormField>& fields, const char* name, const nlohmann::json& value);

template<typename T>
void appendOptionalField(std::vector<HttpFormField>& fields, const char* name, const std::shared_ptr<T>& value) {
    if (value) {
        appendField(fields, name, value);
    }
}

template<typename T>
void appendOptionalField(std::vector<HttpFormField>& fields, const char* name, const std::vector<T>& value) {
    if (!value.empty()) {
        appendField(fields, name, value);
    }
}

template<typename... T>
void appendOptionalField(std::vector<HttpFormField>& fields, const char* name, const std::variant<T...>& value) {
    std::visit([&](const auto& item) { appendOptionalField(fields, name, item); }, value);
}

template<bool Required, typename T>
struct Parameter {
    static constexpr bool isRequired = Required;

    const char* name;
    const T& value;
};

template<typename T>
struct ParameterWithDefault {
    static constexpr bool isRequired = false;

    const char* name;
    const T& value;
    T defaultValue;
};

template<typename T>
Parameter<true, T> required(const char* name, const T& value) {
    return { name, value };
}

template<typename T>
Parameter<false, T> optional(const char* name, const T& value) {
    return { name, value };
}

template<typename T>
ParameterWithDefault<T> optional(const char* name, const T& value, T defaultValue) {
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
