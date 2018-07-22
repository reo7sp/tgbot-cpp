/*
 * Copyright (c) 2015 Oleg Morozenkov
 * Copyright (c) 2018 JellyBrick
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

#ifndef TGBOT_STICKERSET_H
#define TGBOT_STICKERSET_H

#include <memory>
#include <string>
#include <vector>

#include "tgbot/types/Sticker.h"

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