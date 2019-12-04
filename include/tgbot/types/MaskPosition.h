#ifndef TGBOT_MARKPOSITION_H
#define TGBOT_MARKPOSITION_H

#include <memory>
#include <string>

namespace TgBot {

/**
 * @brief This object describes the position on faces where a mask should be placed by default.
 *
 * @ingroup types
 */
class MaskPosition {
public:
    typedef std::shared_ptr<MaskPosition> Ptr;

    /**
     * @brief The part of the face relative to which the mask should be placed. One of “forehead”, “eyes”, “mouth”, or “chin”.
     */
    std::string point;

    /**
     * @brief Shift by X-axis measured in widths of the mask scaled to the face size, from left to right. For example, choosing -1.0 will place mask just to the left of the default mask position.
     */
    float xShift;

    /**
     * @brief Shift by Y-axis measured in heights of the mask scaled to the face size, from top to bottom. For example, 1.0 will place the mask just below the default mask position.
     */
    float yShift;

    /**
     * @brief Mask scaling coefficient. For example, 2.0 means double size.
     */
    float scale;
};
}

#endif //TGBOT_MARKPOSITION_H
