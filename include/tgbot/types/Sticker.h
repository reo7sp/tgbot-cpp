#ifndef TGBOT_CPP_STICKER_H
#define TGBOT_CPP_STICKER_H

#include "tgbot/types/PhotoSize.h"
#include "tgbot/types/MaskPosition.h"

#include <cstdint>
#include <string>
#include <memory>

namespace TgBot {

/**
 * @brief This object represents a sticker.
 *
 * @ingroup types
 */
class Sticker {

public:
    typedef std::shared_ptr<Sticker> Ptr;

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
     * @brief Sticker width
     */
    std::int32_t width;

    /**
     * @brief Sticker height
     */
    std::int32_t height;

    /**
     * @brief True, if the sticker is animated
     */
    bool isAnimated;

    /**
     * @brief True, if the sticker is a video sticker
     */
    bool isVideo;

    /**
     * @brief Optional. Sticker thumbnail in the .WEBP or .JPG format
     */
    PhotoSize::Ptr thumb;

    /**
     * @brief Optional. Emoji associated with the sticker
     */
    std::string emoji;

    /**
     * @brief Optional. Name of the sticker set to which the sticker belongs
     */
    std::string setName;

    /**
     * @brief Optional. For mask stickers, the position where the mask should be placed
     */
    MaskPosition::Ptr maskPosition;

    /**
     * @brief Optional. File size in bytes
     */
    std::int32_t fileSize;
};
}

#endif //TGBOT_CPP_STICKER_H
