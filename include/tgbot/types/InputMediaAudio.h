#ifndef TGBOT_INPUTMEDIAAUDIO_H
#define TGBOT_INPUTMEDIAAUDIO_H

#include "tgbot/types/InputMedia.h"

#include <memory>
#include <string>

namespace TgBot {

/**
 * @brief Represents an audio file to be treated as music to be sent.
 * 
 * @ingroup types
 */
class InputMediaAudio : public InputMedia {

public:
    static const std::string TYPE;

    typedef std::shared_ptr<InputMediaAudio> Ptr;

    InputMediaAudio() {
        this->type = TYPE;
    }

    /**
     * @brief Optional. Thumbnail of the file sent; can be ignored if thumbnail generation for the file is supported server-side.
     * The thumbnail should be in JPEG format and less than 200 kB in size.
     * A thumbnail's width and height should not exceed 320.
     * Ignored if the file is not uploaded using multipart/form-data.
     * Thumbnails can't be reused and can be only uploaded as a new file, so you can pass “attach://<file_attach_name>” if the thumbnail was uploaded using multipart/form-data under <file_attach_name>.
     * https://core.telegram.org/bots/api#sending-files
     */
    std::string thumbnail;

    /**
     * @brief Optional. Duration of the audio in seconds
     */
    std::int32_t duration;

    /**
     * @brief Optional. Performer of the audio
     */
    std::string performer;

    /**
     * @brief Optional. Title of the audio
     */
    std::string title;
};
}

#endif //TGBOT_INPUTMEDIAAUDIO_H
