#ifndef TGBOT_INLINEQUERYRESULTCACHEDGIF_H
#define TGBOT_INLINEQUERYRESULTCACHEDGIF_H

#include "tgbot/types/InlineQueryResult.h"
#include "tgbot/types/MessageEntity.h"
#include "tgbot/types/InputMessageContent.h"

#include <string>
#include <memory>
#include <vector>

namespace TgBot {

/**
 * @brief Represents a link to an animated GIF file stored on the Telegram servers.
 * By default, this animated GIF file will be sent by the user with an optional caption.
 * Alternatively, you can use inputMessageContent to send a message with specified content instead of the animation.
 *
 * @ingroup types
 */
class InlineQueryResultCachedGif : public InlineQueryResult {
public:
    static const std::string TYPE;

    typedef std::shared_ptr<InlineQueryResultCachedGif> Ptr;

    InlineQueryResultCachedGif() {
        this->type = TYPE;
    }

    /**
     * @brief A valid file identifier for the GIF file
     */
    std::string gifFileId;

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

#endif //TGBOT_INLINEQUERYRESULTCACHEDGIF_H
