#ifndef TGBOT_INLINEQUERYRESULTCACHEDMPEG4GIF_H
#define TGBOT_INLINEQUERYRESULTCACHEDMPEG4GIF_H

#include "tgbot/types/InlineQueryResult.h"
#include "tgbot/types/MessageEntity.h"
#include "tgbot/types/InputMessageContent.h"

#include <string>
#include <memory>
#include <vector>

namespace TgBot {

/**
 * @brief Represents a link to a video animation (H.264/MPEG-4 AVC video without sound) stored on the Telegram servers.
 * By default, this animated MPEG-4 file will be sent by the user with an optional caption. 
 * Alternatively, you can use inputMessageContent to send a message with the specified content instead of the animation.
 *
 * @ingroup types
 */
class InlineQueryResultCachedMpeg4Gif : public InlineQueryResult {
public:
    static const std::string TYPE;

    typedef std::shared_ptr<InlineQueryResultCachedMpeg4Gif> Ptr;

    InlineQueryResultCachedMpeg4Gif() {
        this->type = TYPE;
    }

    /**
     * @brief A valid file identifier for the MP4 file
     */
    std::string mpeg4FileId;

    /**
     * @brief Optional. Title for the result
     */
    std::string title;

    /**
     * @brief Optional. Caption of the MPEG-4 file to be sent, 0-1024 characters after entities parsing
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
     * @brief Optional. Content of the message to be sent instead of the video animation
     */
    InputMessageContent::Ptr inputMessageContent;
};
}

#endif //TGBOT_INLINEQUERYRESULTCACHEDMPEG4GIF_H
