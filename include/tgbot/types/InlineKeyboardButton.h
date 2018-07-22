//
// Created by Andrea Giove on 17/04/16.
//

#ifndef TGBOT_INLINEKEYBOARDBUTTON_H
#define TGBOT_INLINEKEYBOARDBUTTON_H

#include <string>
#include <memory>

#include "tgbot/types/CallbackGame.h"

namespace TgBot {

/**
 * @brief This object represents one button of an inline keyboard. You must use exactly one of the optional fields.
 * 
 * @ingroup types
 */
class InlineKeyboardButton {
public:
    typedef std::shared_ptr<InlineKeyboardButton> Ptr;

    /**
     * @brief Label text on the button
     */
    std::string text;

    /**
     * @brief Optional. HTTP url to be opened when button is pressed.
     */
    std::string url;

    /**
     * @brief Optional. Data to be sent in a callback query to the bot when button is pressed.
     */
    std::string callbackData;

    /**
     * @brief Optional. If set, pressing the button will prompt the user to select one of their chats, open that chat and insert the bot‘s username and the specified inline query in the input field. Can be empty, in which case just the bot’s username will be inserted.
     *
     * Note: This offers an easy way for users to start using your bot in inline mode when they are currently in a private chat with it. Especially useful when combined with switch_pm… actions – in this case the user will be automatically returned to the chat they switched from, skipping the chat selection screen.
     */
    std::string switchInlineQuery;

    /**
     * @brief Optional. If set, pressing the button will insert the bot‘s username and the specified inline query in the current chat's input field. Can be empty, in which case only the bot’s username will be inserted.
     */
    std::string switchInlineQueryCurrentChat;

    /**
     * @brief Optional. Description of the game that will be launched when the user presses the button.
     *
     * Note: This type of button must always be the first button in the first row.
     */
    CallbackGame::Ptr callbackGame;

    /**
     * @brief Optional. Specify True, to send a Pay button.
     *
     * Note: This type of button must always be the first button in the first row.
     */
    bool pay = false;
};
}

#endif //TGBOT_INLINEKEYBOARDBUTTON_H
