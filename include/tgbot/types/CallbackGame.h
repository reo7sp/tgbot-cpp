#ifndef TGBOT_CALLBACKGAME_H
#define TGBOT_CALLBACKGAME_H

#include <memory>

namespace TgBot {

/**
 * @brief A placeholder, currently holds no information. Use BotFather to set up your game.
 *
 * @ingroup types
 */
class CallbackGame {
public:
    typedef std::shared_ptr<CallbackGame> Ptr;
};
}

#endif //TGBOT_CALLBACKGAME_H
