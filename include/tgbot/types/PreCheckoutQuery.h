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

#ifndef TGBOT_PRECHECKOUTQUERY_H
#define TGBOT_PRECHECKOUTQUERY_H

#include <string>
#include <memory>
#include <vector>
#include "tgbot/types/User.h"
#include "tgbot/types/OrderInfo.h"

namespace TgBot {

/**
 * @brief This object contains information about an incoming pre-checkout query.
 *
 * https://core.telegram.org/bots/api#precheckoutquery
 * 
 * @ingroup types
 */
class PreCheckoutQuery {
public:
    typedef std::shared_ptr<PreCheckoutQuery> Ptr;

    /**
     * @brief Unique query identifier.
     */
    std::string id;

    /**
     * @brief User who sent the query.
     */
    User::Ptr from;

    /**
     * @brief Three-letter ISO 4217 currency code.
     */ 
    std::string currency;

    /** 
     * @brief Total price in the smallest units of the currency (integer,
     * not float/double). 
     * 
     * For example, for a price of US$ 1.45 pass 
     * amount = 145. See the exp parameter in currencies.json, it shows
     * the number of digits past the decimal point for each currency (2
     * for the majority of currencies).
     * 
     * https://core.telegram.org/bots/payments/currencies.json
     */
    int32_t totalAmount;

    /**
     * @brief Bot specified invoice payload.
     */
    std::string invoicePayload;

    /**
     * @brief Optional. Identifier of the shipping option chosen by the user.
     */
    std::string shippingOptionId;

    /**
     * @brief Optional. Order info provided by the user.
     */
    OrderInfo::Ptr orderInfo;
};
}

#endif //TGBOT_PRECHECKOUTQUERY_H
