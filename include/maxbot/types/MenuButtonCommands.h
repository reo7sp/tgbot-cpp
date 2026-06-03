#ifndef MAXBOT_MENUBUTTONCOMMANDS_H
#define MAXBOT_MENUBUTTONCOMMANDS_H

#include "maxbot/types/MenuButton.h"

#include <memory>

namespace MaxBot {

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

#endif //MAXBOT_MENUBUTTONCOMMANDS_H
