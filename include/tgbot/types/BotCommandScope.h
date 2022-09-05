#ifndef TGBOT_BOTCOMMANDSCOPE_H
#define TGBOT_BOTCOMMANDSCOPE_H

#include <memory>
#include <string>

namespace TgBot {

/**
 * @brief This abstract class is base of all bot command scopes.
 * 
 * This object represents the scope to which bot commands are applied.
 *
 * @ingroup types
 */
class BotCommandScope {
public:
    typedef std::shared_ptr<BotCommandScope> Ptr;

    BotCommandScope() {}

    virtual ~BotCommandScope() {}

    /**
     * @brief Scope type
     */
    std::string type;
};
}

#endif //TGBOT_BOTCOMMANDSCOPE_H
