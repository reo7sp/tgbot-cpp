#include "tgbot/net/TgLongPoll.h"

#include "tgbot/ApiImpl.h"
#include "tgbot/Bot.h"
#include "tgbot/EventHandler.h"

#include <cstdint>
#include <memory>
#include <vector>
#include <utility>

namespace TgBot {

TgLongPoll::TgLongPoll(const Bot& bot, std::int32_t limit, std::int32_t timeout, const std::shared_ptr<std::vector<std::string>>& allowUpdates)
    : _api(&bot.getApi()), _eventHandler(&bot.getEventHandler()), _limit(limit), _timeout(timeout), _allowUpdates(allowUpdates) {
    dynamic_cast<const ApiImpl *>(_api)->_httpClient->_timeout = _timeout + 5;
}

void TgLongPoll::start() {
    // handle updates
    for (Update::Ptr& item : _updates) {
        if (item->updateId >= _lastUpdateId) {
            _lastUpdateId = item->updateId + 1;
        }
        _eventHandler->handleUpdate(item);
    }

    // confirm handled updates
    _updates = _api->getUpdates(_lastUpdateId, _limit, _timeout, _allowUpdates);
}

}
