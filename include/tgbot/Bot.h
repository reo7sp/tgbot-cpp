#ifndef TGBOT_CPP_BOT_H
#define TGBOT_CPP_BOT_H

#include "tgbot/Api.h"
#include "tgbot/EventHandler.h"

#include <memory>
#include <string>
#include <utility>

namespace TgBot {

class EventBroadcaster;
class HttpClient;

/**
 * @brief This object holds other objects specific for this bot instance.
 *
 * @ingroup general
 */
class TGBOT_API Bot {

public:
    explicit Bot(std::string token, const HttpClient &httpClient = _getDefaultHttpClient());

    /**
     * @return Token for accessing api.
     */
    inline const std::string& getToken() const {
        return _token;
    }

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
     * @return Object which handles new update objects. Usually it's only needed for TgLongPoll, TgWebhookLocalServer and TgWebhookTcpServer objects.
     */
    inline const EventHandler& getEventHandler() const {
        return _eventHandler;
    }

private:
    static HttpClient &_getDefaultHttpClient();

    const std::string _token;
    const Api _api;
    std::unique_ptr<EventBroadcaster> _eventBroadcaster;
    const EventHandler _eventHandler;
};

}

#endif //TGBOT_CPP_BOT_H
