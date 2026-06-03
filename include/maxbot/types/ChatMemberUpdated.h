#ifndef MAXBOT_CHATMEMBERUPDATED_H
#define MAXBOT_CHATMEMBERUPDATED_H

#include "maxbot/types/Chat.h"
#include "maxbot/types/User.h"
#include "maxbot/types/ChatMember.h"
#include "maxbot/types/ChatInviteLink.h"

#include <cstdint>
#include <memory>

namespace MaxBot {

/**
 * @brief This object represents changes in the status of a chat member.
 *
 * @ingroup types
 */
class ChatMemberUpdated {

public:
    typedef std::shared_ptr<ChatMemberUpdated> Ptr;

    /**
     * @brief Chat the user belongs to
     */
    Chat::Ptr chat;

    /**
     * @brief Performer of the action, which resulted in the change
     */
    User::Ptr from;

    /**
     * @brief Date the change was done in Unix time
     */
    std::uint32_t date;

    /**
     * @brief Previous information about the chat member
     */
    ChatMember::Ptr oldChatMember;

    /**
     * @brief New information about the chat member
     */
    ChatMember::Ptr newChatMember;

    /**
     * @brief Optional. Chat invite link, which was used by the user to join the chat; for joining by invite link events only.
     */
    ChatInviteLink::Ptr inviteLink;

    /**
     * @brief Optional. True, if the user joined the chat via a chat folder invite link
     */
    bool viaChatFolderInviteLink;
};
}

#endif //MAXBOT_CHATMEMBERUPDATED_H
