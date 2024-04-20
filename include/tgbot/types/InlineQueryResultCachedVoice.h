#ifndef TGBOT_INLINEQUERYRESULTCACHEDVOICE_H
#define TGBOT_INLINEQUERYRESULTCACHEDVOICE_H

#include "tgbot/types/InlineQueryResult.h"
#include "tgbot/types/MessageEntity.h"
#include "tgbot/types/InputMessageContent.h"

#include <memory>
#include <string>
#include <vector>

namespace TgBot {

/**
 * @brief Represents a link to a voice message stored on the Telegram servers.
 *
 * By default, this voice message will be sent by the user.
 * Alternatively, you can use inputMessageContent to send a message with the specified content instead of the voice message.
 *
 * @ingroup types
 */
class InlineQueryResultCachedVoice : public InlineQueryResult {

public:
    static const std::string TYPE;

    typedef std::shared_ptr<InlineQueryResultCachedVoice> Ptr;

    InlineQueryResultCachedVoice() {
        this->type = TYPE;
    }

    /**
     * @brief A valid file identifier for the voice message
     */
    std::string voiceFileId;

    /**
     * @brief Voice message title
     */
    std::string title;

    /**
     * @brief Optional. Caption, 0-1024 characters after entities parsing
     */
    std::string caption;

    /**
     * @brief Optional. Mode for parsing entities in the voice message caption.
     *
     * See [formatting options](https://core.telegram.org/bots/api#formatting-options) for more details.
     */
    std::string parseMode;

    /**
     * @brief Optional. List of special entities that appear in the caption, which can be specified instead of parseMode
     */
    std::vector<MessageEntity::Ptr> captionEntities;

    /**
     * @brief Optional. Content of the message to be sent instead of the voice message
     */
    InputMessageContent::Ptr inputMessageContent;
};
}

#endif //TGBOT_INLINEQUERYRESULTCACHEDVOICE_H
