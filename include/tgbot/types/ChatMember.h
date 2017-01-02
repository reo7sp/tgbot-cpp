//
// Created by Konstantin Kukin on 26/12/16.
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
	 * The member's status in the chat. Can be “creator”, “administrator”, “member”, “left” or “kicked”
	 */
	std::string status;
};
}

#endif //TGBOT_CHATMEMBER_H
