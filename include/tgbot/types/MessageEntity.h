#ifndef TGBOT_MESSAGEENTITY_H
#define TGBOT_MESSAGEENTITY_H

#include "tgbot/types/User.h"

#include <cstdint>
#include <memory>
#include <string>

namespace TgBot {

/**
 * @brief This object represents one special entity in a text message.
 * For example, hashtags, usernames, URLs, etc.
 *
 * @ingroup types
 */
class MessageEntity {
public:
    typedef std::shared_ptr<MessageEntity> Ptr;

    /**
     * @brief Enum of possible types.
     */
    enum class Type {
        Mention, Hashtag, Cashtag, BotCommand, Url, Email, PhoneNumber, Bold, Italic, Underline, Strikethrough, Spoiler, Code, Pre, TextLink, TextMention, CustomEmoji
    };

    /**
     * @brief Type of the entity.
     * Currently, can be “mention” (@username), “hashtag” (#hashtag), “cashtag” ($USD), “bot_command” (/start@jobs_bot), “url” (https://telegram.org), “email” (do-not-reply@telegram.org), “phone_number” (+1-212-555-0123), “bold” (bold text), “italic” (italic text), “underline” (underlined text), “strikethrough” (strikethrough text), “spoiler” (spoiler message), “code” (monowidth string), “pre” (monowidth block), “text_link” (for clickable text URLs), “text_mention” (for users without usernames), “custom_emoji” (for inline custom emoji stickers)
     */
    Type type;

    /**
     * @brief Offset in UTF-16 code units to the start of the entity
     */
    std::int32_t offset;

    /**
     * @brief Length of the entity in UTF-16 code units
     */
    std::int32_t length;

    /**
     * @brief Optional. For “text_link” only, URL that will be opened after user taps on the text
     */
    std::string url;

    /**
     * @brief Optional. For “text_mention” only, the mentioned user
     */
    User::Ptr user;

    /**
     * @brief Optional. For “pre” only, the programming language of the entity text
     */
    std::string language;

    /**
     * @brief Optional. For “custom_emoji” only, unique identifier of the custom emoji.
     * Use Api::getCustomEmojiStickers to get full information about the sticker
     */
    std::string customEmojiId;
};
}

#endif //TGBOT_MESSAGEENTITY_H
