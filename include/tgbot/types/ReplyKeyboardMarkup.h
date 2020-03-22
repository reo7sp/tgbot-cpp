#ifndef TGBOT_CPP_REPLYKEYBOARDMARKUP_H
#define TGBOT_CPP_REPLYKEYBOARDMARKUP_H

#include "tgbot/types/GenericReply.h"
#include "tgbot/types/KeyboardButton.h"

#include <string>
#include <vector>
#include <memory>

namespace TgBot {

/**
 * @brief This object represents a custom keyboard with reply options.
 *
 * @ingroup types
 */
class ReplyKeyboardMarkup : public GenericReply {

public:
    typedef std::shared_ptr<ReplyKeyboardMarkup> Ptr;

    /**
     * @brief Array of button rows, each represented by an Array of KeyboardButton.
     */
    std::vector<std::vector<KeyboardButton::Ptr>> keyboard;

    /**
     * @brief Optional. Requests clients to resize the keyboard vertically for optimal fit (e.g., make the keyboard smaller if there are just two rows of buttons). Defaults to false, in which case the custom keyboard is always of the same height as the app's standard keyboard.
     */
    bool resizeKeyboard = false;

    /**
     * @brief Optional. Requests clients to hide the keyboard as soon as it's been used. Defaults to false.
     */
    bool oneTimeKeyboard = false;

    /**
     * @brief Optional. Use this parameter if you want to show the keyboard to specific users only. Targets: 1) users that are @mentioned in the text of the Message object; 2) if the bot's message is a reply (has reply_to_message_id), sender of the original message.
     *
     * Example: A user requests to change the bot‘s language, bot replies to the request with a keyboard to select the new language. Other users in the group don’t see the keyboard.
     */
    bool selective = false;
};

}

#endif //TGBOT_CPP_REPLYKEYBOARDMARKUP_H
