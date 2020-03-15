#include "tgbot/Bot.h"

#include "tgbot/EventBroadcaster.h"

#if __cplusplus < 201402L 
namespace std {
    template<class T> struct _Unique_if {
        typedef unique_ptr<T> _Single_object;
    };

    template<class T> struct _Unique_if<T[]> {
        typedef unique_ptr<T[]> _Unknown_bound;
    };

    template<class T, size_t N> struct _Unique_if<T[N]> {
        typedef void _Known_bound;
    };

    template<class T, class... Args>
        typename _Unique_if<T>::_Single_object
        make_unique(Args&&... args) {
            return unique_ptr<T>(new T(std::forward<Args>(args)...));
        }

    template<class T>
        typename _Unique_if<T>::_Unknown_bound
        make_unique(size_t n) {
            typedef typename remove_extent<T>::type U;
            return unique_ptr<T>(new U[n]());
        }

    template<class T, class... Args>
        typename _Unique_if<T>::_Known_bound
        make_unique(Args&&...) = delete;
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
