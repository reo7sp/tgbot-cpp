#ifndef TGBOT_CHATBOOSTSOURCEGIFTCODE_H
#define TGBOT_CHATBOOSTSOURCEGIFTCODE_H

#include "tgbot/types/ChatBoostSource.h"

#include <memory>

namespace TgBot {

/**
 * @brief The boost was obtained by the creation of Telegram Premium gift codes to boost a chat.
 *
 * Each such code boosts the chat 4 times for the duration of the corresponding Telegram Premium subscription.
 *
 * @ingroup types
 */
class ChatBoostSourceGiftCode : public ChatBoostSource {

public:
    static constexpr std::string_view SOURCE = "gift_code";

    using Ptr = std::shared_ptr<ChatBoostSourceGiftCode>;

    ChatBoostSourceGiftCode() {
        this->source = SOURCE;
    }
};
}

#endif //TGBOT_CHATBOOSTSOURCEGIFTCODE_H
