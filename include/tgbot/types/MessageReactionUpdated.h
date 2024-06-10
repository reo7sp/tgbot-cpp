#ifndef TGBOT_MESSAGEREACTIONUPDATED_H
#define TGBOT_MESSAGEREACTIONUPDATED_H

#include "tgbot/types/Chat.h"
#include "tgbot/types/User.h"
#include "tgbot/types/ReactionType.h"

#include <cstdint>
#include <memory>
#include <vector>

namespace TgBot {

/**
 * @brief This object represents a change of a reaction on a message performed by a user.
 *
 * @ingroup types
 */
class MessageReactionUpdated {

public:
    typedef std::shared_ptr<MessageReactionUpdated> Ptr;

    /**
     * @brief The chat containing the message the user reacted to
     */
    Chat::Ptr chat;

    /**
     * @brief Unique identifier of the message inside the chat
     */
    std::int32_t messageId;

    /**
     * @brief Optional. The user that changed the reaction, if the user isn't anonymous
     */
    User::Ptr user;

    /**
     * @brief Optional. The chat on behalf of which the reaction was changed, if the user is anonymous
     */
    Chat::Ptr actorChat;

    /**
     * @brief Date of the change in Unix time
     */
    std::uint32_t date;

    /**
     * @brief Previous list of reaction types that were set by the user
     */
    std::vector<ReactionType::Ptr> oldReaction;

    /**
     * @brief New list of reaction types that have been set by the user
     */
    std::vector<ReactionType::Ptr> newReaction;
};
}

#endif //TGBOT_MESSAGEREACTIONUPDATED_H
