#ifndef TGBOT_FORCEREPLY_H
#define TGBOT_FORCEREPLY_H

#include "tgbot/types/GenericReply.h"
#include "tgbot/Optional.h"

#include <memory>
#include <string>

namespace TgBot {

/**
 * @brief Upon receiving a message with this object, Telegram clients will display a reply interface to the user (act as if the user has selected the bot's message and tapped 'Reply').
 *
 * This can be extremely useful if you want to create user-friendly step-by-step interfaces without having to sacrifice [privacy mode](https://core.telegram.org/bots/features#privacy-mode).
 * 
 * Example: A [poll bot](https://t.me/PollBot) for groups runs in privacy mode (only receives commands, replies to its messages and mentions).
 * There could be two ways to create a new poll:
 * - Explain the user how to send a command with parameters (e.g. /newpoll question answer1 answer2). May be appealing for hardcore users but lacks modern day polish.
 * - Guide the user through a step-by-step process. 'Please send me your question', 'Cool, now let's add the first answer option', 'Great. Keep adding answer options, then send /done when you're ready'.
 * The last option is definitely more attractive.
 * And if you use ForceReply in your bot's questions, it will receive the user's answers even if it only receives replies, commands and mentions - without any extra work for the user.
 *
 * @ingroup types
 */
class ForceReply : public GenericReply {

public:
    typedef std::shared_ptr<ForceReply> Ptr;

    /**
     * @brief Shows reply interface to the user, as if they manually selected the bot's message and tapped 'Reply'
     */
    bool forceReply;

    /**
     * @brief Optional. The placeholder to be shown in the input field when the reply is active; 1-64 characters
     */
    Optional<std::string> inputFieldPlaceholder;

    /**
     * @brief Optional. Use this parameter if you want to force reply from specific users only.
     *
     * Targets: 1) users that are @mentioned in the text of the Message object; 2) if the bot's message is a reply to a message in the same chat and forum topic, sender of the original message.
     */
    Optional<bool> selective;
};
}

#endif //TGBOT_FORCEREPLY_H
