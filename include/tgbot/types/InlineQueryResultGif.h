#ifndef TGBOT_INLINEQUERYRESULTGIF_H
#define TGBOT_INLINEQUERYRESULTGIF_H

#include "tgbot/types/InlineQueryResult.h"
#include "tgbot/types/MessageEntity.h"
#include "tgbot/types/InputMessageContent.h"

#include <cstdint>
#include <string>
#include <memory>
#include <vector>

namespace TgBot {

/**
 * @brief Represents a link to an animated GIF file.
 * By default, this animated GIF file will be sent by the user with optional caption.
 * Alternatively, you can use inputMessageContent to send a message with the specified content instead of the animation.
 *
 * @ingroup types
 */
class InlineQueryResultGif : public InlineQueryResult {
public:
    static const std::string TYPE;

    typedef std::shared_ptr<InlineQueryResultGif> Ptr;

    InlineQueryResultGif() {
        this->type = TYPE;
    }

    /**
     * @brief A valid URL for the GIF file.
     * File size must not exceed 1MB
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
    std::string thumbnailUrl;

    /**
     * @brief Optional. MIME type of the thumbnail, must be one of “image/jpeg”, “image/gif”, or “video/mp4”.
     * Defaults to “image/jpeg”
     */
    std::string thumbnailMimeType;

    /**
     * @brief Optional. Title for the result
     */
    std::string title;

    /**
     * @brief Optional. Caption of the GIF file to be sent, 0-1024 characters after entities parsing
     */
    std::string caption;

    /**
     * @brief Optional. Mode for parsing entities in the caption.
     * See https://core.telegram.org/bots/api#formatting-options for more details.
     */
    std::string parseMode;

    /**
     * @brief Optional. List of special entities that appear in the caption, which can be specified instead of parseMode
     */
    std::vector<MessageEntity::Ptr> captionEntities;

    /**
     * @brief Optional. Content of the message to be sent instead of the GIF animation
     */
    InputMessageContent::Ptr inputMessageContent;
};
}

#endif //TGBOT_INLINEQUERYRESULTGIF_H
