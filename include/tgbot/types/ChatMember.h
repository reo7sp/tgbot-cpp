//
// Created by Konstantin Kukin on 26/12/16.
// Edit by JellyBrick on 27/05/18.
//

#ifndef TGBOT_CHATMEMBER_H
#define TGBOT_CHATMEMBER_H

#include <memory>
#include <string>

#include "tgbot/types/User.h"

namespace TgBot {

/**
 * @brief This object contains information about one member of the chat.
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
     * @brief The member's status in the chat. Can be “creator”, “administrator”, “member”, “restricted”, “left” or “kicked”
     */
    std::string status;

    /**
     * @brief Optional. Restricted and kicked only. Date when restrictions will be lifted for this user, unix time.
     */
    uint64_t untilDate;

    /**
     * @brief Optional. Administrators only. True, if the bot is allowed to edit administrator privileges of that user.
     */
    bool canBeEdited = false;

    /**
     * @brief Optional. Administrators only. True, if the administrator can change the chat title, photo and other settings.
     */
    bool canChangeInfo = false;

    /**
     * @brief Optional. Administrators only. True, if the administrator can post in the channel, channels only.
     */
    bool canPostMessages = false;

    /**
     * @brief Optional. Administrators only. True, if the administrator can edit messages of other users and can pin messages, channels only.
     */
    bool canEditMessages = false;

    /**
     * @brief Optional. Administrators only. True, if the administrator can delete messages of other users.
     */
    bool canDeleteMessages = false;

    /**
     * @brief Optional. Administrators only. True, if the administrator can invite new users to the chat.
     */
    bool canInviteUsers = false;

    /**
     * @brief Optional. Administrators only. True, if the administrator can restrict, ban or unban chat members.
     */
    bool canRestrictMembers = false;

    /**
     * @brief Optional. Administrators only. True, if the administrator can pin messages, supergroups only.
     */
    bool canPinMessages = false;

    /**
     * @brief Optional. Administrators only. True, if the administrator can add new administrators with a subset of his own privileges or demote administrators that he has promoted, directly or indirectly (promoted by administrators that were appointed by the user).
     */
    bool canPromoteMembers = false;

    /**
     * @brief Optional. Restricted only. True, if the user can send text messages, contacts, locations and venues.
     */
    bool canSendMessages = false;

    /**
     * @brief Optional. Restricted only. True, if the user can send audios, documents, photos, videos, video notes and voice notes, implies can_send_messages.
     */
    bool canSendMediaMessages = false;

    /**
     * @brief Optional. Restricted only. True, if the user can send animations, games, stickers and use inline bots, implies can_send_media_messages.
     */
    bool canSendOtherMessages = false;

    /**
     * @brief Optional. Restricted only. True, if user may add web page previews to his messages, implies can_send_media_messages.
     */
    bool canAddWebPagePreviews = false;
};
}

#endif //TGBOT_CHATMEMBER_H
