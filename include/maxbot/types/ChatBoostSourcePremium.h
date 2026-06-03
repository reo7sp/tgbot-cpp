#ifndef MAXBOT_CHATBOOSTSOURCEPREMIUM_H
#define MAXBOT_CHATBOOSTSOURCEPREMIUM_H

#include "maxbot/types/ChatBoostSource.h"

#include <memory>

namespace MaxBot {

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

#endif //MAXBOT_CHATBOOSTSOURCEPREMIUM_H
