//
// Created by Maks Mazurov (fox.cpp) on 21.05.17.
//

#ifndef TGBOT_SHIPPINGOPTION_H
#define TGBOT_SHIPPINGOPTION_H

#include <string>
#include <memory>
#include <vector>
#include "tgbot/types/LabeledPrice.h"

namespace TgBot {

/**
 * @brief This object represents one shipping option.
 *
 * https://core.telegram.org/bots/api#shippingoption 
 * 
 * @ingroup types
 */
class ShippingOption {
public:
    typedef std::shared_ptr<ShippingOption> Ptr;

    /**
     * @brief Shipping option identifier.
     */
    std::string id;

    /**
     * @brief Option title.
     */
    std::string title;

    /**
     * @brief List of price options.
     */
    std::vector<LabeledPrice::Ptr> prices;
};
}

#endif //TGBOT_SHIPPINGOPTION_H
