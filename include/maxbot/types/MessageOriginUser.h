#ifndef MAXBOT_MESSAGEORIGINUSER_H
#define MAXBOT_MESSAGEORIGINUSER_H

#include "maxbot/types/MessageOrigin.h"
#include "maxbot/types/User.h"

#include <memory>

namespace MaxBot {

/**
 * @brief The message was originally sent by a known user.
 *
 * @ingroup types
 */
class MessageOriginUser : public MessageOrigin {

public:
    static const std::string TYPE;

    typedef std::shared_ptr<MessageOriginUser> Ptr;

    MessageOriginUser() {
        this->type = TYPE;
    }

    /**
     * @brief User that sent the message originally
     */
    User::Ptr senderUser;
};
}

#endif //MAXBOT_MESSAGEORIGINUSER_H
