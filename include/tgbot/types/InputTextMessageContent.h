#ifndef TGBOT_INPUTTEXTMESSAGECONTENT_H
#define TGBOT_INPUTTEXTMESSAGECONTENT_H

#include "tgbot/types/InputMessageContent.h"
#include "tgbot/types/MessageEntity.h"
#include "tgbot/types/LinkPreviewOptions.h"

#include <memory>
#include <string>
#include <vector>

namespace TgBot {

/**
 * @brief Represents the [content](https://core.telegram.org/bots/api#inputmessagecontent) of a text message to be sent as the result of an inline query.
 *
 * @ingroup types
 */
class InputTextMessageContent : public InputMessageContent {

public:
    static const std::string TYPE;

    typedef std::shared_ptr<InputTextMessageContent> Ptr;

    InputTextMessageContent() {
        this->type = TYPE;
    }

    /**
     * @brief Text of the message to be sent, 1-4096 characters
     */
    std::string messageText;

    /**
     * @brief Optional. Mode for parsing entities in the message text.
     *
     * See [formatting options](https://core.telegram.org/bots/api#formatting-options) for more details.
     */
    std::string parseMode;

    /**
     * @brief Optional. List of special entities that appear in message text, which can be specified instead of parseMode
     */
    std::vector<MessageEntity::Ptr> entities;

    /**
     * @brief Optional. Link preview generation options for the message
     */
    LinkPreviewOptions::Ptr linkPreviewOptions;
};
}

#endif //TGBOT_INPUTTEXTMESSAGECONTENT_H
