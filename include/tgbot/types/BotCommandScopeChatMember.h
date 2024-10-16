#ifndef TGBOT_BOTCOMMANDSCOPECHATMEMBER_H
#define TGBOT_BOTCOMMANDSCOPECHATMEMBER_H

#include "tgbot/types/BotCommandScope.h"

#include <cstdint>
#include <memory>

namespace TgBot {

/**
 * @brief Represents the scope of bot commands, covering a specific member of a group or supergroup chat.
 *
 * @ingroup types
 */
class BotCommandScopeChatMember : public BotCommandScope {
public:
    static constexpr std::string_view TYPE = "chat_member";

    using Ptr = std::shared_ptr<BotCommandScopeChatMember>;

    BotCommandScopeChatMember() {
        this->type = TYPE;
    }

    /**
     * @brief Unique identifier for the target chat or username of the target supergroup (in the format @supergroupusername)
     */
    std::int64_t chatId{};

    /**
     * @brief Unique identifier of the target user
     */
    std::int64_t userId{};
};
}

#endif //TGBOT_BOTCOMMANDSCOPECHATMEMBER_H
