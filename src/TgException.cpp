#include "tgbot/TgException.h"

namespace TgBot {

TgException::TgException(std::string_view description, ErrorCode errorCode)
    : runtime_error(std::string(description))
    , errorCode(errorCode) {
}

} // namespace TgBot
