#ifndef MAXBOT_CALLBACKQUERY_H
#define MAXBOT_CALLBACKQUERY_H

#include "maxbot/types/User.h"
#include "maxbot/types/Message.h"

#include <memory>
#include <string>

namespace MaxBot {

/**
 * @brief This object represents an incoming callback query from a callback button in an inline keyboard.
 * @ingroup types
 */
class CallbackQuery {
public:
    typedef std::shared_ptr<CallbackQuery> Ptr;

    /**
     * @brief Unique identifier for this query.
     */
    std::string id;

    /**
     * @brief Sender.
     */
    User::Ptr from;

    /**
     * @brief Optional. Message with the callback button that originated the query. Note that message content and message date will not be available if the message is too old.
     */
    Message::Ptr message;

    /**
     * @brief Optional. Identifier of the message sent via the bot in inline mode, that originated the query.
     */
    std::string inlineMessageId;

    /**
     * @brief Global identifier, uniquely corresponding to the chat to which the message with the callback button was sent. Useful for high scores in games.
     */
    std::string chatInstance;

    /**
     * @brief Data associated with the callback button. Be aware that a bad client can send arbitrary data in this field.
     */
    std::string data;

    /*
     * @brief Optional. Short name of a Game to be returned, serves as the unique identifier for the game
     */
    std::string gameShortName;
};
}

#endif //MAXBOT_CALLBACKQUERY_H
