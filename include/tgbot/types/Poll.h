#ifndef TGBOT_POLL_H
#define TGBOT_POLL_H

#include <memory>
#include <string>
#include <vector>
#include "tgbot/types/PollOption.h"

namespace TgBot {
    /**
     * @brief This object represents a Poll.
     *
     * @ingroup types
     */
    class Poll {
    public:
        typedef std::shared_ptr<Poll> Ptr;

        /**
         * @brief Unique poll identifier.
         */
        int64_t id;

        /**
         * @brief Poll question, 1-255 characters.
         */
         std::string question;

        /**
         * @brief List of poll options.
         */
        PollOption::Ptr options;

        /**
         * @brief True, if the poll is closed.
         */
         bool is_closed;
    };
}

#endif //TGBOT_POLL_H
