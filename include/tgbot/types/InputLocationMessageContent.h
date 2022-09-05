#ifndef TGBOT_INPUTLOCATIONMESSAGECONTENT_H
#define TGBOT_INPUTLOCATIONMESSAGECONTENT_H

#include "tgbot/types/InputMessageContent.h"

#include <memory>

namespace TgBot {

/**
 * @brief Represents the content of a location message to be sent as the result of an inline query.
 *
 * @ingroup types
 */
class InputLocationMessageContent : public InputMessageContent {
public:
    static const std::string TYPE;

    typedef std::shared_ptr<InputLocationMessageContent> Ptr;

    InputLocationMessageContent() {
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
     * @brief Optional. The radius of uncertainty for the location, measured in meters; 0-1500
     */
    float horizontalAccuracy;

    /**
     * @brief Optional. Period in seconds for which the location can be updated, should be between 60 and 86400.
     */
    std::int32_t livePeriod;

    /**
     * @brief Optional. For live locations, a direction in which the user is moving, in degrees.
     * Must be between 1 and 360 if specified.
     */
    std::int32_t heading;

    /**
     * @brief Optional. For live locations, a maximum distance for proximity alerts about approaching another chat member, in meters.
     * Must be between 1 and 100000 if specified.
     */
    std::int32_t proximityAlertRadius;
};
}

#endif //TGBOT_INPUTLOCATIONMESSAGECONTENT_H
