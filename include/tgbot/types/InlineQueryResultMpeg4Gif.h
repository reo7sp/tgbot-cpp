#ifndef TGBOT_INLINEQUERYRESULTMPEG4GIF_H
#define TGBOT_INLINEQUERYRESULTMPEG4GIF_H

#include <cstdint>
#include <memory>
#include <string>

namespace TgBot {

/**
 * @brief Represents a link to a video animation (H.264/MPEG-4 AVC video without sound).
 * By default, this animated MPEG-4 file will be sent by the user with optional caption.
 * Alternatively, you can use @ref InlineQueryResult::inputMessageContent to send a message with the specified content instead of the animation.
 *
 * @ingroup types
 */
class InlineQueryResultMpeg4Gif : public InlineQueryResult {
public:
    static const std::string TYPE;

    typedef std::shared_ptr<InlineQueryResultMpeg4Gif> Ptr;

    InlineQueryResultMpeg4Gif() {
        this->type = TYPE;
        this->mpeg4Width = 0;
        this->mpeg4Height = 0;
    }

    /**
     * @brief A valid URL for the MP4 file.
     * File size must not exceed 1MB
     */
    std::string mpeg4Url;

    /**
     * @brief Optional. Video width
     */
    std::int32_t mpeg4Width;

    /**
     * @brief Optional. Video height
     */
    std::int32_t mpeg4Height;

    /**
     * @brief Optional. Video duration
     */
    std::int32_t mpeg4Duration;

    /**
    * @brief URL of the static (JPEG or GIF) or animated (MPEG4) thumbnail for the result
    */
    std::string thumbUrl;

    /**
    * @brief Optional. MIME type of the thumbnail, must be one of “image/jpeg”, “image/gif”, or “video/mp4”.
    * Defaults to “image/jpeg”
    */
    std::string thumbMimeType;
};
}

#endif //TGBOT_INLINEQUERYRESULTMPEG4GIF_H
