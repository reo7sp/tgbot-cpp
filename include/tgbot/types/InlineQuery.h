//
// Created by Andrea Giove on 26/03/16.
//

#ifndef TGBOT_INLINEQUERY_H
#define TGBOT_INLINEQUERY_H

#include <memory>
#include <string>

#include "tgbot/types/User.h"
#include "tgbot/types/Location.h"

namespace TgBot {

/**
 * @brief This object represents an incoming inline query.
 * 
 * @ingroup types
 */
class InlineQuery {
public:
    typedef std::shared_ptr<InlineQuery> Ptr;

    /**
     * @brief Unique query identifier.
     */
    std::string id;

    /**
     * @brief Sender.
     */
    User::Ptr from;

    /**
     * @brief Optional. Sender location, only for bots that request user location
     */
    Location::Ptr location;

    /**
     * @brief Text of the query.
     */
    std::string query;

    /**
     * @brief Offset of the results to be returned.
     */
    std::string offset;
};

}

#endif //TGBOT_INLINEQUERY_H
