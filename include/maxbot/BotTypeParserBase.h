#pragma once

#include "maxbot/export.h"

#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>

#include <memory>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

namespace MaxBot {

class MAXBOT_API BotTypeParserBase {

public:
    template<typename T>
    using JsonToBotTypeFunc = std::shared_ptr<T> (*)(const boost::property_tree::ptree&);

    template<typename T>
    using BotTypeToJsonFunc = std::string (*)(const std::shared_ptr<T>&);

    static inline boost::property_tree::ptree parseJson(const std::string& json) {
        boost::property_tree::ptree tree;
        std::istringstream input(json);
        boost::property_tree::read_json(input, tree);
        return tree;
    }

    template<typename T>
    static std::shared_ptr<T> tryParseJson(JsonToBotTypeFunc<T> parseFunc, const boost::property_tree::ptree& data, const std::string& keyName) {
        auto treeItem = data.find(keyName);
        if (treeItem == data.not_found()) {
            return std::shared_ptr<T>();
        }
        return parseFunc(treeItem->second);
    }

    template<typename T>
    static std::vector<std::shared_ptr<T>> parseJsonAndGetArray(JsonToBotTypeFunc<T> parseFunc, const boost::property_tree::ptree& data) {
        std::vector<std::shared_ptr<T>> result;
        result.reserve(data.size());
        for (const std::pair<const std::string, boost::property_tree::ptree>& innerTreeItem : data) {
            result.push_back(parseFunc(innerTreeItem.second));
        }
        return result;
    }

    template<typename T>
    static std::vector<T> parseJsonAndGetArray(std::function<T(const boost::property_tree::ptree&)> parseFunc, const boost::property_tree::ptree& data, const std::string& keyName) {
        std::vector<T> result;
        auto treeItem = data.find(keyName);
        if (treeItem == data.not_found()) {
            return result;
        }
        result.reserve(treeItem->second.size());
        for (const std::pair<const std::string, boost::property_tree::ptree>& innerTreeItem : treeItem->second) {
            result.push_back(parseFunc(innerTreeItem.second));
        }
        return result;
    }

    template<typename T>
    static std::vector<std::shared_ptr<T>> parseJsonAndGetArray(JsonToBotTypeFunc<T> parseFunc, const boost::property_tree::ptree& data, const std::string& keyName) {
        std::vector<std::shared_ptr<T>> result;
        auto treeItem = data.find(keyName);
        if (treeItem == data.not_found()) {
            return result;
        }
        result.reserve(treeItem->second.size());
        for (const std::pair<const std::string, boost::property_tree::ptree>& innerTreeItem : treeItem->second) {
            result.push_back(parseFunc(innerTreeItem.second));
        }
        return result;
    }

    template<typename T>
    static std::vector<std::vector<std::shared_ptr<T>>> parseJsonAndGet2DArray(JsonToBotTypeFunc<T> parseFunc, const boost::property_tree::ptree& data, const std::string& keyName) {
        std::vector<std::vector<std::shared_ptr<T>>> result;
        auto treeItem = data.find(keyName);
        if (treeItem == data.not_found()) {
            return result;
        }
        result.reserve(treeItem->second.size());
        for (const std::pair<const std::string, boost::property_tree::ptree>& innerTreeItem : treeItem->second) {
            std::vector<std::shared_ptr<T>> innerResult;
            for (const std::pair<const std::string, boost::property_tree::ptree>& innerInnerTreeItem : innerTreeItem.second) {
                innerResult.push_back(parseFunc(innerInnerTreeItem.second));
            }
            result.push_back(innerResult);
        }
        return result;
    }

    template<typename T>
    static std::string parseArray(BotTypeToJsonFunc<T> parseFunc, const std::vector<std::shared_ptr<T>>& objects) {
        if (objects.empty())
            return "";
        std::string result;
        result += '[';
        for (const std::shared_ptr<T>& item : objects) {
            result += parseFunc(item);
            result += ',';
        }
        result.erase(result.length() - 1);
        result += ']';
        return result;
    }

    template<typename T>
    static std::string parseArray(std::function<T(const T&)> parseFunc, const std::vector<T>& objects) {
        if (objects.empty())
            return "";
        std::string result;
        result += '[';
        for (const T& item : objects) {
            result += parseFunc(item);
            result += ',';
        }
        result.erase(result.length() - 1);
        result += ']';
        return result;
    }

    template<typename T>
    static std::string parse2DArray(BotTypeToJsonFunc<T> parseFunc, const std::vector<std::vector<std::shared_ptr<T>>>& objects) {
        if (objects.empty())
            return "";
        std::string result;
        result += '[';
        for (const std::vector<std::shared_ptr<T>>& item : objects) {
            result += parseArray(parseFunc, item);
            result += ',';
        }
        result.erase(result.length() - 1);
        result += ']';
        return result;
    }

    static inline void removeLastComma(std::string& input) {
        input.erase(input.length() - 1);
    }

    template<typename T>
    static inline void appendToJson(std::string& json, const std::string& varName, const std::shared_ptr<T>& value) {
        if (value == nullptr) {
            return;
        }
        json += '"';
        json += varName;
        json += R"(":)";
        json += value;
        json += ',';
    }

    template<typename T>
    static inline void appendToJson(std::string& json, const std::string& varName, const T& value) {
        json += '"';
        json += varName;
        json += R"(":)";
        json += value;
        json += ',';
    }

    template<typename T>
    static inline void appendToJsonNumber(std::string& json, const std::string& varName, const T& value) {
        json += '"';
        json += varName;
        json += R"(":)";
        json += std::to_string(value);
        json += ',';
    }

    static inline void appendToJson(std::string &json, const std::string &varName, const int &value) { appendToJsonNumber(json, varName, value); }
    static inline void appendToJson(std::string &json, const std::string &varName, const long &value) { appendToJsonNumber(json, varName, value); }
    static inline void appendToJson(std::string &json, const std::string &varName, const long long &value) { appendToJsonNumber(json, varName, value); }
    static inline void appendToJson(std::string &json, const std::string &varName, const unsigned &value) { appendToJsonNumber(json, varName, value); }
    static inline void appendToJson(std::string &json, const std::string &varName, const unsigned long &value) { appendToJsonNumber(json, varName, value); }
    static inline void appendToJson(std::string &json, const std::string &varName, const unsigned long long &value) { appendToJsonNumber(json, varName, value); }
    static inline void appendToJson(std::string &json, const std::string &varName, const float &value) { appendToJsonNumber(json, varName, value); }
    static inline void appendToJson(std::string &json, const std::string &varName, const double &value) { appendToJsonNumber(json, varName, value); }
    static inline void appendToJson(std::string &json, const std::string &varName, const long double &value) { appendToJsonNumber(json, varName, value); }

    static inline void appendToJson(std::string& json, const std::string& varName, const bool& value) {
        json += '"';
        json += varName;
        json += R"(":)";
        json += (value ? "true" : "false");
        json += ',';
    }

    static inline void appendToJson(std::string& json, const std::string& varName, const char* value) {
        if (value != nullptr){
            std::string strValue(value);
            appendToJson(json, varName, strValue);
        }
    }

    static void appendToJson(std::string& json, const std::string& varName, const std::string& value);
};
}
