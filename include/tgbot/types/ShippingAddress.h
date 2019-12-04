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
