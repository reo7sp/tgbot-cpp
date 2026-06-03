#ifndef MAXBOT_VIDEOCHATSTARTED_H
#define MAXBOT_VIDEOCHATSTARTED_H

#include <memory>

namespace MaxBot {

/**
 * @brief This object represents a service message about a video chat started in the chat.
 * Currently holds no information.
 *
 * @ingroup types
 */
class VideoChatStarted {

public:
    typedef std::shared_ptr<VideoChatStarted> Ptr;
};
}

#endif //MAXBOT_VIDEOCHATSTARTED_H
