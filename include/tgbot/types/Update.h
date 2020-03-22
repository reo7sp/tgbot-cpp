#ifndef TGBOT_CPP_UPDATE_H
#define TGBOT_CPP_UPDATE_H

#include "tgbot/types/Message.h"
#include "tgbot/types/InlineQuery.h"
#include "tgbot/types/ChosenInlineResult.h"
#include "tgbot/types/CallbackQuery.h"
#include "tgbot/types/ShippingQuery.h"
#include "tgbot/types/PreCheckoutQuery.h"

#include <cstdint>
#include <memory>

namespace TgBot {

/**
 * @brief This object represents an incoming update.
 *
 * @ingroup types
 */
class Update {

public:
    typedef std::shared_ptr<Update> Ptr;

    /**
     * @brief The update‘s unique identifier. Update identifiers start from a certain positive number and increase sequentially. This ID becomes especially handy if you’re using Webhooks, since it allows you to ignore repeated updates or to restore the correct update sequence, should they get out of order.
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
     */
    ChosenInlineResult::Ptr chosenInlineResult;

    /**
     * @brief Optional. New incoming callback query.
     */
    CallbackQuery::Ptr callbackQuery;

    /**
     * @brief Optional. New incoming shipping query.
     *
     * Only for invoices with flexible price
     */
    ShippingQuery::Ptr shippingQuery;

    /**
     * @brief Optional. New incoming pre-checkout query.
     *
     * Contains full information about checkout
     */
    PreCheckoutQuery::Ptr preCheckoutQuery;
};

}

#endif //TGBOT_CPP_UPDATE_H
