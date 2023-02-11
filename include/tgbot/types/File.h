#ifndef TGBOT_FILE_H
#define TGBOT_FILE_H

#include <cstdint>
#include <memory>
#include <string>

namespace TgBot {

/**
 * @brief This object represents a file ready to be downloaded.
 * The file can be downloaded via Api::downloadFile or via the link https://api.telegram.org/file/bot<token>/<filePath>.
 * It is guaranteed that the File::filePath will be valid for at least 1 hour.
 * When the File::filePath expires, a new one can be requested by calling Api::getFile.
 * 
 * The maximum file size to download is 20 MB
 *
 * @ingroup types
 */
class File {

public:
    typedef std::shared_ptr<File> Ptr;

    /**
     * @brief Identifier for this file, which can be used to download or reuse the file
     */
    std::string fileId;

    /**
     * @brief Unique identifier for this file, which is supposed to be the same over time and for different bots.
     * Can't be used to download or reuse the file.
     */
    std::string fileUniqueId;

    /**
     * @brief Optional. File size in bytes.
     * 
     * It can be bigger than 2^31 and some programming languages may have difficulty/silent defects in interpreting it.
     * But it has at most 52 significant bits, so a signed 64-bit integer or double-precision float type are safe for storing this value.
     */
    std::int64_t fileSize;

    /**
     * @brief Optional. File path.
     * Use Api::downloadFile or https://api.telegram.org/file/bot<token>/<filePath> to get the file.
     */
    std::string filePath;
};
}

#endif //TGBOT_FILE_H
