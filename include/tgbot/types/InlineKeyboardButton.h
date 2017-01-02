//
// Created by Andrea Giove on 17/04/16.
//

#ifndef TGBOT_INLINEKEYBOARDBUTTON_H
#define TGBOT_INLINEKEYBOARDBUTTON_H

#include <string>
#include <memory>

namespace TgBot {

/**
 * This object represents one button of an inline keyboard. You must use exactly one of the optional fields.
 * @ingroup types
 */
class InlineKeyboardButton {
public:
	typedef std::shared_ptr<InlineKeyboardButton> Ptr;

	/**
	 * Label text on the button
	 */
	std::string text;

	/**
	 * Optional. HTTP url to be opened when button is pressed.
	 */
	std::string url;

	/**
	 * Optional. Data to be sent in a callback query to the bot when button is pressed.
	 */
	std::string callbackData;

	/**
	 * Optional. If set, pressing the button will prompt the user to select one of their chats, open that chat and insert the bot‘s username and the specified inline query in the input field. Can be empty, in which case just the bot’s username will be inserted.
	 */
	std::string switchInlineQuery;

	/**
	* Optional. If set, pressing the button will insert the bot‘s username and the specified inline query in the current chat's input field. Can be empty, in which case only the bot’s username will be inserted.
	*/
	std::string switchInlineQueryCurrentChat;
};
}

#endif //TGBOT_INLINEKEYBOARDBUTTON_H
