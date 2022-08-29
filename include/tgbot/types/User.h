#ifndef TGBOT_CPP_USER_H
#define TGBOT_CPP_USER_H

#include <cstdint>
#include <string>
#include <memory>

namespace TgBot {

/**
 * @brief This object represents a Telegram user or bot.
 *
 * @ingroup types
 */
class User  {

public:
    typedef std::shared_ptr<User> Ptr;

    /**
     * @brief Unique identifier for this user or bot
     */
    std::int64_t id;

    /**
     * @brief True, if this user is a bot
     */
    bool isBot = false;

    /**
     * @brief User‘s or bot’s first name
     */
    std::string firstName;

    /**
     * @brief Optional. User‘s or bot’s last name
     */
    std::string lastName;

    /**
     * @brief Optional. User‘s or bot’s username
     */
    std::string username;

    /**
     * @brief Optional. IETF language tag of the user's language
     */
    std::string languageCode;

    /**
     * @brief Optional. True, if the bot can be invited to groups. Returned only in getMe.
     */
    bool canJoinGroups;

    /**
     * @brief Optional. True, if privacy mode is disabled for the bot. Returned only in getMe.
     */
    bool canReadAllGroupMessages;

    /**
     * @brief Optional. True, if the bot supports inline queries. Returned only in getMe.
     */
    bool supportsInlineQueries;
};

}

#endif //TGBOT_CPP_USER_H
