#ifndef TGBOT_BUSINESSOPENINGHOURSINTERVAL_H
#define TGBOT_BUSINESSOPENINGHOURSINTERVAL_H

#include <cstdint>
#include <memory>

namespace TgBot {

/**
 * @ingroup types
 */
class BusinessOpeningHoursInterval {

public:
    typedef std::shared_ptr<BusinessOpeningHoursInterval> Ptr;

    /**
     * @brief The minute's sequence number in a week, starting on Monday, marking the start of the time interval during which the business is open; 0 - 7 * 24 * 60
     */
    std::int32_t openingMinute;

    /**
     * @brief The minute's sequence number in a week, starting on Monday, marking the end of the time interval during which the business is open; 0 - 8 * 24 * 60
     */
    std::int32_t closingMinute;
};
}

#endif //TGBOT_BUSINESSOPENINGHOURSINTERVAL_H
