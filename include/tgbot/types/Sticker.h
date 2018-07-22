/*
 * Copyright (c) 2015 Oleg Morozenkov
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef TGBOT_CPP_STICKER_H
#define TGBOT_CPP_STICKER_H

#include <string>
#include <memory>

#include "tgbot/types/PhotoSize.h"
#include "tgbot/types/MaskPosition.h"

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
    int32_t width;

    /**
     * @brief Optional. Sticker height.
     */
    int32_t height;

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
    int32_t fileSize;
};

}

#endif //TGBOT_CPP_STICKER_H
