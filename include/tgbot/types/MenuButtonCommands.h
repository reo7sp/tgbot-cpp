#ifndef TGBOT_MENUBUTTONCOMMANDS_H
#define TGBOT_MENUBUTTONCOMMANDS_H

#include "tgbot/types/MenuButton.h"

#include <memory>

namespace TgBot {

/**
 * @brief Represents a menu button, which opens the bot's list of commands.
 *
 * @ingroup types
 */
class MenuButtonCommands : public MenuButton {
public:
    static const std::string TYPE;

    typedef std::shared_ptr<MenuButtonCommands> Ptr;

    MenuButtonCommands() {
        this->type = TYPE;
    }
};
}

#endif //TGBOT_MENUBUTTONCOMMANDS_H
