/*
 * Copyright (c) 2015 Oleg Morozenkov
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef TGBOT_CPP_BOT_H
#define TGBOT_CPP_BOT_H

#include <string>
#include <utility>
#include "tgbot/Api.h"
#include "tgbot/EventBroadcaster.h"
#include "tgbot/EventHandler.h"
#include "tgbot/net/HttpClient.h"
#include "tgbot/net/BoostHttpOnlySslClient.h"

namespace TgBot {

/**
 * @brief This object holds other objects specific for this bot instance.
 *
 * @ingroup general
 */
class Bot {

public:
    explicit Bot(std::string token, const HttpClient& httpClient = _getDefaultHttpClient())
        : _token(std::move(token)), _api(_token, httpClient), _eventHandler(_eventBroadcaster) {
    }

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
        return _eventBroadcaster;
    }

    /**
     * @return Object which handles new update objects. Usually it's only needed for TgLongPoll, TgWebhookLocalServer and TgWebhookTcpServer objects.
     */
    inline const EventHandler& getEventHandler() const {
        return _eventHandler;
    }

private:
    static HttpClient& _getDefaultHttpClient() {
        static BoostHttpOnlySslClient instance;
        return instance;
    }

    const std::string _token;
    const Api _api;
    EventBroadcaster _eventBroadcaster;
    const EventHandler _eventHandler;
};

}

#endif //TGBOT_CPP_BOT_H
