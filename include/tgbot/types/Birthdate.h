#ifndef TGBOT_BIRTHDATE_H
#define TGBOT_BIRTHDATE_H

#include <cstdint>
#include <memory>

namespace TgBot {

/**
 * @ingroup types
 */
class Birthdate {

public:
    typedef std::shared_ptr<Birthdate> Ptr;

    /**
     * @brief Day of the user's birth; 1-31
     */
    std::uint8_t day;

    /**
     * @brief Month of the user's birth; 1-12
     */
    std::uint8_t month;

    /**
     * @brief Optional. Year of the user's birth
     */
    std::uint16_t year;
};
}

#endif //TGBOT_BIRTHDATE_H
