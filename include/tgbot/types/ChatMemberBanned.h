#ifndef TGBOT_CHATMEMBERBANNED_H
#define TGBOT_CHATMEMBERBANNED_H

#include "tgbot/types/ChatMember.h"

#include <cstdint>
#include <memory>

namespace TgBot {

/**
 * @brief Represents a chat member that was banned in the chat and can't return to the chat or view chat messages.
 *
 * @ingroup types
 */
class ChatMemberBanned : public ChatMember {
public:
    static const std::string STATUS;

    typedef std::shared_ptr<ChatMemberBanned> Ptr;

    ChatMemberBanned() {
        this->status = STATUS;
    }

    /**
     * @brief Date when restrictions will be lifted for this user; Unix time.
     * 
     * If 0, then the user is banned forever
     */
    std::uint32_t untilDate;
};
}

#endif //TGBOT_CHATMEMBERBANNED_H
