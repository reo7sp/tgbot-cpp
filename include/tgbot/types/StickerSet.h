#ifndef TGBOT_STICKERSET_H
#define TGBOT_STICKERSET_H

#include "tgbot/types/Sticker.h"

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
     * @brief Sticker set name.
     */
    std::string name;

    /**
     * @brief Sticker set title.
     */
    std::string title;

    /**
 * @brief True, if the sticker set contains animated stickers.
    */
    bool isAnimated = false;

    /**
     * @brief True, if the sticker set contains masks.
     */
    bool containsMasks = false;

    /**
     * @brief List of all set stickers.
     */
    std::vector<Sticker::Ptr> stickers;
};
}

#endif //TGBOT_STICKERSET_H
