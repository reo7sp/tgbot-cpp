#include <memory>
#include <string>
#include <vector>

#ifndef TGBOT_POLLOPTION_H
#define TGBOT_POLLOPTION_H

namespace TgBot {

class PollOption {

public:
    typedef std::shared_ptr<PollOption> Ptr;

    /**
     * @brief Option text, 1-100 characters.
     */
    std::string text;

    /**
     * @brief Number of users that voted for this option.
     */
    int64_t voter_count;
};

}

#endif //TGBOT_POLLOPTION_H
