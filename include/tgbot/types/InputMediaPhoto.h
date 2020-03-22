#ifndef TGBOT_INPUTMEDIAPHOTO_H
#define TGBOT_INPUTMEDIAPHOTO_H

#include "tgbot/types/InputMedia.h"

#include <memory>
#include <string>

namespace TgBot {

/**
 * @brief Represents a photo to be sent.
 * @ingroup types
 */
class InputMediaPhoto : public InputMedia {
public:
    typedef std::shared_ptr<InputMediaPhoto> Ptr;

    InputMediaPhoto() {
        this->type = TYPE::PHOTO;
    }
};
}

#endif //TGBOT_INPUTMEDIAPHOTO_H
