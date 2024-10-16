#ifndef TGBOT_BOTCOMMANDSCOPECHATADMINISTRATORS_H
#define TGBOT_BOTCOMMANDSCOPECHATADMINISTRATORS_H

#include "tgbot/types/BotCommandScope.h"

#include <cstdint>
#include <memory>

namespace TgBot {

/**
 * @brief Represents the scope of bot commands, covering all administrators of a specific group or supergroup chat.
 *
 * @ingroup types
 */
class BotCommandScopeChatAdministrators : public BotCommandScope {
public:
    static constexpr std::string_view TYPE = "chat_administrators";

    using Ptr = std::shared_ptr<BotCommandScopeChatAdministrators>;

    BotCommandScopeChatAdministrators() {
        this->type = TYPE;
    }

    /**
     * @brief Unique identifier for the target chat or username of the target supergroup (in the format @supergroupusername)
     */
    std::int64_t chatId{};
};
}

#endif //TGBOT_BOTCOMMANDSCOPECHATADMINISTRATORS_H
