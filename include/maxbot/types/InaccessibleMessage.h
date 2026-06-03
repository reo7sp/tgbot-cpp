#ifndef MAXBOT_INACCESSIBLEMESSAGE_H
#define MAXBOT_INACCESSIBLEMESSAGE_H

#include "maxbot/types/Chat.h"

#include <cstdint>
#include <memory>

namespace MaxBot {

/**
 * @brief This object describes a message that was deleted or is otherwise inaccessible to the bot.
 *
 * @ingroup types
 */
class InaccessibleMessage {

public:
    typedef std::shared_ptr<InaccessibleMessage> Ptr;

    /**
     * @brief Chat the message belonged to
     */
    Chat::Ptr chat;

    /**
     * @brief Unique message identifier inside the chat
     */
    std::int32_t messageId;

    /**
     * @brief Always 0.
     *
     * The field can be used to differentiate regular and inaccessible messages.
     */
    std::uint8_t date;
};
}

#endif //MAXBOT_INACCESSIBLEMESSAGE_H
