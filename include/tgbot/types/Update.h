#ifndef TGBOT_CPP_UPDATE_H
#define TGBOT_CPP_UPDATE_H

#include "tgbot/types/Message.h"
#include "tgbot/types/InlineQuery.h"
#include "tgbot/types/ChosenInlineResult.h"
#include "tgbot/types/CallbackQuery.h"
#include "tgbot/types/ShippingQuery.h"
#include "tgbot/types/PreCheckoutQuery.h"
#include "tgbot/types/Poll.h"
#include "tgbot/types/PollAnswer.h"
#include "tgbot/types/ChatMemberUpdated.h"
#include "tgbot/types/ChatJoinRequest.h"

#include <cstdint>
#include <memory>

namespace TgBot {

/**
 * @brief This object represents an incoming update.
 * At most one of the optional parameters can be present in any given update.
 *
 * @ingroup types
 */
class Update {

public:
    typedef std::shared_ptr<Update> Ptr;

    /**
     * @brief The update‘s unique identifier.
     * Update identifiers start from a certain positive number and increase sequentially.
     * This ID becomes especially handy if you’re using Webhooks, since it allows you to ignore repeated updates or to restore the correct update sequence, should they get out of order.
     * If there are no new updates for at least a week, then identifier of the next update will be chosen randomly instead of sequentially.
     */
    std::int32_t updateId;

    /**
     * @brief Optional. New incoming message of any kind — text, photo, sticker, etc.
     */
    Message::Ptr message;

    /**
    * @brief Optional. New version of a message that is known to the bot and was edited
    */
    Message::Ptr editedMessage;

    /**
    * @brief Optional. New incoming channel post of any kind — text, photo, sticker, etc.
    */
    Message::Ptr channelPost;

    /**
    * @brief Optional. New version of a channel post that is known to the bot and was edited
    */
    Message::Ptr editedChannelPost;

    /**
     * @brief Optional. New incoming inline query
     */
    InlineQuery::Ptr inlineQuery;

    /**
     * @brief Optional. The result of an inline query that was chosen by a user and sent to their chat partner.
     * Please see https://core.telegram.org/bots/inline#collecting-feedback for details on how to enable these updates for your bot. (https://core.telegram.org/bots/inline#collecting-feedback)
     */
    ChosenInlineResult::Ptr chosenInlineResult;

    /**
     * @brief Optional. New incoming callback query
     */
    CallbackQuery::Ptr callbackQuery;

    /**
     * @brief Optional. New incoming shipping query.
     * Only for invoices with flexible price
     */
    ShippingQuery::Ptr shippingQuery;

    /**
     * @brief Optional. New incoming pre-checkout query.
     * Contains full information about checkout
     */
    PreCheckoutQuery::Ptr preCheckoutQuery;

    /**
     * @brief Optional. New poll state.
     * Bots receive only updates about stopped polls and polls, which are sent by the bot
     */
    Poll::Ptr poll;

    /**
     * @brief Optional. A user changed their answer in a non-anonymous poll.
     * Bots receive new votes only in polls that were sent by the bot itself.
     */
    PollAnswer::Ptr pollAnswer;

    /**
     * @brief Optional. The bot's chat member status was updated in a chat.
     * For private chats, this update is received only when the bot is blocked or unblocked by the user.
     */
    ChatMemberUpdated::Ptr myChatMember;

    /**
     * @brief Optional. A chat member's status was updated in a chat.
     * The bot must be an administrator in the chat and must explicitly specify “chatMember” in the list of allowedUpdates to receive these updates.
     */
    ChatMemberUpdated::Ptr chatMember;

    /**
     * @brief Optional. A request to join the chat has been sent.
     * The bot must have the canInviteUsers administrator right in the chat to receive these updates.
     */
    ChatJoinRequest::Ptr chatJoinRequest;
};
}

#endif //TGBOT_CPP_UPDATE_H
