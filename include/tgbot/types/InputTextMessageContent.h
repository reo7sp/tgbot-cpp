//
// Created by Konstantin Kukin on 26/12/16.
//

#ifndef TGBOT_INPUTTEXTMESSAGECONTENT_H
#define TGBOT_INPUTTEXTMESSAGECONTENT_H

#include <memory>
#include <string>

namespace TgBot {

/**
 * @brief Represents the content of a text message to be sent as the result of an inline query.
 * 
 * @ingroup types
 */
class InputTextMessageContent : public InputMessageContent {
public:
    typedef std::shared_ptr<InputTextMessageContent> Ptr;

    InputTextMessageContent():
        InputMessageContent("InputTextMessageContent")
    {}

    /**
     * @brief Text of the message to be sent, 1-4096 characters
     */
    std::string messageText;

    /**
     * @brief Optional. Send Markdown or HTML, if you want Telegram apps to show bold, italic, fixed-width text or inline URLs in your bot's message.
     */
    std::string parseMode;

    /**
     * @brief Optional. Disables link previews for links in the sent message
     */
    bool disableWebPagePreview;

    virtual ~InputTextMessageContent() { }
};
}

#endif //TGBOT_INPUTTEXTMESSAGECONTENT_H
