#ifndef TGBOT_SWITCHINLINEQUERYCHOSENCHAT_H
#define TGBOT_SWITCHINLINEQUERYCHOSENCHAT_H

#include <memory>
#include <string>

namespace TgBot {

/**
 * @brief This object represents an inline button that switches the current user to inline mode in a chosen chat, with an optional default inline query.
 *
 * @ingroup types
 */
class SwitchInlineQueryChosenChat {

public:
    typedef std::shared_ptr<SwitchInlineQueryChosenChat> Ptr;

    /**
     * @brief Optional. The default inline query to be inserted in the input field. If left empty, only the bot's username will be inserted
     */
    std::string query;

    /**
     * @brief Optional. True, if private chats with users can be chosen
     */
    bool allowUserChats;

    /**
     * @brief Optional. True, if private chats with bots can be chosen
     */
    bool allowBotChats;

    /**
     * @brief Optional. True, if group and supergroup chats can be chosen
     */
    bool allowGroupChats;

    /**
     * @brief Optional. True, if channel chats can be chosen
     */
    bool allowChannelChats;
};
}

#endif //TGBOT_SWITCHINLINEQUERYCHOSENCHAT_H
