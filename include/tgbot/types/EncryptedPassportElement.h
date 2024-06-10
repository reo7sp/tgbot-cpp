#ifndef TGBOT_ENCRYPTEDPASSPORTELEMENT_H
#define TGBOT_ENCRYPTEDPASSPORTELEMENT_H

#include "tgbot/types/PassportFile.h"

#include <memory>
#include <string>
#include <vector>

namespace TgBot {

/**
 * @brief Describes documents or other Telegram Passport elements shared with the bot by the user.
 *
 * @ingroup types
 */
class EncryptedPassportElement {

public:
    typedef std::shared_ptr<EncryptedPassportElement> Ptr;

    /**
     * @brief Element type. One of “personal_details”, “passport”, “driver_license”, “identity_card”, “internal_passport”, “address”, “utility_bill”, “bank_statement”, “rental_agreement”, “passport_registration”, “temporary_registration”, “phone_number”, “email”.
     */
    std::string type;

    /**
     * @brief Optional. Base64-encoded encrypted Telegram Passport element data provided by the user; available only for “personal_details”, “passport”, “driver_license”, “identity_card”, “internal_passport” and “address” types.
     *
     * Can be decrypted and verified using the accompanying EncryptedCredentials.
     */
    std::string data;

    /**
     * @brief Optional. User's verified phone number; available only for “phone_number” type
     */
    std::string phoneNumber;

    /**
     * @brief Optional. User's verified email address; available only for “email” type
     */
    std::string email;

    /**
     * @brief Optional. Array of encrypted files with documents provided by the user; available only for “utility_bill”, “bank_statement”, “rental_agreement”, “passport_registration” and “temporary_registration” types.
     *
     * Files can be decrypted and verified using the accompanying EncryptedCredentials.
     */
    std::vector<PassportFile::Ptr> files;

    /**
     * @brief Optional. Encrypted file with the front side of the document, provided by the user; available only for “passport”, “driver_license”, “identity_card” and “internal_passport”.
     *
     * The file can be decrypted and verified using the accompanying EncryptedCredentials.
     */
    PassportFile::Ptr frontSide;

    /**
     * @brief Optional. Encrypted file with the reverse side of the document, provided by the user; available only for “driver_license” and “identity_card”.
     *
     * The file can be decrypted and verified using the accompanying EncryptedCredentials.
     */
    PassportFile::Ptr reverseSide;

    /**
     * @brief Optional. Encrypted file with the selfie of the user holding a document, provided by the user; available if requested for “passport”, “driver_license”, “identity_card” and “internal_passport”.
     *
     * The file can be decrypted and verified using the accompanying EncryptedCredentials.
     */
    PassportFile::Ptr selfie;

    /**
     * @brief Optional. Array of encrypted files with translated versions of documents provided by the user; available if requested for “passport”, “driver_license”, “identity_card”, “internal_passport”, “utility_bill”, “bank_statement”, “rental_agreement”, “passport_registration” and “temporary_registration” types.
     *
     * Files can be decrypted and verified using the accompanying EncryptedCredentials.
     */
    std::vector<PassportFile::Ptr> translation;

    /**
     * @brief Base64-encoded element hash for using in PassportElementErrorUnspecified
     */
    std::string hash;
};
}

#endif //TGBOT_ENCRYPTEDPASSPORTELEMENT_H
