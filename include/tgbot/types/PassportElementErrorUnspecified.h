#ifndef TGBOT_PASSPORTELEMENTERRORUNSPECIFIED_H
#define TGBOT_PASSPORTELEMENTERRORUNSPECIFIED_H

#include "tgbot/types/PassportElementError.h"

#include <string>
#include <memory>

namespace TgBot {

/**
 * @brief Represents an issue in an unspecified place.
 * The error is considered resolved when new data is added.
 *
 * @ingroup types
 */
class PassportElementErrorUnspecified : public PassportElementError {
public:
    static const std::string SOURCE;

    typedef std::shared_ptr<PassportElementErrorUnspecified> Ptr;

    PassportElementErrorUnspecified() {
        this->source = SOURCE;
    }

    /**
     * @brief Base64-encoded element hash
     */
    std::string elementHash;
};
}

#endif //TGBOT_PASSPORTELEMENTERRORUNSPECIFIED_H
