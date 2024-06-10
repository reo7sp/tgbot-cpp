#ifndef TGBOT_INLINEQUERYRESULT_H
#define TGBOT_INLINEQUERYRESULT_H

#include "tgbot/types/InlineKeyboardMarkup.h"

#include <memory>
#include <string>

namespace TgBot {

/**
 * @brief This object represents one result of an inline query.
 *
 * Telegram clients currently support results of the following 20 types:
 * - InlineQueryResultCachedAudio
 * - InlineQueryResultCachedDocument
 * - InlineQueryResultCachedGif
 * - InlineQueryResultCachedMpeg4Gif
 * - InlineQueryResultCachedPhoto
 * - InlineQueryResultCachedSticker
 * - InlineQueryResultCachedVideo
 * - InlineQueryResultCachedVoice
 * - InlineQueryResultArticle
 * - InlineQueryResultAudio
 * - InlineQueryResultContact
 * - InlineQueryResultGame
 * - InlineQueryResultDocument
 * - InlineQueryResultGif
 * - InlineQueryResultLocation
 * - InlineQueryResultMpeg4Gif
 * - InlineQueryResultPhoto
 * - InlineQueryResultVenue
 * - InlineQueryResultVideo
 * - InlineQueryResultVoice
 *
 * Note: All URLs passed in inline query results will be available to end users and therefore must be assumed to be public.
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
     * @brief Optional. [Inline keyboard](https://core.telegram.org/bots/features#inline-keyboards) attached to the message
     */
    InlineKeyboardMarkup::Ptr replyMarkup;
};
}

#endif //TGBOT_INLINEQUERYRESULT_H
