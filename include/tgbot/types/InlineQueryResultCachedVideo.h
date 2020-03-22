#ifndef TGBOT_INLINEQUERYRESULTCACHEDVIDEO_H
#define TGBOT_INLINEQUERYRESULTCACHEDVIDEO_H

#include "tgbot/types/InlineQueryResult.h"

#include <string>
#include <memory>

namespace TgBot {

/**
 * @brief Represents a link to a video file stored on the Telegram servers.
 *
 *  @ingroup types
 */
class InlineQueryResultCachedVideo : public InlineQueryResult {
public:
    static const std::string TYPE;

    typedef std::shared_ptr<InlineQueryResultCachedVideo> Ptr;

    InlineQueryResultCachedVideo() {
        this->type = TYPE;
    }

    /**
     * @brief A valid file identifier of the video
     */
    std::string videoFileId;

    /**
    * @brief Optional. Short description of the result
    */
    std::string description;
};
}

#endif //TGBOT_INLINEQUERYRESULTCACHEDVIDEO_H
