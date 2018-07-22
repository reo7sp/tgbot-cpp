//
// Created by Konstantin Kukin on 27/12/16
//

#ifndef TGBOT_INLINEQUERYRESULTAUDIO_H
#define TGBOT_INLINEQUERYRESULTAUDIO_H

#include <string>
#include <memory>

#include "tgbot/types/InlineQueryResult.h"

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
    int32_t audioDuration;
};
}

#endif //TGBOT_INLINEQUERYRESULTAUDIO_H
