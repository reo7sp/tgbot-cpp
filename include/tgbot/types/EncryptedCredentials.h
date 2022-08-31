#ifndef TGBOT_CPP_ENCRYPTEDCREDENTIALS_H
#define TGBOT_CPP_ENCRYPTEDCREDENTIALS_H

#include <memory>
#include <string>

namespace TgBot {

/**
 * @brief Contains data required for decrypting and authenticating EncryptedPassportElement.
 * See https://core.telegram.org/passport#receiving-information for a complete description of the data decryption and authentication
 *
 * @ingroup types
 */
class EncryptedCredentials {

public:
    typedef std::shared_ptr<EncryptedCredentials> Ptr;

    /**
     * @brief Base64-encoded encrypted JSON-serialized data with unique user's payload, data hashes and secrets required for @ref EncryptedPassportElement decryption and authentication
     */
    std::string data;

    /**
     * @brief Base64-encoded data hash for data authentication
     */
    std::string hash;

    /**
     * @brief Base64-encoded secret, encrypted with the bot's public RSA key, required for data decryption
     */
    std::string secret;
};
}

#endif //TGBOT_CPP_ENCRYPTEDCREDENTIALS_H
