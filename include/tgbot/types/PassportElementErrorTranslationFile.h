#ifndef TGBOT_PASSPORTELEMENTERRORTRANSLATIONFILE_H
#define TGBOT_PASSPORTELEMENTERRORTRANSLATIONFILE_H

#include "tgbot/types/PassportElementError.h"

#include <string>
#include <memory>

namespace TgBot {

/**
 * @brief Represents an issue with one of the files that constitute the translation of a document.
 * The error is considered resolved when the file changes.
 *
 * @ingroup types
 */
class PassportElementErrorTranslationFile : public PassportElementError {
public:
    static const std::string SOURCE;

    typedef std::shared_ptr<PassportElementErrorTranslationFile> Ptr;

    PassportElementErrorTranslationFile() {
        this->source = SOURCE;
    }

    /**
     * @brief Base64-encoded file hash
     */
    std::string fileHash;
};
}

#endif //TGBOT_PASSPORTELEMENTERRORTRANSLATIONFILE_H
