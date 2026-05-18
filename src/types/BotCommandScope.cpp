#include "maxbot/types/BotCommandScopeDefault.h"
#include "maxbot/types/BotCommandScopeAllPrivateChats.h"
#include "maxbot/types/BotCommandScopeAllGroupChats.h"
#include "maxbot/types/BotCommandScopeAllChatAdministrators.h"
#include "maxbot/types/BotCommandScopeChat.h"
#include "maxbot/types/BotCommandScopeChatAdministrators.h"
#include "maxbot/types/BotCommandScopeChatMember.h"

#include <string>

using namespace MaxBot;

const std::string BotCommandScopeDefault::TYPE = "default";
const std::string BotCommandScopeAllPrivateChats::TYPE = "all_private_chats";
const std::string BotCommandScopeAllGroupChats::TYPE = "all_group_chats";
const std::string BotCommandScopeAllChatAdministrators::TYPE = "all_chat_administrators";
const std::string BotCommandScopeChat::TYPE = "chat";
const std::string BotCommandScopeChatAdministrators::TYPE = "chat_administrators";
const std::string BotCommandScopeChatMember::TYPE = "chat_member";
