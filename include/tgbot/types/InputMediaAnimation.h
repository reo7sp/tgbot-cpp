#ifndef TGBOT_INPUTMEDIAANIMATION_H
#define TGBOT_INPUTMEDIAANIMATION_H

#include "tgbot/types/InputMedia.h"

#include <memory>
#include <string>

namespace TgBot {

/**
 * @brief Represents an animation file (GIF or H.264/MPEG-4 AVC video without sound) to be sent.
 * 
 * @ingroup types
 */
class InputMediaAnimation : public InputMedia {

public:
    static const std::string TYPE;

    typedef std::shared_ptr<InputMediaAnimation> Ptr;

    InputMediaAnimation() {
        this->type = TYPE;
    }

    /**
     * @brief Optional. Thumbnail of the file sent; can be ignored if thumbnail generation for the file is supported server-side.
     * 
     * The thumbnail should be in JPEG format and less than 200 kB in size.
     * A thumbnail's width and height should not exceed 320.
     * Ignored if the file is not uploaded using multipart/form-data.
     * Thumbnails can't be reused and can be only uploaded as a new file, so you can pass “attach://<file_attach_name>” if the thumbnail was uploaded using multipart/form-data under <file_attach_name>.
     * https://core.telegram.org/bots/api#sending-files
     */
    std::string thumbnail;

    /**
     * @brief Optional. Animation width
     */
    std::int32_t width;

    /**
     * @brief Optional. Animation height
     */
    std::int32_t height;

    /**
     * @brief Optional. Animation duration in seconds
     */
    std::int32_t duration;

    /**
     * @brief Optional. Pass True if the animation needs to be covered with a spoiler animation
     */
    bool hasSpoiler;
};
}

#endif //TGBOT_INPUTMEDIAANIMATION_H
