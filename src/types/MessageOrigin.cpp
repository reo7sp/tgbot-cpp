#include "maxbot/types/MessageOriginUser.h"
#include "maxbot/types/MessageOriginHiddenUser.h"
#include "maxbot/types/MessageOriginChat.h"
#include "maxbot/types/MessageOriginChannel.h"

#include <string>

using namespace MaxBot;

const std::string MessageOriginUser::TYPE = "user";
const std::string MessageOriginHiddenUser::TYPE = "hidden_user";
const std::string MessageOriginChat::TYPE = "chat";
const std::string MessageOriginChannel::TYPE = "channel";
