#include "tgbot/types/BotCommandScopeDefault.h"
#include "tgbot/types/BotCommandScopeAllPrivateChats.h"
#include "tgbot/types/BotCommandScopeAllGroupChats.h"
#include "tgbot/types/BotCommandScopeAllChatAdministrators.h"
#include "tgbot/types/BotCommandScopeChat.h"
#include "tgbot/types/BotCommandScopeChatAdministrators.h"
#include "tgbot/types/BotCommandScopeChatMember.h"

#include <string>

using namespace TgBot;

const std::string BotCommandScopeDefault::TYPE = "default";
const std::string BotCommandScopeAllPrivateChats::TYPE = "all_private_chats";
const std::string BotCommandScopeAllGroupChats::TYPE = "all_group_chats";
const std::string BotCommandScopeAllChatAdministrators::TYPE = "all_chat_administrators";
const std::string BotCommandScopeChat::TYPE = "chat";
const std::string BotCommandScopeChatAdministrators::TYPE = "chat_administrators";
const std::string BotCommandScopeChatMember::TYPE = "chat_member";
