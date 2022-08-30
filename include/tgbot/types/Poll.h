#ifndef TGBOT_POLL_H
#define TGBOT_POLL_H

#include "tgbot/types/PollOption.h"

#include <cstdint>
#include <memory>
#include <string>
#include <vector>

namespace TgBot {

/**
 * @brief This object contains information about a poll.
 *
 * @ingroup types
 */
class Poll {

public:
    typedef std::shared_ptr<Poll> Ptr;

    /**
     * @brief Unique poll identifier
     */
    std::string id;

    /**
     * @brief Poll question, 1-255 characters
     */
    std::string question;

    /**
     * @brief List of poll options
     */
    std::vector<PollOption::Ptr> options;

    /**
     * @brief Total number of users that voted in the poll
     */
    std::int32_t totalVoterCount;

    /**
     * @brief True, if the poll is closed
     */
    bool isClosed;

    /**
     * @brief True, if the poll is anonymous
     */
    bool isAnonymous;

    /**
     * @brief Poll type, currently can be “regular” or “quiz”
     */
    std::string type;

    /**
     * @brief True, if the poll allows multiple answers
     */
    bool allowsMultipleAnswers;

    /**
     * @brief Optional. 0-based identifier of the correct answer option.
     * Available only for polls in the quiz mode, which are closed, or was sent (not forwarded) by the bot or to the private chat with the bot.
     */
    std::int32_t correctOptionId;
};
}

#endif //TGBOT_POLL_H
