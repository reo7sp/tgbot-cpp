//
// Created by Konstantin Kukin on 27/12/16.
//

#ifndef TGBOT_INLINEQUERYRESULTCACHEDGIF_H
#define TGBOT_INLINEQUERYRESULTCACHEDGIF_H

#include <string>
#include <memory>

#include "tgbot/types/InlineQueryResult.h"

namespace TgBot {

/**
 * @brief Represents a link to an animated GIF file stored on the Telegram servers.
 * 
 * @ingroup types
 */
class InlineQueryResultCachedGif : public InlineQueryResult {
public:
    static const std::string TYPE;

    typedef std::shared_ptr<InlineQueryResultCachedGif> Ptr;

    InlineQueryResultCachedGif() {
        this->type = TYPE;
    }

    /**
     * @brief A valid file identifier for the GIF file
     */
    std::string gifFileId;

};
}

#endif //TGBOT_INLINEQUERYRESULTCACHEDGIF_H
