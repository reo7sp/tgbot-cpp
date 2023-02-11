#ifndef TGBOT_CHATMEMBERADMINISTRATOR_H
#define TGBOT_CHATMEMBERADMINISTRATOR_H

#include "tgbot/types/ChatMember.h"

#include <memory>
#include <string>

namespace TgBot {

/**
 * @brief Represents a chat member that has some additional privileges.
 *
 * @ingroup types
 */
class ChatMemberAdministrator : public ChatMember {
public:
    static const std::string STATUS;

    typedef std::shared_ptr<ChatMemberAdministrator> Ptr;

    ChatMemberAdministrator() {
        this->status = STATUS;
    }

    /**
     * @brief True, if the bot is allowed to edit administrator privileges of that user
     */
    bool canBeEdited;

    /**
     * @brief True, if the user's presence in the chat is hidden
     */
    bool isAnonymous;

    /**
     * @brief True, if the administrator can access the chat event log, chat statistics, message statistics in channels, see channel members, see anonymous administrators in supergroups and ignore slow mode.
     * 
     * Implied by any other administrator privilege
     */
    bool canManageChat;

    /**
     * @brief True, if the administrator can delete messages of other users
     */
    bool canDeleteMessages;

    /**
     * @brief True, if the administrator can manage video chats
     */
    bool canManageVideoChats;

    /**
     * @brief True, if the administrator can restrict, ban or unban chat members
     */
    bool canRestrictMembers;

    /**
     * @brief True, if the administrator can add new administrators with a subset of their own privileges or demote administrators that they have promoted, directly or indirectly (promoted by administrators that were appointed by the user)
     */
    bool canPromoteMembers;

    /**
     * @brief True, if the user is allowed to change the chat title, photo and other settings
     */
    bool canChangeInfo;

    /**
     * @brief True, if the user is allowed to invite new users to the chat
     */
    bool canInviteUsers;

    /**
     * @brief Optional. True, if the administrator can post in the channel; channels only
     */
    bool canPostMessages;

    /**
     * @brief Optional. True, if the administrator can edit messages of other users and can pin messages; channels only
     */
    bool canEditMessages;

    /**
     * @brief Optional. True, if the user is allowed to pin messages; groups and supergroups only
     */
    bool canPinMessages;

    /**
     * @brief Optional. True, if the user is allowed to create, rename, close, and reopen forum topics; supergroups only
     */
    bool canManageTopics;

    /**
     * @brief Optional. Custom title for this user
     */
    std::string customTitle;
};
}

#endif //TGBOT_CHATMEMBERADMINISTRATOR_H
