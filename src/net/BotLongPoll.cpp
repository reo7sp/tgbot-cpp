#include "maxbot/net/BotLongPoll.h"

#include "maxbot/Api.h"
#include "maxbot/Bot.h"
#include "maxbot/EventHandler.h"

#include <cstdint>
#include <memory>
#include <vector>
#include <utility>

namespace MaxBot {

BotLongPoll::BotLongPoll(const Api* api, const EventHandler* eventHandler, std::int32_t limit, std::int32_t timeout)
    : _api(api), _eventHandler(eventHandler), _limit(limit), _timeout(timeout)
{

    const_cast<MaxBot::HttpClient&>(_api->_httpClient)._timeout = _timeout + 5;
}

BotLongPoll::BotLongPoll(const Bot& bot, std::int32_t limit, std::int32_t timeout)
    : BotLongPoll(&bot.getApi(), &bot.getEventHandler(), limit, timeout) {
}

void BotLongPoll::start() {
	// handle updates
	for (Update::Ptr& item : _updates)
		_eventHandler->handleUpdate(item);

	// confirm handled updates
	auto resp = _api->getUpdates(_marker, _limit, _timeout);
	_marker = resp->marker;
	_updates = std::move(resp->updates);
}

}
