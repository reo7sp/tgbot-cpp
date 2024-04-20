#ifndef TGBOT_TEXTQUOTE_H
#define TGBOT_TEXTQUOTE_H

#include "tgbot/types/MessageEntity.h"

#include <cstdint>
#include <memory>
#include <string>
#include <vector>

namespace TgBot {

/**
 * @brief This object contains information about the quoted part of a message that is replied to by the given message.
 *
 * @ingroup types
 */
class TextQuote {

public:
    typedef std::shared_ptr<TextQuote> Ptr;

    /**
     * @brief Text of the quoted part of a message that is replied to by the given message
     */
    std::string text;

    /**
     * @brief Optional. Special entities that appear in the quote.
     *
     * Currently, only bold, italic, underline, strikethrough, spoiler, and customEmoji entities are kept in quotes.
     */
    std::vector<MessageEntity::Ptr> entities;

    /**
     * @brief Approximate quote position in the original message in UTF-16 code units as specified by the sender
     */
    std::int32_t position;

    /**
     * @brief Optional. True, if the quote was chosen manually by the message sender.
     *
     * Otherwise, the quote was added automatically by the server.
     */
    bool isManual;
};
}

#endif //TGBOT_TEXTQUOTE_H
