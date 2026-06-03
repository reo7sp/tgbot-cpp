#ifndef MAXBOT_INLINEQUERYRESULTARTICLE_H
#define MAXBOT_INLINEQUERYRESULTARTICLE_H

#include "maxbot/types/InlineQueryResult.h"
#include "maxbot/types/InputMessageContent.h"

#include <cstdint>
#include <string>
#include <memory>

namespace MaxBot {

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
    }

    /**
     * @brief Title of the result
     */
    std::string title;

    /**
     * @brief Content of the message to be sent
     */
    InputMessageContent::Ptr inputMessageContent;

    /**
     * @brief Optional. URL of the result
     */
    std::string url;

    /**
     * @brief Optional. Pass True if you don't want the URL to be shown in the message.
     */
    bool hideUrl;

    /**
     * @brief Optional. Short description of the result
     */
    std::string description;

    /**
     * @brief Optional. Url of the thumbnail for the result
     */
    std::string thumbnailUrl;

    /**
     * @brief Optional. Thumbnail width
     */
    std::int32_t thumbnailWidth;

    /**
     * @brief Optional. Thumbnail height
     */
    std::int32_t thumbnailHeight;
};
}

#endif //MAXBOT_INLINEQUERYRESULTARTICLE_H
