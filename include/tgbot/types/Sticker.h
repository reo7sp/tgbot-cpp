#ifndef TGBOT_STICKER_H
#define TGBOT_STICKER_H

#include "tgbot/types/PhotoSize.h"
#include "tgbot/types/File.h"
#include "tgbot/types/MaskPosition.h"

#include <cstdint>
#include <memory>
#include <string>

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
     * @brief Enum of possible types of a sticker.
     */
    enum class Type {
        Regular, Mask, CustomEmoji
    };

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
     * @brief Type of the sticker, currently one of “regular”, “mask”, “custom_emoji”.
     * The type of the sticker is independent from its format, which is determined by the fields isAnimated and isVideo.
     */
    Type type;

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
    PhotoSize::Ptr thumbnail;

    /**
     * @brief Optional. Emoji associated with the sticker
     */
    std::string emoji;

    /**
     * @brief Optional. Name of the sticker set to which the sticker belongs
     */
    std::string setName;

    /**
     * @brief Optional. For premium regular stickers, premium animation for the sticker
     */
    File::Ptr premiumAnimation;

    /**
     * @brief Optional. For mask stickers, the position where the mask should be placed
     */
    MaskPosition::Ptr maskPosition;

    /**
     * @brief Optional. For custom emoji stickers, unique identifier of the custom emoji
     */
    std::string customEmojiId;

    /**
     * @brief Optional. True, if the sticker must be repainted to a text color in messages, the color of the Telegram Premium badge in emoji status, white color on chat photos, or another appropriate color in other places
     */
    bool needsRepainting = true;

    /**
     * @brief Optional. File size in bytes
     */
    std::int32_t fileSize;
};
}

#endif //TGBOT_STICKER_H
