#ifndef TGBOT_MENUBUTTONDEFAULT_H
#define TGBOT_MENUBUTTONDEFAULT_H

#include "tgbot/types/MenuButton.h"

#include <memory>

namespace TgBot {

/**
 * @brief Describes that no specific value for the menu button was set.
 *
 * @ingroup types
 */
class MenuButtonDefault : public MenuButton {
public:
    static constexpr std::string_view TYPE = "default";

    using Ptr = std::shared_ptr<MenuButtonDefault>;

    MenuButtonDefault() {
        this->type = TYPE;
    }
};
}

#endif //TGBOT_MENUBUTTONDEFAULT_H
