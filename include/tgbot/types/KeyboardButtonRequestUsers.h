#ifndef TGBOT_KEYBOARDBUTTONREQUESTUSERS_H
#define TGBOT_KEYBOARDBUTTONREQUESTUSERS_H

#include <cstdint>
#include <memory>

namespace TgBot {

/**
 * @brief This object defines the criteria used to request suitable users.
 *
 * Information about the selected users will be shared with the bot when the corresponding button is pressed.
 * [More about requesting users »](https://core.telegram.org/bots/features#chat-and-user-selection)
 *
 * @ingroup types
 */
class KeyboardButtonRequestUsers {

public:
    typedef std::shared_ptr<KeyboardButtonRequestUsers> Ptr;

    /**
     * @brief Signed 32-bit identifier of the request that will be received back in the UsersShared object.
     *
     * Must be unique within the message
     */
    std::int32_t requestId;

    /**
     * @brief Optional. Pass True to request bots, pass False to request regular users.
     *
     * If not specified, no additional restrictions are applied.
     */
    bool userIsBot;

    /**
     * @brief Optional. Pass True to request premium users, pass False to request non-premium users.
     *
     * If not specified, no additional restrictions are applied.
     */
    bool userIsPremium;

    /**
     * @brief Optional. The maximum number of users to be selected; 1-10.
     *
     * Defaults to 1.
     */
    std::uint8_t maxQuantity;

    /**
     * @brief Optional. Pass True to request the users' first and last name
     */
    bool requestName;

    /**
     * @brief Optional. Pass True to request the users' username
     */
    bool requestUsername;

    /**
     * @brief Optional. Pass True to request the users' photo
     */
    bool requestPhoto;
};
}

#endif //TGBOT_KEYBOARDBUTTONREQUESTUSERS_H
