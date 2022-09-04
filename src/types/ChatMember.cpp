#include "tgbot/types/ChatMemberOwner.h"
#include "tgbot/types/ChatMemberAdministrator.h"
#include "tgbot/types/ChatMemberMember.h"
#include "tgbot/types/ChatMemberRestricted.h"
#include "tgbot/types/ChatMemberLeft.h"
#include "tgbot/types/ChatMemberBanned.h"

#include <string>

using namespace TgBot;

const std::string ChatMemberOwner::STATUS = "creator";
const std::string ChatMemberAdministrator::STATUS = "administrator";
const std::string ChatMemberMember::STATUS = "member";
const std::string ChatMemberRestricted::STATUS = "restricted";
const std::string ChatMemberLeft::STATUS = "left";
const std::string ChatMemberBanned::STATUS = "kicked";
