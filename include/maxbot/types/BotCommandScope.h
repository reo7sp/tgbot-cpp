#ifndef MAXBOT_BOTCOMMANDSCOPE_H
#define MAXBOT_BOTCOMMANDSCOPE_H

#include <memory>
#include <string>

namespace MaxBot {

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

#endif //MAXBOT_BOTCOMMANDSCOPE_H
