#ifndef MAXBOT_BOTCOMMANDSCOPEALLGROUPCHATS_H
#define MAXBOT_BOTCOMMANDSCOPEALLGROUPCHATS_H

#include "maxbot/types/BotCommandScope.h"

#include <memory>

namespace MaxBot {

/**
 * @brief Represents the scope of bot commands, covering all group and supergroup chats.
 *
 * @ingroup types
 */
class BotCommandScopeAllGroupChats : public BotCommandScope {
public:
    static const std::string TYPE;

    typedef std::shared_ptr<BotCommandScopeAllGroupChats> Ptr;

    BotCommandScopeAllGroupChats() {
        this->type = TYPE;
    }
};
}

#endif //MAXBOT_BOTCOMMANDSCOPEALLGROUPCHATS_H
