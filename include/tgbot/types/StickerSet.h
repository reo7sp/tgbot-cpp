#ifndef TGBOT_STICKERSET_H
#define TGBOT_STICKERSET_H

#include "tgbot/types/Sticker.h"
#include "tgbot/types/PhotoSize.h"

#include <memory>
#include <string>
#include <vector>

namespace TgBot {

/**
 * @brief This object represents a sticker set.
 *
 * @ingroup types
 */
class StickerSet {
public:
    typedef std::shared_ptr<StickerSet> Ptr;

    /**
     * @brief Enum of possible types of a sticker.
     */
    enum class Type {
        Regular, Mask, CustomEmoji
    };

    /**
     * @brief Sticker set name
     */
    std::string name;

    /**
     * @brief Sticker set title
     */
    std::string title;

    /**
     * @brief Type of stickers in the set, currently one of “regular”, “mask”, “custom_emoji”
     */
    Type type;

    /**
     * @brief True, if the sticker set contains animated stickers
     */
    bool isAnimated;

    /**
     * @brief True, if the sticker set contains video stickers
     */
    bool isVideo;

    /**
     * @brief List of all set stickers
     */
    std::vector<Sticker::Ptr> stickers;

    /**
     * @brief Optional. Sticker set thumbnail in the .WEBP, .TGS, or .WEBM format
     */
    PhotoSize::Ptr thumb;
};
}

#endif //TGBOT_STICKERSET_H
