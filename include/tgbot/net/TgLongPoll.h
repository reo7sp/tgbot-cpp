#ifndef TGBOT_TGLONGPOLL_H
#define TGBOT_TGLONGPOLL_H

#include "tgbot/Bot.h"
#include "tgbot/Api.h"
#include "tgbot/EventHandler.h"

namespace TgBot {

/**
 * @brief This class handles long polling and updates parsing.
 *
 * @ingroup net
 */
class TgLongPoll {

public:
    TgLongPoll(const Api* api, const EventHandler* eventHandler, int32_t, int32_t, const std::shared_ptr<std::vector<std::string>>&);
    TgLongPoll(const Bot& bot, int32_t = 100, int32_t = 60, const std::shared_ptr<std::vector<std::string>>& = nullptr);

    /**
     * @brief Starts long poll. After new update will come, this method will parse it and send to EventHandler which invokes your listeners. Designed to be executed in a loop.
     */
    void start();

private:
    const Api* _api;
    const EventHandler* _eventHandler;
    int32_t _lastUpdateId = 0;
    int32_t _limit;
    int32_t _timeout;
    std::shared_ptr<std::vector<std::string>> _allowupdates;
};

}

#endif //TGBOT_TGLONGPOLL_H
