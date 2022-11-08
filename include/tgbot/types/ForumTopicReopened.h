#ifndef TGBOT_FORUMTOPICREOPENED_H
#define TGBOT_FORUMTOPICREOPENED_H

#include <memory>

namespace TgBot {

/**
 * @brief This object represents a service message about a forum topic reopened in the chat.
 * 
 * Currently holds no information.
 *
 * @ingroup types
 */
class ForumTopicReopened {
public:
    typedef std::shared_ptr<ForumTopicReopened> Ptr;
};
}

#endif //TGBOT_FORUMTOPICREOPENED_H
