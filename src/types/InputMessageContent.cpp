#include "tgbot/types/InputTextMessageContent.h"
#include "tgbot/types/InputLocationMessageContent.h"
#include "tgbot/types/InputVenueMessageContent.h"
#include "tgbot/types/InputContactMessageContent.h"
#include "tgbot/types/InputInvoiceMessageContent.h"

#include <string>

using namespace TgBot;

const std::string InputTextMessageContent::TYPE = "text";
const std::string InputLocationMessageContent::TYPE = "location";
const std::string InputVenueMessageContent::TYPE = "venue";
const std::string InputContactMessageContent::TYPE = "contact";
const std::string InputInvoiceMessageContent::TYPE = "invoice";
