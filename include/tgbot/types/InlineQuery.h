//
// Created by Andrea Giove on 26/03/16.
//

#ifndef TGBOT_INLINEQUERY_H
#define TGBOT_INLINEQUERY_H

#include <memory>
#include <string>

#include "tgbot/types/User.h"

namespace TgBot {

/**
 * This object represents an incoming inline query.
 * @ingroup types
 */
class InlineQuery {
public:
    typedef std::shared_ptr<InlineQuery> Ptr;

    /**
     * Unique query identifier.
     */
    std::string id;

    /**
     * Sender.
     */
    User::Ptr from;

    /**
     * Text of the query.
     */
    std::string query;

    /**
     * Offset of the results to be returned.
     */
    std::string offset;
};

}

#endif //TGBOT_INLINEQUERY_H
