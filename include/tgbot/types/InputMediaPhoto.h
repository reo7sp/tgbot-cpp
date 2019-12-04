#ifndef TGBOT_INPUTMEDIAPHOTO_H
#define TGBOT_INPUTMEDIAPHOTO_H

#include <memory>
#include <string>

#include "tgbot/types/InputMedia.h"

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
