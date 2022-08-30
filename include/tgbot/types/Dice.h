#ifndef TGBOT_CPP_DICE_H
#define TGBOT_CPP_DICE_H

#include <memory>

namespace TgBot {

/**
 * @brief This object represents a dice with a random value from 1 to 6 for currently supported base emoji.
 *
 * @ingroup types
 */
class Dice {

public:
    typedef std::shared_ptr<Dice> Ptr;

    /**
     * @brief Emoji on which the dice throw animation is based
     */
    std::string emoji;

    /**
     * @brief Value of the dice, 1-6 for currently supported base emoji
     */
    std::int8_t value;
};
}

#endif //TGBOT_CPP_DICE_H
