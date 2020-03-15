#include "tgbot/Bot.h"

#include "tgbot/EventBroadcaster.h"

namespace TgBot {

Bot::Bot(std::string token, const HttpClient& httpClient)
    : _token(std::move(token))
    , _api(_token, httpClient)
#if __cplusplus > 201103L
    , _eventBroadcaster(std::make_unique<EventBroadcaster>())
#else
    , _eventBroadcaster(new EventBroadcaster())
#endif
    , _eventHandler(getEvents()) {
}

}
