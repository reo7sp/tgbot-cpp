//
// Created by Konstantin Kukin on 27/12/16
//

#ifndef TGBOT_INLINEQUERYRESULTVOICE_H
#define TGBOT_INLINEQUERYRESULTVOICE_H

namespace TgBot {

/**
 * @brief Represents link to a page containing an embedded video player or a video file.
 * 
 * @ingroup types
 */
class InlineQueryResultVoice : public InlineQueryResult {
public:
    static const std::string TYPE;

    typedef std::shared_ptr<InlineQueryResultVoice> Ptr;

    InlineQueryResultVoice() {
        this->type = TYPE;
        this->voiceDuration = 0;
    };

    /**
     * @brief A valid URL for the voice recording
     */
    std::string voiceUrl;

    /**
     * @brief Optional. Recording duration in seconds
     */
    int32_t voiceDuration;
};
}

#endif //TGBOT_INLINEQUERYRESULTVOICE_H
