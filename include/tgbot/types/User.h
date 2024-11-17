#ifndef TGBOT_USER_H
#define TGBOT_USER_H

#include "tgbot/Optional.h"

#include <cstdint>
#include <memory>
#include <string>

namespace TgBot {

/**
 * @brief This object represents a Telegram user or bot.
 *
 * @ingroup types
 */
class User {

public:
    typedef std::shared_ptr<User> Ptr;

    /**
     * @brief Unique identifier for this user or bot.
     *
     * This number may have more than 32 significant bits and some programming languages may have difficulty/silent defects in interpreting it.
     * But it has at most 52 significant bits, so a 64-bit integer or double-precision float type are safe for storing this identifier.
     */
    Required<std::int64_t> id;

    /**
     * @brief True, if this user is a bot
     */
    Required<bool> isBot;

    /**
     * @brief User's or bot's first name
     */
    Required<std::string> firstName;

    /**
     * @brief Optional. User's or bot's last name
     */
    Optional<std::string> lastName;

    /**
     * @brief Optional. User's or bot's username
     */
    Optional<std::string> username;

    /**
     * @brief Optional. [IETF language tag](https://en.wikipedia.org/wiki/IETF_language_tag) of the user's language
     */
    Optional<std::string> languageCode;

    /**
     * @brief Optional. True, if this user is a Telegram Premium user
     */
    Optional<bool> isPremium;

    /**
     * @brief Optional. True, if this user added the bot to the attachment menu
     */
    Optional<bool> addedToAttachmentMenu;

    /**
     * @brief Optional. True, if the bot can be invited to groups.
     *
     * Returned only in Api::getMe.
     */
    Optional<bool> canJoinGroups;

    /**
     * @brief Optional. True, if [privacy mode](https://core.telegram.org/bots/features#privacy-mode) is disabled for the bot.
     *
     * Returned only in Api::getMe.
     */
    Optional<bool> canReadAllGroupMessages;

    /**
     * @brief Optional. True, if the bot supports inline queries.
     *
     * Returned only in Api::getMe.
     */
    Optional<bool> supportsInlineQueries;

    /**
     * @brief Optional. True, if the bot can be connected to a Telegram Business account to receive its messages.
     *
     * Returned only in Api::getMe.
     */
    Optional<bool> canConnectToBusiness;
};
}

#endif //TGBOT_USER_H
