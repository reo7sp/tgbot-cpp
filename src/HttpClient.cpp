#include "tgbot/HttpClient.h"

namespace TgBot {

RequestCancelled::RequestCancelled()
    : std::runtime_error("request cancelled") {
}

RequestCancelled::RequestCancelled(std::string_view request)
    : std::runtime_error(std::string("request cancelled: ").append(request)) {
}

} // namespace TgBot
