#ifndef TGBOT_KEYBOARDBUTTONREQUESTUSER_H
#define TGBOT_KEYBOARDBUTTONREQUESTUSER_H

#include <cstdint>
#include <memory>

namespace TgBot {

/**
 * @brief This object defines the criteria used to request a suitable user.
 * The identifier of the selected user will be shared with the bot when the corresponding button is pressed.
 *
 * @ingroup types
 */
class KeyboardButtonRequestUser {

public:
    typedef std::shared_ptr<KeyboardButtonRequestUser> Ptr;

    /**
     * @brief Signed 32-bit identifier of the request, which will be received back in the UserShared object.
     * 
     * Must be unique within the message
     */
    std::int32_t requestId;

    /**
     * @brief Optional. Pass True to request a bot, pass False to request a regular user.
     * 
     * If not specified, no additional restrictions are applied.
     */
    bool userIsBot;

    /**
     * @brief Optional. Pass True to request a premium user, pass False to request a non-premium user.
     * 
     * If not specified, no additional restrictions are applied.
     */
    bool userIsPremium;
};
}

#endif //TGBOT_KEYBOARDBUTTONREQUESTUSER_H
