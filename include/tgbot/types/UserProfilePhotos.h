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

#ifndef TGBOT_CPP_USERPROFILEPHOTOS_H
#define TGBOT_CPP_USERPROFILEPHOTOS_H

#include <vector>
#include <memory>

#include "tgbot/types/PhotoSize.h"

namespace TgBot {

/**
 * @brief This object represent a user's profile pictures.
 * 
 * @ingroup types
 */
class UserProfilePhotos {

public:
    typedef std::shared_ptr<UserProfilePhotos> Ptr;

    /**
     * @brief Total number of profile pictures the target user has.
     */
    int32_t totalCount;

    /**
     * @brief Requested profile pictures (in up to 4 sizes each).
     */
    std::vector<std::vector<PhotoSize::Ptr>> photos;
};

}

#endif //TGBOT_CPP_USERPROFILEPHOTOS_H
