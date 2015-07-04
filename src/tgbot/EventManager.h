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

#ifndef TGBOT_CPP_EVENTMANAGER_H
#define TGBOT_CPP_EVENTMANAGER_H

#include <string>
#include <functional>
#include <vector>
#include <map>

#include "tgbot/types/Update.h"
#include "tgbot/types/Message.h"

namespace TgBot {

class Bot;

class EventManager {

friend Bot;

public:
    typedef std::function<void (const Message::Ptr&, Bot* const)> Listener;

    inline void onAnyMessage(const Listener& listener) {
        _onAnyMessageListeners.push_back(listener);
    }

    inline void onCommand(const std::string& commandName, const Listener& listener) {
        _onCommandListeners[commandName] = listener;
    }

    inline void onUnknownCommand(const Listener& listener) {
        _onUnknownCommandListeners.push_back(listener);
    }

    inline void onNonCommandMessage(const Listener& listener) {
        _onNonCommandMessageListeners.push_back(listener);
    }

private:
    explicit EventManager(Bot* const bot);

    void handleUpdate(const Update::Ptr& update);

    Bot* const _bot;
    std::vector<Listener> _onAnyMessageListeners;
    std::map<std::string, Listener> _onCommandListeners;
    std::vector<Listener> _onUnknownCommandListeners;
    std::vector<Listener> _onNonCommandMessageListeners;
};

}

#endif //TGBOT_CPP_EVENTMANAGER_H
