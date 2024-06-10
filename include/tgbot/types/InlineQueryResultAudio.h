#ifndef TGBOT_INLINEQUERYRESULTAUDIO_H
#define TGBOT_INLINEQUERYRESULTAUDIO_H

#include "tgbot/types/InlineQueryResult.h"
#include "tgbot/types/MessageEntity.h"
#include "tgbot/types/InputMessageContent.h"

#include <cstdint>
#include <memory>
#include <string>
#include <vector>

namespace TgBot {

/**
 * @brief Represents a link to an MP3 audio file.
 *
 * By default, this audio file will be sent by the user.
 * Alternatively, you can use inputMessageContent to send a message with the specified content instead of the audio.
 *
 * @ingroup types
 */
class InlineQueryResultAudio : public InlineQueryResult {

public:
    static const std::string TYPE;

    typedef std::shared_ptr<InlineQueryResultAudio> Ptr;

    InlineQueryResultAudio() {
        this->type = TYPE;
    }

    /**
     * @brief A valid URL for the audio file
     */
    std::string audioUrl;

    /**
     * @brief Title
     */
    std::string title;

    /**
     * @brief Optional. Caption, 0-1024 characters after entities parsing
     */
    std::string caption;

    /**
     * @brief Optional. Mode for parsing entities in the audio caption.
     *
     * See [formatting options](https://core.telegram.org/bots/api#formatting-options) for more details.
     */
    std::string parseMode;

    /**
     * @brief Optional. List of special entities that appear in the caption, which can be specified instead of parseMode
     */
    std::vector<MessageEntity::Ptr> captionEntities;

    /**
     * @brief Optional. Performer
     */
    std::string performer;

    /**
     * @brief Optional. Audio duration in seconds
     */
    std::int32_t audioDuration;

    /**
     * @brief Optional. Content of the message to be sent instead of the audio
     */
    InputMessageContent::Ptr inputMessageContent;
};
}

#endif //TGBOT_INLINEQUERYRESULTAUDIO_H
