#ifndef TGBOT_BUSINESSCONNECTION_H
#define TGBOT_BUSINESSCONNECTION_H

#include "tgbot/types/User.h"

#include <cstdint>
#include <memory>
#include <string>

namespace TgBot {

/**
 * @brief Describes the connection of the bot with a business account.
 *
 * @ingroup types
 */
class BusinessConnection {

public:
    typedef std::shared_ptr<BusinessConnection> Ptr;

    /**
     * @brief Unique identifier of the business connection
     */
    std::string id;

    /**
     * @brief Business account user that created the business connection
     */
    User::Ptr user;

    /**
     * @brief Identifier of a private chat with the user who created the business connection.
     *
     * This number may have more than 32 significant bits and some programming languages may have difficulty/silent defects in interpreting it.
     * But it has at most 52 significant bits, so a 64-bit integer or double-precision float type are safe for storing this identifier.
     */
    std::int64_t userChatId;

    /**
     * @brief Date the connection was established in Unix time
     */
    std::uint32_t date;

    /**
     * @brief True, if the bot can act on behalf of the business account in chats that were active in the last 24 hours
     */
    bool canReply;

    /**
     * @brief True, if the connection is active
     */
    bool isEnabled;
};
}

#endif //TGBOT_BUSINESSCONNECTION_H
