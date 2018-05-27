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
 * This object contains information about one member of the chat.
 * @ingroup types
 */
class ChatMember {
public:
	typedef std::shared_ptr<ChatMember> Ptr;

	/**
	 * Information about the user
	 */
	User::Ptr user;

	/**
	 * The member's status in the chat. Can be “creator”, “administrator”, “member”, “restricted”, “left” or “kicked”
	 */
	std::string status;

	/**
	 * Optional. Restricted and kicked only. Date when restrictions will be lifted for this user, unix time.
	 */
	uint64_t untilDate;

	/**
	 * Optional. Administrators only. True, if the bot is allowed to edit administrator privileges of that user.
	 */
	bool canBeEdited = false;

	/**
	 * Optional. Administrators only. True, if the administrator can change the chat title, photo and other settings.
	 */
	bool canChangeInfo = false;

	/**
	 * Optional. Administrators only. True, if the administrator can post in the channel, channels only.
	 */
	bool canPostMessages = false;

	/**
	 * Optional. Administrators only. True, if the administrator can edit messages of other users and can pin messages, channels only.
	 */
	bool canEditMessages = false;

	/**
	 * Optional. Administrators only. True, if the administrator can delete messages of other users.
	 */
	bool canDeleteMessages = false;

	/**
	 * Optional. Administrators only. True, if the administrator can invite new users to the chat.
	 */
	bool canInviteUsers = false;

	/**
	 * Optional. Administrators only. True, if the administrator can restrict, ban or unban chat members.
	 */
	bool canRestrictMembers = false;

	/**
	 * Optional. Administrators only. True, if the administrator can pin messages, supergroups only.
	 */
	bool canPinMessages = false;

	/**
	 * Optional. Administrators only. True, if the administrator can add new administrators with a subset of his own privileges or demote administrators that he has promoted, directly or indirectly (promoted by administrators that were appointed by the user).
	 */
	bool canPromoteMembers = false;

	/**
	 * Optional. Restricted only. True, if the user can send text messages, contacts, locations and venues.
	 */
	bool canSendMessages = false;

	/**
	 * Optional. Restricted only. True, if the user can send audios, documents, photos, videos, video notes and voice notes, implies can_send_messages.
	 */
	bool canSendMediaMessages = false;

	/**
	 * Optional. Restricted only. True, if the user can send animations, games, stickers and use inline bots, implies can_send_media_messages.
	 */
	bool canSendOtherMessages = false;

	/**
	 * Optional. Restricted only. True, if user may add web page previews to his messages, implies can_send_media_messages.
	 */
	bool canAddWebPagePreviews = false;
};
}

#endif //TGBOT_CHATMEMBER_H
