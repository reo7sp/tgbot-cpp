#ifndef TGBOT_MESSAGEORIGINCHANNEL_H
#define TGBOT_MESSAGEORIGINCHANNEL_H

#include "tgbot/types/MessageOrigin.h"
#include "tgbot/types/Chat.h"

#include <cstdint>
#include <memory>
#include <string>

namespace TgBot {

/**
 * @brief The message was originally sent to a channel chat.
 *
 * @ingroup types
 */
class MessageOriginChannel : public MessageOrigin {

public:
    static const std::string TYPE;

    typedef std::shared_ptr<MessageOriginChannel> Ptr;

    MessageOriginChannel() {
        this->type = TYPE;
    }

    /**
     * @brief Channel chat to which the message was originally sent
     */
    Chat::Ptr chat;

    /**
     * @brief Unique message identifier inside the chat
     */
    std::int32_t messageId;

    /**
     * @brief Optional. Signature of the original post author
     */
    std::string authorSignature;
};
}

#endif //TGBOT_MESSAGEORIGINCHANNEL_H
