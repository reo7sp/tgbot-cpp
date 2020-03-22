#ifndef TGBOT_INLINEQUERYRESULTARTICLE_H
#define TGBOT_INLINEQUERYRESULTARTICLE_H

#include "tgbot/types/InlineQueryResult.h"

#include <cstdint>
#include <string>
#include <memory>

namespace TgBot {

/**
 * @brief Represents a link to an article of web page.
 *
 * @ingroup types
 */
class InlineQueryResultArticle : public InlineQueryResult {
public:
    static const std::string TYPE;

    typedef std::shared_ptr<InlineQueryResultArticle> Ptr;

    InlineQueryResultArticle() {
        this->type = TYPE;
        this->hideUrl = false;
        this->thumbHeight = 0;
        this->thumbWidth = 0;
    }

    /**
     * @brief Optional. URL of the result.
     */
    std::string url;

    /**
     * @brief Optional. Pass True if you don't want the URL to be shown in the message.
     */
    bool hideUrl;

    /**
     * @brief Optional. Short description of the result.
     */
    std::string description;

    /**
     * @brief Optional. Url of the thumbnail for the result
     */
    std::string thumbUrl;

    /**
     * @brief Optional. Thumbnail width.
     */
    std::int32_t thumbWidth;

    /**
     * @brief Optinal. Thumbnail height
     */
    std::int32_t thumbHeight;
};
}

#endif //TGBOT_INLINEQUERYRESULTARTICLE_H
