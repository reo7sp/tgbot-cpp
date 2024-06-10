#ifndef TGBOT_INLINEQUERYRESULTCACHEDDOCUMENT_H
#define TGBOT_INLINEQUERYRESULTCACHEDDOCUMENT_H

#include "tgbot/types/InlineQueryResult.h"
#include "tgbot/types/MessageEntity.h"
#include "tgbot/types/InputMessageContent.h"

#include <memory>
#include <string>
#include <vector>

namespace TgBot {

/**
 * @brief Represents a link to a file stored on the Telegram servers.
 *
 * By default, this file will be sent by the user with an optional caption.
 * Alternatively, you can use inputMessageContent to send a message with the specified content instead of the file.
 *
 * @ingroup types
 */
class InlineQueryResultCachedDocument : public InlineQueryResult {

public:
    static const std::string TYPE;

    typedef std::shared_ptr<InlineQueryResultCachedDocument> Ptr;

    InlineQueryResultCachedDocument() {
        this->type = TYPE;
    }

    /**
     * @brief Title for the result
     */
    std::string title;

    /**
     * @brief A valid file identifier for the file
     */
    std::string documentFileId;

    /**
     * @brief Optional. Short description of the result
     */
    std::string description;

    /**
     * @brief Optional. Caption of the document to be sent, 0-1024 characters after entities parsing
     */
    std::string caption;

    /**
     * @brief Optional. Mode for parsing entities in the document caption.
     *
     * See [formatting options](https://core.telegram.org/bots/api#formatting-options) for more details.
     */
    std::string parseMode;

    /**
     * @brief Optional. List of special entities that appear in the caption, which can be specified instead of parseMode
     */
    std::vector<MessageEntity::Ptr> captionEntities;

    /**
     * @brief Optional. Content of the message to be sent instead of the file
     */
    InputMessageContent::Ptr inputMessageContent;
};
}

#endif //TGBOT_INLINEQUERYRESULTCACHEDDOCUMENT_H
