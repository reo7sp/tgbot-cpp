#ifndef TGBOT_USERCHATBOOSTS_H
#define TGBOT_USERCHATBOOSTS_H

#include "tgbot/types/ChatBoost.h"

#include <memory>
#include <vector>

namespace TgBot {

/**
 * @brief This object represents a list of boosts added to a chat by a user.
 *
 * @ingroup types
 */
class UserChatBoosts {

public:
    typedef std::shared_ptr<UserChatBoosts> Ptr;

    /**
     * @brief The list of boosts added to the chat by the user
     */
    std::vector<ChatBoost::Ptr> boosts;
};
}

#endif //TGBOT_USERCHATBOOSTS_H
