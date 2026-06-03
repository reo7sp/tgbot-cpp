#ifndef MAXBOT_TGLONGPOLL_H
#define MAXBOT_TGLONGPOLL_H

#include "maxbot/Api.h"
#include "maxbot/export.h"

#include <cstdint>
#include <vector>

namespace MaxBot {

class Bot;
class EventHandler;

/**
 * @brief This class handles long polling and updates parsing.
 *
 * @ingroup net
 */
class MAXBOT_API BotLongPoll {

public:
    BotLongPoll(const Api* api, const EventHandler* eventHandler, std::int32_t limit, std::int32_t timeout);
    BotLongPoll(const Bot& bot, std::int32_t limit = 100, std::int32_t timeout = 10);

    /**
     * @brief Starts long poll. After new update will come, this method will parse it and send to EventHandler which invokes your listeners. Designed to be executed in a loop.
     */
    void start();

private:
    const Api* _api;
    const EventHandler* _eventHandler;
    std::int64_t _marker = 0;
    std::int32_t _limit;
    std::int32_t _timeout;

    std::vector<Update::Ptr> _updates;
};

}

#endif //MAXBOT_TGLONGPOLL_H
