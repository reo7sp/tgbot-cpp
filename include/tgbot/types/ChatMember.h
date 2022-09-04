#ifndef TGBOT_CHATMEMBER_H
#define TGBOT_CHATMEMBER_H

#include "tgbot/types/User.h"

#include <cstdint>
#include <memory>
#include <string>

namespace TgBot {

/**
 * @brief This object contains information about one member of the chat.
 *
 * @ingroup types
 */
class ChatMember {

public:
    typedef std::shared_ptr<ChatMember> Ptr;

    /**
     * @brief Information about the user
     */
    User::Ptr user;

    /**
     * @brief The member's status in the chat.
     * Can be “creator”, “administrator”, “member”, “restricted”, “left” or “kicked”
     */
    std::string status;

    /**
     * @brief Optional. Owner and administrators only. Custom title for this user
     */
    std::string customTitle;

    /**
     * @brief Optional. Owner and administrators only. True, if the user's presence in the chat is hidden
     */
    bool isAnonymous;

    /**
     * @brief Optional. Administrators only. True, if the bot is allowed to edit administrator privileges of that user
     */
    bool canBeEdited;

    /**
     * @brief Optional. Administrators only. True, if the administrator can access the chat event log, chat statistics, message statistics in channels, see channel members, see anonymous administrators in supergroups and ignore slow mode.
     * Implied by any other administrator privilege
     */
    bool canManageChat;

    /**
     * @brief Optional. Administrators only. True, if the administrator can post in the channel; channels only
     */
    bool canPostMessages;

    /**
     * @brief Optional. Administrators only. True, if the administrator can edit messages of other users and can pin messages; channels only
     */
    bool canEditMessages;

    /**
     * @brief Optional. Administrators only. True, if the administrator can delete messages of other users
     */
    bool canDeleteMessages;

    /**
     * @brief Optional. Administrators only. True, if the administrator can manage voice chats
     */
    bool canManageVoiceChats;

    /**
     * @brief Optional. Administrators only. True, if the administrator can restrict, ban or unban chat members
     */
    bool canRestrictMembers;

    /**
     * @brief Optional. Administrators only. True, if the administrator can add new administrators with a subset of his own privileges or demote administrators that he has promoted, directly or indirectly (promoted by administrators that were appointed by the user)
     */
    bool canPromoteMembers;

    /**
     * @brief Optional. Administrators and restricted only. True, if the user is allowed to change the chat title, photo and other settings
     */
    bool canChangeInfo;

    /**
     * @brief Optional. Administrators and restricted only. True, if the user is allowed to invite new users to the chat
     */
    bool canInviteUsers;

    /**
     * @brief Optional. Administrators and restricted only. True, if the user is allowed to pin messages; groups and supergroups only
     */
    bool canPinMessages;

    /**
     * @brief Optional. Restricted only. True, if the user is a member of the chat at the moment of the request
     */
    bool isMember;

    /**
     * @brief Optional. Restricted only. True, if the user is allowed to send text messages, contacts, locations and venues
     */
    bool canSendMessages;

    /**
     * @brief Optional. Restricted only. True, if the user is allowed to send audios, documents, photos, videos, video notes and voice notes
     */
    bool canSendMediaMessages;

    /**
     * @brief Optional. Restricted only. True, if the user is allowed to send polls
     */
    bool canSendPolls;

    /**
     * @brief Optional. Restricted only. True, if the user is allowed to send animations, games, stickers and use inline bots
     */
    bool canSendOtherMessages;

    /**
     * @brief Optional. Restricted only. True, if the user is allowed to add web page previews to their messages
     */
    bool canAddWebPagePreviews;

    /**
     * @brief Optional. Restricted and kicked only. Date when restrictions will be lifted for this user; unix time
     */
    std::uint64_t untilDate;
};
}

#endif //TGBOT_CHATMEMBER_H
