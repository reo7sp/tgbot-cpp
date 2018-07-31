//
// Created by Andrea Giove on 17/04/16.
//

#ifndef TGBOT_MESSAGEENTITY_H
#define TGBOT_MESSAGEENTITY_H

#include <memory>
#include <string>
#include "tgbot/types/User.h"

namespace TgBot {

/**
 * @brief This object represents one special entity in a text message. For example, hashtags, usernames, URLs, etc.
 * 
 * @ingroup types
 */
class MessageEntity {
public:
    typedef std::shared_ptr<MessageEntity> Ptr;

    /**
     * @brief Type of the entity.
     * 
     * Can be mention (@username), hashtag, cashtag, bot_command, url, email, phone_number, bold (bold text), italic (italic text), code (monowidth string), pre (monowidth block), text_link (for clickable text URLs), text_mention (for users without usernames)
     */
    std::string type;

    /**
     * @brief Offset in UTF-16 code units to the start of the entity.
     */
    int32_t offset;

    /**
     * @brief Length of the entity in UTF-16 code units
     */
    int32_t length;

    /**
     * @brief Optional. For “text_link” only, url that will be opened after user taps on the text
     */
    std::string url;

    /**
     * @brief Optional. For “text_mention” only, the mentioned user
     */
    User::Ptr user;
};
}

#endif //TGBOT_MESSAGEENTITY_H
