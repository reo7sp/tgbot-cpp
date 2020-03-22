#ifndef TGBOT_GAME_H
#define TGBOT_GAME_H

#include "tgbot/types/MessageEntity.h"
#include "tgbot/types/Animation.h"
#include "tgbot/types/PhotoSize.h"

#include <memory>
#include <string>
#include <vector>

namespace TgBot {

/**
 * @brief This object represents a game.
 *
 * Use BotFather to create and edit games, their short names will act as unique identifiers.
 *
 * @ingroup types
 */
class Game {
public:
    typedef std::shared_ptr<Game> Ptr;

    /**
     * @brief Title of the game.
     */
    std::string title;

    /**
     * @brief Description of the game.
     */
    std::string description;

    /**
     * @brief Photo that will be displayed in the game message in chats.
     */
    std::vector<PhotoSize::Ptr> photo;

    /**
     * @brief Optional. Brief description of the game or high scores included in the game message.
     *
     * Can be automatically edited to include current high scores for the game when the bot calls setGameScore, or manually edited using editMessageText. 0-4096 characters.
     */
    std::string text;

    /**
     * @brief Optional. Special entities that appear in text, such as usernames, URLs, bot commands, etc.
     */
    std::vector<MessageEntity::Ptr> textEntities;

    /**
     * @brief Optional. Animation that will be displayed in the game message in chats. Upload via BotFather.
     */
    Animation::Ptr animation;
};
}

#endif //TGBOT_GAME_H
