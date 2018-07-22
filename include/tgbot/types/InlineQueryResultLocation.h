//
// Created by Konstantin Kukin on 27/12/16
//

#ifndef TGBOT_INLINEQUERYRESULTLOCATION_H
#define TGBOT_INLINEQUERYRESULTLOCATION_H

#include <string>
#include <memory>

#include "tgbot/types/InlineQueryResult.h"

namespace TgBot {

/**
 * @brief Represents a location on a map. 
 * 
 * @ingroup types
 */
class InlineQueryResultLocation : public InlineQueryResult {
public:
    static const std::string TYPE;

    typedef std::shared_ptr<InlineQueryResultLocation> Ptr;

    InlineQueryResultLocation() {
        this->type = TYPE;
        this->thumbHeight = 0;
        this->thumbWidth = 0;
    }

    /**
    * @brief Location latitude in degrees
    */
    float latitude;

    /**
    * @brief Location longitude in degrees
    */
    float longitude;

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

#endif //TGBOT_INLINEQUERYRESULTLOCATION_H
