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

#ifndef TGBOT_EVENTBROADCASTER_H
#define TGBOT_EVENTBROADCASTER_H

#include <string>
#include <functional>
#include <vector>
#include <map>

#include "tgbot/types/Message.h"

namespace TgBot {

class EventHandler;

class EventBroadcaster {

friend EventHandler;

public:
    typedef std::function<void (const Message::Ptr&)> MessageListener;

    inline void onAnyMessage(const MessageListener& listener) {
        _onAnyMessageListeners.push_back(listener);
    }

    inline void onCommand(const std::string& commandName, const MessageListener& listener) {
        _onCommandListeners[commandName] = listener;
    }

    inline void onUnknownCommand(const MessageListener& listener) {
        _onUnknownCommandListeners.push_back(listener);
    }

    inline void onNonCommandMessage(const MessageListener& listener) {
        _onNonCommandMessageListeners.push_back(listener);
    }

private:
    inline void broadcastAnyMessage(const Message::Ptr& message) const {
        for (const MessageListener& item : _onAnyMessageListeners) {
            item(message);
        }
    }

    inline bool broadcastCommand(const std::string command, const Message::Ptr& message) const {
        std::map<std::string, MessageListener>::const_iterator iter = _onCommandListeners.find(command);
        if (iter == _onCommandListeners.end()) {
            return false;
        }
        iter->second(message);
        return true;
    }

    inline void broadcastUnknownCommand(const Message::Ptr& message) const {
        for (const MessageListener& item : _onUnknownCommandListeners) {
            item(message);
        }
    }

    inline void broadcastNonCommandMessage(const Message::Ptr& message) const {
        for (const MessageListener& item : _onNonCommandMessageListeners) {
            item(message);
        }
    }

    std::vector<MessageListener> _onAnyMessageListeners;
    std::map<std::string, MessageListener> _onCommandListeners;
    std::vector<MessageListener> _onUnknownCommandListeners;
    std::vector<MessageListener> _onNonCommandMessageListeners;
};

}

#endif //TGBOT_EVENTBROADCASTER_H
