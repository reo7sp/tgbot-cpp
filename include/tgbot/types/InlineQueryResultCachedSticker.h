//
// Created by Konstantin Kukin on 27/12/16.
//

#ifndef TGBOT_INLINEQUERYRESULTCACHEDSTICKER_H
#define TGBOT_INLINEQUERYRESULTCACHEDSTICKER_H

#include <string>
#include <memory>

#include "tgbot/types/InlineQueryResult.h"

namespace TgBot {

/**
 * @brief Represents a link to a sticker stored on the Telegram servers.
 *
 * @ingroup types
 */
class InlineQueryResultCachedSticker : public InlineQueryResult {
public:
    static const std::string TYPE;

    typedef std::shared_ptr<InlineQueryResultCachedSticker> Ptr;

    InlineQueryResultCachedSticker() {
        this->type = TYPE;
    }

    /**
     * @brief A valid file identifier of the sticker
     */
    std::string stickerFileId;
};
}

#endif //TGBOT_INLINEQUERYRESULTCACHEDSTICKER_H
