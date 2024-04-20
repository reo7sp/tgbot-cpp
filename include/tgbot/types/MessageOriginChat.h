#ifndef TGBOT_MESSAGEORIGINCHAT_H
#define TGBOT_MESSAGEORIGINCHAT_H

#include "tgbot/types/MessageOrigin.h"
#include "tgbot/types/Chat.h"

#include <memory>
#include <string>

namespace TgBot {

/**
 * @brief The message was originally sent on behalf of a chat to a group chat.
 *
 * @ingroup types
 */
class MessageOriginChat : public MessageOrigin {

public:
    static const std::string TYPE;

    typedef std::shared_ptr<MessageOriginChat> Ptr;

    MessageOriginChat() {
        this->type = TYPE;
    }

    /**
     * @brief Chat that sent the message originally
     */
    Chat::Ptr senderChat;

    /**
     * @brief Optional. For messages originally sent by an anonymous chat administrator, original message author signature
     */
    std::string authorSignature;
};
}

#endif //TGBOT_MESSAGEORIGINCHAT_H
