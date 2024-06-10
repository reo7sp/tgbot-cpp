#ifndef TGBOT_LOCATION_H
#define TGBOT_LOCATION_H

#include <cstdint>
#include <memory>

namespace TgBot {

/**
 * @brief This object represents a point on the map.
 *
 * @ingroup types
 */
class Location {

public:
    typedef std::shared_ptr<Location> Ptr;

    /**
     * @brief Latitude as defined by sender
     */
    float latitude;

    /**
     * @brief Longitude as defined by sender
     */
    float longitude;

    /**
     * @brief Optional. The radius of uncertainty for the location, measured in meters; 0-1500
     */
    float horizontalAccuracy;

    /**
     * @brief Optional. Time relative to the message sending date, during which the location can be updated; in seconds.
     *
     * For active live locations only.
     */
    std::int32_t livePeriod;

    /**
     * @brief Optional. The direction in which user is moving, in degrees; 1-360.
     *
     * For active live locations only.
     */
    std::int32_t heading;

    /**
     * @brief Optional. The maximum distance for proximity alerts about approaching another chat member, in meters.
     *
     * For sent live locations only.
     */
    std::int32_t proximityAlertRadius;
};
}

#endif //TGBOT_LOCATION_H
