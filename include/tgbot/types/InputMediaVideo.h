#ifndef TGBOT_INPUTMEDIAVIDEO_H
#define TGBOT_INPUTMEDIAVIDEO_H

#include "tgbot/types/InputMedia.h"
#include "tgbot/types/InputFile.h"

#include <memory>
#include <string>

namespace TgBot {

/**
 * @brief Represents a video to be sent.
 * 
 * @ingroup types
 */
class InputMediaVideo : public InputMedia {
public:
    static const std::string TYPE;

    typedef std::shared_ptr<InputMediaVideo> Ptr;

    InputMediaVideo() {
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
     * @brief Optional. Video width
     */
    std::int32_t width;

    /**
     * @brief Optional. Video height
     */
    std::int32_t height;

    /**
     * @brief Optional. Video duration in seconds
     */
    std::int32_t duration;

    /**
     * @brief Optional. Pass True if the uploaded video is suitable for streaming
     */
    bool supportsStreaming;

    /**
     * @brief Optional. Pass True if the video needs to be covered with a spoiler animation
     */
    bool hasSpoiler;
};
}

#endif //TGBOT_INPUTMEDIAVIDEO_H
