/*
 * Copyright (c) 2015 Oleg Morozenkov
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef TGBOT_CPP_MESSAGE_H
#define TGBOT_CPP_MESSAGE_H

#include <string>
#include <vector>
#include <memory>

#include "tgbot/types/Chat.h"
#include "tgbot/types/User.h"
#include "tgbot/types/Message.h"
#include "tgbot/types/Audio.h"
#include "tgbot/types/Document.h"
#include "tgbot/types/Sticker.h"
#include "tgbot/types/Video.h"
#include "tgbot/types/Contact.h"
#include "tgbot/types/Location.h"
#include "tgbot/types/PhotoSize.h"

namespace TgBot {

/**
 * This object represents a message.
 * @ingroup types
 */
class Message {

public:
	typedef std::shared_ptr<Message> Ptr;

	/**
	 * Unique message identifier.
	 */
	int32_t messageId;

	/**
	 * Optional. Sender, can be empty for messages sent to channels.
	 */
	User::Ptr from;

	/**
	 * Date the message was sent in Unix time.
	 */
	int32_t date;

	/**
	 * Conversation the message belongs to.
	 */
	Chat::Ptr chat;

	/**
	 * Optional. For forwarded messages, sender of the original message.
	 */
	User::Ptr forwardFrom;

	/**
	 * Optional. For forwarded messages, date the original message was sent in Unix time.
	 */
	int32_t forwardDate;

	/**
	 * Optional. For replies, the original message. Note that the Message object in this field will not contain further reply_to_message fields even if it itself is a reply.
	 */
	Message::Ptr replyToMessage;

	/**
	 * Optional. For text messages, the actual UTF-8 text of the message.
	 */
	std::string text;

	/**
	 * Optional. Message is an audio file, information about the file.
	 */
	Audio::Ptr audio;

	/**
	 * Optional. Message is a general file, information about the file.
	 */
	Document::Ptr document;

	/**
	 * Optional. Message is a photo, available sizes of the photo.
	 */
	std::vector<PhotoSize::Ptr> photo;

	/**
	 * Optional. Message is a sticker, information about the sticker.
	 */
	Sticker::Ptr sticker;

	/**
	 * Optional. Message is a video, information about the video.
	 */
	Video::Ptr video;

	// TODO voice

	/**
	 * Optional. Message is a shared contact, information about the contact.
	 */
	Contact::Ptr contact;

	/**
	 * Optional. Message is a shared location, information about the location.
	 */
	Location::Ptr location;

	/**
	 * Optional. A new member was added to the group, information about them (this member may be bot itself).
	 */
	User::Ptr newChatParticipant;

	/**
	 * Optional. A member was removed from the group, information about them (this member may be bot itself).
	 */
	User::Ptr leftChatParticipant;

	/**
	 * Optional. A group title was changed to this value.
	 */
	std::string newChatTitle;

	/**
	 * Optional. A group photo was change to this value.
	 */
	std::vector<PhotoSize::Ptr> newChatPhoto;

	/**
	 * Optional. Informs that the group photo was deleted.
	 */
	bool deleteChatPhoto;

	/**
	 * Optional. Informs that the group has been created.
	 */
	bool groupChatCreated;

	/**
	 * Optional. Text description of the photo or the video.
	 */
	std::string caption;

	/**
	 * Optional. Service message: the supergroup has been created.
	 */
	bool supergroupChatCreated;

	/**
	 * Optional. Service message: the channel has been created.
	 */
	bool channelChatCreated;

	/**
	 * Optional. The group has been migrated to a supergroup with the specified identifier, not exceeding 1e13 by absolute value.
	 */
	int64_t migrateToChatId;

	/**
	 * Optional. The supergroup has been migrated from a group with the specified identifier, not exceeding 1e13 by absolute value
	 */
	int64_t migrateFromChatId;

};

}

#endif //TGBOT_CPP_MESSAGE_H
