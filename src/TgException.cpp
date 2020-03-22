#include "tgbot/TgException.h"

#include <string>

namespace TgBot {

TgBot::TgException::TgException(const std::string& description) : runtime_error(description) {
}

}
