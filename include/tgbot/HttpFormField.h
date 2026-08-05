#pragma once

#include <string>
#include <variant>

namespace TgBot {

struct HttpFile {
    std::string data;
    std::string mimeType;
    std::string fileName;
};

struct HttpFormField {
    std::string name;
    std::variant<std::string, HttpFile> value;
};

} // namespace TgBot
