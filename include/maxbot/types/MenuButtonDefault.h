#ifndef MAXBOT_MENUBUTTONDEFAULT_H
#define MAXBOT_MENUBUTTONDEFAULT_H

#include "maxbot/types/MenuButton.h"

#include <memory>

namespace MaxBot {

/**
 * @brief Describes that no specific value for the menu button was set.
 *
 * @ingroup types
 */
class MenuButtonDefault : public MenuButton {
public:
    static const std::string TYPE;

    typedef std::shared_ptr<MenuButtonDefault> Ptr;

    MenuButtonDefault() {
        this->type = TYPE;
    }
};
}

#endif //MAXBOT_MENUBUTTONDEFAULT_H
