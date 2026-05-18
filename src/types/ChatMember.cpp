#include "maxbot/types/ChatMemberOwner.h"
#include "maxbot/types/ChatMemberAdministrator.h"
#include "maxbot/types/ChatMemberMember.h"
#include "maxbot/types/ChatMemberRestricted.h"
#include "maxbot/types/ChatMemberLeft.h"
#include "maxbot/types/ChatMemberBanned.h"

#include <string>

using namespace MaxBot;

const std::string ChatMemberOwner::STATUS = "creator";
const std::string ChatMemberAdministrator::STATUS = "administrator";
const std::string ChatMemberMember::STATUS = "member";
const std::string ChatMemberRestricted::STATUS = "restricted";
const std::string ChatMemberLeft::STATUS = "left";
const std::string ChatMemberBanned::STATUS = "kicked";
