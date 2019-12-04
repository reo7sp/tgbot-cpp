#ifndef TGBOT_CPP_AUDIO_H
#define TGBOT_CPP_AUDIO_H

#include <string>
#include <memory>

#include "tgbot/types/PhotoSize.h"

namespace TgBot {

/**
 * @brief This object represents an audio file (voice note).
 *
 * @ingroup types
 */
class Audio {

public:
    typedef std::shared_ptr<Audio> Ptr;

    /**
     * @brief Unique identifier for this file.
     */
    std::string fileId;

    /**
     * @brief Duration of the audio in seconds as defined by sender.
     */
    int32_t duration;

    /**
     * @brief Optional. Performer of the audio as defined by sender
     * or by audio tags
     */
    std::string performer;

    /**
    * @brief Optional. Title of the audio as defined by sender or
    * by audio tags
    */
    std::string title;

    /**
     * @brief Optional. MIME type of the file as defined by sender.
     */
    std::string mimeType;

    /**
     * @brief Optional. File size.
     */
    int32_t fileSize;

    /**
     * @brief Optional. Thumbnail of the album cover to which the music file belongs
     */
    PhotoSize::Ptr thumb;
};

}

#endif //TGBOT_CPP_AUDIO_H
