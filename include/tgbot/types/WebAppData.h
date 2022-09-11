#ifndef TGBOT_WEBAPPDATA_H
#define TGBOT_WEBAPPDATA_H

#include <memory>
#include <string>

namespace TgBot {

/**
 * @brief Contains data sent from a Web App to the bot.
 *
 * @ingroup types
 */
class WebAppData {
public:
    typedef std::shared_ptr<WebAppData> Ptr;

    /**
     * @brief The data.
     * Be aware that a bad client can send arbitrary data in this field.
     */
    std::string data;

    /**
     * @brief Text of the webApp keyboard button, from which the Web App was opened.
     * Be aware that a bad client can send arbitrary data in this field.
     */
    std::string buttonText;
};
}

#endif //TGBOT_WEBAPPMESSAGE_H
