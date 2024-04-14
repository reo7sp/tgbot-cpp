#ifndef TGBOT_BOTDESCRIPTION_H
#define TGBOT_BOTDESCRIPTION_H

#include <memory>
#include <string>

namespace TgBot {

/**
 * @brief This object represents the bot's description.
 *
 * @ingroup types
 */
class BotDescription {
public:
    typedef std::shared_ptr<BotDescription> Ptr;

    /**
     * @brief The bot's description
     */
    std::string description;
};
}

#endif //TGBOT_BOTDESCRIPTION_H
