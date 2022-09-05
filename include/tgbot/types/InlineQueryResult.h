#ifndef TGBOT_INLINEQUERYRESULT_H
#define TGBOT_INLINEQUERYRESULT_H

#include "tgbot/types/InlineKeyboardMarkup.h"

#include <memory>
#include <string>

namespace TgBot {

/**
 * @brief This abstract class is base of all inline query results.
 * 
 * This object represents one result of an inline query.
 *
 * @ingroup types
 */
class InlineQueryResult {
public:
    typedef std::shared_ptr<InlineQueryResult> Ptr;

    InlineQueryResult() { }

    virtual ~InlineQueryResult() { }

    /**
     * @brief Type of the result
     */
    std::string type;

    /**
     * @brief Unique identifier for this result, 1-64 bytes
     */
    std::string id;

    /**
     * @brief Optional. Inline keyboard attached to the message
     */
    InlineKeyboardMarkup::Ptr replyMarkup;
};
}

#endif //TGBOT_INLINEQUERYRESULT_H
