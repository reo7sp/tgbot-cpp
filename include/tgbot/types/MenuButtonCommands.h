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
    static constexpr std::string_view TYPE = "commands";

    using Ptr = std::shared_ptr<MenuButtonCommands>;

    MenuButtonCommands() {
        this->type = TYPE;
    }
};
}

#endif //TGBOT_MENUBUTTONCOMMANDS_H
