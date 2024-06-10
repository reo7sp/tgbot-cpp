#include "tgbot/types/ChatBoostSourcePremium.h"
#include "tgbot/types/ChatBoostSourceGiftCode.h"
#include "tgbot/types/ChatBoostSourceGiveaway.h"

#include <string>

using namespace TgBot;

const std::string ChatBoostSourcePremium::SOURCE = "premium";
const std::string ChatBoostSourceGiftCode::SOURCE = "gift_code";
const std::string ChatBoostSourceGiveaway::SOURCE = "giveaway";
