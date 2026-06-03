#ifndef MAXBOT_BOTCOMMANDSCOPEALLCHATADMINISTRATORS_H
#define MAXBOT_BOTCOMMANDSCOPEALLCHATADMINISTRATORS_H

#include "maxbot/types/BotCommandScope.h"

#include <memory>

namespace MaxBot {

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

#endif //MAXBOT_BOTCOMMANDSCOPEALLCHATADMINISTRATORS_H
