#ifndef TGBOT_CPP_LOCATION_H
#define TGBOT_CPP_LOCATION_H

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
     * @brief Longitude as defined by sender.
     */
    float longitude;

    /**
     * @brief Latitude as defined by sender.
     */
    float latitude;
};

}

#endif //TGBOT_CPP_LOCATION_H
