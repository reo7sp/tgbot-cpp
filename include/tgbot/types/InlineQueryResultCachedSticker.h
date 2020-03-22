#ifndef TGBOT_INLINEQUERYRESULTCACHEDSTICKER_H
#define TGBOT_INLINEQUERYRESULTCACHEDSTICKER_H

#include "tgbot/types/InlineQueryResult.h"

#include <string>
#include <memory>

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
