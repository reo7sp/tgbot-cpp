//
// Created by Andrea Giove on 17/04/16.
//

#ifndef TGBOT_MESSAGEENTITY_H
#define TGBOT_MESSAGEENTITY_H

#include <memory>
#include <string>
#include "tgbot/types/User.h"

namespace TgBot {

/**
 * This object represents one special entity in a text message. For example, hashtags, usernames, URLs, etc.
 * @ingroup types
 */
class MessageEntity {
public:
	typedef std::shared_ptr<MessageEntity> Ptr;

	/**
	 * Type of the entity. One of mention (@username), hashtag, bot_command, url, email, bold (bold text), italic (italic text), code (monowidth string), pre (monowidth block), text_link (for clickable text URLs).
	 */
	std::string type;

	/**
	 * Offset in UTF-16 code units to the start of the entity.
	 */
	int32_t offset;

	/**
	 * Length of the entity in UTF-16 code units
	 */
	int32_t length;

	/**
	 * Optional. For “text_link” only, url that will be opened after user taps on the text
	 */
	std::string url;

	/**
	 * Optional. For “text_mention” only, the mentioned user
	 */
	User::Ptr user;
};
}

#endif //TGBOT_MESSAGEENTITY_H
