//
// Created by Konstantin Kukin on 26/12/16.
//

#ifndef TGBOT_CPP_KEYBOARDBUTTON_H
#define TGBOT_CPP_KEYBOARDBUTTON_H

#include <string>
#include <memory>

namespace TgBot {

/**
 * @brief This object represents one button of the reply keyboard.
 *  
 * For simple text buttons String can be used instead of this
 * object to specify text of the button. Optional fields are mutually exclusive. 
 * 
 * @ingroup types
 */
class KeyboardButton {

public:
    typedef std::shared_ptr<KeyboardButton> Ptr;

    /**
     * @brief Text of the button. If none of the optional fields are used,
     * it will be sent to the bot as a message when the button is pressed
     */
    std::string text;

    /**
     * @brief Optional. If True, the user's phone number will be sent as a contact
     * when the button is pressed. Available in private chats only
     */
    bool requestContact = false;

    /**
     * @brief Optional. If True, the user's current location will be sent when the button is pressed. Available in private chats only. 
     */
    bool requestLocation = false;
};

}

#endif //TGBOT_CPP_KEYBOARDBUTTON_H
