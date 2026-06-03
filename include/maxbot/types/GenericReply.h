#ifndef MAXBOT_CPP_GENERICREPLY_H
#define MAXBOT_CPP_GENERICREPLY_H

#include <memory>

namespace MaxBot {

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

#endif //MAXBOT_CPP_GENERICREPLY_H
