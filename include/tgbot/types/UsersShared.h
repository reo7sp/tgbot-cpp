#ifndef TGBOT_USERSSHARED_H
#define TGBOT_USERSSHARED_H

#include <cstdint>
#include <memory>
#include <vector>

namespace TgBot {

/**
 * @brief This object contains information about the users whose identifiers were shared with the bot using a KeyboardButtonRequestUsers button.
 *
 * @ingroup types
 */
class UsersShared {

public:
    typedef std::shared_ptr<UsersShared> Ptr;

    /**
     * @brief Identifier of the request
     */
    std::int32_t requestId;

    /**
     * @brief Identifiers of the shared users.
     *
     * These numbers may have more than 32 significant bits and some programming languages may have difficulty/silent defects in interpreting them.
     * But they have at most 52 significant bits, so 64-bit integers or double-precision float types are safe for storing these identifiers.
     * The bot may not have access to the users and could be unable to use these identifiers, unless the users are already known to the bot by some other means.
     */
    std::vector<std::int64_t> userIds;
};
}

#endif //TGBOT_USERSSHARED_H
