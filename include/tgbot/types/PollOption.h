#ifndef TGBOT_POLLOPTION_H
#define TGBOT_POLLOPTION_H

#include <cstdint>
#include <memory>
#include <string>
#include <vector>

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
    std::int64_t voterCount;
};

}

#endif //TGBOT_POLLOPTION_H
