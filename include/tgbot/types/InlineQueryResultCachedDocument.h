//
// Created by Konstantin Kukin on 27/12/16.
//

#ifndef TGBOT_INLINEQUERYRESULTCACHEDDOCUMENT_H
#define TGBOT_INLINEQUERYRESULTCACHEDDOCUMENT_H

#include <string>
#include <memory>

#include "tgbot/types/InlineQueryResult.h"

namespace TgBot {

/**
 * @brief Represents a link to a file stored on the Telegram servers.
 * 
 * @ingroup types
 */
class InlineQueryResultCachedDocument : public InlineQueryResult {
public:
    static const std::string TYPE;

    typedef std::shared_ptr<InlineQueryResultCachedDocument> Ptr;

    InlineQueryResultCachedDocument() {
        this->type = TYPE;
    }

    /**
     * @brief A valid file identifier for the file
     */
    std::string documentFileId;

    /**
     * @brief Optional. Short description of the result
     */
    std::string description;
};
}

#endif //TGBOT_INLINEQUERYRESULTCACHEDDOCUMENT_H
