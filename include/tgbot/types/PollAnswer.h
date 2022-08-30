#ifndef TGBOT_CPP_POLLANSWER_H
#define TGBOT_CPP_POLLANSWER_H

#include "tgbot/types/User.h"

#include <string>
#include <memory>
#include <vector>

namespace TgBot {

/**
 * @brief This object represents an answer of a user in a non-anonymous poll.
 *
 * @ingroup types
 */
class PollAnswer {

public:
    typedef std::shared_ptr<PollAnswer> Ptr;

    /**
     * @brief Unique poll identifier
     */
    std::string pollId;

    /**
     * @brief The user, who changed the answer to the poll
     */
    User::Ptr user;

    /**
     * @brief 0-based identifiers of answer options, chosen by the user.
     * May be empty if the user retracted their vote.
     */
    std::vector<std::int32_t> optionIds;
};
}

#endif //TGBOT_CPP_POLLANSWER_H
