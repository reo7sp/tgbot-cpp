#ifndef TGBOT_SENTWEBAPPMESSAGE_H
#define TGBOT_SENTWEBAPPMESSAGE_H

#include <memory>
#include <string>

namespace TgBot {

/**
 * @brief Contains information about an inline message sent by a Web App on behalf of a user.
 *
 * @ingroup types
 */
class SentWebAppMessage {
public:
    typedef std::shared_ptr<SentWebAppMessage> Ptr;

    /**
     * @brief Optional. Identifier of the sent inline message.
     * Available only if there is an inline keyboard attached to the message.
     */
    std::string inlineMessageId;
};
}

#endif //TGBOT_SENTWEBAPPMESSAGE_H
