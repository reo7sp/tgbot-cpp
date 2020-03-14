#include "tgbot/Bot.h"

#include "tgbot/EventBroadcaster.h"

namespace TgBot {

Bot::Bot(std::string token, const HttpClient& httpClient)
    : _token(std::move(token))
    , _api(_token, httpClient)
    // uncomment when c++14 is available
    //, _eventBroadcaster(std::make_unique<EventBroadcaster>())
    , _eventBroadcaster(new EventBroadcaster())
    , _eventHandler(getEvents()) {
}

}
