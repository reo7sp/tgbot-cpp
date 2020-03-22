#ifndef TGBOT_INLINEQUERYRESULTDOCUMENT_H
#define TGBOT_INLINEQUERYRESULTDOCUMENT_H

#include "tgbot/types/InlineQueryResult.h"

#include <cstdint>
#include <string>
#include <memory>

namespace TgBot {

/**
 * @brief Represents a link to a file.
 *
 * @ingroup types
 */
class InlineQueryResultDocument : public InlineQueryResult {
public:
    static const std::string TYPE;

    typedef std::shared_ptr<InlineQueryResultDocument> Ptr;

    InlineQueryResultDocument() {
        this->type = TYPE;
        this->thumbHeight = 0;
        this->thumbWidth = 0;
    }

    /**
     * @brief A valid URL for the file
     */
    std::string documentUrl;

    /**
     * @brief Mime type of the content of the file, either 'application/pdf' or 'application/zip'
     */
    std::string mimeType;

    /**
     * @brief Optional. Short description of the result
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

#endif //TGBOT_INLINEQUERYRESULTDOCUMENT_H
