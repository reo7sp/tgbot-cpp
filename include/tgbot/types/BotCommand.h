#ifndef TGBOT_BOTCOMMAND_H
#define TGBOT_BOTCOMMAND_H

#include <cstdint>
#include <string>
#include <memory>

namespace TgBot {

/**
 * @brief This object represents a bot command.
 *
 * https://core.telegram.org/bots/api#botcommand
 * @ingroup types
 */
class BotCommand {
public:
    typedef std::shared_ptr<BotCommand> Ptr;
    BotCommand() { }

    virtual ~BotCommand() { }

    /**
     * @brief command label.
     */
    std::string command;

    /**
     * @brief description label.
     */
    std::string description;

};
}

#endif //TGBOT_BOTCOMMAND_H
