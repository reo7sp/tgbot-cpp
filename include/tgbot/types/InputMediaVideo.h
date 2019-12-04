#ifndef TGBOT_INPUTMEDIAVIDEO_H
#define TGBOT_INPUTMEDIAVIDEO_H

#include <memory>
#include <string>

#include "tgbot/types/InputMedia.h"

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
