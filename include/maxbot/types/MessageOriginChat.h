#ifndef MAXBOT_MESSAGEORIGINCHAT_H
#define MAXBOT_MESSAGEORIGINCHAT_H

#include "maxbot/types/MessageOrigin.h"
#include "maxbot/types/Chat.h"

#include <memory>
#include <string>

namespace MaxBot {

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

#endif //MAXBOT_MESSAGEORIGINCHAT_H
