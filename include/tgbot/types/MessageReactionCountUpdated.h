#ifndef TGBOT_MESSAGEREACTIONCOUNTUPDATED_H
#define TGBOT_MESSAGEREACTIONCOUNTUPDATED_H

#include "tgbot/types/Chat.h"
#include "tgbot/types/ReactionCount.h"

#include <cstdint>
#include <memory>
#include <vector>

namespace TgBot {

/**
 * @brief This object represents reaction changes on a message with anonymous reactions.
 *
 * @ingroup types
 */
class MessageReactionCountUpdated {

public:
    typedef std::shared_ptr<MessageReactionCountUpdated> Ptr;

    /**
     * @brief The chat containing the message
     */
    Chat::Ptr chat;

    /**
     * @brief Unique message identifier inside the chat
     */
    std::int32_t messageId;

    /**
     * @brief Date of the change in Unix time
     */
    std::uint32_t date;

    /**
     * @brief List of reactions that are present on the message
     */
    std::vector<ReactionCount::Ptr> reactions;
};
}

#endif //TGBOT_MESSAGEREACTIONCOUNTUPDATED_H
