//
// Created by Andrea Giove on 17/04/16.
//

#ifndef TGBOT_INLINEKEYBOARDMARKUP_H
#define TGBOT_INLINEKEYBOARDMARKUP_H

#include <vector>
#include <memory>

#include "tgbot/types/GenericReply.h"
#include "tgbot/types/InlineKeyboardButton.h"

namespace TgBot {

/**
 * @brief This object represents an inline keyboard that appears right next to the message it belongs to.
 * 
 * @ingroup types
 */
class InlineKeyboardMarkup : public GenericReply {
public:
    typedef std::shared_ptr<InlineKeyboardMarkup> Ptr;

    /**
     * @brief Array of button rows, each represented by an Array of InlineKeyboardButton objects.
     */
    std::vector<std::vector<InlineKeyboardButton::Ptr>> inlineKeyboard;

};
}

#endif //TGBOT_INLINEKEYBOARDMARKUP_H
