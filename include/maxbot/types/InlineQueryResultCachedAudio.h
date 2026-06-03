#ifndef MAXBOT_INLINEQUERYRESULTCACHEDAUDIO_H
#define MAXBOT_INLINEQUERYRESULTCACHEDAUDIO_H

#include "maxbot/types/InlineQueryResult.h"
#include "maxbot/types/MessageEntity.h"
#include "maxbot/types/InputMessageContent.h"

#include <memory>
#include <string>
#include <vector>

namespace MaxBot {

/**
 * @brief Represents a link to an MP3 audio file stored on the Telegram servers.
 *
 * By default, this audio file will be sent by the user.
 * Alternatively, you can use inputMessageContent to send a message with the specified content instead of the audio.
 *
 * @ingroup types
 */
class InlineQueryResultCachedAudio : public InlineQueryResult {

public:
    static const std::string TYPE;

    typedef std::shared_ptr<InlineQueryResultCachedAudio> Ptr;

    InlineQueryResultCachedAudio() {
        this->type = TYPE;
    }

    /**
     * @brief A valid file identifier for the audio file
     */
    std::string audioFileId;

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
     * @brief Optional. Content of the message to be sent instead of the audio
     */
    InputMessageContent::Ptr inputMessageContent;
};
}

#endif //MAXBOT_INLINEQUERYRESULTCACHEDAUDIO_H
