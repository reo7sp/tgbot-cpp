#ifndef TGBOT_PASSPORTELEMENTERROR_H
#define TGBOT_PASSPORTELEMENTERROR_H

#include <memory>
#include <string>

namespace TgBot {

/**
 * @brief This abstract class is base of all passport element errors.
 * 
 * This object represents an error in the Telegram Passport element which was submitted that should be resolved by the user.
 *
 * @ingroup types
 */
class PassportElementError {
public:
    typedef std::shared_ptr<PassportElementError> Ptr;

    PassportElementError() { }

    virtual ~PassportElementError() { }

    /**
     * @brief Error source
     */
    std::string source;

    /**
     * @brief See description of derived classes.
     * Type of element of the user's Telegram Passport which has the issue
     */
    std::string type;

    /**
     * @brief Error message
     */
    std::string message;
};
}

#endif //TGBOT_PASSPORTELEMENTERROR_H
