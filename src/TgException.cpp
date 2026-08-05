#include "tgbot/TgException.h"

namespace TgBot {

TgException::TgException(const std::string& description, ErrorCode errorCode)
    : runtime_error(description)
    , errorCode(errorCode) {
}

} // namespace TgBot
