//
// Created by Konstantin Kukin on 27/12/16
//

#ifndef TGBOT_INLINEQUERYRESULTVENUE_H
#define TGBOT_INLINEQUERYRESULTVENUE_H

#include <string>
#include <memory>

#include "tgbot/types/InlineQueryResult.h"

namespace TgBot {

/**
 * @brief Represents a venue. 
 * 
 * @ingroup types
 */
class InlineQueryResultVenue : public InlineQueryResult {
public:
    static const std::string TYPE;

    typedef std::shared_ptr<InlineQueryResultVenue> Ptr;

    InlineQueryResultVenue() {
        this->type = TYPE;
        this->thumbHeight = 0;
        this->thumbWidth = 0;
    }

    /**
    * @brief Latitude of the venue location in degrees
    */
    float latitude;

    /**
    * @brief Longitude of the venue location in degrees
    */
    float longitude;

    /**
    * @brief Address of the venue
    */
    std::string address;

    /**
    * @brief Optional. Foursquare identifier of the venue if known
    */
    std::string foursquareId;

    /**
     * @brief Optional. Foursquare type of the venue, if known. (For example, “arts_entertainment/default”, “arts_entertainment/aquarium” or “food/icecream”.)
     */
    std::string foursquareType;

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

#endif //TGBOT_INLINEQUERYRESULTVENUE_H
