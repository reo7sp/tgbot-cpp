#ifndef TGBOT_INLINEQUERYRESULTPHOTO_H
#define TGBOT_INLINEQUERYRESULTPHOTO_H

#include "tgbot/types/InlineQueryResult.h"
#include "tgbot/types/MessageEntity.h"
#include "tgbot/types/InputMessageContent.h"

#include <cstdint>
#include <string>
#include <memory>
#include <vector>

namespace TgBot {

/**
 * @brief Represents a link to a photo.
 * By default, this photo will be sent by the user with optional caption. 
 * Alternatively, you can use inputMessageContent to send a message with the specified content instead of the photo.
 *
 * @ingroup types
 */
class InlineQueryResultPhoto : public InlineQueryResult {
public:
    static const std::string TYPE;

    typedef std::shared_ptr<InlineQueryResultPhoto> Ptr;

    InlineQueryResultPhoto() {
        this->type = TYPE;
    }

    /**
     * @brief A valid URL of the photo.
     * Photo must be in jpeg format.
     * Photo size must not exceed 5MB
     */
    std::string photoUrl;

    /**
     * @brief URL of the thumbnail for the photo
     */
    std::string thumbnailUrl;

    /**
     * @brief Optional. Width of the photo
     */
    std::int32_t photoWidth;

    /**
     * @brief Optional. Height of the photo
     */
    std::int32_t photoHeight;

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

#endif //TGBOT_INLINEQUERYRESULTPHOTO_H
