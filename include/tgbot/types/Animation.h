#ifndef TGBOT_ANIMATION_H
#define TGBOT_ANIMATION_H

#include "tgbot/types/PhotoSize.h"

#include <cstdint>
#include <memory>
#include <string>

namespace TgBot {

/**
 * @brief This object represents an animation file (GIF or H.264/MPEG-4 AVC video without sound).
 *
 * @ingroup types
 */
class Animation {
public:
    typedef std::shared_ptr<Animation> Ptr;

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
     * @brief Optional. Animation thumbnail as defined by sender
     */
    PhotoSize::Ptr thumb;

    /**
     * @brief Optional. Original animation filename as defined by sender
     */
    std::string fileName;

    /**
     * @brief Optional. MIME type of the file as defined by sender
     */
    std::string mimeType;

    /**
     * @brief Optional. File size
     */
    std::int32_t fileSize;
};
}

#endif //TGBOT_ANIMATION_H
