#ifndef TGBOT_INLINEQUERYRESULTGAME_H
#define TGBOT_INLINEQUERYRESULTGAME_H

#include "tgbot/types/InlineQueryResult.h"

#include <string>
#include <memory>

namespace TgBot {

/**
 * @brief Represents a Game.
 *
 * @ingroup types
 */
class InlineQueryResultGame : public InlineQueryResult {
public:
    static const std::string TYPE;

    typedef std::shared_ptr<InlineQueryResultGame> Ptr;

    InlineQueryResultGame() {
        this->type = TYPE;
    }

    /**
     * @brief Short name of the game
     */
    std::string gameShortName;
};
}

#endif //TGBOT_INLINEQUERYRESULTGAME_H
