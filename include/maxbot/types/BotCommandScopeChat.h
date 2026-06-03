#ifndef MAXBOT_BOTCOMMANDSCOPECHAT_H
#define MAXBOT_BOTCOMMANDSCOPECHAT_H

#include "maxbot/types/BotCommandScope.h"

#include <cstdint>
#include <memory>

namespace MaxBot {

/**
 * @brief Represents the scope of bot commands, covering a specific chat.
 *
 * @ingroup types
 */
class BotCommandScopeChat : public BotCommandScope {
public:
    static const std::string TYPE;

    typedef std::shared_ptr<BotCommandScopeChat> Ptr;

    BotCommandScopeChat() {
        this->type = TYPE;
    }

    /**
     * @brief Unique identifier for the target chat or username of the target supergroup (in the format @supergroupusername)
     */
    std::int64_t chatId;
};
}

#endif //MAXBOT_BOTCOMMANDSCOPECHAT_H
