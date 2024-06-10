#ifndef TGBOT_MESSAGEORIGINHIDDENUSER_H
#define TGBOT_MESSAGEORIGINHIDDENUSER_H

#include "tgbot/types/MessageOrigin.h"

#include <memory>
#include <string>

namespace TgBot {

/**
 * @brief The message was originally sent by an unknown user.
 *
 * @ingroup types
 */
class MessageOriginHiddenUser : public MessageOrigin {

public:
    static const std::string TYPE;

    typedef std::shared_ptr<MessageOriginHiddenUser> Ptr;

    MessageOriginHiddenUser() {
        this->type = TYPE;
    }

    /**
     * @brief Name of the user that sent the message originally
     */
    std::string senderUserName;
};
}

#endif //TGBOT_MESSAGEORIGINHIDDENUSER_H
