#ifndef TGBOT_LABELEDPRICE_H
#define TGBOT_LABELEDPRICE_H

#include <cstdint>
#include <string>
#include <memory>

namespace TgBot {

/**
 * @brief This object represents a portion of the price for goods or services.
 *
 * https://core.telegram.org/bots/api#labeledprice
 * @ingroup types
 */
class LabeledPrice {
public:
    typedef std::shared_ptr<LabeledPrice> Ptr;

    /**
     * @brief Portion label.
     */
    std::string label;

    /**
     * @brief Price of the product in the smallest units of the currency (integer,
     * not float/double).
     *
     * For example, for a price of US$ 1.45 pass amount = 145. See the exp parameter
     * in currencies.json, it shows the number of digits past the decimal point
     * for each currency  (2 for the majority of currencies).
     *
     * https://core.telegram.org/bots/payments/currencies.json
     */
    std::int32_t amount;
};
}

#endif //TGBOT_LABELEDPRICE_H
