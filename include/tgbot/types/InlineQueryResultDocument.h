#ifndef TGBOT_INLINEQUERYRESULTDOCUMENT_H
#define TGBOT_INLINEQUERYRESULTDOCUMENT_H

#include "tgbot/types/InlineQueryResult.h"
#include "tgbot/types/MessageEntity.h"
#include "tgbot/types/InputMessageContent.h"

#include <cstdint>
#include <memory>
#include <string>
#include <vector>

namespace TgBot {

/**
 * @brief Represents a link to a file.
 *
 * By default, this file will be sent by the user with an optional caption.
 * Alternatively, you can use inputMessageContent to send a message with the specified content instead of the file.
 * Currently, only .PDF and .ZIP files can be sent using this method.
 *
 * @ingroup types
 */
class InlineQueryResultDocument : public InlineQueryResult {

public:
    static const std::string TYPE;

    typedef std::shared_ptr<InlineQueryResultDocument> Ptr;

    InlineQueryResultDocument() {
        this->type = TYPE;
    }

    /**
     * @brief Title for the result
     */
    std::string title;

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
     * @brief A valid URL for the file
     */
    std::string documentUrl;

    /**
     * @brief MIME type of the content of the file, either “application/pdf” or “application/zip”
     */
    std::string mimeType;

    /**
     * @brief Optional. Short description of the result
     */
    std::string description;

    /**
     * @brief Optional. Content of the message to be sent instead of the file
     */
    InputMessageContent::Ptr inputMessageContent;

    /**
     * @brief Optional. URL of the thumbnail (JPEG only) for the file
     */
    std::string thumbnailUrl;

    /**
     * @brief Optional. Thumbnail width
     */
    std::int32_t thumbnailWidth;

    /**
     * @brief Optional. Thumbnail height
     */
    std::int32_t thumbnailHeight;
};
}

#endif //TGBOT_INLINEQUERYRESULTDOCUMENT_H
