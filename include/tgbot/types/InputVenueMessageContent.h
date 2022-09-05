#ifndef TGBOT_INPUTVENUEMESSAGECONTENT_H
#define TGBOT_INPUTVENUEMESSAGECONTENT_H

#include "tgbot/types/InputMessageContent.h"

#include <memory>
#include <string>

namespace TgBot {

/**
 * @brief Represents the content of a venue message to be sent as the result of an inline query.
 *
 * @ingroup types
 */
class InputVenueMessageContent : public InputMessageContent {
public:
    static const std::string TYPE;

    typedef std::shared_ptr<InputVenueMessageContent> Ptr;

    InputVenueMessageContent() {
        this->type = TYPE;
    }

    /**
     * @brief Latitude of the location in degrees
     */
    float latitude;

    /**
     * @brief Longitude of the location in degrees
     */
    float longitude;

    /**
     * @brief Name of the venue
     */
    std::string title;

    /**
     * @brief Address of the venue
     */
    std::string address;

    /**
     * @brief Optional. Foursquare identifier of the venue, if known
     */
    std::string foursquareId;

    /**
     * @brief Optional. Foursquare type of the venue, if known.
     * (For example, “arts_entertainment/default”, “arts_entertainment/aquarium” or “food/icecream”.)
     */
    std::string foursquareType;

    /**
     * @brief Optional. Google Places identifier of the venue
     */
    std::string googlePlaceId;

    /**
     * @brief Optional. Google Places type of the venue.
     * (See https://developers.google.com/places/web-service/supported_types)
     */
    std::string googlePlaceType;
};
}

#endif //TGBOT_INPUTVENUEMESSAGECONTENT_H
