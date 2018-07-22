//
// Created by Andrea Giove on 27/03/16.
//

#ifndef TGBOT_CHOSENINLINERESULT_H
#define TGBOT_CHOSENINLINERESULT_H

#include <string>
#include <memory>

#include "tgbot/types/User.h"
#include "tgbot/types/Location.h"

namespace TgBot {

/**
 * @brief This object represents a result of an inline query that was chosen by the user and sent to their chat partner.
 * 
 * @ingroup types
 */
class ChosenInlineResult {
public:
    typedef std::shared_ptr<ChosenInlineResult> Ptr;

    /**
     * @brief The unique identifier for the result that was chosen.
     */
    std::string resultId;

    /**
     * @brief The user that chose the result.
     */
    User::Ptr from;

    /**
    * @brief Optional. Sender location, only for bots that require user location
    */
    Location::Ptr location;

    /**
     * @brief Optional. Identifier of the sent inline message.
     *
     * Available only if there is an inline keyboard attached to the message.
     * Will be also received in callback queries and can be used to edit the message.
     */
    std::string inlineMessageId;

    /**
     * @brief The query that was used to obtain the result.
     */
    std::string query;
};
}

#endif //TGBOT_CHOSENINLINERESULT_H
