#ifndef TGBOT_PASSPORTELEMENTERRORFILES_H
#define TGBOT_PASSPORTELEMENTERRORFILES_H

#include "tgbot/types/PassportElementError.h"

#include <string>
#include <memory>
#include <vector>

namespace TgBot {

/**
 * @brief Represents an issue with a list of scans.
 * The error is considered resolved when the list of files containing the scans changes.
 *
 * @ingroup types
 */
class PassportElementErrorFiles : public PassportElementError {
public:
    static constexpr std::string_view SOURCE = "files";

    using Ptr = std::shared_ptr<PassportElementErrorFiles>;

    PassportElementErrorFiles() {
        this->source = SOURCE;
    }

    /**
     * @brief List of base64-encoded file hashes
     */
    std::vector<std::string> fileHashes;
};
}

#endif //TGBOT_PASSPORTELEMENTERRORFILES_H
