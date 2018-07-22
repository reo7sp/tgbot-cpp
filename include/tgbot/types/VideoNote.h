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

#ifndef TGBOT_CPP_VIDEONOTE_H
#define TGBOT_CPP_VIDEONOTE_H

#include <string>
#include <memory>

#include "tgbot/types/PhotoSize.h"

namespace TgBot {

/**
 * @brief This object represents a video message (available in Telegram apps as of v.4.0).
 * 
 * @ingroup types
 */
class VideoNote {

public:
    typedef std::shared_ptr<VideoNote> Ptr;

    /**
     * @brief Unique identifier for this file.
     */
    std::string fileId;

    /**
     * @brief Video width and height as defined by sender.
     */
    int32_t length;

    /**
     * @brief Duration of the video in seconds as defined by sender.
     */
    int32_t duration;

    /**
     * @brief Optional. Video thumbnail.
     */
    PhotoSize::Ptr thumb;

    /**
     * @brief Optional. File size.
     */
    int32_t fileSize;
};

}

#endif //TGBOT_CPP_VIDEONOTE_H
