#ifndef TGBOT_VENUE_H
#define TGBOT_VENUE_H

#include "tgbot/types/Location.h"

#include <memory>
#include <string>

namespace TgBot {

/**
 * @brief This object represents a venue.
 *
 * @ingroup types
 */
class Venue {
public:
    typedef std::shared_ptr<Venue> Ptr;

    /**
     * @brief Venue location. Can't be a live location
     */
    Location::Ptr location;

    /**
     * @brief Name of the venue
     */
    std::string title;

    /**
     * @brief Address of the venue
     */
    std::string address;

    /**
     * @brief Optional. Foursquare identifier of the venue
     */
    std::string foursquareId;

    /**
     * @brief Optional. Foursquare type of the venue.
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

#endif //TGBOT_VENUE_H
