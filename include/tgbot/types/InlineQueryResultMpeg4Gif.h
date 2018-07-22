//
// Created by Andrea Giove on 27/03/16.
//

#ifndef TGBOT_INLINEQUERYRESULTMPEG4GIF_H
#define TGBOT_INLINEQUERYRESULTMPEG4GIF_H

namespace TgBot {

/**
 * @brief Represents a link to a video animation (H.264/MPEG-4 AVC video without sound).
 * 
 * @ingroup types
 */
class InlineQueryResultMpeg4Gif : public InlineQueryResult {
public:
    static const std::string TYPE;

    typedef std::shared_ptr<InlineQueryResultMpeg4Gif> Ptr;

    InlineQueryResultMpeg4Gif() {
        this->type = TYPE;
        this->mpeg4Width = 0;
        this->mpeg4Height = 0;
    }

    /**
     * @brief A valid URL for the MP4 file.
     */
    std::string mpeg4Url;

    /**
     * @brief Optional. Video width.
     */
    int32_t mpeg4Width;

    /**
     * @brief Optional. Video height.
     */
    int32_t mpeg4Height;

    /**
     * @brief Optional. Video duration.
     */
    int32_t mpeg4Duration;

    /**
    * @brief URL of the static thumbnail (jpeg or gif) for the result
    */
    std::string thumbUrl;

};
}

#endif //TGBOT_INLINEQUERYRESULTMPEG4GIF_H
