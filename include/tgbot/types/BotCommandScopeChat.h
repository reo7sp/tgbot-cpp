#ifndef TGBOT_BOTCOMMANDSCOPECHAT_H
#define TGBOT_BOTCOMMANDSCOPECHAT_H

#include "tgbot/types/BotCommandScope.h"

#include <cstdint>
#include <memory>

namespace TgBot {

/**
 * @brief Represents the scope of bot commands, covering a specific chat.
 *
 * @ingroup types
 */
class BotCommandScopeChat : public BotCommandScope {
public:
    static constexpr std::string_view TYPE = "chat";

    using Ptr = std::shared_ptr<BotCommandScopeChat>;

    BotCommandScopeChat() {
        this->type = TYPE;
    }

    /**
     * @brief Unique identifier for the target chat or username of the target supergroup (in the format @supergroupusername)
     */
    std::int64_t chatId;
};
}

#endif //TGBOT_BOTCOMMANDSCOPECHAT_H
