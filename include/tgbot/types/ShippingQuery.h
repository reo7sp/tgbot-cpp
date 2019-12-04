#ifndef TGBOT_SHIPPINGQUERY_H
#define TGBOT_SHIPPINGQUERY_H

#include <string>
#include <memory>
#include <vector>
#include "tgbot/types/User.h"
#include "tgbot/types/ShippingAddress.h"

namespace TgBot {

/**
 * @brief This object contains information about an incoming shipping query.
 *
 * https://core.telegram.org/bots/api#shippingquery
 *
 * @ingroup types
 */
class ShippingQuery {
public:
    typedef std::shared_ptr<ShippingQuery> Ptr;

    /**
     * @brief Unique query identifier.
     */
    std::string id;

    /**
     * @brief User who sent the query.
     */
    User::Ptr from;

    /**
     * @brief Bot specified invoice payload.
     */
    std::string invoicePayload;

    /**
     * @brief User specified shipping address.
     */
    ShippingAddress::Ptr shippingAddress;
};
}

#endif //TGBOT_SHIPPINGQUERY_H
