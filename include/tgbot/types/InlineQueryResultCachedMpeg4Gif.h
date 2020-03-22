#ifndef TGBOT_INLINEQUERYRESULTCACHEDMPEG4GIF_H
#define TGBOT_INLINEQUERYRESULTCACHEDMPEG4GIF_H

#include "tgbot/types/InlineQueryResult.h"

#include <string>
#include <memory>

namespace TgBot {

/**
 * @brief Represents a link to a video animation (H.264/MPEG-4 AVC video without sound) stored on the Telegram servers.
 *
 * @ingroup types
 */
class InlineQueryResultCachedMpeg4Gif : public InlineQueryResult {
public:
    static const std::string TYPE;

    typedef std::shared_ptr<InlineQueryResultCachedMpeg4Gif> Ptr;

    InlineQueryResultCachedMpeg4Gif() {
        this->type = TYPE;
    }

    /**
     * @brief A valid file identifier for the MP4 file
     */
    std::string mpeg4FileId;

};
}

#endif //TGBOT_INLINEQUERYRESULTCACHEDMPEG4GIF_H
