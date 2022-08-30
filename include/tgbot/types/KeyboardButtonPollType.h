#ifndef TGBOT_CPP_KEYBOARDBUTTONPOLLTYPE_H
#define TGBOT_CPP_KEYBOARDBUTTONPOLLTYPE_H

#include <string>
#include <memory>

namespace TgBot {

/**
 * @brief This object represents type of a poll, which is allowed to be created and sent when the corresponding button is pressed.
 *
 * @ingroup types
 */
class KeyboardButtonPollType {

public:
    typedef std::shared_ptr<KeyboardButtonPollType> Ptr;

    /**
     * @brief Optional. If quiz is passed, the user will be allowed to create only polls in the quiz mode.
     * If regular is passed, only regular polls will be allowed.
     * Otherwise, the user will be allowed to create a poll of any type.
     */
    std::string type;
};
}

#endif //TGBOT_CPP_KEYBOARDBUTTONPOLLTYPE_H
