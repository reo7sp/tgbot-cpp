#ifndef TGBOT_INLINEQUERYRESULTGIF_H
#define TGBOT_INLINEQUERYRESULTGIF_H

#include "tgbot/types/InlineQueryResult.h"

#include <cstdint>
#include <string>
#include <memory>

namespace TgBot {

/**
 * @brief Represents a link to an animated GIF file.
 * By default, this animated GIF file will be sent by the user with optional caption.
 * Alternatively, you can use @ref InlineQueryResult::inputMessageContent to send a message with the specified content instead of the animation.
 *
 * @ingroup types
 */
class InlineQueryResultGif : public InlineQueryResult {
public:
    static const std::string TYPE;

    typedef std::shared_ptr<InlineQueryResultGif> Ptr;

    InlineQueryResultGif() {
        this->type = TYPE;
        this->gifWidth = 0;
        this->gifHeight = 0;
    }

    /**
     * @brief A valid URL for the GIF file. File size must not exceed 1MB
     */
    std::string gifUrl;

    /**
     * @brief Optional. Width of the GIF
     */
    std::int32_t gifWidth;

    /**
     * @brief Optional. Height of the GIF
     */
    std::int32_t gifHeight;

    /**
     * @brief Optional. Duration of the GIF
     */
    std::int32_t gifDuration;

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

#endif //TGBOT_INLINEQUERYRESULTGIF_H
