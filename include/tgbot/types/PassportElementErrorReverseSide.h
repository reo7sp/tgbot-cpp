#ifndef TGBOT_PASSPORTELEMENTERRORREVERSESIDE_H
#define TGBOT_PASSPORTELEMENTERRORREVERSESIDE_H

#include "tgbot/types/PassportElementError.h"

#include <string>
#include <memory>

namespace TgBot {

/**
 * @brief Represents an issue with the reverse side of a document.
 * The error is considered resolved when the file with reverse side of the document changes.
 *
 * @ingroup types
 */
class PassportElementErrorReverseSide : public PassportElementError {
public:
    static const std::string SOURCE;

    typedef std::shared_ptr<PassportElementErrorReverseSide> Ptr;

    PassportElementErrorReverseSide() {
        this->source = SOURCE;
    }

    /**
     * @brief Base64-encoded hash of the file with the reverse side of the document
     */
    std::string fileHash;
};
}

#endif //TGBOT_PASSPORTELEMENTERRORREVERSESIDE_H
