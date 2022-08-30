#ifndef TGBOT_CPP_AUDIO_H
#define TGBOT_CPP_AUDIO_H

#include "tgbot/types/PhotoSize.h"

#include <cstdint>
#include <string>
#include <memory>

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
     * @brief Optional. MIME type of the file as defined by sender
     */
    std::string mimeType;

    /**
     * @brief Optional. File size
     */
    std::int32_t fileSize;

    /**
     * @brief Optional. Thumbnail of the album cover to which the music file belongs
     */
    PhotoSize::Ptr thumb;
};
}

#endif //TGBOT_CPP_AUDIO_H
