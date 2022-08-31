#ifndef TGBOT_PASSPORTELEMENTERRORFILE_H
#define TGBOT_PASSPORTELEMENTERRORFILE_H

#include "tgbot/types/PassportElementError.h"

#include <string>
#include <memory>

namespace TgBot {

/**
 * @brief Represents an issue with a document scan.
 * The error is considered resolved when the file with the document scan changes.
 *
 * @ingroup types
 */
class PassportElementErrorFile : public PassportElementError {
public:
    static const std::string SOURCE;

    typedef std::shared_ptr<PassportElementErrorFile> Ptr;

    PassportElementErrorFile() {
        this->source = SOURCE;
    }

    /**
     * @brief Base64-encoded file hash
     */
    std::string fileHash;
};
}

#endif //TGBOT_PASSPORTELEMENTERRORFILE_H
