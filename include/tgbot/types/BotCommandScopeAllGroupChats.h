#ifndef TGBOT_BOTCOMMANDSCOPEALLGROUPCHATS_H
#define TGBOT_BOTCOMMANDSCOPEALLGROUPCHATS_H

#include "tgbot/types/BotCommandScope.h"

#include <memory>

namespace TgBot {

/**
 * @brief Represents the scope of bot commands, covering all group and supergroup chats.
 *
 * @ingroup types
 */
class BotCommandScopeAllGroupChats : public BotCommandScope {
public:
    static constexpr std::string_view TYPE = "all_group_chats";

    using Ptr = std::shared_ptr<BotCommandScopeAllGroupChats>;

    BotCommandScopeAllGroupChats() {
        this->type = TYPE;
    }
};
}

#endif //TGBOT_BOTCOMMANDSCOPEALLGROUPCHATS_H
