#ifndef TGBOT_INPUTINVOICEMESSAGECONTENT_H
#define TGBOT_INPUTINVOICEMESSAGECONTENT_H

#include "tgbot/types/InputMessageContent.h"
#include "tgbot/types/LabeledPrice.h"

#include <cstdint>
#include <memory>
#include <string>
#include <vector>

namespace TgBot {

/**
 * @brief Represents the content of an invoice message to be sent as the result of an inline query.
 *
 * @ingroup types
 */
class InputInvoiceMessageContent : public InputMessageContent {
public:
    static const std::string TYPE;

    typedef std::shared_ptr<InputInvoiceMessageContent> Ptr;

    InputInvoiceMessageContent() {
        this->type = TYPE;
    }

    /**
     * @brief Product name, 1-32 characters
     */
    std::string title;

    /**
     * @brief Product description, 1-255 characters
     */
    std::string description;

    /**
     * @brief Bot-defined invoice payload, 1-128 bytes.
     * This will not be displayed to the user, use for your internal processes.
     */
    std::string payload;

    /**
     * @brief Payment provider token, obtained via Botfather
     */
    std::string providerToken;

    /**
     * @brief Three-letter ISO 4217 currency code, see https://core.telegram.org/bots/payments#supported-currencies
     */
    std::string currency;

    /**
     * @brief Price breakdown, a JSON-serialized list of components (e.g. product price, tax, discount, delivery cost, delivery tax, bonus, etc.)
     */
    std::vector<LabeledPrice::Ptr> prices;

    /**
     * @brief Optional. The maximum accepted amount for tips in the smallest units of the currency (integer, not float/double).
     * For example, for a maximum tip of US$ 1.45 pass max_tip_amount = 145.
     * See the exp parameter in https://core.telegram.org/bots/payments/currencies.json, it shows the number of digits past the decimal point for each currency (2 for the majority of currencies).
     * Defaults to 0
     */
    std::int32_t maxTipAmount;

    /**
     * @brief Optional. A JSON-serialized array of suggested amounts of tip in the smallest units of the currency (integer, not float/double).
     * At most 4 suggested tip amounts can be specified.
     * The suggested tip amounts must be positive, passed in a strictly increased order and must not exceed maxTipAmount.
     */
    std::vector<std::int32_t> suggestedTipAmounts;

    /**
     * @brief Optional. A JSON-serialized object for data about the invoice, which will be shared with the payment provider.
     * A detailed description of the required fields should be provided by the payment provider.
     */
    std::string providerData;

    /**
     * @brief Optional. URL of the product photo for the invoice.
     * Can be a photo of the goods or a marketing image for a service.
     * People like it better when they see what they are paying for.
     */
    std::string photoUrl;

    /**
     * @brief Optional. Photo size
     */
    std::int32_t photoSize;

    /**
     * @brief Optional. Photo width
     */
    std::int32_t photoWidth;

    /**
     * @brief Optional. Photo height
     */
    std::int32_t photoHeight;

    /**
     * @brief Optional. Pass True, if you require the user's full name to complete the order
     */
    bool needName;

    /**
     * @brief Optional. Pass True, if you require the user's phone number to complete the order
     */
    bool needPhoneNumber;

    /**
     * @brief Optional. Pass True, if you require the user's email address to complete the order
     */
    bool needEmail;

    /**
     * @brief Optional. Pass True, if you require the user's shipping address to complete the order
     */
    bool needShippingAddress;

    /**
     * @brief Optional. Pass True, if user's phone number should be sent to provider
     */
    bool sendPhoneNumberToProvider;

    /**
     * @brief Optional. Pass True, if user's email address should be sent to provider
     */
    bool sendEmailToProvider;

    /**
     * @brief Optional. Pass True, if the final price depends on the shipping method
     */
    bool isFlexible;
};
}

#endif //TGBOT_INPUTINVOICEMESSAGECONTENT_H
