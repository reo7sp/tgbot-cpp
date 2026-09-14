#include "tgbot/TgException.h"

#include <utility>

namespace TgBot {

TgException::TgException(std::string_view description, ErrorCode errorCode,
                         std::shared_ptr<ResponseParameters> parameters)
    : runtime_error(std::string(description))
    , errorCode(errorCode)
    , parameters(std::move(parameters)) {
}

} // namespace TgBot
