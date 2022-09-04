#ifndef TGBOT_CHATMEMBER_H
#define TGBOT_CHATMEMBER_H

#include "tgbot/types/User.h"

#include <memory>
#include <string>

namespace TgBot {

/**
 * @brief This abstract class is base of all chat members.
 * 
 * This object contains information about one member of a chat.
 *
 * @ingroup types
 */
class ChatMember {

public:
    typedef std::shared_ptr<ChatMember> Ptr;

    ChatMember() {}

    virtual ~ChatMember() {}

    /**
     * @brief The member's status in the chat
     */
    std::string status;

    /**
     * @brief Information about the user
     */
    User::Ptr user;
};
}

#endif //TGBOT_CHATMEMBER_H
