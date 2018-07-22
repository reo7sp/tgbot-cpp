//
// Created by Konstantin Kukin on 27/12/16
//

#ifndef TGBOT_INLINEQUERYRESULTGAME_H
#define TGBOT_INLINEQUERYRESULTGAME_H

#include <string>
#include <memory>

#include "tgbot/types/InlineQueryResult.h"

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
