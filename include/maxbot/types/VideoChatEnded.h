#ifndef MAXBOT_VIDEOCHATENDED_H
#define MAXBOT_VIDEOCHATENDED_H

#include <cstdint>
#include <memory>

namespace MaxBot {

/**
 * @brief This object represents a service message about a video chat ended in the chat.
 *
 * @ingroup types
 */
class VideoChatEnded {

public:
    typedef std::shared_ptr<VideoChatEnded> Ptr;

    /**
     * @brief Video chat duration in seconds
     */
    std::int32_t duration;
};
}

#endif //MAXBOT_VIDEOCHATENDED_H
