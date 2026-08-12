#include "tgbot/HttpClient.h"

namespace TgBot {

RequestCancelled::RequestCancelled()
    : std::runtime_error("request cancelled") {
}

RequestCancelled::RequestCancelled(const std::string& request)
    : std::runtime_error("request cancelled: " + request) {
}

} // namespace TgBot
