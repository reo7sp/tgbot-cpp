#ifndef TGBOT_BOTCOMMANDSCOPEALLPRIVATECHATS_H
#define TGBOT_BOTCOMMANDSCOPEALLPRIVATECHATS_H

#include "tgbot/types/BotCommandScope.h"

#include <memory>

namespace TgBot {

/**
 * @brief Represents the scope of bot commands, covering all private chats.
 *
 * @ingroup types
 */
class BotCommandScopeAllPrivateChats : public BotCommandScope {
public:
    static constexpr std::string_view TYPE = "all_private_chats";

    using Ptr = std::shared_ptr<BotCommandScopeAllPrivateChats>;

    BotCommandScopeAllPrivateChats() {
        this->type = TYPE;
    }
};
}

#endif //TGBOT_BOTCOMMANDSCOPEALLPRIVATECHATS_H
