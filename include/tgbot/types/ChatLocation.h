#ifndef TGBOT_CPP_CHATLOCATION_H
#define TGBOT_CPP_CHATLOCATION_H

#include "tgbot/types/Location.h"

#include <memory>

namespace TgBot {

/**
 * @brief Represents a location to which a chat is connected.
 *
 * @ingroup types
 */
class ChatLocation {

public:
    typedef std::shared_ptr<ChatLocation> Ptr;

    /**
     * @brief The location to which the supergroup is connected.
     * Can't be a live location.
     */
    Location::Ptr location;

    /**
     * @brief Location address; 1-64 characters, as defined by the chat owner
     */
    std::string address;
};
}

#endif //TGBOT_CPP_CHATLOCATION_H
