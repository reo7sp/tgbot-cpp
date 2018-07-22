//
// Created by Konstantin Kukin on 27/12/16.
//

#ifndef TGBOT_INLINEQUERYRESULTCACHEDPHOTO_H
#define TGBOT_INLINEQUERYRESULTCACHEDPHOTO_H

#include <string>
#include <memory>

#include "tgbot/types/InlineQueryResult.h"

namespace TgBot {

/**
 * @brief Represents a link to a photo stored on the Telegram servers.
 * 
 * @ingroup types
 */
class InlineQueryResultCachedPhoto : public InlineQueryResult {
public:
    static const std::string TYPE;

    typedef std::shared_ptr<InlineQueryResultCachedPhoto> Ptr;

    InlineQueryResultCachedPhoto() {
        this->type = TYPE;
    }

    /**
     * @brief A valid file identifier of the photo
     */
    std::string photoFileId;

    /**
    * @brief Optional. Short description of the result
    */
    std::string description;
};
}

#endif //TGBOT_INLINEQUERYRESULTCACHEDPHOTO_H
