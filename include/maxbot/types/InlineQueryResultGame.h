#ifndef TGBOT_INLINEQUERYRESULTGAME_H
#define TGBOT_INLINEQUERYRESULTGAME_H

#include "maxbot/types/InlineQueryResult.h"

#include <memory>
#include <string>

namespace MaxBot {

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
