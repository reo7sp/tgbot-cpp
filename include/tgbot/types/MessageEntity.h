#ifndef TGBOT_MESSAGEENTITY_H
#define TGBOT_MESSAGEENTITY_H

#include "tgbot/types/User.h"

#include <cstdint>
#include <memory>
#include <string>

namespace TgBot {

/**
 * @brief This object represents one special entity in a text message.
 *
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
        Mention, Hashtag, Cashtag, BotCommand, Url, Email, PhoneNumber, Bold, Italic, Underline, Strikethrough, Spoiler, Blockquote, Code, Pre, TextLink, TextMention, CustomEmoji
    };

    /**
     * @brief Type of the entity.
     *
     * Currently, can be Type::Mention (@username), Type::Hashtag (#hashtag), Type::Cashtag ($USD), Type::BotCommand (/start@jobs_bot), Type::Url (https://telegram.org), Type::Email (do-not-reply@telegram.org), Type::PhoneNumber (+1-212-555-0123), Type::Bold (bold text), Type::Italic (italic text), Type::Underline (underlined text), Type::Strikethrough (strikethrough text), Type::Spoiler (spoiler message), Type::Blockquote (block quotation), Type::Code (monowidth string), Type::Pre (monowidth block), Type::TextLink (for clickable text URLs), Type::TextMention (for users [without usernames](https://telegram.org/blog/edit#new-mentions)), Type::CustomEmoji (for inline custom emoji stickers)
     */
    Type type;

    /**
     * @brief Offset in [UTF-16 code units](https://core.telegram.org/api/entities#entity-length) to the start of the entity
     *
     */
    std::int32_t offset;

    /**
     * @brief Length of the entity in [UTF-16 code units](https://core.telegram.org/api/entities#entity-length)
     */
    std::int32_t length;

    /**
     * @brief Optional. For Type::TextLink only, URL that will be opened after user taps on the text
     */
    std::string url;

    /**
     * @brief Optional. For Type::TextMention only, the mentioned user
     */
    User::Ptr user;

    /**
     * @brief Optional. For Type::Pre only, the programming language of the entity text
     */
    std::string language;

    /**
     * @brief Optional. For Type::CustomEmoji only, unique identifier of the custom emoji.
     *
     * Use Api::getCustomEmojiStickers to get full information about the sticker
     */
    std::string customEmojiId;
};
}

#endif //TGBOT_MESSAGEENTITY_H
