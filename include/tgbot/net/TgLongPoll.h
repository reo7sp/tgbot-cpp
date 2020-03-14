#ifndef TGBOT_TGLONGPOLL_H
#define TGBOT_TGLONGPOLL_H

#include "tgbot/export.h"

#include <cstdint>
#include <memory>
#include <string>
#include <vector>

namespace TgBot {

class Api;
class Bot;
class EventHandler;

/**
 * @brief This class handles long polling and updates parsing.
 *
 * @ingroup net
 */
class TGBOT_API TgLongPoll {

public:
    TgLongPoll(const Api* api, const EventHandler* eventHandler, std::int32_t, std::int32_t, std::shared_ptr<std::vector<std::string>>);
    TgLongPoll(const Bot& bot, std::int32_t = 100, std::int32_t = 10, const std::shared_ptr<std::vector<std::string>>& = nullptr);

    /**
     * @brief Starts long poll. After new update will come, this method will parse it and send to EventHandler which invokes your listeners. Designed to be executed in a loop.
     */
    void start();

private:
    const Api* _api;
    const EventHandler* _eventHandler;
    std::int32_t _lastUpdateId = 0;
    std::int32_t _limit;
    std::int32_t _timeout;
    std::shared_ptr<std::vector<std::string>> _allowUpdates;
};

}

#endif //TGBOT_TGLONGPOLL_H
