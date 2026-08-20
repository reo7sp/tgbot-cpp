#pragma once

#include "tgbot/export.h"

#include <memory>
#include <optional>
#include <string>
#include <string_view>

namespace TgBot {

/**
 * @brief This object represents the contents of a file to be uploaded.
 *
 * @ingroup api
 */
struct TGBOT_API InputFile {
    using Ptr = std::shared_ptr<InputFile>;

    /**
     * @brief Contents used for an in-memory upload.
     *
     * Empty for files created with fromFile().
     */
    std::string data;

    /**
     * @brief Mime type of the contents.
     */
    std::string mimeType;

    /**
     * @brief File name.
     */
    std::string fileName;

    /**
     * @brief Local path used for a streaming upload.
     *
     * When set, the file is read by the HTTP client during the request and data is
     * ignored. The file must remain accessible and unchanged until the request completes.
     */
    std::optional<std::string> filePath;

    /**
     * @brief Creates new std::shared_ptr<InputFile> from binary data held in memory.
     *
     * @param data File contents. May contain null bytes.
     * @param mimeType Mime type of the file.
     * @param fileName File name reported in the multipart upload.
     */
    static std::shared_ptr<InputFile> fromData(std::string data, std::string mimeType, std::string fileName);

    /**
     * @brief Creates new std::shared_ptr<InputFile> from an existing file.
     *
     * Stores the path without reading the file. The HTTP client streams its contents
     * during the request and uses the basename of filePath as the multipart file name.
     * The file must remain accessible and unchanged until the request completes.
     *
     * @param filePath Path to the file to stream.
     * @param mimeType Mime type of the file.
     */
    static std::shared_ptr<InputFile> fromFile(std::string_view filePath, std::string mimeType);
};

/**
 * @brief A named multipart file referenced from a Telegram API argument as attach://name.
 *
 * @ingroup api
 */
struct InputFileAttachment {
    /**
     * @brief Multipart form field name used in the attach:// reference.
     */
    std::string name;

    /**
     * @brief File contents to upload under the specified name.
     */
    std::shared_ptr<InputFile> file;
};

} // namespace TgBot
