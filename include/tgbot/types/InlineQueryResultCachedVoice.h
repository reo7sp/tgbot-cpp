#ifndef TGBOT_INLINEQUERYRESULTCACHEDVOICE_H
#define TGBOT_INLINEQUERYRESULTCACHEDVOICE_H

#include "tgbot/types/InlineQueryResult.h"

#include <string>
#include <memory>

namespace TgBot {

/**
 * @brief Represents a link to a voice message stored on the Telegram servers.
 *
 * @ingroup types
 */
class InlineQueryResultCachedVoice : public InlineQueryResult {
public:
    static const std::string TYPE;

    typedef std::shared_ptr<InlineQueryResultCachedVoice> Ptr;

    InlineQueryResultCachedVoice() {
        this->type = TYPE;
    }

    /**
     * @brief A valid file identifier of the voice message
     */
    std::string voiceFileId;
};
}

#endif //TGBOT_INLINEQUERYRESULTCACHEDVOICE_H
