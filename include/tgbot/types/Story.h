#ifndef TGBOT_STORY_H
#define TGBOT_STORY_H

#include <memory>

namespace TgBot {

/**
 * @brief This object represents a message about a forwarded story in the chat.
 * 
 * Currently holds no information.
 *
 * @ingroup types
 */
class Story {

public:
    typedef std::shared_ptr<Story> Ptr;
};
}

#endif //TGBOT_STORY_H
