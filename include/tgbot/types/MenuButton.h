#ifndef TGBOT_MENUBUTTON_H
#define TGBOT_MENUBUTTON_H

#include <memory>
#include <string>

namespace TgBot {

/**
 * @brief This abstract class is base of all bot menu buttons.
 * 
 * This object describes the bot's menu button in a private chat.
 * If a menu button other than MenuButtonDefault is set for a private chat, then it is applied in the chat.
 * Otherwise the default menu button is applied.
 * By default, the menu button opens the list of bot commands.
 *
 * @ingroup types
 */
class MenuButton {
public:
    typedef std::shared_ptr<MenuButton> Ptr;

    MenuButton() {}

    virtual ~MenuButton() {}

    /**
     * @brief Type of the button
     */
    std::string type;
};
}

#endif //TGBOT_MENUBUTTON_H
