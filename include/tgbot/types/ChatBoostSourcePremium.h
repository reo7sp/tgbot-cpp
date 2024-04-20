#ifndef TGBOT_CHATBOOSTSOURCEPREMIUM_H
#define TGBOT_CHATBOOSTSOURCEPREMIUM_H

#include "tgbot/types/ChatBoostSource.h"

#include <memory>

namespace TgBot {

/**
 * @brief The boost was obtained by subscribing to Telegram Premium or by gifting a Telegram Premium subscription to another user.
 *
 * @ingroup types
 */
class ChatBoostSourcePremium : public ChatBoostSource {

public:
    static const std::string SOURCE;

    typedef std::shared_ptr<ChatBoostSourcePremium> Ptr;

    ChatBoostSourcePremium() {
        this->source = SOURCE;
    }
};
}

#endif //TGBOT_CHATBOOSTSOURCEPREMIUM_H
