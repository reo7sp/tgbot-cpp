#ifndef TGBOT_CHATADMINISTRATORRIGHTS_H
#define TGBOT_CHATADMINISTRATORRIGHTS_H

#include <memory>

namespace TgBot {

/**
 * @brief Represents the rights of an administrator in a chat.
 *
 * @ingroup types
 */
class ChatAdministratorRights {

public:
    typedef std::shared_ptr<ChatAdministratorRights> Ptr;

    /**
     * @brief True, if the user's presence in the chat is hidden
     */
    bool isAnonymous;

    /**
     * @brief True, if the administrator can access the chat event log, boost list in channels, see channel members, report spam messages, see anonymous administrators in supergroups and ignore slow mode.
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
     * @brief True, if the administrator can restrict, ban or unban chat members, or access supergroup statistics
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
     * @brief Optional. True, if the administrator can post messages in the channel, or access channel statistics; channels only
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
     * @brief Optional. True, if the administrator can post stories in the channel; channels only
     */
    bool canPostStories;

    /**
     * @brief Optional. True, if the administrator can edit stories posted by other users; channels only
     */
    bool canEditStories;

    /**
     * @brief Optional. True, if the administrator can delete stories posted by other users; channels only
     */
    bool canDeleteStories;

    /**
     * @brief Optional. True, if the user is allowed to create, rename, close, and reopen forum topics; supergroups only
     */
    bool canManageTopics;
};
}

#endif //TGBOT_CHATADMINISTRATORRIGHTS_H
