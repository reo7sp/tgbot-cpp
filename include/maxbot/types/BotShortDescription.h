#ifndef MAXBOT_BOTSHORTDESCRIPTION_H
#define MAXBOT_BOTSHORTDESCRIPTION_H

#include <memory>
#include <string>

namespace MaxBot {

/**
 * @brief This object represents the bot's short description.
 *
 * @ingroup types
 */
class BotShortDescription {
public:
    typedef std::shared_ptr<BotShortDescription> Ptr;

    /**
     * @brief The bot's short description
     */
    std::string shortDescription;
};
}

#endif //MAXBOT_BOTSHORTDESCRIPTION_H
