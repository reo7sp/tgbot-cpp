#ifndef MAXBOT_CPP_MESSAGEID_H
#define MAXBOT_CPP_MESSAGEID_H

#include <memory>

namespace MaxBot {

/**
 * @brief This object represents a unique message identifier.
 *
 * @ingroup types
 */
class MessageId {

public:
    typedef std::shared_ptr<MessageId> Ptr;

    /**
     * @brief Unique message identifier
     */
    std::int32_t messageId;
};
}

#endif //MAXBOT_CPP_MESSAGEID_H
