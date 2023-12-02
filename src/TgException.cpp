#include "tgbot/TgException.h"

#include <string>

namespace TgBot {

TgException::TgException(const std::string& description, ErrorCode errorCode) 
        : runtime_error(description), errorCode(errorCode)
{
}

}
