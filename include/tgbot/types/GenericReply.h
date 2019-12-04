#ifndef TGBOT_CPP_GENERICREPLY_H
#define TGBOT_CPP_GENERICREPLY_H

#include <memory>

namespace TgBot {

/**
 * @brief This abstract class is base of all keyboard related events.
 * @ingroup types
 */
class GenericReply {

public:
    typedef std::shared_ptr<GenericReply> Ptr;

    virtual ~GenericReply() { }
};

}

#endif //TGBOT_CPP_GENERICREPLY_H
