#ifndef MAXBOT_GIVEAWAYCREATED_H
#define MAXBOT_GIVEAWAYCREATED_H

#include <memory>

namespace MaxBot {

/**
 * @brief This object represents a service message about the creation of a scheduled giveaway.
 *
 * Currently holds no information.
 *
 * @ingroup types
 */
class GiveawayCreated {

public:
    typedef std::shared_ptr<GiveawayCreated> Ptr;
};
}

#endif //MAXBOT_GIVEAWAYCREATED_H
