#ifndef MAXBOT_CPP_BOT_H
#define MAXBOT_CPP_BOT_H

#include "maxbot/Api.h"
#include "maxbot/EventHandler.h"

#include <memory>
#include <string>
#include <utility>

namespace MaxBot {

class EventBroadcaster;
class HttpClient;

/**
 * @brief This object holds other objects specific for this bot instance.
 *
 * @ingroup general
 */
class MAXBOT_API Bot {

public:
    explicit Bot(const HttpClient &httpClient, const std::string& url="https://platform-api.max.ru");

    /**
     * @return Object which can execute Telegram Bot API methods.
     */
    inline const Api& getApi() const {
        return _api;
    }

    /**
     * @return Object which holds all event listeners.
     */
    inline EventBroadcaster& getEvents() {
        return *_eventBroadcaster;
    }

    /**
     * @return Object which handles new update objects. Usually it's only needed for BotLongPoll, BotWebhookLocalServer and BotWebhookTcpServer objects.
     */
    inline const EventHandler& getEventHandler() const {
        return _eventHandler;
    }

private:
    const Api _api;
    std::unique_ptr<EventBroadcaster> _eventBroadcaster;
    const EventHandler _eventHandler;
};

}

#endif //MAXBOT_CPP_BOT_H
