#ifndef MAXBOT_STICKERSET_H
#define MAXBOT_STICKERSET_H

#include "maxbot/types/Sticker.h"
#include "maxbot/types/PhotoSize.h"

#include <memory>
#include <string>
#include <vector>

namespace MaxBot {

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
     * @brief Type of stickers in the set, currently one of Type::Regular, Type::Mask, Type::CustomEmoji”
     */
    Type stickerType;

    /**
     * @brief List of all set stickers
     */
    std::vector<Sticker::Ptr> stickers;

    /**
     * @brief Optional. Sticker set thumbnail in the .WEBP, .TGS, or .WEBM format
     */
    PhotoSize::Ptr thumbnail;
};
}

#endif //MAXBOT_STICKERSET_H
