#include "maxbot/Bot.h"

#include "maxbot/EventBroadcaster.h"

#include <memory>
#include <string>

namespace MaxBot {

Bot::Bot(const HttpClient& httpClient, const std::string& url)
    : _api(httpClient, url)
    , _eventBroadcaster(std::make_unique<EventBroadcaster>())
    , _eventHandler(getEvents()) {
}

}
