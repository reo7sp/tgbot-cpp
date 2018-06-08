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

#include "tgbot/net/TgLongPoll.h"

namespace TgBot {

TgLongPoll::TgLongPoll(const Api* api, const EventHandler* eventHandler, int32_t limit, int32_t timeout, const std::shared_ptr<std::vector<std::string>>& allowupdates)
	: _api(api), _eventHandler(eventHandler), _limit(limit), _timeout(timeout), _allowupdates(allowupdates) {
}

TgLongPoll::TgLongPoll(const Bot& bot, int32_t limit, int32_t timeout, const std::shared_ptr<std::vector<std::string>>& allowupdates) :
	TgLongPoll(&bot.getApi(), &bot.getEventHandler(), limit, timeout, allowupdates) {
}

void TgLongPoll::start() {
	auto updates = _api->getUpdates(_lastUpdateId, _limit, _timeout, _allowupdates);
	for (auto& item : updates) {
		if (item->updateId >= _lastUpdateId) {
			_lastUpdateId = item->updateId + 1;
		}
		_eventHandler->handleUpdate(item);
	}
}

}
