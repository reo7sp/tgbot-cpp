#ifndef TGBOT_AUDIO_H
#define TGBOT_AUDIO_H

#include "tgbot/types/PhotoSize.h"

#include <cstdint>
#include <memory>
#include <string>

namespace TgBot {

/**
 * @brief This object represents an audio file to be treated as music by the Telegram clients.
 *
 * @ingroup types
 */
class Audio {

public:
    typedef std::shared_ptr<Audio> Ptr;

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
     * @brief Duration of the audio in seconds as defined by sender
     */
    std::int32_t duration;

    /**
     * @brief Optional. Performer of the audio as defined by sender or by audio tags
     */
    std::string performer;

    /**
    * @brief Optional. Title of the audio as defined by sender or by audio tags
    */
    std::string title;

    /**
     * @brief Optional. Original filename as defined by sender
     */
    std::string fileName;

    /**
     * @brief Optional. MIME type of the file as defined by sender
     */
    std::string mimeType;

    /**
     * @brief Optional. File size in bytes.
     * 
     * It can be bigger than 2^31 and some programming languages may have difficulty/silent defects in interpreting it.
     * But it has at most 52 significant bits, so a signed 64-bit integer or double-precision float type are safe for storing this value.
     */
    std::int64_t fileSize;

    /**
     * @brief Optional. Thumbnail of the album cover to which the music file belongs
     */
    PhotoSize::Ptr thumbnail;
};
}

#endif //TGBOT_AUDIO_H
