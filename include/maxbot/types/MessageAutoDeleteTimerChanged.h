#ifndef MAXBOT_CPP_MESSAGEAUTODELETETIMERCHANGED_H
#define MAXBOT_CPP_MESSAGEAUTODELETETIMERCHANGED_H

#include <cstdint>
#include <memory>

namespace MaxBot {

/**
 * @brief This object represents a service message about a change in auto-delete timer settings.
 *
 * @ingroup types
 */
class MessageAutoDeleteTimerChanged {

public:
    typedef std::shared_ptr<MessageAutoDeleteTimerChanged> Ptr;

    /**
     * @brief New auto-delete time for messages in the chat
     */
    std::int32_t messageAutoDeleteTime;
};
}

#endif //MAXBOT_CPP_MESSAGEAUTODELETETIMERCHANGED_H
