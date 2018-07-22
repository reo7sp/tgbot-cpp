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

#ifndef TGBOT_CPP_USER_H
#define TGBOT_CPP_USER_H

#include <string>
#include <memory>

namespace TgBot {

/**
 * @brief This object represents a Telegram user or bot.
 * 
 * @ingroup types
 */
class User  {

public:
    typedef std::shared_ptr<User> Ptr;

    /**
     * @brief Unique identifier for this user or bot.
     */
    int32_t id;

    /**
     * @brief True, if this user is a bot
     */
    bool isBot = false;

    /**
     * @brief User‘s or bot’s first name.
     */
    std::string firstName;

    /**
     * @brief Optional. User‘s or bot’s last name.
     */
    std::string lastName;

    /**
     * @brief Optional. User‘s or bot’s username.
     */
    std::string username;

    /**
     * @brief Optional. IETF language tag of the user's language.
     */
    std::string languageCode;
};

}

#endif //TGBOT_CPP_USER_H
