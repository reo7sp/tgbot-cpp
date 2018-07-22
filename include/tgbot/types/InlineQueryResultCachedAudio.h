//
// Created by Konstantin Kukin on 27/12/16.
//

#ifndef TGBOT_INLINEQUERYRESULTCACHEDAUDIO_H
#define TGBOT_INLINEQUERYRESULTCACHEDAUDIO_H

#include <string>
#include <memory>

#include "tgbot/types/InlineQueryResult.h"

namespace TgBot {

/**
 * @brief Represents a link to an mp3 audio file stored on the Telegram servers. 
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

};
}

#endif //TGBOT_INLINEQUERYRESULTCACHEDAUDIO_H
