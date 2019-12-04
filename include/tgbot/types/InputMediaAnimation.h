#ifndef TGBOT_INPUTMEDIAANIMATION_H
#define TGBOT_INPUTMEDIAANIMATION_H

#include <memory>
#include <string>

#include "tgbot/types/InputMedia.h"

namespace TgBot {

/**
 * @brief Represents a video to be sent.
 * @ingroup types
 */
class InputMediaAnimation : public InputMedia {
public:
    typedef std::shared_ptr<InputMediaAnimation> Ptr;

    InputMediaAnimation() {
        this->type = TYPE::ANIMATION;
    }
};
}

#endif //TGBOT_INPUTMEDIAANIMATION_H
