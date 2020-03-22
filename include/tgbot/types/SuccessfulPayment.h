#ifndef TGBOT_SUCCESSFULPAYMENT_H
#define TGBOT_SUCCESSFULPAYMENT_H

#include "tgbot/types/OrderInfo.h"

#include <cstdint>
#include <string>
#include <memory>
#include <vector>

namespace TgBot {

/**
 * @brief This object contains basic information about a successful payment.
 *
 * https://core.telegram.org/bots/api#successfulpayment
 *
 * @ingroup types
 */
class SuccessfulPayment {
public:
    typedef std::shared_ptr<SuccessfulPayment> Ptr;

    /**
     * @brief Three-letter ISO 4217 currency code
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
    std::int32_t totalAmount;

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

    /**
     * @brief Telegram payment identifier.
     */
    std::string telegramPaymentChargeId;

    /**
     * @brief Provider payment identifier.
     */
    std::string providerPaymentChargeId;
};
}

#endif //TGBOT_SUCCESSFULPAYMENT_H
