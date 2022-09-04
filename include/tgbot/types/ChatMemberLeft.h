#ifndef TGBOT_CHATMEMBERLEFT_H
#define TGBOT_CHATMEMBERLEFT_H

#include "tgbot/types/ChatMember.h"

#include <memory>

namespace TgBot {

/**
 * @brief Represents a chat member that isn't currently a member of the chat, but may join it themselves.
 *
 * @ingroup types
 */
class ChatMemberLeft : public ChatMember {
public:
    static const std::string STATUS;

    typedef std::shared_ptr<ChatMemberLeft> Ptr;

    ChatMemberLeft() {
        this->status = STATUS;
    }
};
}

#endif //TGBOT_CHATMEMBERLEFT_H
