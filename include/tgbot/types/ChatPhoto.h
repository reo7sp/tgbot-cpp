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

#ifndef TGBOT_CHATPHOTO_H
#define TGBOT_CHATPHOTO_H

#include <memory>
#include <string>

namespace TgBot {

/**
 * @brief This object represents a chat photo.
 * @ingroup types
 */
class ChatPhoto {
public:
    typedef std::shared_ptr<ChatPhoto> Ptr;

    /**
     * @brief Unique file identifier of small (160x160) chat photo. This file_id can be used only for photo download.
     */
    std::string smallFileId;

    /**
     * @brief Unique file identifier of big (640x640) chat photo. This file_id can be used only for photo download.
     */
    std::string bigFileId;
};
}

#endif //TGBOT_CHATPHOTO_H