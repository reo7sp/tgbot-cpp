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

#ifndef TGBOT_EVENTHANDLER_H
#define TGBOT_EVENTHANDLER_H

#include "tgbot/EventBroadcaster.h"
#include "tgbot/types/Update.h"
#include "tgbot/tools/StringTools.h"

namespace TgBot {

class EventHandler {

	void handleMessage(const Message::Ptr& message) const {
		_broadcaster->broadcastAnyMessage(message);

		if (StringTools::startsWith(message->text, "/")) {
			unsigned long splitPosition;
			unsigned long spacePosition = message->text.find(' ');
			unsigned long atSymbolPosition = message->text.find('@');
			if (spacePosition == message->text.npos) {
				if (atSymbolPosition == message->text.npos) {
					splitPosition = message->text.size();
				} else {
					splitPosition = atSymbolPosition;
				}
			} else if (atSymbolPosition == message->text.npos) {
				splitPosition = spacePosition;
			} else {
				splitPosition = std::min(spacePosition, atSymbolPosition);
			}
			std::string command = message->text.substr(1, splitPosition - 1);
			if (!_broadcaster->broadcastCommand(command, message)) {
				_broadcaster->broadcastUnknownCommand(message);
			}
		} else {
			_broadcaster->broadcastNonCommandMessage(message);
		}
	};

public:
	explicit EventHandler(const EventBroadcaster* broadcaster) : _broadcaster(broadcaster) {
	}

	inline void handleUpdate(const Update::Ptr& update) const {
		if (update->inlineQuery != NULL)
			_broadcaster->broadcastInlineQuery(update->inlineQuery);
		if (update->chosenInlineResult != NULL)
			_broadcaster->broadcastChosenInlineResult(update->chosenInlineResult);
		if (update->callbackQuery != NULL)
			_broadcaster->broadcastCallbackQuery(update->callbackQuery);
		if (update->message != NULL)
			handleMessage(update->message);
	}

private:
	const EventBroadcaster* _broadcaster;
};

}

#endif //TGBOT_EVENTHANDLER_H
