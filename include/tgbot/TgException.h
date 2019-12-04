#ifndef TGBOT_TGEXCEPTION_H
#define TGBOT_TGEXCEPTION_H

#include <string>
#include <stdexcept>

namespace TgBot {

/**
 * @brief Exception type which is only thrown when Telegram refuses API request.
 *
 * @ingroup general
 */
class TgException : public std::runtime_error {

public:
    explicit TgException(const std::string description);
};

}

#endif //TGBOT_TGEXCEPTION_H
