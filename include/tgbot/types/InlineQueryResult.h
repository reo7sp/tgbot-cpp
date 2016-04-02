//
// Created by Andrea Giove on 26/03/16.
//

#ifndef TGBOT_INLINEQUERYRESULT_H
#define TGBOT_INLINEQUERYRESULT_H

#include <memory>
#include <string>

namespace TgBot {

/**
 * This abstract class is base of all inline query results.
 * @ingroup types
 */
class InlineQueryResult {
public:
    typedef std::shared_ptr<InlineQueryResult> Ptr;

    InlineQueryResult() {
        this->disableWebPagePreview = false;
    }

    virtual ~InlineQueryResult() { }

    /**
     * Type of the result.
     */
    std::string type;

    /**
     * Unique identifier for this result. (1-64 bytes)
     */
    std::string id;

    /**
     * Optional. Title of the result.
     */
    std::string title;

    /**
     * Text of the message t be sent. (1-4096 characters)
     */
    std::string messageText;

    /**
     * Optional. Send Markdown or HTML, if you want Telegram apps to
     * show bold, italic, fixed-width text or inline URLs in your bot's message.
     */
    std::string parseMode;

    /**
     * Optional. Disables link previews for links in the send message.
     */
    bool disableWebPagePreview;

    /**
     * Optional. Url of the thumbnail for the result.
     */
    std::string thumbUrl;

};
}

#endif //TGBOT_INLINEQUERYRESULT_H
