#ifndef TGBOT_VIDEOCHATENDED_H
#define TGBOT_VIDEOCHATENDED_H

#include <cstdint>
#include <memory>

namespace TgBot {

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

#endif //TGBOT_VIDEOCHATENDED_H
