#ifndef TGBOT_CPP_VIDEO_H
#define TGBOT_CPP_VIDEO_H

#include "tgbot/types/PhotoSize.h"

#include <cstdint>
#include <string>
#include <memory>

namespace TgBot {

/**
 * @brief This object represents a video file.
 *
 * @ingroup types
 */
class Video {

public:
    typedef std::shared_ptr<Video> Ptr;

    /**
     * @brief Identifier for this file, which can be used to download or reuse the file
     */
    std::string fileId;

    /**
     * @brief Unique identifier for this file, which is supposed to be the same over time and for different bots.
     *
     * Can't be used to download or reuse the file.
     */
    std::string fileUniqueId;

    /**
     * @brief Video width as defined by sender
     */
    std::int32_t width;

    /**
     * @brief Video height as defined by sender
     */
    std::int32_t height;

    /**
     * @brief Duration of the video in seconds as defined by sender
     */
    std::int32_t duration;

    /**
     * @brief Optional. Video thumbnail
     */
    PhotoSize::Ptr thumb;

    /**
     * @brief Optional. Mime type of a file as defined by sender
     */
    std::string mimeType;

    /**
     * @brief Optional. File size
     */
    std::int32_t fileSize;
};
}

#endif //TGBOT_CPP_VIDEO_H
