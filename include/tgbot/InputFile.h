#pragma once

#include "tgbot/export.h"

#include <memory>
#include <string>

namespace TgBot {

/**
 * @brief This object represents the contents of a file to be uploaded.
 *
 * @ingroup api
 */
class TGBOT_API InputFile {
public:
    using Ptr = std::shared_ptr<InputFile>;

    /**
     * @brief Contents of a file.
     */
    std::string data;

    /**
     * @brief Mime type of a file.
     */
    std::string mimeType;

    /**
     * @brief File name.
     */
    std::string fileName;

    /**
     * @brief Creates new std::shared_ptr<InputFile> from an existing file.
     */
    static std::shared_ptr<InputFile> fromFile(const std::string& filePath, const std::string& mimeType);
};

} // namespace TgBot
