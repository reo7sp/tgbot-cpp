#ifndef TGBOT_CPP_FILE_H
#define TGBOT_CPP_FILE_H

#include <cstdint>
#include <string>
#include <memory>

namespace TgBot {

/**
 * @brief This object represents a file ready to be downloaded.
 *
 * The file can be downloaded via the link https://api.telegram.org/file/bot<token>/<file_path>.
 * It is guaranteed that the link will be valid for at least 1 hour.
 * When the link expires, a new one can be requested by calling getFile.
 * Maximum file size to download is 20 MB
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
     *
     * Can't be used to download or reuse the file.
     */
    std::string fileUniqueId;

    /**
     * @brief Optional. File size, if known
     */
    std::int32_t fileSize;

    /**
     * @brief Optional. File path.
     *
     * Use https://api.telegram.org/file/bot<token>/<file_path> to get the file.
     */
    std::string filePath;
};
}

#endif //TGBOT_CPP_FILE_H
