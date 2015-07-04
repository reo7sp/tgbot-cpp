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

#include "tgbot/Api.h"
#include "tgbot/EventManager.h"
#include "tgbot/Http.h"
#include "tgbot/Parser.h"

namespace TgBot {

class Bot {

public:
    explicit Bot(const std::string& token);

    void startLongPoll();

    inline void startServer(unsigned short port) {
        _http.startServer(port, _webhooksServerHandler);
    }

    inline void startServer(const std::string& unixSocketPath) {
        _http.startServer(unixSocketPath, _webhooksServerHandler);
    }

    inline const std::string& getToken() const {
        return _token;
    }

    inline const Api& getApi() const {
        return _api;
    }

    inline const EventManager& getEvents() const {
        return _events;
    }

    inline EventManager& getEvents() {
        return _events;
    }

    inline const Http& getHttp() const {
        return _http;
    }

    inline Http& getHttp() {
        return _http;
    }

    inline const Parser& getParser() const {
        return _parser;
    }

private:
    const std::string _token;
    const Api _api;
    EventManager _events;
    Http _http;
    const Parser _parser;
    const Http::ServerHandler _webhooksServerHandler;
    int32_t _lastUpdateId = 0;
};

}

#endif //TGBOT_CPP_BOT_H
