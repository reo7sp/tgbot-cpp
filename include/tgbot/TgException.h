#ifndef TGBOT_TGEXCEPTION_H
#define TGBOT_TGEXCEPTION_H

#include "tgbot/export.h"

#include <string>
#include <stdexcept>
#include <cstdint>

namespace TgBot {

/**
 * @brief Exception type which is only thrown when Telegram refuses API request.
 *
 * @ingroup general
 */
class TGBOT_API TgException : public std::runtime_error {

public:

    /**
     * @brief Enum of possible errors from Api requests 
     */
    enum class ErrorCode : std::int32_t {
        Undefined = 0,
        BadRequest = 400, Unauthorized = 401, 
        Forbidden = 403, NotFound = 404, 
        Flood = 402, Conflict = 409, Internal = 500,
        HtmlResponse = 100, InvalidJson = 101
    };

    explicit TgException(const std::string& description, ErrorCode errorCode);

    const ErrorCode errorCode;
};

}

#endif //TGBOT_TGEXCEPTION_H
