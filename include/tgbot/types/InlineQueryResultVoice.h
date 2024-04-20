#ifndef TGBOT_INLINEQUERYRESULTVOICE_H
#define TGBOT_INLINEQUERYRESULTVOICE_H

#include "tgbot/types/InlineQueryResult.h"
#include "tgbot/types/MessageEntity.h"
#include "tgbot/types/InputMessageContent.h"

#include <cstdint>
#include <memory>
#include <string>
#include <vector>

namespace TgBot {

/**
 * @brief Represents a link to a voice recording in an .OGG container encoded with OPUS.
 *
 * By default, this voice recording will be sent by the user.
 * Alternatively, you can use inputMessageContent to send a message with the specified content instead of the the voice message.
 *
 * @ingroup types
 */
class InlineQueryResultVoice : public InlineQueryResult {

public:
    static const std::string TYPE;

    typedef std::shared_ptr<InlineQueryResultVoice> Ptr;

    InlineQueryResultVoice() {
        this->type = TYPE;
    };

    /**
     * @brief A valid URL for the voice recording
     */
    std::string voiceUrl;

    /**
     * @brief Recording title
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
     * @brief Optional. Recording duration in seconds
     */
    std::int32_t voiceDuration;

    /**
     * @brief Optional. Content of the message to be sent instead of the voice recording
     */
    InputMessageContent::Ptr inputMessageContent;
};
}

#endif //TGBOT_INLINEQUERYRESULTVOICE_H
