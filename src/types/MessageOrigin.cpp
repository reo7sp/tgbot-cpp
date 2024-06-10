#include "tgbot/types/MessageOriginUser.h"
#include "tgbot/types/MessageOriginHiddenUser.h"
#include "tgbot/types/MessageOriginChat.h"
#include "tgbot/types/MessageOriginChannel.h"

#include <string>

using namespace TgBot;

const std::string MessageOriginUser::TYPE = "user";
const std::string MessageOriginHiddenUser::TYPE = "hidden_user";
const std::string MessageOriginChat::TYPE = "chat";
const std::string MessageOriginChannel::TYPE = "channel";
