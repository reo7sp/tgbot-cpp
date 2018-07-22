//
// Created by Andrea Giove on 26/03/16.
//

#ifndef TGBOT_INLINEQUERYRESULTARTICLE_H
#define TGBOT_INLINEQUERYRESULTARTICLE_H

#include <string>
#include <memory>

#include "tgbot/types/InlineQueryResult.h"

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
    int32_t thumbWidth;

    /**
     * @brief Optinal. Thumbnail height
     */
    int32_t thumbHeight;
};
}

#endif //TGBOT_INLINEQUERYRESULTARTICLE_H
