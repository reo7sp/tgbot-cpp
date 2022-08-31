#ifndef TGBOT_CPP_PASSPORTDATA_H
#define TGBOT_CPP_PASSPORTDATA_H

#include "tgbot/types/EncryptedPassportElement.h"
#include "tgbot/types/EncryptedCredentials.h"
#include <memory>

namespace TgBot {

/**
 * @brief Contains information about Telegram Passport data shared with the bot by the user.
 *
 * @ingroup types
 */
class PassportData {

public:
    typedef std::shared_ptr<PassportData> Ptr;

    /**
     * @brief Array with information about documents and other Telegram Passport elements that was shared with the bot
     */
    std::vector<EncryptedPassportElement::Ptr> data;

    /**
     * @brief Encrypted credentials required to decrypt the data
     */
    EncryptedCredentials::Ptr credentials;
};
}

#endif //TGBOT_CPP_PASSPORTDATA_H
