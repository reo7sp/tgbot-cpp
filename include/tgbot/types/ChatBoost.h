#ifndef TGBOT_CHATBOOST_H
#define TGBOT_CHATBOOST_H

#include "tgbot/types/ChatBoostSource.h"

#include <cstdint>
#include <memory>
#include <string>

namespace TgBot {

/**
 * @brief This object contains information about a chat boost.
 *
 * @ingroup types
 */
class ChatBoost {

public:
    typedef std::shared_ptr<ChatBoost> Ptr;

    /**
     * @brief Unique identifier of the boost
     */
    std::string boostId;

    /**
     * @brief Point in time (Unix timestamp) when the chat was boosted
     */
    std::uint32_t addDate;

    /**
     * @brief Point in time (Unix timestamp) when the boost will automatically expire, unless the booster's Telegram Premium subscription is prolonged
     */
    std::uint32_t expirationDate;

    /**
     * @brief Source of the added boost
     */
    ChatBoostSource::Ptr source;
};
}

#endif //TGBOT_CHATBOOST_H
