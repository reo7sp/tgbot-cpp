#ifndef MAXBOT_GENERALFORUMTOPICHIDDEN_H
#define MAXBOT_GENERALFORUMTOPICHIDDEN_H

#include <memory>

namespace MaxBot {

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

#endif //MAXBOT_GENERALFORUMTOPICHIDDEN_H
