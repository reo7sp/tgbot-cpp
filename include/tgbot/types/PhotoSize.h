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

#ifndef TGBOT_CPP_PHOTOSIZE_H
#define TGBOT_CPP_PHOTOSIZE_H

#include <string>
#include <memory>

namespace TgBot {

/**
 * @brief This object represents one size of a photo or a file / sticker thumbnail.
 * 
 * @ingroup types
 */
class PhotoSize {

public:
    typedef std::shared_ptr<PhotoSize> Ptr;

    /**
     * @brief Unique identifier for this file.
     */
    std::string fileId;

    /**
     * @brief Photo width.
     */
    int32_t width;

    /**
     * @brief Photo height.
     */
    int32_t height;

    /**
     * @brief Optional. File size.
     */
    int32_t fileSize;
};

}

#endif //TGBOT_CPP_PHOTOSIZE_H
