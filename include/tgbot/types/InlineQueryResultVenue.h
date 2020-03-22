#ifndef TGBOT_INLINEQUERYRESULTVENUE_H
#define TGBOT_INLINEQUERYRESULTVENUE_H

#include "tgbot/types/InlineQueryResult.h"

#include <cstdint>
#include <string>
#include <memory>

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
    std::int32_t thumbWidth;

    /**
     * @brief Optinal. Thumbnail height
     */
    std::int32_t thumbHeight;
};
}

#endif //TGBOT_INLINEQUERYRESULTVENUE_H
