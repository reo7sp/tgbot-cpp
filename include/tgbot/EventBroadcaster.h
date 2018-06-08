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
#include <unordered_map>

#include "tgbot/types/Message.h"
#include "tgbot/types/InlineQuery.h"
#include "tgbot/types/ChosenInlineResult.h"
#include "tgbot/types/CallbackQuery.h"

namespace TgBot {

class EventHandler;

/**
 * @brief This class holds all event listeners.
 * 
 * @ingroup general
 */
class EventBroadcaster {

friend EventHandler;

public:
	typedef std::function<void (const Message::Ptr)> MessageListener;
	typedef std::function<void (const InlineQuery::Ptr)> InlineQueryListener;
	typedef std::function<void (const ChosenInlineResult::Ptr)> ChosenInlineResultListener;
	typedef std::function<void (const CallbackQuery::Ptr)> CallbackQueryListener;

	/**
	 * @brief Registers listener which receives all messages which the bot can ever receive.
	 * @param listener Listener.
	 */
	inline void onAnyMessage(const MessageListener& listener) {
		_onAnyMessageListeners.push_back(listener);
	}

	/**
	 * @brief Registers listener which receives all messages with commands (messages with leading '/' char).
	 * @param commandName Command name which listener can handle.
	 * @param listener Listener.
	 */
	inline void onCommand(const std::string& commandName, const MessageListener& listener) {
		_onCommandListeners[commandName] = listener;
	}

	/**
	* @brief Registers listener which receives all messages with commands (messages with leading '/' char).
	* @param commandsList Commands names which listener can handle.
	* @param listener Listener.
	*/
	inline void onCommand(const std::initializer_list<std::string>& commandsList, const MessageListener& listener) {
		for (const auto& command : commandsList)
		{
			_onCommandListeners[command] = listener;
		}
	}

	/**
	 * @brief Registers listener which receives all messages with commands (messages with leading '/' char) which haven't been handled by other listeners.
	 * @param listener Listener.
	 */
	inline void onUnknownCommand(const MessageListener& listener) {
		_onUnknownCommandListeners.push_back(listener);
	}

	/**
	 * @brief Registers listener which receives all messages without commands (messages with no leading '/' char)
	 * @param listener Listener.
	 */
	inline void onNonCommandMessage(const MessageListener& listener) {
		_onNonCommandMessageListeners.push_back(listener);
	}

	/**
	 * @brief Registers listener which receives all the inline query.
	 * @param listener Listener.
	 */
	inline void onInlineQuery(const InlineQueryListener& listener) {
		_onInlineQueryListeners.push_back(listener);
	}

	/**
	 * @brief Registers listener which receives all the chosen inline result.
	 * @param listener Listener.
	 */
	inline void onChosenInlineResult(const ChosenInlineResultListener& listener){
		_onChosenInlineResultListeners.push_back(listener);
	}

	inline void onCallbackQuery(const CallbackQueryListener& listener){
		_onCallbackQueryListeners.push_back(listener);
	}

private:
	template<typename ListenerType, typename ObjectType>
	inline void broadcast(const std::vector<ListenerType>& listeners, const ObjectType object) const {
		if (!object)
			return;
		
		for (const ListenerType& item : listeners) {
			item(object);
		}
	}

	inline void broadcastAnyMessage(const Message::Ptr message) const {
		broadcast<MessageListener, Message::Ptr>(_onAnyMessageListeners, message);
	}

	inline bool broadcastCommand(const std::string command, const Message::Ptr message) const {
		std::unordered_map<std::string, MessageListener>::const_iterator iter = _onCommandListeners.find(command);
		if (iter == _onCommandListeners.end()) {
			return false;
		}
		iter->second(message);
		return true;
	}

	inline void broadcastUnknownCommand(const Message::Ptr message) const {
		broadcast<MessageListener, Message::Ptr>(_onUnknownCommandListeners, message);
	}

	inline void broadcastNonCommandMessage(const Message::Ptr message) const {
		broadcast<MessageListener, Message::Ptr>(_onNonCommandMessageListeners, message);
	}

	inline void broadcastInlineQuery(const InlineQuery::Ptr query) const {
		broadcast<InlineQueryListener, InlineQuery::Ptr>(_onInlineQueryListeners, query);
	}

	inline void broadcastChosenInlineResult(const ChosenInlineResult::Ptr result) const {
		broadcast<ChosenInlineResultListener, ChosenInlineResult::Ptr>(_onChosenInlineResultListeners, result);
	}

	inline void broadcastCallbackQuery(const CallbackQuery::Ptr result) const {
		broadcast<CallbackQueryListener, CallbackQuery::Ptr>(_onCallbackQueryListeners, result);
	}

	std::vector<MessageListener> _onAnyMessageListeners;
	std::unordered_map<std::string, MessageListener> _onCommandListeners;
	std::vector<MessageListener> _onUnknownCommandListeners;
	std::vector<MessageListener> _onNonCommandMessageListeners;
	std::vector<InlineQueryListener> _onInlineQueryListeners;
	std::vector<ChosenInlineResultListener> _onChosenInlineResultListeners;
	std::vector<CallbackQueryListener> _onCallbackQueryListeners;
};

}

#endif //TGBOT_EVENTBROADCASTER_H
