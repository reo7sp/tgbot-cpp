#ifndef TGBOT_CPP_PASSPORTFILE_H
#define TGBOT_CPP_PASSPORTFILE_H

#include <memory>
#include <string>

namespace TgBot {

/**
 * @brief This object represents a file uploaded to Telegram Passport.
 * Currently all Telegram Passport files are in JPEG format when decrypted and don't exceed 10MB.
 *
 * @ingroup types
 */
class PassportFile {

public:
    typedef std::shared_ptr<PassportFile> Ptr;

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
     * @brief File size
     */
    std::int32_t fileSize;

    /**
     * @brief Unix time when the file was uploaded
     */
    std::int32_t fileDate;
};
}

#endif //TGBOT_CPP_PASSPORTFILE_H
