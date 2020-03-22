#ifndef TGBOT_INLINEQUERYRESULT_H
#define TGBOT_INLINEQUERYRESULT_H

#include "tgbot/types/InlineKeyboardMarkup.h"
#include "tgbot/types/InputMessageContent.h"

#include <memory>
#include <string>

namespace TgBot {

/**
 * @brief This abstract class is base of all inline query results.
 *
 * @ingroup types
 */
class InlineQueryResult {
public:
    typedef std::shared_ptr<InlineQueryResult> Ptr;

    InlineQueryResult() { }

    virtual ~InlineQueryResult() { }

    /**
     * @brief Type of the result.
     */
    std::string type;

    /**
     * @brief Unique identifier for this result. (1-64 bytes)
     */
    std::string id;

    /**
     * @brief Requred, optional or missing. See description of derived classes. Title of the result.
     */
    std::string title;

    /**
     * @brief Optional or missing. See description of derived classes. Caption of the file to be sent, 0-200 characters
     */
    std::string caption;

    /**
     * @brief Optional. Inline keyboard attached to the message
     */
    InlineKeyboardMarkup::Ptr replyMarkup;

    /**
     * @brief Requred, optional or missing. See description of derived classes. Content of the message to be sent
     */
    InputMessageContent::Ptr inputMessageContent;
};
}

#endif //TGBOT_INLINEQUERYRESULT_H
