#ifndef TGBOT_USERSSHARED_H
#define TGBOT_USERSSHARED_H

#include "tgbot/types/SharedUser.h"

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
     * @brief Information about users shared with the bot.
     */
    std::vector<SharedUser::Ptr> users;
};
}

#endif //TGBOT_USERSSHARED_H
