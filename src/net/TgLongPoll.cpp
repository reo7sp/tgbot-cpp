#include "tgbot/net/TgLongPoll.h"

namespace TgBot {

TgLongPoll::TgLongPoll(const Api* api, const EventHandler* eventHandler, int32_t limit, int32_t timeout, const std::shared_ptr<std::vector<std::string>>& allowupdates)
    : _api(api), _eventHandler(eventHandler), _limit(limit), _timeout(timeout), _allowupdates(allowupdates) {
}

TgLongPoll::TgLongPoll(const Bot& bot, int32_t limit, int32_t timeout, const std::shared_ptr<std::vector<std::string>>& allowupdates) :
    TgLongPoll(&bot.getApi(), &bot.getEventHandler(), limit, timeout, allowupdates) {
}

void TgLongPoll::start() {
    std::vector<Update::Ptr> updates = _api->getUpdates(_lastUpdateId, _limit, _timeout, _allowupdates);
    for (Update::Ptr& item : updates) {
        if (item->updateId >= _lastUpdateId) {
            _lastUpdateId = item->updateId + 1;
        }
        _eventHandler->handleUpdate(item);
    }
}

}
