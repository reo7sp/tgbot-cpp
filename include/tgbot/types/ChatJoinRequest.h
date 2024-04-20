#ifndef TGBOT_CHATJOINREQUEST_H
#define TGBOT_CHATJOINREQUEST_H

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
     * @brief Identifier of a private chat with the user who sent the join request.
     *
     * This number may have more than 32 significant bits and some programming languages may have difficulty/silent defects in interpreting it.
     * But it has at most 52 significant bits, so a 64-bit integer or double-precision float type are safe for storing this identifier.
     * The bot can use this identifier for 5 minutes to send messages until the join request is processed, assuming no other administrator contacted the user.
     */
    std::int64_t userChatId;

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

#endif //TGBOT_CHATJOINREQUEST_H
