#ifndef TGBOT_CPP_VIDEONOTE_H
#define TGBOT_CPP_VIDEONOTE_H

#include "tgbot/types/PhotoSize.h"

#include <cstdint>
#include <string>
#include <memory>

namespace TgBot {

/**
 * @brief This object represents a video message.
 *
 * @ingroup types
 */
class VideoNote {

public:
    typedef std::shared_ptr<VideoNote> Ptr;

    /**
     * @brief Identifier for this file, which can be used to download or reuse the file
     */
    std::string fileId;

    /**
     * @brief Unique identifier for this file, which is supposed to be the same over time and for different bots.
     * Can't be used to download or reuse the file.
     */
    std::string fileUniqueId;

    /**
     * @brief Video width and height (diameter of the video message) as defined by sender
     */
    std::int32_t length;

    /**
     * @brief Duration of the video in seconds as defined by sender
     */
    std::int32_t duration;

    /**
     * @brief Optional. Video thumbnail
     */
    PhotoSize::Ptr thumbnail;

    /**
     * @brief Optional. File size
     */
    std::int32_t fileSize;
};
}

#endif //TGBOT_CPP_VIDEONOTE_H
