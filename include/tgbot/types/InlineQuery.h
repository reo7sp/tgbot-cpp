#ifndef TGBOT_INLINEQUERY_H
#define TGBOT_INLINEQUERY_H

#include "tgbot/types/User.h"
#include "tgbot/types/Location.h"

#include <memory>
#include <string>

namespace TgBot {

/**
 * @brief This object represents an incoming inline query.
 * When the user sends an empty query, your bot could return some default or trending results.
 *
 * @ingroup types
 */
class InlineQuery {
public:
    typedef std::shared_ptr<InlineQuery> Ptr;

    /**
     * @brief Unique identifier for this query
     */
    std::string id;

    /**
     * @brief Sender
     */
    User::Ptr from;

    /**
     * @brief Text of the query (up to 256 characters)
     */
    std::string query;

    /**
     * @brief Offset of the results to be returned, can be controlled by the bot
     */
    std::string offset;

    /**
     * @brief Optional. Type of the chat, from which the inline query was sent.
     * Can be either “sender” for a private chat with the inline query sender, “private”, “group”, “supergroup”, or “channel”.
     * The chat type should be always known for requests sent from official clients and most third-party clients, unless the request was sent from a secret chat
     */
    std::string chatType;

    /**
     * @brief Optional. Sender location, only for bots that request user location
     */
    Location::Ptr location;
};
}

#endif //TGBOT_INLINEQUERY_H
