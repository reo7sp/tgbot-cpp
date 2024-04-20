#ifndef TGBOT_CHATBOOSTADDED_H
#define TGBOT_CHATBOOSTADDED_H

#include <cstdint>
#include <memory>

namespace TgBot {

/**
 * @brief This object represents a service message about a user boosting a chat.
 *
 * @ingroup types
 */
class ChatBoostAdded {

public:
    typedef std::shared_ptr<ChatBoostAdded> Ptr;

    /**
     * @brief Number of boosts added by the user
     */
    std::int32_t boostCount;
};
}

#endif //TGBOT_CHATBOOSTADDED_H
