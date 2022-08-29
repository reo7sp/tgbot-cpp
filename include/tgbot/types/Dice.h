#ifndef TGBOT_CPP_DICE_H
#define TGBOT_CPP_DICE_H

#include <memory>

namespace TgBot {

/**
 * @brief This object represents a dice with random value from 1 to 6.
 *
 * @ingroup types
 */
class Dice {

public:
    typedef std::shared_ptr<Dice> Ptr;

    /**
     * @brief Value of the dice, 1-6
     */
    std::int8_t value;
};
}

#endif //TGBOT_CPP_DICE_H
