#ifndef TGBOT_INLINEQUERYRESULTVIDEO_H
#define TGBOT_INLINEQUERYRESULTVIDEO_H

#include "tgbot/types/InlineQueryResult.h"
#include "tgbot/types/MessageEntity.h"
#include "tgbot/types/InputMessageContent.h"

#include <cstdint>
#include <memory>
#include <string>
#include <vector>

namespace TgBot {

/**
 * @brief Represents a link to a page containing an embedded video player or a video file.
 * By default, this video file will be sent by the user with an optional caption.
 * Alternatively, you can use inputMessageContent to send a message with the specified content instead of the video.
 * 
 * If an InlineQueryResultVideo message contains an embedded video (e.g., YouTube), you must replace its content using inputMessageContent.
 *
 * @ingroup types
 */
class InlineQueryResultVideo : public InlineQueryResult {
public:
    static const std::string TYPE;

    typedef std::shared_ptr<InlineQueryResultVideo> Ptr;

    InlineQueryResultVideo() {
        this->type = TYPE;
    };

    /**
     * @brief A valid URL for the embedded video player or video file
     */
    std::string videoUrl;

    /**
     * @brief Mime type of the content of video url, “text/html” or “video/mp4”
     */
    std::string mimeType;

    /**
    * @brief URL of the thumbnail (jpeg only) for the video
    */
    std::string thumbnailUrl;

    /**
     * @brief Title for the result
     */
    std::string title;

    /**
     * @brief Optional. Caption of the video to be sent, 0-1024 characters after entities parsing
     */
    std::string caption;

    /**
     * @brief Optional. Mode for parsing entities in the video caption.
     * See https://core.telegram.org/bots/api#formatting-options for more details.
     */
    std::string parseMode;

    /**
     * @brief Optional. List of special entities that appear in the caption, which can be specified instead of parseMode
     */
    std::vector<MessageEntity::Ptr> captionEntities;

    /**
     * @brief Optional. Video width
     */
    std::int32_t videoWidth;

    /**
     * @brief Optional. Video height
     */
    std::int32_t videoHeight;

    /**
     * @brief Optional. Video duration in seconds
     */
    std::int32_t videoDuration;

    /**
     * @brief Optional. Short description of the result
     */
    std::string description;

    /**
     * @brief Optional. Content of the message to be sent instead of the video.
     * This field is required if InlineQueryResultVideo is used to send an HTML-page as a result (e.g., a YouTube video).
     */
    InputMessageContent::Ptr inputMessageContent;
};
}

#endif //TGBOT_INLINEQUERYRESULTVIDEO_H
