#pragma once

#include <nlohmann/json.hpp>

#include <cstddef>
#include <memory>
#include <optional>
#include <stdexcept>
#include <string>
#include <utility>
#include <variant>
#include <vector>

/** @cond */

namespace TgBot::Json {

template<typename T>
void decode(const nlohmann::json& json, T& value);

template<typename T>
void decode(const nlohmann::json& json, std::shared_ptr<T>& value);

template<typename T>
void decode(const nlohmann::json& json, std::optional<T>& value);

template<typename T>
void decode(const nlohmann::json& json, std::vector<T>& value);

template<std::size_t Index = 0, typename... T>
void decode(const nlohmann::json& json, std::variant<T...>& value);

template<typename T>
bool matchesDiscriminator(const nlohmann::json& json) {
    if constexpr (requires { typename T::element_type; }) {
        using Element = typename T::element_type;
        if constexpr (requires { Element::TYPE; }) {
            return json.is_object() && json.value("type", std::string { }) == Element::TYPE;
        }
        if constexpr (requires { Element::STATUS; }) {
            return json.is_object() && json.value("status", std::string { }) == Element::STATUS;
        }
        if constexpr (requires { Element::SOURCE; }) {
            return json.is_object() && json.value("source", std::string { }) == Element::SOURCE;
        }
    }

    return true;
}

template<typename T>
void decode(const nlohmann::json& json, T& value) {
    json.get_to(value);
}

template<typename T>
void decode(const nlohmann::json& json, std::shared_ptr<T>& value) {
    if (json.is_null()) {
        throw std::invalid_argument("Required Telegram object is null");
    }
    value = std::make_shared<T>();
    from_json(json, *value);
}

template<typename T>
void decode(const nlohmann::json& json, std::optional<T>& value) {
    if (json.is_null()) {
        value.reset();
        return;
    }
    value.emplace();
    decode(json, *value);
}

template<typename T>
void decode(const nlohmann::json& json, std::vector<T>& value) {
    if (!json.is_array()) {
        throw std::invalid_argument("Telegram array field is not an array");
    }
    value.clear();
    value.reserve(json.size());
    for (const auto& item : json) {
        T decoded { };
        decode(item, decoded);
        value.push_back(std::move(decoded));
    }
}

template<std::size_t Index, typename... T>
void decode(const nlohmann::json& json, std::variant<T...>& value) {
    if constexpr (Index == sizeof...(T)) {
        throw std::invalid_argument("JSON value does not match Telegram union");
    } else {
        try {
            using Candidate = std::variant_alternative_t<Index, std::variant<T...>>;
            if (!matchesDiscriminator<Candidate>(json)) {
                throw std::invalid_argument("Telegram union discriminator does not match");
            }
            Candidate candidate { };
            decode(json, candidate);
            value = std::move(candidate);
        } catch (const std::exception&) {
            decode<Index + 1>(json, value);
        }
    }
}

template<typename T>
nlohmann::json encode(const T& value);

template<typename T>
nlohmann::json encode(const std::shared_ptr<T>& value);

template<typename T>
nlohmann::json encode(const std::optional<T>& value);

template<typename T>
nlohmann::json encode(const std::vector<T>& value);

template<typename... T>
nlohmann::json encode(const std::variant<T...>& value);

template<typename T>
nlohmann::json encode(const T& value) {
    return nlohmann::json(value);
}

template<typename T>
nlohmann::json encode(const std::shared_ptr<T>& value) {
    if (!value) {
        return nullptr;
    }
    nlohmann::json json;
    to_json(json, *value);

    return json;
}

template<typename T>
nlohmann::json encode(const std::optional<T>& value) {
    return value ? encode(*value) : nlohmann::json(nullptr);
}

template<typename T>
nlohmann::json encode(const std::vector<T>& value) {
    nlohmann::json json = nlohmann::json::array();
    for (const auto& item : value) {
        json.push_back(encode(item));
    }

    return json;
}

template<typename... T>
nlohmann::json encode(const std::variant<T...>& value) {
    return std::visit(
        [](const auto& item) {
            return encode(item);
        },
        value);
}

template<typename T>
void readRequiredField(const nlohmann::json& json, const char* name, T& value) {
    decode(json.at(name), value);
}

template<typename T>
void readOptionalField(const nlohmann::json& json, const char* name, T& value) {
    const auto item = json.find(name);
    if (item == json.end() || item->is_null()) {
        value = T { };
        return;
    }
    decode(*item, value);
}

template<typename T>
void writeRequiredField(nlohmann::json& json, const char* name, const T& value) {
    json[name] = encode(value);
}

template<typename T>
void writeOptionalField(nlohmann::json& json, const char* name, const std::optional<T>& value) {
    if (value) {
        json[name] = encode(value);
    }
}

template<typename T>
void writeOptionalField(nlohmann::json& json, const char* name, const std::shared_ptr<T>& value) {
    if (value) {
        json[name] = encode(value);
    }
}

} // namespace TgBot::Json

/** @endcond */
