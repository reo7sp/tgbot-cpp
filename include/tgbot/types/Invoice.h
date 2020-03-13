#ifndef TGBOT_INVOICE_H
#define TGBOT_INVOICE_H

#include <cstdint>
#include <string>
#include <memory>

namespace TgBot {

/**
 * @brief This object contains basic information about an invoice.
 *
 * https://core.telegram.org/bots/api#invoice
 *
 * @ingroup types
 */
class Invoice {
public:
    typedef std::shared_ptr<Invoice> Ptr;

    /**
     * @brief Product name.
     */
    std::string title;

    /**
     * @brief Product description.
     */
    std::string description;

    /**
     * @brief Unique bot deep-linking parameter that can be used to generate this invoice.
     */
    std::string startParameter;

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
    std::int32_t totalAmount;
};
}

#endif //TGBOT_INVOICE_H
