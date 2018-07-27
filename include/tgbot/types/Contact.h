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

#ifndef TGBOT_CPP_CONTACT_H
#define TGBOT_CPP_CONTACT_H

#include <string>
#include <memory>

namespace TgBot {

/**
 * @brief This object represents a phone contact.
 * 
 * @ingroup types
 */
class Contact {

public:
    typedef std::shared_ptr<Contact> Ptr;

    /**
     * @brief Contact's phone number.
     */
    std::string phoneNumber;

    /**
     * @brief Contact's first name.
     */
    std::string firstName;

    /**
     * @brief Optional. Contact's last name.
     */
    std::string lastName;

    /**
     * @brief Optional. Contact's user identifier in Telegram.
     */
    std::string userId;

    /**
     * @brief Optional. Additional data about the contact in the form of a vCard.
     */
    std::string vcard;
};

}

#endif //TGBOT_CPP_CONTACT_H
