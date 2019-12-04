/*
 * Copyright (c) 2019 Nitan Alexandru Marcel
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

#ifndef TGBOT_POLL_H
#define TGBOT_POLL_H

#include <memory>
#include <string>
#include <vector>
#include "tgbot/types/PollOption.h"

namespace TgBot {
    /**
     * @brief This object represents a Poll.
     *
     * @ingroup types
     */
    class Poll {
    public:
        typedef std::shared_ptr<Poll> Ptr;

        /**
         * @brief Unique poll identifier.
         */
        int64_t id;

        /**
         * @brief Poll question, 1-255 characters.
         */
         std::string question;

        /**
         * @brief List of poll options.
         */
        PollOption::Ptr options;

        /**
         * @brief True, if the poll is closed.
         */
         bool is_closed;
    };
}

#endif //TGBOT_POLL_H
