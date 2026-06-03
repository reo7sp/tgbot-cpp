#ifndef MAXBOT_REACTIONCOUNT_H
#define MAXBOT_REACTIONCOUNT_H

#include "maxbot/types/ReactionType.h"

#include <cstdint>
#include <memory>

namespace MaxBot {

/**
 * @brief Represents a reaction added to a message along with the number of times it was added.
 *
 * @ingroup types
 */
class ReactionCount {

public:
    typedef std::shared_ptr<ReactionCount> Ptr;

    /**
     * @brief Type of the reaction
     */
    ReactionType::Ptr type;

    /**
     * @brief Number of times the reaction was added
     */
    std::int32_t totalCount;
};
}

#endif //MAXBOT_REACTIONCOUNT_H
