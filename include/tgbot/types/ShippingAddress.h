/*
 * Copyright (c) 2015 Oleg Morozenkov
 * Copyright (c) 2017 Maks Mazurov (fox.cpp)
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

#ifndef TGBOT_SHIPPINGADDRESS_H
#define TGBOT_SHIPPINGADDRESS_H

#include <string>
#include <memory>

namespace TgBot {

/**
 * @brief This object represents a shipping address.
 * 
 * https://core.telegram.org/bots/api#shippingaddress
 * 
 * @ingroup types
 */
class ShippingAddress {
public:
    typedef std::shared_ptr<ShippingAddress> Ptr;

    /**
     * @brief ISO 3166-1 alpha-2 country code.
     */
    std::string countryCode;

    /**
     * @brief State, if applicable.
     */
    std::string state;

    /**
     * @brief City.
     */
    std::string city;

    /**
     * @brief First line for the address.
     */
    std::string streetLine1;

    /**
     * @brief Second line for the address.
     */
    std::string streetLine2;

    /**
     * Address post code.
     */
    std::string postCode;
};
}

#endif //TGBOT_SHIPPINGADDRESS_H
