#ifndef TGBOT_REPLYKEYBOARDREMOVE_H
#define TGBOT_REPLYKEYBOARDREMOVE_H

#include "tgbot/Optional.h"
#include "tgbot/types/GenericReply.h"

#include <memory>

namespace TgBot {

/**
 * @brief Upon receiving a message with this object, Telegram clients will remove the current custom keyboard and display the default letter-keyboard.
 *
 * By default, custom keyboards are displayed until a new keyboard is sent by a bot.
 * An exception is made for one-time keyboards that are hidden immediately after the user presses a button (see ReplyKeyboardMarkup).
 *
 * @ingroup types
 */
class ReplyKeyboardRemove : public GenericReply {

public:
    typedef std::shared_ptr<ReplyKeyboardRemove> Ptr;

    /**
     * @brief Requests clients to remove the custom keyboard (user will not be able to summon this keyboard; if you want to hide the keyboard from sight but keep it accessible, use oneTimeKeyboard in ReplyKeyboardMarkup)
     */
    Required<bool> removeKeyboard;

    /**
     * @brief Optional. Use this parameter if you want to remove the keyboard for specific users only.
     *
     * Targets: 1) users that are @mentioned in the text of the Message object; 2) if the bot's message is a reply to a message in the same chat and forum topic, sender of the original message.
     * Example: A user votes in a poll, bot returns confirmation message in reply to the vote and removes the keyboard for that user, while still showing the keyboard with poll options to users who haven't voted yet.
     */
    Optional<bool> selective;
};
}

#endif //TGBOT_REPLYKEYBOARDREMOVE_H
