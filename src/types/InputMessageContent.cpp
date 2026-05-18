#include "maxbot/types/InputTextMessageContent.h"
#include "maxbot/types/InputLocationMessageContent.h"
#include "maxbot/types/InputVenueMessageContent.h"
#include "maxbot/types/InputContactMessageContent.h"
#include "maxbot/types/InputInvoiceMessageContent.h"

#include <string>

using namespace MaxBot;

const std::string InputTextMessageContent::TYPE = "text";
const std::string InputLocationMessageContent::TYPE = "location";
const std::string InputVenueMessageContent::TYPE = "venue";
const std::string InputContactMessageContent::TYPE = "contact";
const std::string InputInvoiceMessageContent::TYPE = "invoice";
