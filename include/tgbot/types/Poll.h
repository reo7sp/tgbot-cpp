#ifndef TGBOT_POLL_H
#define TGBOT_POLL_H

#include "tgbot/types/PollOption.h"
#include "tgbot/types/MessageEntity.h"

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

    /**
     * @brief Optional. Text that is shown when a user chooses an incorrect answer or taps on the lamp icon in a quiz-style poll, 0-200 characters
     */
    std::string explanation;

    /**
     * @brief Optional. Special entities like usernames, URLs, bot commands, etc. that appear in the explanation
     */
    std::vector<MessageEntity::Ptr> explanationEntities;

    /**
     * @brief Optional. Amount of time in seconds the poll will be active after creation
     */
    std::int32_t openPeriod;

    /**
     * @brief Optional. Point in time (Unix timestamp) when the poll will be automatically closed
     */
    std::int64_t closeDate;
};
}

#endif //TGBOT_POLL_H
