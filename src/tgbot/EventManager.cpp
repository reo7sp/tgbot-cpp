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

#include "EventManager.h"

#include "tgbot/tools/StringTools.h"

using namespace std;

namespace TgBot {

EventManager::EventManager(Bot* const bot) : _bot(bot) {
}

void EventManager::handleUpdate(const Update::Ptr& update) {
    for (EventManager::Listener& item : _onAnyMessageListeners) {
        item(update->message, _bot);
    }
    if (StringTools::startsWith(update->message->text, "/")) {
        string command = update->message->text.substr(1, update->message->text.find(' ') - 2);
        for (pair<const string, Listener>& item : _onCommandListeners) {
            if (item.first == command) {
                item.second(update->message, _bot);
                return;
            }
        }
        for (EventManager::Listener& item : _onUnknownCommandListeners) {
            item(update->message, _bot);
        }
    } else {
        for (EventManager::Listener& item : _onNonCommandMessageListeners) {
            item(update->message, _bot);
        }
    }
}

}
