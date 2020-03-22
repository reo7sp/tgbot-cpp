#ifndef TGBOT_INPUTMEDIADOCUMENT_H
#define TGBOT_INPUTMEDIADOCUMENT_H

#include "tgbot/types/InputMedia.h"

#include <memory>
#include <string>

namespace TgBot {

/**
 * @brief Represents a video to be sent.
 * @ingroup types
 */
class InputMediaDocument : public InputMedia {
public:
    typedef std::shared_ptr<InputMediaDocument> Ptr;

    InputMediaDocument() {
        this->type = TYPE::DOCUMENT;
    }
};
}

#endif //TGBOT_INPUTMEDIADOCUMENT_H
