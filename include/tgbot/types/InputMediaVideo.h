#ifndef TGBOT_INPUTMEDIAVIDEO_H
#define TGBOT_INPUTMEDIAVIDEO_H

#include "tgbot/types/InputMedia.h"

#include <memory>
#include <string>

namespace TgBot {

/**
 * @brief Represents a video to be sent.
 * @ingroup types
 */
class InputMediaVideo : public InputMedia {
public:
    typedef std::shared_ptr<InputMediaVideo> Ptr;

    InputMediaVideo() {
        this->type = TYPE::VIDEO;
    }
};
}

#endif //TGBOT_INPUTMEDIAVIDEO_H
