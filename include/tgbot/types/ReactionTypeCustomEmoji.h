#ifndef TGBOT_REACTIONTYPECUSTOMEMOJI_H
#define TGBOT_REACTIONTYPECUSTOMEMOJI_H

#include "tgbot/types/ReactionType.h"

#include <memory>
#include <string>

namespace TgBot {

/**
 * @brief The reaction is based on a custom emoji.
 *
 * @ingroup types
 */
class ReactionTypeCustomEmoji : public ReactionType {

public:
    static const std::string TYPE;

    typedef std::shared_ptr<ReactionTypeCustomEmoji> Ptr;

    ReactionTypeCustomEmoji() {
        this->type = TYPE;
    }

    /**
     * @brief Custom emoji identifier
     */
    std::string customEmojiId;
};
}

#endif //TGBOT_REACTIONTYPECUSTOMEMOJI_H
