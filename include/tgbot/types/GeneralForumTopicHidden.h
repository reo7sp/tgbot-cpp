#ifndef TGBOT_GENERALFORUMTOPICHIDDEN_H
#define TGBOT_GENERALFORUMTOPICHIDDEN_H

#include <memory>

namespace TgBot {

/**
 * @brief This object represents a service message about General forum topic hidden in the chat.
 * 
 * Currently holds no information.
 *
 * @ingroup types
 */
class GeneralForumTopicHidden {
public:
    typedef std::shared_ptr<GeneralForumTopicHidden> Ptr;
};
}

#endif //TGBOT_GENERALFORUMTOPICHIDDEN_H
