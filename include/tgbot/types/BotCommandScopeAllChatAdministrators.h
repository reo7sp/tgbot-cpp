#ifndef TGBOT_BOTCOMMANDSCOPEALLCHATADMINISTRATORS_H
#define TGBOT_BOTCOMMANDSCOPEALLCHATADMINISTRATORS_H

#include "tgbot/types/BotCommandScope.h"

#include <memory>

namespace TgBot {

/**
 * @brief Represents the scope of bot commands, covering all group and supergroup chat administrators.
 *
 * @ingroup types
 */
class BotCommandScopeAllChatAdministrators : public BotCommandScope {
public:
    static const std::string TYPE;

    typedef std::shared_ptr<BotCommandScopeAllChatAdministrators> Ptr;

    BotCommandScopeAllChatAdministrators() {
        this->type = TYPE;
    }
};
}

#endif //TGBOT_BOTCOMMANDSCOPEALLCHATADMINISTRATORS_H
