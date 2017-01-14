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

#ifndef TGBOT_CPP_CHAT_H
#define TGBOT_CPP_CHAT_H

#include <string>
#include <memory>

namespace TgBot {

/**
 * This object represents a Telegram Chat
 * @ingroup types
 */
class Chat {

public:
	typedef std::shared_ptr<Chat> Ptr;

	/**
	 * Enum of possible types of a chat.
	 */
	enum class Type {
		Private, Group, Supergroup, Channel
	};

	/**
	 * Unique identifier for this chat, not exceeding 1e13 by absolute value
	 */
	int64_t id;

	/**
	 * Type of chat: can be either "private", "group", "supergroup, or "channel".
	 */
	Type type;

	/**
	 * Optional. Title for channels and group chat
	 */
	std::string title;

	/**
	 * Optional. Username for
	 * private chats and channels
	 */
	std::string username;

	/**
	 * Optional. First name of the
	 * other party in private chat
	 */
	std::string firstName;

	/**
	 * Optional. Last name of the
	 * other party in private chat
	 */
	std::string lastName;

	/**
	 * Optional. True if a group 
	 * has �All Members Are Admins� enabled.
	 */
	bool allMembersAreAdministrators;
};

}

#endif //TGBOT_CPP_CHAT_H
