#ifndef TGBOT_KEYBOARDBUTTONREQUESTCHAT_H
#define TGBOT_KEYBOARDBUTTONREQUESTCHAT_H

#include "tgbot/types/ChatAdministratorRights.h"

#include <cstdint>
#include <memory>

namespace TgBot {

/**
 * @brief This object defines the criteria used to request a suitable chat.
 *
 * Information about the selected chat will be shared with the bot when the corresponding button is pressed.
 * The bot will be granted requested rights in the сhat if appropriate [More about requesting chats »](https://core.telegram.org/bots/features#chat-and-user-selection)
 *
 * @ingroup types
 */
class KeyboardButtonRequestChat {

public:
    typedef std::shared_ptr<KeyboardButtonRequestChat> Ptr;

    /**
     * @brief Signed 32-bit identifier of the request, which will be received back in the ChatShared object.
     *
     * Must be unique within the message
     */
    std::int32_t requestId;

    /**
     * @brief Pass True to request a channel chat, pass False to request a group or a supergroup chat.
     */
    bool chatIsChannel;

    /**
     * @brief Optional. Pass True to request a forum supergroup, pass False to request a non-forum chat.
     *
     * If not specified, no additional restrictions are applied.
     */
    bool chatIsForum;

    /**
     * @brief Optional. Pass True to request a supergroup or a channel with a username, pass False to request a chat without a username.
     *
     * If not specified, no additional restrictions are applied.
     */
    bool chatHasUsername;

    /**
     * @brief Optional. Pass True to request a chat owned by the user.
     *
     * Otherwise, no additional restrictions are applied.
     */
    bool chatIsCreated;

    /**
     * @brief Optional. A JSON-serialized object listing the required administrator rights of the user in the chat.
     *
     * The rights must be a superset of botAdministratorRights.
     * If not specified, no additional restrictions are applied.
     */
    ChatAdministratorRights::Ptr userAdministratorRights;

    /**
     * @brief Optional. A JSON-serialized object listing the required administrator rights of the bot in the chat.
     *
     * The rights must be a subset of userAdministratorRights.
     * If not specified, no additional restrictions are applied.
     */
    ChatAdministratorRights::Ptr botAdministratorRights;

    /**
     * @brief Optional. Pass True to request a chat with the bot as a member.
     *
     * Otherwise, no additional restrictions are applied.
     */
    bool botIsMember;

    /**
     * @brief Optional. Pass True to request the chat's title
     */
    bool requestTitle;

    /**
     * @brief Optional. Pass True to request the chat's username
     */
    bool requestUsername;

    /**
     * @brief Optional. Pass True to request the chat's photo
     */
    bool requestPhoto;
};
}

#endif //TGBOT_KEYBOARDBUTTONREQUESTCHAT_H
