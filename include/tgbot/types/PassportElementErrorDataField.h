#ifndef TGBOT_PASSPORTELEMENTERRORDATAFILED_H
#define TGBOT_PASSPORTELEMENTERRORDATAFILED_H

#include "tgbot/types/PassportElementError.h"

#include <string>
#include <memory>

namespace TgBot {

/**
 * @brief Represents an issue in one of the data fields that was provided by the user.
 * The error is considered resolved when the field's value changes.
 *
 * @ingroup types
 */
class PassportElementErrorDataField : public PassportElementError {
public:
    static const std::string SOURCE;

    typedef std::shared_ptr<PassportElementErrorDataField> Ptr;

    PassportElementErrorDataField() {
        this->source = SOURCE;
    }

    /**
     * @brief Name of the data field which has the error
     */
    std::string fieldName;

    /**
     * @brief Base64-encoded data hash
     */
    std::string dataHash;
};
}

#endif //TGBOT_PASSPORTELEMENTERRORDATAFILED_H
