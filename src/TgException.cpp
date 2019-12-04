#include "tgbot/TgException.h"

namespace TgBot {

TgBot::TgException::TgException(const std::string description) : runtime_error(description) {
}

}
