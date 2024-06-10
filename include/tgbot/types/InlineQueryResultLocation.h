#ifndef TGBOT_INLINEQUERYRESULTLOCATION_H
#define TGBOT_INLINEQUERYRESULTLOCATION_H

#include "tgbot/types/InlineQueryResult.h"
#include "tgbot/types/InputMessageContent.h"

#include <cstdint>
#include <memory>
#include <string>

namespace TgBot {

/**
 * @brief Represents a location on a map.
 *
 * By default, the location will be sent by the user.
 * Alternatively, you can use inputMessageContent to send a message with the specified content instead of the location.
 *
 * @ingroup types
 */
class InlineQueryResultLocation : public InlineQueryResult {

public:
    static const std::string TYPE;

    typedef std::shared_ptr<InlineQueryResultLocation> Ptr;

    InlineQueryResultLocation() {
        this->type = TYPE;
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
     * @brief Location title
     */
    std::string title;

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
     *
     * Must be between 1 and 360 if specified.
     */
    std::int32_t heading;

    /**
     * @brief Optional. For live locations, a maximum distance for proximity alerts about approaching another chat member, in meters.
     *
     * Must be between 1 and 100000 if specified.
     */
    std::int32_t proximityAlertRadius;

    /**
     * @brief Optional. Content of the message to be sent instead of the location
     */
    InputMessageContent::Ptr inputMessageContent;

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

#endif //TGBOT_INLINEQUERYRESULTLOCATION_H
