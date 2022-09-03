#ifndef TGBOT_INLINEQUERYRESULTCACHEDPHOTO_H
#define TGBOT_INLINEQUERYRESULTCACHEDPHOTO_H

#include "tgbot/types/InlineQueryResult.h"
#include "tgbot/types/MessageEntity.h"
#include "tgbot/types/InputMessageContent.h"

#include <string>
#include <memory>
#include <vector>

namespace TgBot {

/**
 * @brief Represents a link to a photo stored on the Telegram servers.
 * By default, this photo will be sent by the user with an optional caption.
 * Alternatively, you can use inputMessageContent to send a message with the specified content instead of the photo.
 *
 * @ingroup types
 */
class InlineQueryResultCachedPhoto : public InlineQueryResult {
public:
    static const std::string TYPE;

    typedef std::shared_ptr<InlineQueryResultCachedPhoto> Ptr;

    InlineQueryResultCachedPhoto() {
        this->type = TYPE;
    }

    /**
     * @brief A valid file identifier of the photo
     */
    std::string photoFileId;

    /**
     * @brief Optional. Title for the result
     */
    std::string title;

    /**
    * @brief Optional. Short description of the result
    */
    std::string description;

    /**
     * @brief Optional. Caption of the photo to be sent, 0-1024 characters after entities parsing
     */
    std::string caption;

    /**
     * @brief Optional. Mode for parsing entities in the photo caption.
     * See https://core.telegram.org/bots/api#formatting-options for more details.
     */
    std::string parseMode;

    /**
     * @brief Optional. List of special entities that appear in the caption, which can be specified instead of parseMode
     */
    std::vector<MessageEntity::Ptr> captionEntities;

    /**
     * @brief Optional. Content of the message to be sent instead of the photo
     */
    InputMessageContent::Ptr inputMessageContent;
};
}

#endif //TGBOT_INLINEQUERYRESULTCACHEDPHOTO_H
