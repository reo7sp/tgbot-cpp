#ifndef TGBOT_CHATSHARED_H
#define TGBOT_CHATSHARED_H

#include "tgbot/types/PhotoSize.h"

#include <cstdint>
#include <memory>
#include <string>
#include <vector>

namespace TgBot {

/**
 * @brief This object contains information about a chat that was shared with the bot using a KeyboardButtonRequestChat button.
 *
 * @ingroup types
 */
class ChatShared {

public:
    typedef std::shared_ptr<ChatShared> Ptr;

    /**
     * @brief Identifier of the request
     */
    std::int32_t requestId;

    /**
     * @brief Identifier of the shared chat.
     *
     * The bot may not have access to the chat and could be unable to use this identifier, unless the chat is already known to the bot by some other means.
     *
     * This number may have more than 32 significant bits and some programming languages may have difficulty/silent defects in interpreting it.
     * But it has at most 52 significant bits, so a 64-bit integer or double-precision float type are safe for storing this identifier.
     */
    std::int64_t chatId;

    /**
     * @brief Optional. Title of the chat, if the title was requested by the bot.
     */
    std::string title;

    /**
     * @brief Optional. Username of the chat, if the username was requested by the bot and available.
     */
    std::string username;

    /**
     * @brief Optional. Available sizes of the chat photo, if the photo was requested by the bot
     */
    std::vector<PhotoSize::Ptr> photo;
};
}

#endif //TGBOT_CHATSHARED_H
