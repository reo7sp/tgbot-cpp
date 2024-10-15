#include "tgbot/ApiImpl.h"
#include "tgbot/net/BoostHttpOnlySslClient.h"
#include "tgbot/Bot.h"

#include "tgbot/EventBroadcaster.h"

#include <memory>
#include <string>

namespace TgBot {

Bot::Bot(std::string token, std::unique_ptr<HttpClient> httpClient, const std::string& url)
    : _token(std::move(token))
    , _api(std::make_unique<ApiImpl>(_token, std::move(httpClient), url))
    , _eventBroadcaster(std::make_unique<EventBroadcaster>())
    , _eventHandler(getEvents()) {
}

std::unique_ptr<HttpClient> Bot::_getDefaultHttpClient() {
    return std::make_unique<BoostHttpOnlySslClient>();
}

}
