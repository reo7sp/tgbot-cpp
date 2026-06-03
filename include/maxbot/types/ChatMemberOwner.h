#ifndef MAXBOT_CHATMEMBEROWNER_H
#define MAXBOT_CHATMEMBEROWNER_H

#include "maxbot/types/ChatMember.h"

#include <memory>
#include <string>

namespace MaxBot {

/**
 * @brief Represents a chat member that owns the chat and has all administrator privileges.
 *
 * @ingroup types
 */
class ChatMemberOwner : public ChatMember {
public:
    static const std::string STATUS;

    typedef std::shared_ptr<ChatMemberOwner> Ptr;

    ChatMemberOwner() {
        this->status = STATUS;
    }

    /**
     * @brief Custom title for this user
     */
    std::string customTitle;

    /**
     * @brief True, if the user's presence in the chat is hidden
     */
    bool isAnonymous;
};
}

#endif //MAXBOT_CHATMEMBEROWNER_H
