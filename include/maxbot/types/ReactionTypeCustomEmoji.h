#ifndef MAXBOT_REACTIONTYPECUSTOMEMOJI_H
#define MAXBOT_REACTIONTYPECUSTOMEMOJI_H

#include "maxbot/types/ReactionType.h"

#include <memory>
#include <string>

namespace MaxBot {

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

#endif //MAXBOT_REACTIONTYPECUSTOMEMOJI_H
