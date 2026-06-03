#ifndef MAXBOT_BOTNAME_H
#define MAXBOT_BOTNAME_H

#include <memory>
#include <string>

namespace MaxBot {

/**
 * @brief This object represents the bot's name.
 *
 * @ingroup types
 */
class BotName {
public:
    typedef std::shared_ptr<BotName> Ptr;

    /**
     * @brief The bot's name
     */
    std::string name;
};
}

#endif //MAXBOT_BOTNAME_H
