//
// Created by Andrea Giove on 27/03/16.
//

#ifndef TGBOT_INLINEQUERYRESULTGIF_H
#define TGBOT_INLINEQUERYRESULTGIF_H

#include <string>
#include <memory>

#include "tgbot/types/InlineQueryResult.h"

namespace TgBot {

/**
 * Represents a link to an animated GIF file.
 * @ingroup types
 */
class InlineQueryResultGif : public InlineQueryResult {
public:
    static const std::string TYPE = "gif";

    typedef std::shared_ptr<InlineQueryResultGif> Ptr;

    InlineQueryResultGif() : type(TYPE) {};

    /**
     * A valid URL for the GIF file.
     */
    std::string gifUrl;

    /**
     * Optional. Width of the GIF.
     */
    int32_t gifWidth;

    /**
     * Optional. Height of the GIF.
     */
    int32_t gifHeight;

    /**
     * Optional. Caption for the GIF file to be sent.
     */
    std::string caption;

};
}

#endif //TGBOT_INLINEQUERYRESULTGIF_H
