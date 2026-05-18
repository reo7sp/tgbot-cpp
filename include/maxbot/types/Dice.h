#ifndef TGBOT_CPP_DICE_H
#define TGBOT_CPP_DICE_H

#include <memory>

namespace MaxBot {

/**
 * @brief This object represents an animated emoji that displays a random value.
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
     * @brief Value of the dice, 1-6 for “🎲”, “🎯” and “🎳” base emoji, 1-5 for “🏀” and “⚽” base emoji, 1-64 for “🎰” base emoji
     */
    std::int32_t value;
};
}

#endif //TGBOT_CPP_DICE_H
