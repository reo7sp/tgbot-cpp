#ifndef TGBOT_CPP_VIDEONOTE_H
#define TGBOT_CPP_VIDEONOTE_H

#include "tgbot/types/PhotoSize.h"

#include <cstdint>
#include <string>
#include <memory>

namespace TgBot {

/**
 * @brief This object represents a video message (available in Telegram apps as of v.4.0).
 *
 * @ingroup types
 */
class VideoNote {

public:
    typedef std::shared_ptr<VideoNote> Ptr;

    /**
     * @brief Unique identifier for this file.
     */
    std::string fileId;

    /**
     * @brief Video width and height as defined by sender.
     */
    std::int32_t length;

    /**
     * @brief Duration of the video in seconds as defined by sender.
     */
    std::int32_t duration;

    /**
     * @brief Optional. Video thumbnail.
     */
    PhotoSize::Ptr thumb;

    /**
     * @brief Optional. File size.
     */
    std::int32_t fileSize;
};

}

#endif //TGBOT_CPP_VIDEONOTE_H
