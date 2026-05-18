#include "maxbot/BotException.h"

#include <string>

namespace MaxBot {

BotException::BotException(const std::string& description, ErrorCode errorCode) 
        : runtime_error(description), errorCode(errorCode)
{
}

}
