#pragma once

#include <optional>
#include <string>
#include <variant>

namespace TgBot {

/**
 * @ingroup net
 */
struct HttpFile {
    std::string data;
    std::string mimeType;
    std::string fileName;
    std::optional<std::string> filePath;
};

/**
 * @ingroup net
 */
struct HttpFormField {
    std::string name;
    std::variant<std::string, HttpFile> value;
};

} // namespace TgBot
