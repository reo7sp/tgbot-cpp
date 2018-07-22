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

#ifndef TGBOT_ANIMATION_H
#define TGBOT_ANIMATION_H

#include <memory>
#include <string>

#include "tgbot/types/PhotoSize.h"

namespace TgBot {

/**
 * @brief You can provide an animation for your game so that it looks stylish in chats (check out Lumberjack for an example).
 * 
 * This object represents an animation file to be displayed in the message containing a game.
 * 
 * @ingroup types
 */
class Animation {
public:
    typedef std::shared_ptr<Animation> Ptr;

    /**
     * @brief Unique file identifier.
     */
    std::string fileId;

    /**
     * @brief Optional. Animation thumbnail as defined by sender.
     */
    PhotoSize::Ptr thumb;

    /**
     * @brief Optional. Original animation filename as defined by sender.
     */
    std::string fileName;

    /**
     * @brief Optional. MIME type of the file as defined by sender.
     */
    std::string mimeType;

    /**
     * @brief Optional. File size.
     */
    int32_t fileSize;
};
}

#endif //TGBOT_ANIMATION_H