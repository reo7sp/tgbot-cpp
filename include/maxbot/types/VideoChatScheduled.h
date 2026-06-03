#ifndef MAXBOT_VIDEOCHATSCHEDULED_H
#define MAXBOT_VIDEOCHATSCHEDULED_H

#include <cstdint>
#include <memory>

namespace MaxBot {

/**
 * @brief This object represents a service message about a video chat scheduled in the chat.
 *
 * @ingroup types
 */
class VideoChatScheduled {

public:
    typedef std::shared_ptr<VideoChatScheduled> Ptr;

    /**
     * @brief Point in time (Unix timestamp) when the video chat is supposed to be started by a chat administrator
     */
    std::int32_t startDate;
};
}

#endif //MAXBOT_VIDEOCHATSCHEDULED_H
