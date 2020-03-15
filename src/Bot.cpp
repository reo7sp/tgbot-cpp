#include "tgbot/Bot.h"

#include "tgbot/EventBroadcaster.h"

#if __cplusplus == 201103L
namespace std {
    template<typename T>
    inline std::unique_ptr<T> make_unique() {
        return std::unique_ptr<T>(new T());
    }
}
#endif

namespace TgBot {

Bot::Bot(std::string token, const HttpClient& httpClient)
    : _token(std::move(token))
    , _api(_token, httpClient)
    , _eventBroadcaster(std::make_unique<EventBroadcaster>())
    , _eventHandler(getEvents()) {
}

}
