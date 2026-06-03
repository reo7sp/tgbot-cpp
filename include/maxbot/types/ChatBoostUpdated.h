#ifndef MAXBOT_CHATBOOSTUPDATED_H
#define MAXBOT_CHATBOOSTUPDATED_H

#include "maxbot/types/Chat.h"
#include "maxbot/types/ChatBoost.h"

#include <memory>

namespace MaxBot {

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

#endif //MAXBOT_CHATBOOSTUPDATED_H
