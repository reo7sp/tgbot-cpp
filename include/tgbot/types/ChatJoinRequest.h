#ifndef TGBOT_CPP_CHATJOINREQUEST_H
#define TGBOT_CPP_CHATJOINREQUEST_H

#include "tgbot/types/Chat.h"
#include "tgbot/types/User.h"
#include "tgbot/types/ChatInviteLink.h"

#include <cstdint>
#include <memory>
#include <string>

namespace TgBot {

/**
 * @brief Represents a join request sent to a chat.
 *
 * @ingroup types
 */
class ChatJoinRequest {

public:
    typedef std::shared_ptr<ChatJoinRequest> Ptr;

    /**
     * @brief Chat to which the request was sent
     */
    Chat::Ptr chat;

    /**
     * @brief User that sent the join request
     */
    User::Ptr from;

    /**
     * @brief Date the request was sent in Unix time
     */
    std::int32_t date;

    /**
     * @brief Optional. Bio of the user.
     */
    std::string bio;

    /**
     * @brief Optional. Chat invite link that was used by the user to send the join request
     */
    ChatInviteLink::Ptr inviteLink;
};
}

#endif //TGBOT_CPP_CHATJOINREQUEST_H
