#ifndef TGBOT_ORDERINFO_H
#define TGBOT_ORDERINFO_H

#include "tgbot/types/ShippingAddress.h"

#include <string>
#include <memory>

namespace TgBot {

/**
 * @brief This object represents information about an order.
 *
 * https://core.telegram.org/bots/api#orderinfo
 *
 * @ingroup types
 */
class OrderInfo {
public:
    typedef std::shared_ptr<OrderInfo> Ptr;

    /**
     * @brief Optional. User name.
     */
    std::string name;

    /**
     * @brief Optional. User's phone number.
     */
    std::string phoneNumber;

    /**
     * @brief Optional. User email.
     */
    std::string email;

    /**
     * @brief Optional. User shipping address.
     */
    ShippingAddress::Ptr shippingAddress;
};

}

#endif //TGBOT_ORDERINFO_H
