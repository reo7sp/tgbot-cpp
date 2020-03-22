#ifndef TGBOT_CPP_STICKER_H
#define TGBOT_CPP_STICKER_H

#include "tgbot/types/PhotoSize.h"
#include "tgbot/types/MaskPosition.h"

#include <cstdint>
#include <string>
#include <memory>

namespace TgBot {

/**
 * @brief This object represents a general file (as opposed to photos and audio files).
 *
 * @ingroup types
 */
class Sticker {

public:
    typedef std::shared_ptr<Sticker> Ptr;

    /**
     * @brief Unique file identifier.
     */
    std::string fileId;

    /**
     * @brief Optional. Sticker width.
     */
    std::int32_t width;

    /**
     * @brief Optional. Sticker height.
     */
    std::int32_t height;

    /**
 * @brief True, if the sticker is animated.
    */
    bool isAnimated = false;

    /**
     * @brief Optional. Optional. Sticker thumbnail in .webp or .jpg format.
     */
    PhotoSize::Ptr thumb;

    /**
     * @brief Optional. Emoji associated with the sticker
     */
    std::string emoji;

    /**
     * @brief Optional. Name of the sticker set to which the sticker belongs.
     */
    std::string setName;

    /**
     * @brief Optional. For mask stickers, the position where the mask should be placed.
     */
    MaskPosition::Ptr maskPosition;

    /**
     * @brief Optional. File size.
     */
    std::int32_t fileSize;
};

}

#endif //TGBOT_CPP_STICKER_H
