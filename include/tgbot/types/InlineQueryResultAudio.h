#ifndef TGBOT_INLINEQUERYRESULTAUDIO_H
#define TGBOT_INLINEQUERYRESULTAUDIO_H

#include "tgbot/types/InlineQueryResult.h"

#include <cstdint>
#include <string>
#include <memory>

namespace TgBot {

/**
 * @brief Represents a link to an mp3 audio file.
 *
 * @ingroup types
 */
class InlineQueryResultAudio : public InlineQueryResult {
public:
    static const std::string TYPE;

    typedef std::shared_ptr<InlineQueryResultAudio> Ptr;

    InlineQueryResultAudio() {
        this->type = TYPE;
        this->audioDuration = 0;
    }

    /**
     * @brief A valid URL for the audio file
     */
    std::string audioUrl;

    /**
    * @brief Optional. Performer
    */
    std::string performer;

    /**
    * @brief Optional. Audio duration in seconds
    */
    std::int32_t audioDuration;
};
}

#endif //TGBOT_INLINEQUERYRESULTAUDIO_H
