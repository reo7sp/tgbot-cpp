#ifndef TGBOT_CHATBOOSTUPDATED_H
#define TGBOT_CHATBOOSTUPDATED_H

#include "tgbot/types/Chat.h"
#include "tgbot/types/ChatBoost.h"

#include <memory>

namespace TgBot {

/**
 * @brief This object represents a boost added to a chat or changed.
 *
 * @ingroup types
 */
class ChatBoostUpdated {

public:
    typedef std::shared_ptr<ChatBoostUpdated> Ptr;

    /**
     * @brief Chat which was boosted
     */
    Chat::Ptr chat;

    /**
     * @brief Information about the chat boost
     */
    ChatBoost::Ptr boost;
};
}

#endif //TGBOT_CHATBOOSTUPDATED_H
