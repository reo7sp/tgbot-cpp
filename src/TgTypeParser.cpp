#include "tgbot/TgTypeParser.h"

#include <memory>
#include <string>

using namespace std;
using namespace boost::property_tree;

namespace TgBot {

Chat::Ptr TgTypeParser::parseJsonAndGetChat(const ptree& data) const {
    auto result(make_shared<Chat>());
    result->id = data.get<int64_t>("id");
    string type = data.get<string>("type");
    if (type == "private") {
        result->type = Chat::Type::Private;
    } else if (type == "group") {
        result->type = Chat::Type::Group;
    } else if (type == "supergroup") {
        result->type = Chat::Type::Supergroup;
    } else if (type == "channel") {
        result->type = Chat::Type::Channel;
    }
    result->title = data.get("title", "");
    result->username = data.get("username", "");
    result->firstName = data.get("first_name", "");
    result->lastName = data.get("last_name", "");
    result->allMembersAreAdministrators = data.get<bool>("all_members_are_administrators", false);
    result->photo = tryParseJson<ChatPhoto>(&TgTypeParser::parseJsonAndGetChatPhoto, data, "photo");
    result->description = data.get("description", "");
    result->inviteLink = data.get("invite_link", "");
    result->pinnedMessage = tryParseJson<Message>(&TgTypeParser::parseJsonAndGetMessage, data, "pinned_message");
    result->stickerSetName = data.get("sticker_set_name", "");
    result->canSetStickerSet = data.get<bool>("can_set_sticker_set", false);

    return result;
}

string TgTypeParser::parseChat(const Chat::Ptr& object) const {
    if (!object) {
        return "";
    }
    string result;
    result += '{';
    appendToJson(result, "id", object->id);
    if (object->type == Chat::Type::Private) {
        appendToJson(result, "type", "private");
    } else if (object->type == Chat::Type::Group) {
        appendToJson(result, "type", "group");
    } else if (object->type == Chat::Type::Supergroup) {
        appendToJson(result, "type", "supergroup");
    } else if (object->type == Chat::Type::Channel) {
        appendToJson(result, "type", "channel");
    }
    appendToJson(result, "title", object->title);
    appendToJson(result, "username", object->username);
    appendToJson(result, "first_name", object->firstName);
    appendToJson(result, "last_name", object->lastName);
    removeLastComma(result);
    result += '}';
    return result;
}

User::Ptr TgTypeParser::parseJsonAndGetUser(const ptree& data) const {
    auto result(make_shared<User>());
    result->id = data.get<int32_t>("id");
    result->isBot = data.get<bool>("is_bot", false);
    result->firstName = data.get<string>("first_name");
    result->lastName = data.get("last_name", "");
    result->username = data.get("username", "");
    result->languageCode = data.get("language_code", "");
    return result;
}

string TgTypeParser::parseUser(const User::Ptr& object) const {
    if (!object) {
        return "";
    }
    string result;
    result += '{';
    appendToJson(result, "id", object->id);
    appendToJson(result, "is_bot", object->isBot);
    appendToJson(result, "first_name", object->firstName);
    appendToJson(result, "last_name", object->lastName);
    appendToJson(result, "username", object->username);
    appendToJson(result, "language_code", object->languageCode);
    removeLastComma(result);
    result += '}';
    return result;
}

MessageEntity::Ptr TgTypeParser::parseJsonAndGetMessageEntity(const ptree& data) const{
    auto result(make_shared<MessageEntity>());
    result->type = data.get<string>("type");
    result->offset = data.get<int32_t>("offset");
    result->length = data.get<int32_t>("length");
    result->url = data.get<string>("url", "");
    result->user = tryParseJson<User>(&TgTypeParser::parseJsonAndGetUser, data, "user");
    return result;
}

string TgTypeParser::parseMessageEntity(const MessageEntity::Ptr& object) const {
    if (!object) {
        return "";
    }
    string result;
    result += '{';
    appendToJson(result, "type", object->type);
    appendToJson(result, "offset", object->offset);
    appendToJson(result, "length", object->length);
    appendToJson(result, "url", object->url);
    appendToJson(result, "user", parseUser(object->user));
    removeLastComma(result);
    result += '}';
    return result;
}

Message::Ptr TgTypeParser::parseJsonAndGetMessage(const ptree& data) const {
    auto result(make_shared<Message>());
    result->messageId = data.get<int32_t>("message_id");
    result->from = tryParseJson<User>(&TgTypeParser::parseJsonAndGetUser, data, "from");
    result->date = data.get<int32_t>("date");
    result->chat = parseJsonAndGetChat(data.find("chat")->second);
    result->forwardFrom = tryParseJson<User>(&TgTypeParser::parseJsonAndGetUser, data, "forward_from");
    result->forwardFromChat = tryParseJson<Chat>(&TgTypeParser::parseJsonAndGetChat, data, "forward_from_chat");
    result->forwardFromMessageId = data.get<int32_t>("forward_from_message_id", 0);
    result->forwardSignature = data.get("forward_signature", "");
    result->forwardSenderName = data.get("forward_sender_name", "");
    result->forwardDate = data.get("forward_date", 0);
    result->replyToMessage = tryParseJson<Message>(&TgTypeParser::parseJsonAndGetMessage, data, "reply_to_message");
    result->editDate = data.get<int32_t>("edit_date", 0);
    result->authorSignature = data.get("author_signature", "");
    result->text = data.get("text", "");
    result->entities = parseJsonAndGetArray<MessageEntity>(&TgTypeParser::parseJsonAndGetMessageEntity, data, "entities");
    result->captionEntities = parseJsonAndGetArray<MessageEntity>(&TgTypeParser::parseJsonAndGetMessageEntity, data, "caption_entities");
    result->audio = tryParseJson<Audio>(&TgTypeParser::parseJsonAndGetAudio, data, "audio");
    result->document = tryParseJson<Document>(&TgTypeParser::parseJsonAndGetDocument, data, "document");
    result->animation = tryParseJson<Animation>(&TgTypeParser::parseJsonAndGetAnimation, data, "animation");
    result->game = tryParseJson<Game>(&TgTypeParser::parseJsonAndGetGame, data, "game");
    result->photo = parseJsonAndGetArray<PhotoSize>(&TgTypeParser::parseJsonAndGetPhotoSize, data, "photo");
    result->sticker = tryParseJson<Sticker>(&TgTypeParser::parseJsonAndGetSticker, data, "sticker");
    result->video = tryParseJson<Video>(&TgTypeParser::parseJsonAndGetVideo, data, "video");
    result->voice = tryParseJson<Voice>(&TgTypeParser::parseJsonAndGetVoice, data, "voice");
    result->contact = tryParseJson<Contact>(&TgTypeParser::parseJsonAndGetContact, data, "contact");
    result->location = tryParseJson<Location>(&TgTypeParser::parseJsonAndGetLocation, data, "location");
    result->poll = tryParseJson<Poll>(&TgTypeParser::parseJsonAndGetPoll, data, "poll");
    result->newChatMember = tryParseJson<User>(&TgTypeParser::parseJsonAndGetUser, data, "new_chat_participant");
    result->newChatMembers = parseJsonAndGetArray<User>(&TgTypeParser::parseJsonAndGetUser, data, "new_chat_members");
    result->leftChatMember = tryParseJson<User>(&TgTypeParser::parseJsonAndGetUser, data, "left_chat_participant");
    result->newChatTitle = data.get("new_chat_title", "");
    result->newChatPhoto = parseJsonAndGetArray<PhotoSize>(&TgTypeParser::parseJsonAndGetPhotoSize, data, "new_chat_photo");
    result->deleteChatPhoto = data.get("delete_chat_photo", false);
    result->groupChatCreated = data.get("group_chat_created", false);
    result->caption = data.get("caption", "");
    result->supergroupChatCreated = data.get("supergroup_chat_created", false);
    result->channelChatCreated = data.get("channel_chat_created", false);
    result->migrateToChatId = data.get<int64_t>("migrate_to_chat_id", 0);
    result->migrateFromChatId = data.get<int64_t>("migrate_from_chat_id", 0);
    result->pinnedMessage = tryParseJson<Message>(&TgTypeParser::parseJsonAndGetMessage, data, "pinned_message");
    result->invoice = tryParseJson<Invoice>(&TgTypeParser::parseJsonAndGetInvoice, data, "invoice");
    result->successfulPayment = tryParseJson<SuccessfulPayment>(&TgTypeParser::parseJsonAndGetSuccessfulPayment, data, "successful_payment");
    result->connectedWebsite = data.get("connected_website", "");
    result->replyMarkup = tryParseJson<InlineKeyboardMarkup>(&TgTypeParser::parseJsonAndGetInlineKeyboardMarkup, data, "reply_markup");
    return result;
}

string TgTypeParser::parseMessage(const Message::Ptr& object) const {
    if (!object) {
        return "";
    }
    string result;
    result += '{';
    appendToJson(result, "message_id", object->messageId);
    appendToJson(result, "from", parseUser(object->from));
    appendToJson(result, "date", object->date);
    appendToJson(result, "chat", parseChat(object->chat));
    appendToJson(result, "forward_from", parseUser(object->forwardFrom));
    appendToJson(result, "forward_from_chat", parseChat(object->forwardFromChat));
    appendToJson(result, "forward_from_message_id", object->forwardFromMessageId);
    appendToJson(result, "forward_signature", object->forwardSignature);
    appendToJson(result, "forward_sender_name", object->forwardSenderName);
    appendToJson(result, "forward_date", object->forwardDate);
    appendToJson(result, "reply_to_message", parseMessage(object->replyToMessage));
    appendToJson(result, "edit_date", object->editDate);
    appendToJson(result, "author_signature", object->authorSignature);
    appendToJson(result, "text", object->text);
    appendToJson(result, "audio", parseAudio(object->audio));
    appendToJson(result, "document", parseDocument(object->document));
    appendToJson(result, "animation", parseAnimation(object->animation));
    appendToJson(result, "photo", parseArray(&TgTypeParser::parsePhotoSize, object->photo));
    appendToJson(result, "sticker", parseSticker(object->sticker));
    appendToJson(result, "video", parseVideo(object->video));
    appendToJson(result, "voice", parseVoice(object->voice));
    appendToJson(result, "contact", parseContact(object->contact));
    appendToJson(result, "location", parseLocation(object->location));
    appendToJson(result, "poll", parsePoll(object->poll));
    appendToJson(result, "new_chat_member", parseUser(object->newChatMember));
    appendToJson(result, "new_chat_members", parseArray(&TgTypeParser::parseUser, object->newChatMembers));
    appendToJson(result, "left_chat_member", parseUser(object->leftChatMember));
    appendToJson(result, "new_chat_title", object->newChatTitle);
    appendToJson(result, "new_chat_photo", parseArray(&TgTypeParser::parsePhotoSize, object->newChatPhoto));
    appendToJson(result, "delete_chat_photo", object->deleteChatPhoto);
    appendToJson(result, "group_chat_created", object->groupChatCreated);
    appendToJson(result, "caption", object->caption);
    appendToJson(result, "supergroup_chat_created", object->supergroupChatCreated);
    appendToJson(result, "channel_chat_created", object->channelChatCreated);
    appendToJson(result, "migrate_to_chat_id", object->migrateToChatId);
    appendToJson(result, "migrate_from_chat_id", object->migrateFromChatId);
    appendToJson(result, "pinned_message", parseMessage(object->pinnedMessage));
    appendToJson(result, "connected_website", object->connectedWebsite);
    appendToJson(result, "invoice", parseInvoice(object->invoice));
    appendToJson(result, "successful_payment", parseSuccessfulPayment(object->successfulPayment));
    appendToJson(result, "reply_markup", parseInlineKeyboardMarkup(object->replyMarkup));
    removeLastComma(result);
    result += '}';
    return result;
}

PhotoSize::Ptr TgTypeParser::parseJsonAndGetPhotoSize(const ptree& data) const {
    auto result(make_shared<PhotoSize>());
    result->fileId = data.get<string>("file_id");
    result->width = data.get<int32_t>("width");
    result->height = data.get<int32_t>("height");
    result->fileSize = data.get("file_size", 0);
    return result;
}

string TgTypeParser::parsePhotoSize(const PhotoSize::Ptr& object) const {
    if (!object) {
        return "";
    }
    string result;
    result += '{';
    appendToJson(result, "file_id", object->fileId);
    appendToJson(result, "width", object->width);
    appendToJson(result, "height", object->height);
    appendToJson(result, "file_size", object->fileSize);
    removeLastComma(result);
    result += '}';
    return result;
}

Audio::Ptr TgTypeParser::parseJsonAndGetAudio(const ptree& data) const {
    auto result(make_shared<Audio>());
    result->fileId = data.get<string>("file_id");
    result->duration = data.get<int32_t>("duration");
    result->performer = data.get<string>("performer", "");
    result->title = data.get<string>("title", "");
    result->mimeType = data.get("mime_type", "");
    result->fileSize = data.get("file_size", 0);
    result->thumb = tryParseJson<PhotoSize>(&TgTypeParser::parseJsonAndGetPhotoSize, data, "thumb");
    return result;
}

string TgTypeParser::parseAudio(const Audio::Ptr& object) const {
    if (!object) {
        return "";
    }
    string result;
    result += '{';
    appendToJson(result, "file_id", object->fileId);
    appendToJson(result, "duration", object->duration);
    appendToJson(result, "mime_type", object->mimeType);
    appendToJson(result, "file_size", object->fileSize);
    appendToJson(result, "thumb", parsePhotoSize(object->thumb));
    removeLastComma(result);
    result += '}';
    return result;
}

Document::Ptr TgTypeParser::parseJsonAndGetDocument(const ptree& data) const {
    auto result(make_shared<Document>());
    result->fileId = data.get<string>("file_id");
    result->thumb = tryParseJson<PhotoSize>(&TgTypeParser::parseJsonAndGetPhotoSize, data, "thumb");
    result->fileName = data.get("file_name", "");
    result->mimeType = data.get("mime_type", "");
    result->fileSize = data.get("file_size", 0);
    return result;
}

string TgTypeParser::parseDocument(const Document::Ptr& object) const {
    if (!object) {
        return "";
    }
    string result;
    result += '{';
    appendToJson(result, "file_id", object->fileId);
    appendToJson(result, "thumb", parsePhotoSize(object->thumb));
    appendToJson(result, "file_name", object->fileName);
    appendToJson(result, "mime_type", object->mimeType);
    appendToJson(result, "file_size", object->fileSize);
    removeLastComma(result);
    result += '}';
    return result;
}

Sticker::Ptr TgTypeParser::parseJsonAndGetSticker(const ptree& data) const {
    auto result(make_shared<Sticker>());
    result->fileId = data.get<string>("file_id");
    result->width = data.get<int32_t>("width");
    result->height = data.get<int32_t>("height");
    result->isAnimated = data.get<bool>("is_animated", false);
    result->thumb = tryParseJson<PhotoSize>(&TgTypeParser::parseJsonAndGetPhotoSize, data, "thumb");
    result->emoji = data.get("emoji", "");
    result->setName = data.get("set_name", "");
    result->maskPosition = tryParseJson<MaskPosition>(&TgTypeParser::parseJsonAndGetMaskPosition, data, "mask_position");
    result->fileSize = data.get("file_size", 0);
    return result;
}

string TgTypeParser::parseSticker(const Sticker::Ptr& object) const {
    if (!object) {
        return "";
    }
    string result;
    result += '{';
    appendToJson(result, "file_id", object->fileId);
    appendToJson(result, "width", object->width);
    appendToJson(result, "height", object->height);
    appendToJson(result, "is_animated", object->isAnimated);
    appendToJson(result, "thumb", parsePhotoSize(object->thumb));
    appendToJson(result, "emoji", object->emoji);
    appendToJson(result, "file_size", object->fileSize);
    removeLastComma(result);
    result += '}';
    return result;
}

StickerSet::Ptr TgTypeParser::parseJsonAndGetStickerSet(const ptree& data) const {
    auto result(make_shared<StickerSet>());
    result->name = data.get("name", "");
    result->title = data.get("title", "");
    result->containsMasks = data.get<bool>("contains_masks", false);
    result->isAnimated = data.get<bool>("is_animated", false);
    result->stickers = parseJsonAndGetArray<Sticker>(&TgTypeParser::parseJsonAndGetSticker, data, "stickers");
    return result;
}

string TgTypeParser::parseStickerSet(const StickerSet::Ptr& object) const {
    if (!object) {
        return "";
    }
    string result;
    result += '{';
    appendToJson(result, "name", object->name);
    appendToJson(result, "title", object->title);
    appendToJson(result, "is_animated", object->isAnimated);
    appendToJson(result, "contains_masks", object->containsMasks);
    appendToJson(result, "stickers", parseArray(&TgTypeParser::parseSticker, object->stickers));
    removeLastComma(result);
    result += '}';
    return result;
}

MaskPosition::Ptr TgTypeParser::parseJsonAndGetMaskPosition(const ptree& data) const {
    auto result(make_shared<MaskPosition>());
    result->point = data.get("point", "");
    result->xShift = data.get<float>("x_shift", 0);
    result->yShift = data.get<float>("y_shift", 0);
    result->scale = data.get<float>("scale", 0);
    return result;
}

string TgTypeParser::parseMaskPosition(const MaskPosition::Ptr& object) const {
    if (!object) {
        return "";
    }
    string result;
    result += '{';
    appendToJson(result, "point", object->point);
    appendToJson(result, "x_shift", object->xShift);
    appendToJson(result, "y_shift", object->yShift);
    appendToJson(result, "scale", object->scale);
    removeLastComma(result);
    result += '}';
    return result;
}

Poll::Ptr TgTypeParser::parseJsonAndGetPoll(const ptree& data) const {
    auto result(make_shared<Poll>());
    result->id = data.get("id", 0);
    result->question = data.get("question", "");
    result->options = parseJsonAndGetArray<PollOption>(&TgTypeParser::parseJsonAndGetPollOption, data, "options");
    result->isClosed = data.get<bool>("is_closed");
    return result;
}

string TgTypeParser::parsePoll(const Poll::Ptr& object) const {
    if (!object) {
        return "";
    }
    string result;
    result += '{';
    appendToJson(result, "id", object->id);
    appendToJson(result, "question", object->question);
    appendToJson(result, "options", parseArray(&TgTypeParser::parsePollOption, object->options));
    appendToJson(result, "is_closed", object->isClosed);
    removeLastComma(result);
    result += '}';
    return result;
}

PollOption::Ptr TgTypeParser::parseJsonAndGetPollOption(const ptree& data) const {
    auto result(make_shared<PollOption>());
    result->text = data.get("text", "");
    result->voterCount = data.get("voter_count", 0);
    return result;
}

string TgTypeParser::parsePollOption(const PollOption::Ptr& object) const {
    if (!object) {
        return "";
    }
    string result;
    result += '{';
    appendToJson(result, "text", object->text);
    appendToJson(result, "voter_count", object->voterCount);
    removeLastComma(result);
    result += '}';
    return result;
}

ChatPermissions::Ptr TgTypeParser::parseJsonAndGetChatPermissions(const ptree& data) const {
    auto result(make_shared<ChatPermissions>());
    result->canSendMessages = data.get<bool>("can_send_messages");
    result->canSendMediaMessages = data.get<bool>("can_send_media_messages");
    result->canSendPolls = data.get<bool>("can_send_polls");
    result->canSendOtherMessages = data.get<bool>("can_send_other_messages");
    result->canAddWebPagePreviews = data.get<bool>("can_add_web_page_previews");
    result->canChangeInfo = data.get<bool>("can_change_info");
    result->canInviteUsers = data.get<bool>("can_invite_users");
    result->canPinMessages = data.get<bool>("can_pin_messages");
    return result;
}

string TgTypeParser::parseChatPermissions(const ChatPermissions::Ptr& object) const {
    if (!object) {
        return "";
    }
    string result;
    result += '{';
    appendToJson(result, "can_send_messages", object->canSendMessages);
    appendToJson(result, "can_send_media_messages", object->canSendMediaMessages);
    appendToJson(result, "can_send_polls", object->canSendPolls);
    appendToJson(result, "can_send_other_messages", object->canSendOtherMessages);
    appendToJson(result, "can_add_web_page_previews", object->canAddWebPagePreviews);
    appendToJson(result, "can_change_info", object->canChangeInfo);
    appendToJson(result, "can_invite_users", object->canInviteUsers);
    appendToJson(result, "can_pin_messages", object->canPinMessages);
    removeLastComma(result);
    result += '}';
    return result;
}

Video::Ptr TgTypeParser::parseJsonAndGetVideo(const ptree& data) const {
    auto result(make_shared<Video>());
    result->fileId = data.get<string>("file_id");
    result->width = data.get<int32_t>("width");
    result->height = data.get<int32_t>("height");
    result->duration = data.get<int32_t>("duration");
    result->thumb = tryParseJson<PhotoSize>(&TgTypeParser::parseJsonAndGetPhotoSize, data, "thumb");
    result->mimeType = data.get("mime_type", "");
    result->fileSize = data.get("file_size", 0);
    return result;
}

string TgTypeParser::parseVideo(const Video::Ptr& object) const {
    if (!object) {
        return "";
    }
    string result;
    result += '{';
    appendToJson(result, "file_id", object->fileId);
    appendToJson(result, "width", object->width);
    appendToJson(result, "height", object->height);
    appendToJson(result, "duration", object->duration);
    appendToJson(result, "thumb", parsePhotoSize(object->thumb));
    appendToJson(result, "mime_type", object->mimeType);
    appendToJson(result, "file_size", object->fileSize);
    removeLastComma(result);
    result += '}';
    return result;
}

Voice::Ptr TgTypeParser::parseJsonAndGetVoice(const ptree& data) const {
    auto result(make_shared<Voice>());
    result->fileId = data.get<string>("file_id");
    result->duration = data.get<int32_t>("duration");
    result->mimeType = data.get("mime_type", "");
    result->fileSize = data.get("file_size", 0);
    return result;
}

string TgTypeParser::parseVoice(const Voice::Ptr& object) const {
    if (!object) {
        return "";
    }
    string result;
    result += '{';
    appendToJson(result, "file_id", object->fileId);
    appendToJson(result, "duration", object->duration);
    appendToJson(result, "mime_type", object->mimeType);
    appendToJson(result, "file_size", object->fileSize);
    removeLastComma(result);
    result += '}';
    return result;
}

VideoNote::Ptr TgTypeParser::parseJsonAndGetVideoNote(const ptree& data) const {
    auto result(make_shared<VideoNote>());
    result->fileId = data.get<string>("file_id");
    result->length = data.get<int32_t>("length");
    result->duration = data.get<int32_t>("duration");
    result->thumb = tryParseJson<PhotoSize>(&TgTypeParser::parseJsonAndGetPhotoSize, data, "thumb");
    result->fileSize = data.get("file_size", 0);
    return result;
}

string TgTypeParser::parseVideoNote(const VideoNote::Ptr& object) const {
    if (!object) {
        return "";
    }
    string result;
    result += '{';
    appendToJson(result, "file_id", object->fileId);
    appendToJson(result, "length", object->length);
    appendToJson(result, "duration", object->duration);
    appendToJson(result, "thumb", parsePhotoSize(object->thumb));
    appendToJson(result, "file_size", object->fileSize);
    result += '}';
    result.erase();
    return result;
}

Game::Ptr TgTypeParser::parseJsonAndGetGame(const ptree& data) const {
    auto result(make_shared<Game>());
    result->title = data.get("title", "");
    result->description = data.get("description", "");
    result->photo = parseJsonAndGetArray<PhotoSize>(&TgTypeParser::parseJsonAndGetPhotoSize, data, "photo");
    result->text = data.get("text", "");
    result->textEntities = parseJsonAndGetArray<MessageEntity>(&TgTypeParser::parseJsonAndGetMessageEntity, data, "text_entities");
    result->animation = tryParseJson<Animation>(&TgTypeParser::parseJsonAndGetAnimation, data, "animation");
    return result;
}

string TgTypeParser::parseGame(const Game::Ptr& object) const {
    if (!object) {
        return "";
    }
    string result;
    result += '{';
    appendToJson(result, "title", object->title);
    appendToJson(result, "description", object->description);
    appendToJson(result, "photo", parseArray(&TgTypeParser::parsePhotoSize, object->photo));
    appendToJson(result, "text", object->text);
    appendToJson(result, "text_entities", parseArray(&TgTypeParser::parseMessageEntity, object->textEntities));
    appendToJson(result, "animation", parseAnimation(object->animation));
    removeLastComma(result);
    result += '}';
    return result;
}

GameHighScore::Ptr TgTypeParser::parseJsonAndGetGameHighScore(const ptree& data) const {
    auto result(make_shared<GameHighScore>());
    result->position = data.get("position", "");
    result->user = tryParseJson<User>(&TgTypeParser::parseJsonAndGetUser, data, "user");
    result->score = data.get<int32_t>("score", 0);
    return result;
}

string TgTypeParser::parseGameHighScore(const GameHighScore::Ptr& object) const {
    if (!object) {
        return "";
    }
    string result;
    result += '{';
    appendToJson(result, "position", object->position);
    appendToJson(result, "user", parseUser(object->user));
    appendToJson(result, "score", object->score);
    removeLastComma(result);
    result += '}';
    return result;
}

Animation::Ptr TgTypeParser::parseJsonAndGetAnimation(const ptree& data) const {
    auto result(make_shared<Animation>());
    result->fileId = data.get("file_id", "");
    result->thumb = tryParseJson<PhotoSize>(&TgTypeParser::parseJsonAndGetPhotoSize, data, "thumb");
    result->fileName = data.get("file_name", "");
    result->mimeType = data.get("mime_type", "");
    result->fileSize = data.get<int32_t>("file_size", 0);
    return result;
}

string TgTypeParser::parseAnimation(const Animation::Ptr& object) const {
    if (!object) {
        return "";
    }
    string result;
    result += '{';
    appendToJson(result, "file_id", object->fileId);
    appendToJson(result, "thumb", parsePhotoSize(object->thumb));
    appendToJson(result, "file_name", object->fileName);
    appendToJson(result, "mime_type", object->mimeType);
    appendToJson(result, "file_size", object->fileSize);
    removeLastComma(result);
    result += '}';
    return result;
}

Contact::Ptr TgTypeParser::parseJsonAndGetContact(const ptree& data) const {
    auto result(make_shared<Contact>());
    result->phoneNumber = data.get<string>("phone_number");
    result->firstName = data.get<string>("first_name");
    result->lastName = data.get("last_name", "");
    result->userId = data.get("user_id", "");
    result->vcard = data.get("vcard", "");
    return result;
}

string TgTypeParser::parseContact(const Contact::Ptr& object) const {
    if (!object) {
        return "";
    }
    string result;
    result += '{';
    appendToJson(result, "phone_number", object->phoneNumber);
    appendToJson(result, "first_name", object->firstName);
    appendToJson(result, "last_name", object->lastName);
    appendToJson(result, "user_id", object->userId);
    appendToJson(result, "vcard", object->vcard);
    removeLastComma(result);
    result += '}';
    return result;
}

Location::Ptr TgTypeParser::parseJsonAndGetLocation(const ptree& data) const {
    auto result(make_shared<Location>());
    result->longitude = data.get<float>("longitude", 0);
    result->latitude = data.get<float>("latitude", 0);
    return result;
}

string TgTypeParser::parseLocation(const Location::Ptr& object) const {
    if (!object) {
        return "";
    }
    string result;
    result += '{';
    appendToJson(result, "longitude", object->longitude);
    appendToJson(result, "latitude", object->latitude);
    removeLastComma(result);
    result += '}';
    return result;
}

Update::Ptr TgTypeParser::parseJsonAndGetUpdate(const ptree& data) const {
    auto result(make_shared<Update>());
    result->updateId = data.get<int32_t>("update_id");
    result->message = tryParseJson<Message>(&TgTypeParser::parseJsonAndGetMessage, data, "message");
    result->editedMessage = tryParseJson<Message>(&TgTypeParser::parseJsonAndGetMessage, data, "edited_message");
    result->channelPost = tryParseJson<Message>(&TgTypeParser::parseJsonAndGetMessage, data, "channel_post");
    result->editedChannelPost = tryParseJson<Message>(&TgTypeParser::parseJsonAndGetMessage, data, "edited_channel_post");
    result->inlineQuery = tryParseJson<InlineQuery>(&TgTypeParser::parseJsonAndGetInlineQuery, data, "inline_query");
    result->chosenInlineResult = tryParseJson<ChosenInlineResult>(&TgTypeParser::parseJsonAndGetChosenInlineResult, data, "chosen_inline_result");
    result->callbackQuery = tryParseJson<CallbackQuery>(&TgTypeParser::parseJsonAndGetCallbackQuery, data, "callback_query");
    result->shippingQuery = tryParseJson<ShippingQuery>(&TgTypeParser::parseJsonAndGetShippingQuery, data, "shipping_query");
    result->preCheckoutQuery = tryParseJson<PreCheckoutQuery>(&TgTypeParser::parseJsonAndGetPreCheckoutQuery, data, "pre_checkout_query");
    return result;
}

string TgTypeParser::parseUpdate(const Update::Ptr& object) const {
    if (!object) {
        return "";
    }
    string result;
    result += '{';
    appendToJson(result, "update_id", object->updateId);
    appendToJson(result, "message", parseMessage(object->message));
    appendToJson(result, "edited_message", parseMessage(object->editedMessage));
    appendToJson(result, "channel_post", parseMessage(object->channelPost));
    appendToJson(result, "edited_channel_post", parseMessage(object->editedChannelPost));
    appendToJson(result, "inline_query", parseInlineQuery(object->inlineQuery));
    appendToJson(result, "chosen_inline_result", parseChosenInlineResult(object->chosenInlineResult));
    appendToJson(result, "callback_query", parseCallbackQuery(object->callbackQuery));
    appendToJson(result, "shipping_query", parseShippingQuery(object->shippingQuery));
    appendToJson(result, "pre_checkout_query", parsePreCheckoutQuery(object->preCheckoutQuery));
    removeLastComma(result);
    result += '}';
    return result;
}

UserProfilePhotos::Ptr TgTypeParser::parseJsonAndGetUserProfilePhotos(const ptree& data) const {
    auto result(make_shared<UserProfilePhotos>());
    result->totalCount = data.get<int32_t>("total_count");
    result->photos = parseJsonAndGet2DArray<PhotoSize>(&TgTypeParser::parseJsonAndGetPhotoSize, data, "photos");
    return result;
}

string TgTypeParser::parseUserProfilePhotos(const UserProfilePhotos::Ptr& object) const {
    if (!object) {
        return "";
    }
    string result;
    result += '{';
    appendToJson(result, "total_count", object->totalCount);
    appendToJson(result, "photos", parse2DArray(&TgTypeParser::parsePhotoSize, object->photos));
    removeLastComma(result);
    result += '}';
    return result;
}

InputMedia::Ptr TgTypeParser::parseJsonAndGetInputMedia(const ptree& data) const {
    string type = data.get("type", "");
    if (type == "photo") {
        auto result(make_shared<InputMediaPhoto>());
        result->media = data.get("media", "");
        result->caption = data.get("caption", "");
        result->parseMode = data.get("parse_mode", "");
        result->thumb = data.get("thumb", "");
        return result;
    }
    else if (type == "video") {
        auto result(make_shared<InputMediaVideo>());
        result->media = data.get("media", "");
        result->caption = data.get("caption", "");
        result->parseMode = data.get("parse_mode", "");
        result->thumb = data.get("thumb", "");
        result->width = data.get<int32_t>("width", 0);
        result->height = data.get<int32_t>("height", 0);
        result->duration = data.get<int32_t>("duration", 0);
        result->supportsStreaming = data.get<bool>("supports_streaming", false);
        return result;
    }
    else if (type == "animation") {
        auto result(make_shared<InputMediaAnimation>());
        result->media = data.get("media", "");
        result->caption = data.get("caption", "");
        result->parseMode = data.get("parse_mode", "");
        result->thumb = data.get("thumb", "");
        result->width = data.get<int32_t>("width", 0);
        result->height = data.get<int32_t>("height", 0);
        result->duration = data.get<int32_t>("duration", 0);
        return result;
    } else if (type == "document") {
        auto result(make_shared<InputMediaDocument>());
        result->media = data.get("media", "");
        result->caption = data.get("caption", "");
        result->parseMode = data.get("parse_mode", "");
        result->thumb = data.get("thumb", "");
        return result;
    } else if (type == "audio") {
        auto result(make_shared<InputMediaAudio>());
        result->media = data.get("media", "");
        result->caption = data.get("caption", "");
        result->parseMode = data.get("parse_mode", "");
        result->thumb = data.get("thumb", "");
        result->duration = data.get<int32_t>("duration", 0);
        result->title = data.get<int32_t>("title", 0);
        result->performer = data.get<int32_t>("performer", 0);
        return result;
    }
    else {
        return nullptr;
    }
}

string TgTypeParser::parseInputMedia(const InputMedia::Ptr& object) const {
    if (!object) {
        return "";
    }
    string result;
    result += '{';
    switch(object->type) {
        case InputMedia::TYPE::PHOTO:
            appendToJson(result, "type", "photo");
        break;
        case InputMedia::TYPE::VIDEO:
            appendToJson(result, "type", "video");
        break;
        case InputMedia::TYPE::ANIMATION:
            appendToJson(result, "type", "animation");
        break;
        case InputMedia::TYPE::DOCUMENT:
            appendToJson(result, "type", "document");
        break;
        case InputMedia::TYPE::AUDIO:
            appendToJson(result, "type", "audio");
        break;
    }
    appendToJson(result, "media", object->media);
    appendToJson(result, "caption", object->caption);
    appendToJson(result, "parse_mode", object->parseMode);
    if (object->width) {
        appendToJson(result, "width", object->width);
    }
    if (object->height) {
        appendToJson(result, "height", object->height);
    }
    if (object->duration) {
        appendToJson(result, "duration", object->duration);
    }
    if (object->performer) {
        appendToJson(result, "performer", object->performer);
    }
    if (object->supportsStreaming) {
        appendToJson(result, "supports_streaming", object->supportsStreaming);
    }
    removeLastComma(result);
    result += '}';
    return result;
}

File::Ptr TgTypeParser::parseJsonAndGetFile(const boost::property_tree::ptree& data) const {
    auto result(make_shared<File>());
    result->fileId = data.get<string>("file_id");
    result->fileSize = data.get<int32_t>("file_size", 0);
    result->filePath = data.get<string>("file_path", "");
    return result;
}

string TgTypeParser::parseFile(const File::Ptr& object) const {
    if (!object) {
        return "";
    }
    string result;
    result += '{';
    appendToJson(result, "file_id", object->fileId);
    appendToJson(result, "file_size", object->fileSize);
    appendToJson(result, "file_path", object->filePath);
    removeLastComma(result);
    result += '}';
    return result;
}

ReplyKeyboardMarkup::Ptr TgTypeParser::parseJsonAndGetReplyKeyboardMarkup(const boost::property_tree::ptree& data) const {
    auto result(make_shared<ReplyKeyboardMarkup>());
    for (const auto& item : data.find("keyboard")->second){
        result->keyboard.push_back(parseJsonAndGetArray<KeyboardButton>(&TgTypeParser::parseJsonAndGetKeyboardButton, item.second));
    }
    result->resizeKeyboard = data.get<bool>("resize_keyboard", false);
    result->oneTimeKeyboard = data.get<bool>("one_time_keyboard", false);
    result->selective = data.get<bool>("selective", false);
    return result;
}

std::string TgTypeParser::parseReplyKeyboardMarkup(const ReplyKeyboardMarkup::Ptr& object) const {
    if (!object) {
        return "";
    }
    string result;
    result += '{';
    result += R"("keyboard":[)";
    for (const auto& item : object->keyboard) {
        result += '[';
        for (const auto& innerItem : item) {
            result += parseKeyboardButton(innerItem);
            result += ',';
        }
        removeLastComma(result);
        result += "],";
    }
    if (!object->keyboard.empty())
        removeLastComma(result);
    result += "],";
    appendToJson(result, "resize_keyboard", object->resizeKeyboard);
    appendToJson(result, "one_time_keyboard", object->oneTimeKeyboard);
    appendToJson(result, "selective", object->selective);
    removeLastComma(result);
    result += '}';
    return result;
}

KeyboardButton::Ptr TgTypeParser::parseJsonAndGetKeyboardButton(const boost::property_tree::ptree& data) const {
    auto result(make_shared<KeyboardButton>());
    result->text = data.get<string>("text");
    result->requestContact = data.get<bool>("request_contact", false);
    result->requestLocation = data.get<bool>("request_location", false);
    return result;
}

std::string TgTypeParser::parseKeyboardButton(const KeyboardButton::Ptr& object) const {
    if (!object) {
        return "";
    }
    string result;
    result += '{';
    appendToJson(result, "text", object->text);
    appendToJson(result, "request_contact", object->requestContact);
    appendToJson(result, "request_location", object->requestLocation);
    removeLastComma(result);
    result += '}';
    return result;
}

ReplyKeyboardRemove::Ptr TgTypeParser::parseJsonAndGetReplyKeyboardRemove(const boost::property_tree::ptree& data) const {
    auto result(make_shared<ReplyKeyboardRemove>());
    result->selective = data.get<bool>("selective", false);
    return result;
}

std::string TgTypeParser::parseReplyKeyboardRemove(const ReplyKeyboardRemove::Ptr& object) const {
    if (!object) {
        return "";
    }
    string result;
    result += '{';
    appendToJson(result, "remove_keyboard", object->removeKeyboard);
    appendToJson(result, "selective", object->selective);
    removeLastComma(result);
    result += '}';
    return result;
}

ForceReply::Ptr TgTypeParser::parseJsonAndGetForceReply(const boost::property_tree::ptree& data) const {
    auto result(make_shared<ForceReply>());
    result->selective = data.get<bool>("selective");
    return result;
}

std::string TgTypeParser::parseForceReply(const ForceReply::Ptr& object) const {
    if (!object) {
        return "";
    }
    string result;
    result += '{';
    appendToJson(result, "force_reply", object->forceReply);
    appendToJson(result, "selective", object->selective);
    removeLastComma(result);
    result += '}';
    return result;
}

ChatMember::Ptr TgTypeParser::parseJsonAndGetChatMember(const boost::property_tree::ptree& data) const {
    auto result(make_shared<ChatMember>());
    result->user = tryParseJson<User>(&TgTypeParser::parseJsonAndGetUser, data, "user");
    result->status = data.get("status", "");
    result->untilDate = data.get<uint64_t>("until_date", 0);
    result->canBeEdited = data.get<bool>("can_be_edited", false);
    result->canChangeInfo = data.get<bool>("can_change_info", false);
    result->canPostMessages = data.get<bool>("can_post_messages", false);
    result->canEditMessages = data.get<bool>("can_edit_messages", false);
    result->canDeleteMessages = data.get<bool>("can_delete_messages", false);
    result->canInviteUsers = data.get<bool>("can_invite_users", false);
    result->canRestrictMembers = data.get<bool>("can_restrict_members", false);
    result->canPinMessages = data.get<bool>("can_pin_messages", false);
    result->isMember = data.get<bool>("is_member", false);
    result->canPromoteMembers = data.get<bool>("can_promote_messages", false);
    result->canSendMessages = data.get<bool>("can_send_messages", false);
    result->canSendMediaMessages = data.get<bool>("can_send_media_messages", false);
    result->canSendOtherMessages = data.get<bool>("can_send_other_messages", false);
    result->canAddWebPagePreviews = data.get<bool>("can_add_web_page_previews", false);
    return result;
}

std::string TgTypeParser::parseChatMember(const ChatMember::Ptr& object) const {
    if (!object) {
        return "";
    }
    string result;
    result += '{';
    appendToJson(result, "user", parseUser(object->user));
    appendToJson(result, "status", object->status);
    removeLastComma(result);
    result += '}';
    return result;
}

ChatPhoto::Ptr TgTypeParser::parseJsonAndGetChatPhoto(const boost::property_tree::ptree& data) const {
    auto result(make_shared<ChatPhoto>());
    result->smallFileId = data.get("small_file_id", "");
    result->bigFileId = data.get("big_file_id", "");
    return result;
}

std::string TgTypeParser::parseChatPhoto(const ChatPhoto::Ptr& object) const {
    if (!object) {
        return "";
    }
    string result;
    result += '{';
    appendToJson(result, "small_file_id", object->smallFileId);
    appendToJson(result, "big_file_id", object->bigFileId);
    removeLastComma(result);
    result += '}';
    return result;
}

ResponseParameters::Ptr TgTypeParser::parseJsonAndGetResponseParameters(const boost::property_tree::ptree& data) const {
    auto result(make_shared<ResponseParameters>());
    result->migrateToChatId = data.get<int32_t>("migrate_to_chat_id", 0);
    result->retryAfter = data.get<int32_t>("retry_after", 0);
    return result;
}

std::string TgTypeParser::parseResponseParameters(const ResponseParameters::Ptr& object) const {
    if (!object) {
        return "";
    }
    string result;
    result += '{';
    appendToJson(result, "migrate_to_chat_id", object->migrateToChatId);
    appendToJson(result, "retry_after", object->retryAfter);
    removeLastComma(result);
    result += '}';
    return result;
}

GenericReply::Ptr TgTypeParser::parseJsonAndGetGenericReply(const boost::property_tree::ptree& data) const {
    if (data.find("force_reply") != data.not_found()) {
        return static_pointer_cast<GenericReply>(parseJsonAndGetForceReply(data));
    } else if (data.find("remove_keyboard") != data.not_found()) {
        return static_pointer_cast<GenericReply>(parseJsonAndGetReplyKeyboardRemove(data));
    } else if (data.find("keyboard") != data.not_found()) {
        return static_pointer_cast<GenericReply>(parseJsonAndGetReplyKeyboardMarkup(data));
    } else if (data.find("inline_keyboard") != data.not_found()) {
        return static_pointer_cast<GenericReply>(parseJsonAndGetInlineKeyboardMarkup(data));
    }
    return make_shared<GenericReply>();
}

std::string TgTypeParser::parseGenericReply(const GenericReply::Ptr& object) const {
    if (!object) {
        return "";
    }
    if (dynamic_pointer_cast<ForceReply>(object) != nullptr) {
        return parseForceReply(static_pointer_cast<ForceReply>(object));
    } else if (dynamic_pointer_cast<ReplyKeyboardRemove>(object) != nullptr) {
        return parseReplyKeyboardRemove(static_pointer_cast<ReplyKeyboardRemove>(object));
    } else if (dynamic_pointer_cast<ReplyKeyboardMarkup>(object) != nullptr){
        return parseReplyKeyboardMarkup(static_pointer_cast<ReplyKeyboardMarkup>(object));
    } else if (dynamic_pointer_cast<InlineKeyboardMarkup>(object) != nullptr){
        return parseInlineKeyboardMarkup(static_pointer_cast<InlineKeyboardMarkup>(object));
    }
    return "";
}

InlineQuery::Ptr TgTypeParser::parseJsonAndGetInlineQuery(const boost::property_tree::ptree& data) const {
    auto result(make_shared<InlineQuery>());
    result->id = data.get<string>("id");
    result->from = tryParseJson<User>(&TgTypeParser::parseJsonAndGetUser, data, "from");
    result->location = tryParseJson<Location>(&TgTypeParser::parseJsonAndGetLocation, data, "location");
    result->query = data.get<string>("query");
    result->offset = data.get<string>("offset");

    return result;
}

std::string TgTypeParser::parseInlineQuery(const InlineQuery::Ptr& object) const{
    if (!object) {
        return "";
    }
    string result;
    result += '{';
    appendToJson(result, "id", object->id);
    appendToJson(result, "from", parseUser(object->from));
    appendToJson(result, "location", parseLocation(object->location));
    appendToJson(result, "query", object->query);
    appendToJson(result, "offset", object->offset);
    removeLastComma(result);
    result += '}';
    return result;
}

InlineQueryResult::Ptr TgTypeParser::parseJsonAndGetInlineQueryResult(const boost::property_tree::ptree& data) const {
    string type = data.get<string>("type");
    InlineQueryResult::Ptr result;

    if (type == InlineQueryResultCachedAudio::TYPE) {
        result = static_pointer_cast<InlineQueryResult>(parseJsonAndGetInlineQueryResultCachedAudio(data));
    } else if (type == InlineQueryResultCachedDocument::TYPE) {
        result = static_pointer_cast<InlineQueryResult>(parseJsonAndGetInlineQueryResultCachedDocument(data));
    } else if (type == InlineQueryResultCachedGif::TYPE) {
        result = static_pointer_cast<InlineQueryResult>(parseJsonAndGetInlineQueryResultCachedGif(data));
    } else if (type == InlineQueryResultCachedMpeg4Gif::TYPE) {
        result = static_pointer_cast<InlineQueryResult>(parseJsonAndGetInlineQueryResultCachedMpeg4Gif(data));
    } else if (type == InlineQueryResultCachedPhoto::TYPE) {
        result = static_pointer_cast<InlineQueryResult>(parseJsonAndGetInlineQueryResultCachedPhoto(data));
    } else if (type == InlineQueryResultCachedSticker::TYPE) {
        result = static_pointer_cast<InlineQueryResult>(parseJsonAndGetInlineQueryResultCachedSticker(data));
    } else if (type == InlineQueryResultCachedVideo::TYPE) {
        result = static_pointer_cast<InlineQueryResult>(parseJsonAndGetInlineQueryResultCachedVideo(data));
    } else if (type == InlineQueryResultCachedVoice::TYPE) {
        result = static_pointer_cast<InlineQueryResult>(parseJsonAndGetInlineQueryResultCachedVoice(data));
    } else if (type == InlineQueryResultArticle::TYPE) {
        result = static_pointer_cast<InlineQueryResult>(parseJsonAndGetInlineQueryResultArticle(data));
    } else if (type == InlineQueryResultAudio::TYPE) {
        result = static_pointer_cast<InlineQueryResult>(parseJsonAndGetInlineQueryResultAudio(data));
    } else if (type == InlineQueryResultContact::TYPE) {
        result = static_pointer_cast<InlineQueryResult>(parseJsonAndGetInlineQueryResultContact(data));
    } else if (type == InlineQueryResultGame::TYPE) {
        result = static_pointer_cast<InlineQueryResult>(parseJsonAndGetInlineQueryResultGame(data));
    } else if (type == InlineQueryResultDocument::TYPE) {
        result = static_pointer_cast<InlineQueryResult>(parseJsonAndGetInlineQueryResultDocument(data));
    } else if (type == InlineQueryResultLocation::TYPE) {
        result = static_pointer_cast<InlineQueryResult>(parseJsonAndGetInlineQueryResultLocation(data));
    } else if (type == InlineQueryResultVenue::TYPE) {
        result = static_pointer_cast<InlineQueryResult>(parseJsonAndGetInlineQueryResultVenue(data));
    } else if (type == InlineQueryResultVoice::TYPE) {
        result = static_pointer_cast<InlineQueryResult>(parseJsonAndGetInlineQueryResultVoice(data));
    } else if (type == InlineQueryResultPhoto::TYPE) {
        result = static_pointer_cast<InlineQueryResult>(parseJsonAndGetInlineQueryResultPhoto(data));
    } else if (type == InlineQueryResultGif::TYPE) {
        result = static_pointer_cast<InlineQueryResult>(parseJsonAndGetInlineQueryResultGif(data));
    } else if (type == InlineQueryResultMpeg4Gif::TYPE) {
        result = static_pointer_cast<InlineQueryResult>(parseJsonAndGetInlineQueryResultMpeg4Gif(data));
    } else if (type == InlineQueryResultVideo::TYPE) {
        result = static_pointer_cast<InlineQueryResult>(parseJsonAndGetInlineQueryResultVideo(data));
    } else {
        result = make_shared<InlineQueryResult>();
    }

    result->id = data.get<string>("id");
    result->title = data.get<string>("title", "");
    result->caption = data.get<string>("caption", "");
    result->replyMarkup = tryParseJson<InlineKeyboardMarkup>(&TgTypeParser::parseJsonAndGetInlineKeyboardMarkup, data, "reply_markup");
    result->inputMessageContent = tryParseJson<InputMessageContent>(&TgTypeParser::parseJsonAndGetInputMessageContent, data, "input_message_content");

    return result;
}

std::string TgTypeParser::parseInlineQueryResult(const InlineQueryResult::Ptr& object) const {
    if (!object){
        return "";
    }

    string result;
    result += '{';
    appendToJson(result, "id", object->id);
    appendToJson(result, "type", object->type);
    appendToJson(result, "title", object->title);
    appendToJson(result, "caption", object->caption);
    appendToJson(result, "reply_markup", parseInlineKeyboardMarkup(object->replyMarkup));
    appendToJson(result, "input_message_content", parseInputMessageContent(object->inputMessageContent));

    if (object->type == InlineQueryResultCachedAudio::TYPE) {
        result += parseInlineQueryResultCachedAudio(static_pointer_cast<InlineQueryResultCachedAudio>(object));
    }
    else if (object->type == InlineQueryResultCachedDocument::TYPE) {
        result += parseInlineQueryResultCachedDocument(static_pointer_cast<InlineQueryResultCachedDocument>(object));
    }
    else if (object->type == InlineQueryResultCachedGif::TYPE) {
        result += parseInlineQueryResultCachedGif(static_pointer_cast<InlineQueryResultCachedGif>(object));
    }
    else if (object->type == InlineQueryResultCachedMpeg4Gif::TYPE) {
        result += parseInlineQueryResultCachedMpeg4Gif(static_pointer_cast<InlineQueryResultCachedMpeg4Gif>(object));
    }
    else if (object->type == InlineQueryResultCachedPhoto::TYPE) {
        result += parseInlineQueryResultCachedPhoto(static_pointer_cast<InlineQueryResultCachedPhoto>(object));
    }
    else if (object->type == InlineQueryResultCachedSticker::TYPE) {
        result += parseInlineQueryResultCachedSticker(static_pointer_cast<InlineQueryResultCachedSticker>(object));
    }
    else if (object->type == InlineQueryResultCachedVideo::TYPE) {
        result += parseInlineQueryResultCachedVideo(static_pointer_cast<InlineQueryResultCachedVideo>(object));
    }
    else if (object->type == InlineQueryResultCachedVoice::TYPE) {
        result += parseInlineQueryResultCachedVoice(static_pointer_cast<InlineQueryResultCachedVoice>(object));
    }
    else if (object->type == InlineQueryResultArticle::TYPE) {
        result += parseInlineQueryResultArticle(static_pointer_cast<InlineQueryResultArticle>(object));
    }
    else if (object->type == InlineQueryResultAudio::TYPE) {
        result += parseInlineQueryResultAudio(static_pointer_cast<InlineQueryResultAudio>(object));
    }
    else if (object->type == InlineQueryResultContact::TYPE) {
        result += parseInlineQueryResultContact(static_pointer_cast<InlineQueryResultContact>(object));
    }
    else if (object->type == InlineQueryResultGame::TYPE) {
        result += parseInlineQueryResultGame(static_pointer_cast<InlineQueryResultGame>(object));
    }
    else if (object->type == InlineQueryResultDocument::TYPE) {
        result += parseInlineQueryResultDocument(static_pointer_cast<InlineQueryResultDocument>(object));
    }
    else if (object->type == InlineQueryResultLocation::TYPE) {
        result += parseInlineQueryResultLocation(static_pointer_cast<InlineQueryResultLocation>(object));
    }
    else if (object->type == InlineQueryResultVenue::TYPE) {
        result += parseInlineQueryResultVenue(static_pointer_cast<InlineQueryResultVenue>(object));
    }
    else if (object->type == InlineQueryResultVoice::TYPE) {
        result += parseInlineQueryResultVoice(static_pointer_cast<InlineQueryResultVoice>(object));
    }
    else if (object->type == InlineQueryResultPhoto::TYPE) {
        result += parseInlineQueryResultPhoto(static_pointer_cast<InlineQueryResultPhoto>(object));
    }
    else if (object->type == InlineQueryResultGif::TYPE) {
        result += parseInlineQueryResultGif(static_pointer_cast<InlineQueryResultGif>(object));
    }
    else if (object->type == InlineQueryResultMpeg4Gif::TYPE) {
        result += parseInlineQueryResultMpeg4Gif(static_pointer_cast<InlineQueryResultMpeg4Gif>(object));
    }
    else if (object->type == InlineQueryResultVideo::TYPE) {
        result += parseInlineQueryResultVideo(static_pointer_cast<InlineQueryResultVideo>(object));
    }

    removeLastComma(result);
    result += '}';
    return result;
}

InlineQueryResultCachedAudio::Ptr TgTypeParser::parseJsonAndGetInlineQueryResultCachedAudio(const boost::property_tree::ptree& data) const {
    // NOTE: This function will be called by parseJsonAndGgetInlineQueryResult().
    auto result(make_shared<InlineQueryResultCachedAudio>());
    result->audioFileId = data.get<string>("audio_file_id");
    return result;
}

std::string TgTypeParser::parseInlineQueryResultCachedAudio(const InlineQueryResultCachedAudio::Ptr& object) const {
    if (!object){
        return "";
    }
    // This function will be called by parseInlineQueryResult(), so I don't add
    // curly brackets to the result string.
    string result;
    appendToJson(result, "audio_file_id", object->audioFileId);
    // The last comma will be erased by parseInlineQueryResult().
    return result;
}

InlineQueryResultCachedDocument::Ptr TgTypeParser::parseJsonAndGetInlineQueryResultCachedDocument(const boost::property_tree::ptree& data) const {
    // NOTE: This function will be called by parseJsonAndGgetInlineQueryResult().
    auto result(make_shared<InlineQueryResultCachedDocument>());
    result->documentFileId = data.get<string>("document_file_id");
    result->description = data.get<string>("description", "");
    return result;
}

std::string TgTypeParser::parseInlineQueryResultCachedDocument(const InlineQueryResultCachedDocument::Ptr& object) const {
    if (!object){
        return "";
    }
    // This function will be called by parseInlineQueryResult(), so I don't add
    // curly brackets to the result string.
    string result;
    appendToJson(result, "document_file_id", object->documentFileId);
    appendToJson(result, "description", object->description);
    // The last comma will be erased by parseInlineQueryResult().
    return result;
}


InlineQueryResultCachedGif::Ptr TgTypeParser::parseJsonAndGetInlineQueryResultCachedGif(const boost::property_tree::ptree& data) const {
    // NOTE: This function will be called by parseJsonAndGgetInlineQueryResult().
    auto result(make_shared<InlineQueryResultCachedGif>());
    result->gifFileId = data.get<string>("gif_file_id");
    return result;
}

std::string TgTypeParser::parseInlineQueryResultCachedGif(const InlineQueryResultCachedGif::Ptr& object) const {
    if (!object){
        return "";
    }
    // This function will be called by parseInlineQueryResult(), so I don't add
    // curly brackets to the result string.
    string result;
    appendToJson(result, "gif_file_id", object->gifFileId);
    // The last comma will be erased by parseInlineQueryResult().
    return result;
}


InlineQueryResultCachedMpeg4Gif::Ptr TgTypeParser::parseJsonAndGetInlineQueryResultCachedMpeg4Gif(const boost::property_tree::ptree& data) const {
    // NOTE: This function will be called by parseJsonAndGgetInlineQueryResult().
    auto result(make_shared<InlineQueryResultCachedMpeg4Gif>());
    result->mpeg4FileId = data.get<string>("mpeg4_file_id");
    return result;
}

std::string TgTypeParser::parseInlineQueryResultCachedMpeg4Gif(const InlineQueryResultCachedMpeg4Gif::Ptr& object) const {
    if (!object){
        return "";
    }
    // This function will be called by parseInlineQueryResult(), so I don't add
    // curly brackets to the result string.
    string result;
    appendToJson(result, "mpeg4_file_id", object->mpeg4FileId);
    // The last comma will be erased by parseInlineQueryResult().
    return result;
}


InlineQueryResultCachedPhoto::Ptr TgTypeParser::parseJsonAndGetInlineQueryResultCachedPhoto(const boost::property_tree::ptree& data) const {
    // NOTE: This function will be called by parseJsonAndGgetInlineQueryResult().
    auto result(make_shared<InlineQueryResultCachedPhoto>());
    result->photoFileId = data.get<string>("photo_file_id");
    result->description = data.get<string>("description", "");
    return result;
}

std::string TgTypeParser::parseInlineQueryResultCachedPhoto(const InlineQueryResultCachedPhoto::Ptr& object) const {
    if (!object){
        return "";
    }
    // This function will be called by parseInlineQueryResult(), so I don't add
    // curly brackets to the result string.
    string result;
    appendToJson(result, "photo_file_id", object->photoFileId);
    appendToJson(result, "description", object->description);
    // The last comma will be erased by parseInlineQueryResult().
    return result;
}


InlineQueryResultCachedSticker::Ptr TgTypeParser::parseJsonAndGetInlineQueryResultCachedSticker(const boost::property_tree::ptree& data) const {
    // NOTE: This function will be called by parseJsonAndGgetInlineQueryResult().
    auto result(make_shared<InlineQueryResultCachedSticker>());
    result->stickerFileId = data.get<string>("sticker_file_id");
    return result;
}

std::string TgTypeParser::parseInlineQueryResultCachedSticker(const InlineQueryResultCachedSticker::Ptr& object) const {
    if (!object){
        return "";
    }
    // This function will be called by parseInlineQueryResult(), so I don't add
    // curly brackets to the result string.
    string result;
    appendToJson(result, "sticker_file_id", object->stickerFileId);
    // The last comma will be erased by parseInlineQueryResult().
    return result;
}

InlineQueryResultCachedVideo::Ptr TgTypeParser::parseJsonAndGetInlineQueryResultCachedVideo(const boost::property_tree::ptree& data) const {
    // NOTE: This function will be called by parseJsonAndGgetInlineQueryResult().
    auto result(make_shared<InlineQueryResultCachedVideo>());
    result->videoFileId = data.get<string>("video_file_id");
    result->description = data.get<string>("description", "");
    return result;
}

std::string TgTypeParser::parseInlineQueryResultCachedVideo(const InlineQueryResultCachedVideo::Ptr& object) const {
    if (!object){
        return "";
    }
    // This function will be called by parseInlineQueryResult(), so I don't add
    // curly brackets to the result string.
    string result;
    appendToJson(result, "video_file_id", object->videoFileId);
    appendToJson(result, "description", object->description);
    // The last comma will be erased by parseInlineQueryResult().
    return result;
}


InlineQueryResultCachedVoice::Ptr TgTypeParser::parseJsonAndGetInlineQueryResultCachedVoice(const boost::property_tree::ptree& data) const {
    // NOTE: This function will be called by parseJsonAndGgetInlineQueryResult().
    auto result(make_shared<InlineQueryResultCachedVoice>());
    result->voiceFileId = data.get<string>("voice_file_id");
    return result;
}

std::string TgTypeParser::parseInlineQueryResultCachedVoice(const InlineQueryResultCachedVoice::Ptr& object) const {
    if (!object){
        return "";
    }
    // This function will be called by parseInlineQueryResult(), so I don't add
    // curly brackets to the result string.
    string result;
    appendToJson(result, "voice_file_id", object->voiceFileId);
    // The last comma will be erased by parseInlineQueryResult().
    return result;
}

InlineQueryResultArticle::Ptr TgTypeParser::parseJsonAndGetInlineQueryResultArticle(const boost::property_tree::ptree& data) const {
    // NOTE: This function will be called by parseJsonAndGgetInlineQueryResult().
    auto result(make_shared<InlineQueryResultArticle>());
    result->url = data.get<string>("url", "");
    result->hideUrl = data.get("hide_url", false);
    result->description = data.get<string>("description", "");
    result->thumbUrl = data.get<string>("thumb_url", "");
    result->thumbWidth = data.get("thumb_width", 0);
    result->thumbHeight = data.get("thumb_height", 0);
    return result;
}

std::string TgTypeParser::parseInlineQueryResultArticle(const InlineQueryResultArticle::Ptr& object) const {
    if (!object){
        return "";
    }
    // This function will be called by parseInlineQueryResult(), so I don't add
    // curly brackets to the result string.
    string result;
    appendToJson(result, "url", object->url);
    appendToJson(result, "hide_url", object->hideUrl);
    appendToJson(result, "description", object->description);
    appendToJson(result, "thumb_url", object->thumbUrl);
    appendToJson(result, "thumb_width", object->thumbWidth);
    appendToJson(result, "thumb_height", object->thumbHeight);
    // The last comma will be erased by parseInlineQueryResult().
    return result;
}

InlineQueryResultAudio::Ptr TgTypeParser::parseJsonAndGetInlineQueryResultAudio(const boost::property_tree::ptree& data) const {
    // NOTE: This function will be called by parseJsonAndGgetInlineQueryResult().
    auto result(make_shared<InlineQueryResultAudio>());
    result->audioUrl = data.get<string>("audio_url");
    result->performer = data.get<string>("performer", "");
    result->audioDuration = data.get<int32_t>("audio_duration", 0);
    return result;
}

std::string TgTypeParser::parseInlineQueryResultAudio(const InlineQueryResultAudio::Ptr& object) const {
    if (!object){
        return "";
    }
    // This function will be called by parseInlineQueryResult(), so I don't add
    // curly brackets to the result string.
    string result;
    appendToJson(result, "audio_url", object->audioUrl);
    appendToJson(result, "performer", object->performer);
    appendToJson(result, "audio_duration", object->audioDuration);
    // The last comma will be erased by parseInlineQueryResult().
    return result;
}


InlineQueryResultContact::Ptr TgTypeParser::parseJsonAndGetInlineQueryResultContact(const boost::property_tree::ptree& data) const {
    // NOTE: This function will be called by parseJsonAndGgetInlineQueryResult().
    auto result(make_shared<InlineQueryResultContact>());
    result->phoneNumber = data.get<string>("phone_number");
    result->firstName = data.get<string>("first_name");
    result->lastName = data.get<string>("last_name", "");
    result->vcard = data.get<string>("vcard", "");
    result->thumbUrl = data.get<string>("thumb_url", "");
    result->thumbWidth = data.get<int32_t>("thumb_width", 0);
    result->thumbHeight = data.get<int32_t>("thumb_height", 0);
    return result;
}

std::string TgTypeParser::parseInlineQueryResultContact(const InlineQueryResultContact::Ptr& object) const {
    if (!object){
        return "";
    }
    // This function will be called by parseInlineQueryResult(), so I don't add
    // curly brackets to the result string.
    string result;
    appendToJson(result, "phone_number", object->phoneNumber);
    appendToJson(result, "first_name", object->firstName);
    appendToJson(result, "last_name", object->lastName);
    appendToJson(result, "vcard", object->vcard);
    appendToJson(result, "thumb_url", object->thumbUrl);
    appendToJson(result, "thumb_width", object->thumbWidth);
    appendToJson(result, "thumb_height", object->thumbHeight);
    // The last comma will be erased by parseInlineQueryResult().
    return result;
}


InlineQueryResultGame::Ptr TgTypeParser::parseJsonAndGetInlineQueryResultGame(const boost::property_tree::ptree& data) const {
    // NOTE: This function will be called by parseJsonAndGgetInlineQueryResult().
    auto result(make_shared<InlineQueryResultGame>());
    result->gameShortName = data.get<string>("game_short_name");
    return result;
}

std::string TgTypeParser::parseInlineQueryResultGame(const InlineQueryResultGame::Ptr& object) const {
    if (!object){
        return "";
    }
    // This function will be called by parseInlineQueryResult(), so I don't add
    // curly brackets to the result string.
    string result;
    appendToJson(result, "game_short_name", object->gameShortName);
    // The last comma will be erased by parseInlineQueryResult().
    return result;
}

InlineQueryResultDocument::Ptr TgTypeParser::parseJsonAndGetInlineQueryResultDocument(const boost::property_tree::ptree& data) const {
    // NOTE: This function will be called by parseJsonAndGgetInlineQueryResult().
    auto result(make_shared<InlineQueryResultDocument>());
    result->documentUrl = data.get<string>("document_url");
    result->mimeType = data.get<string>("mime_type");
    result->description = data.get<string>("description", "");
    result->thumbUrl = data.get<string>("thumb_url", "");
    result->thumbWidth = data.get<int32_t>("thumb_width", 0);
    result->thumbHeight = data.get<int32_t>("thumb_height", 0);
    return result;
}

std::string TgTypeParser::parseInlineQueryResultDocument(const InlineQueryResultDocument::Ptr& object) const {
    if (!object){
        return "";
    }
    // This function will be called by parseInlineQueryResult(), so I don't add
    // curly brackets to the result string.
    string result;
    appendToJson(result, "document_url", object->documentUrl);
    appendToJson(result, "mime_type", object->mimeType);
    appendToJson(result, "description", object->description);
    appendToJson(result, "thumb_url", object->thumbUrl);
    appendToJson(result, "thumb_width", object->thumbWidth);
    appendToJson(result, "thumb_height", object->thumbHeight);
    // The last comma will be erased by parseInlineQueryResult().
    return result;
}

InlineQueryResultLocation::Ptr TgTypeParser::parseJsonAndGetInlineQueryResultLocation(const boost::property_tree::ptree& data) const {
    // NOTE: This function will be called by parseJsonAndGgetInlineQueryResult().
    auto result(make_shared<InlineQueryResultLocation>());
    result->latitude = data.get<float>("latitude");
    result->longitude = data.get<float>("longitude");
    result->thumbUrl = data.get<string>("thumb_url", "");
    result->thumbWidth = data.get<int32_t>("thumb_width", 0);
    result->thumbHeight = data.get<int32_t>("thumb_height", 0);
    return result;
}

std::string TgTypeParser::parseInlineQueryResultLocation(const InlineQueryResultLocation::Ptr& object) const {
    if (!object){
        return "";
    }
    // This function will be called by parseInlineQueryResult(), so I don't add
    // curly brackets to the result string.
    string result;
    appendToJson(result, "latitude", object->latitude);
    appendToJson(result, "longitude", object->longitude);
    appendToJson(result, "thumb_url", object->thumbUrl);
    appendToJson(result, "thumb_width", object->thumbWidth);
    appendToJson(result, "thumb_height", object->thumbHeight);
    // The last comma will be erased by parseInlineQueryResult().
    return result;
}


InlineQueryResultVenue::Ptr TgTypeParser::parseJsonAndGetInlineQueryResultVenue(const boost::property_tree::ptree& data) const {
    // NOTE: This function will be called by parseJsonAndGgetInlineQueryResult().
    auto result(make_shared<InlineQueryResultVenue>());
    result->latitude = data.get<float>("latitude");
    result->longitude = data.get<float>("longitude");
    result->address = data.get<string>("address");
    result->foursquareId = data.get<string>("foursquare_id", "");
    result->foursquareType = data.get<string>("foursquare_type", "");
    result->thumbUrl = data.get<string>("thumb_url", "");
    result->thumbWidth = data.get<int32_t>("thumb_width", 0);
    result->thumbHeight = data.get<int32_t>("thumb_height", 0);
    return result;
}

std::string TgTypeParser::parseInlineQueryResultVenue(const InlineQueryResultVenue::Ptr& object) const {
    if (!object){
        return "";
    }
    // This function will be called by parseInlineQueryResult(), so I don't add
    // curly brackets to the result string.
    string result;
    appendToJson(result, "latitude", object->latitude);
    appendToJson(result, "longitude", object->longitude);
    appendToJson(result, "address", object->address);
    appendToJson(result, "foursquare_id", object->foursquareId);
    appendToJson(result, "foursquare_type", object->foursquareType);
    appendToJson(result, "thumb_url", object->thumbUrl);
    appendToJson(result, "thumb_width", object->thumbWidth);
    appendToJson(result, "thumb_height", object->thumbHeight);
    // The last comma will be erased by parseInlineQueryResult().
    return result;
}

InlineQueryResultVoice::Ptr TgTypeParser::parseJsonAndGetInlineQueryResultVoice(const boost::property_tree::ptree& data) const {
    // NOTE: This function will be called by parseJsonAndGgetInlineQueryResult().
    auto result(make_shared<InlineQueryResultVoice>());
    result->voiceUrl = data.get<string>("voice_url");
    result->voiceDuration = data.get<int32_t>("voice_duration", 0);
    return result;
}

std::string TgTypeParser::parseInlineQueryResultVoice(const InlineQueryResultVoice::Ptr& object) const {
    if (!object){
        return "";
    }
    // This function will be called by parseInlineQueryResult(), so I don't add
    // curly brackets to the result string.
    string result;
    appendToJson(result, "voice_url", object->voiceUrl);
    appendToJson(result, "voice_duration", object->voiceDuration);
    // The last comma will be erased by parseInlineQueryResult().
    return result;
}

InlineQueryResultPhoto::Ptr TgTypeParser::parseJsonAndGetInlineQueryResultPhoto(const boost::property_tree::ptree& data) const {
    // NOTE: This function will be called by parseJsonAndGgetInlineQueryResult().
    auto result(make_shared<InlineQueryResultPhoto>());
    result->photoUrl = data.get<string>("photo_url", "");
    result->thumbUrl = data.get<string>("thumb_url");
    result->photoWidth = data.get("photo_width", 0);
    result->photoHeight = data.get("photo_height", 0);
    result->description = data.get<string>("description", "");
    return result;
}

std::string TgTypeParser::parseInlineQueryResultPhoto(const InlineQueryResultPhoto::Ptr& object) const{
    if (!object){
        return "";
    }
    // This function will be called by parseInlineQueryResult(), so I don't add
    // curly brackets to the result string.
    string result;
    appendToJson(result, "photo_url", object->photoUrl);
    appendToJson(result, "thumb_url", object->thumbUrl);
    appendToJson(result, "photo_width", object->photoWidth);
    appendToJson(result, "photo_height", object->photoHeight);
    appendToJson(result, "description", object->description);
    // The last comma will be erased by parseInlineQueryResult().
    return result;
}

InlineQueryResultGif::Ptr TgTypeParser::parseJsonAndGetInlineQueryResultGif(const boost::property_tree::ptree& data) const {
    // NOTE: This function will be called by parseJsonAndGgetInlineQueryResult().
    auto result(make_shared<InlineQueryResultGif>());
    result->gifUrl = data.get<string>("gif_url", "");
    result->gifWidth = data.get("gif_width", 0);
    result->gifHeight = data.get("gif_height", 0);
    result->gifDuration = data.get("gif_duration", 0);
    result->thumbUrl = data.get<string>("thumb_url");
    return result;
}
std::string TgTypeParser::parseInlineQueryResultGif(const InlineQueryResultGif::Ptr& object) const {
    if (!object){
        return "";
    }
    // This function will be called by parseInlineQueryResult(), so I don't add
    // curly brackets to the result string.
    string result;
    appendToJson(result, "gif_url", object->gifUrl);
    appendToJson(result, "gif_width", object->gifWidth);
    appendToJson(result, "gif_height", object->gifHeight);
    appendToJson(result, "gif_duration", object->gifDuration);
    appendToJson(result, "thumb_url", object->thumbUrl);
    // The last comma will be erased by parseInlineQueryResult().
    return result;
}

InlineQueryResultMpeg4Gif::Ptr TgTypeParser::parseJsonAndGetInlineQueryResultMpeg4Gif(const boost::property_tree::ptree& data) const {
    // NOTE: This function will be called by parseJsonAndGgetInlineQueryResult().
    auto result(make_shared<InlineQueryResultMpeg4Gif>());
    result->mpeg4Url = data.get<string>("mpeg4_url");
    result->mpeg4Width = data.get("mpeg4_width", 0);
    result->mpeg4Height = data.get("mpeg4_height", 0);
    result->mpeg4Duration = data.get("mpeg4_duration", 0);
    result->thumbUrl = data.get<string>("thumb_url");
    return result;
}

std::string TgTypeParser::parseInlineQueryResultMpeg4Gif(const InlineQueryResultMpeg4Gif::Ptr& object) const {
    if (!object){
        return "";
    }
    // This function will be called by parseInlineQueryResult(), so I don't add
    // curly brackets to the result string.
    string result;
    appendToJson(result, "mpeg4_url", object->mpeg4Url);
    appendToJson(result, "mpeg4_width", object->mpeg4Width);
    appendToJson(result, "mpeg4_height", object->mpeg4Height);
    appendToJson(result, "mpeg4_duration", object->mpeg4Duration);
    appendToJson(result, "thumb_url", object->thumbUrl);
    // The last comma will be erased by parseInlineQueryResult().
    return result;
}

InlineQueryResultVideo::Ptr TgTypeParser::parseJsonAndGetInlineQueryResultVideo(const boost::property_tree::ptree& data) const {
    // NOTE: This function will be called by parseJsonAndGgetInlineQueryResult().
    auto result(make_shared<InlineQueryResultVideo>());
    result->videoUrl = data.get<string>("video_url");
    result->mimeType = data.get<string>("mime_type");
    result->thumbUrl = data.get<string>("thumb_url");
    result->videoWidth = data.get("video_width", 0);
    result->videoHeight = data.get("video_height", 0);
    result->videoDuration = data.get("video_duration", 0);
    result->description = data.get<string>("description", "");
    return result;
}

std::string TgTypeParser::parseInlineQueryResultVideo(const InlineQueryResultVideo::Ptr& object) const {
    if (!object){
        return "";
    }
    // This function will be called by parseInlineQueryResult(), so I don't add
    // curly brackets to the result string.
    string result;
    appendToJson(result, "video_url", object->videoUrl);
    appendToJson(result, "mime_type", object->mimeType);
    appendToJson(result, "thumb_url", object->thumbUrl);
    appendToJson(result, "video_width", object->videoWidth);
    appendToJson(result, "video_height", object->videoHeight);
    appendToJson(result, "video_duration", object->videoDuration);
    appendToJson(result, "description", object->description);
    // The last comma will be erased by parseInlineQueryResult().
    return result;
}

ChosenInlineResult::Ptr TgTypeParser::parseJsonAndGetChosenInlineResult(const boost::property_tree::ptree& data) const {
    auto result(make_shared<ChosenInlineResult>());
    result->resultId = data.get<string>("result_id");
    result->from = tryParseJson<User>(&TgTypeParser::parseJsonAndGetUser, data, "from");
    result->location = tryParseJson<Location>(&TgTypeParser::parseJsonAndGetLocation, data, "location");
    result->inlineMessageId = data.get<string>("inline_message_id", "");
    result->query = data.get<string>("query");
    return result;
}

std::string TgTypeParser::parseChosenInlineResult(const ChosenInlineResult::Ptr& object) const {
    if (!object){
        return "";
    }

    string result;
    result += '{';
    appendToJson(result, "result_id", object->resultId);
    appendToJson(result, "from", parseUser(object->from));
    appendToJson(result, "query", object->query);
    removeLastComma(result);
    result += '}';
    return result;
}

CallbackQuery::Ptr TgTypeParser::parseJsonAndGetCallbackQuery(const boost::property_tree::ptree& data) const {
    auto result(make_shared<CallbackQuery>());
    result->id = data.get<string>("id");
    result->from = tryParseJson<User>(&TgTypeParser::parseJsonAndGetUser, data, "from");
    result->message = tryParseJson<Message>(&TgTypeParser::parseJsonAndGetMessage, data, "message");
    result->inlineMessageId = data.get<string>("inline_message_id", "");
    result->chatInstance = data.get<string>("chat_instance");
    result->gameShortName = data.get<string>("game_short_name", "");
    result->data = data.get<string>("data", "");
    return result;
}

std::string TgTypeParser::parseCallbackQuery(const CallbackQuery::Ptr& object) const {
    if (!object){
        return "";
    }

    string result;
    result += '{';
    appendToJson(result, "id", object->id);
    appendToJson(result, "from", parseUser(object->from));
    appendToJson(result, "message", parseMessage(object->message));
    appendToJson(result, "inline_message_id", object->inlineMessageId);
    appendToJson(result, "chat_instance", object->chatInstance);
    appendToJson(result, "game_short_name", object->gameShortName);
    appendToJson(result, "data", object->data);
    removeLastComma(result);
    result += '}';
    return result;
}

InlineKeyboardMarkup::Ptr TgTypeParser::parseJsonAndGetInlineKeyboardMarkup(const boost::property_tree::ptree& data) const {
    auto result(make_shared<InlineKeyboardMarkup>());
    for (const auto& item : data.find("inline_keyboard")->second){
        result->inlineKeyboard.push_back(parseJsonAndGetArray<InlineKeyboardButton>(&TgTypeParser::parseJsonAndGetInlineKeyboardButton, item.second));
    }
    return result;
}

std::string TgTypeParser::parseInlineKeyboardMarkup(const InlineKeyboardMarkup::Ptr& object) const {
    if (!object){
        return "";
    }
    string result;
    result += '{';
    result += R"("inline_keyboard":[)";
    for (const auto& item : object->inlineKeyboard){
        result += '[';
        for (const auto& innerItem : item){
            result += parseInlineKeyboardButton(innerItem);
            result += ',';
        }
        removeLastComma(result);
        result += "],";
    }
    if (!object->inlineKeyboard.empty())
        removeLastComma(result);
    result += "]}";
    return result;
}

InlineKeyboardButton::Ptr TgTypeParser::parseJsonAndGetInlineKeyboardButton(const boost::property_tree::ptree& data) const {
    auto result(make_shared<InlineKeyboardButton>());
    result->text = data.get<string>("text");
    result->url = data.get<string>("url", "");
    result->loginUrl = make_shared<LoginUrl>();
    result->callbackData = data.get<string>("callback_data", "");
    result->switchInlineQuery = data.get<string>("switch_inline_query", "");
    result->switchInlineQueryCurrentChat = data.get<string>("switch_inline_query_current_chat", "");
    result->callbackGame = make_shared<CallbackGame>();
    result->pay = data.get<bool>("pay", false);
    return result;
}
std::string TgTypeParser::parseInlineKeyboardButton(const InlineKeyboardButton::Ptr& object) const {
    if (!object){
        return "";
    }
    string result;
    result += '{';
    if(object->pay)
        appendToJson(result, "pay", object->pay);
    appendToJson(result, "text", object->text);
    appendToJson(result, "url", object->url);
    appendToJson(result, "callback_data", object->callbackData);
    appendToJson(result, "switch_inline_query", object->switchInlineQuery);
    appendToJson(result, "switch_inline_query_current_chat", object->switchInlineQueryCurrentChat);
    removeLastComma(result);
    result += '}';
    return result;
}

WebhookInfo::Ptr TgTypeParser::parseJsonAndGetWebhookInfo(const boost::property_tree::ptree& data) const {
    auto result(make_shared<WebhookInfo>());
    result->url = data.get<string>("url");
    result->hasCustomCertificate = data.get<bool>("has_custom_certificate");
    result->pendingUpdateCount = data.get<int32_t>("pending_update_count");
    result->lastErrorDate = data.get<int32_t>("last_error_date", 0);
    result->lastErrorMessage = data.get<string>("last_error_message", "");
    result->maxConnections = data.get<int32_t>("max_connections", 0);
    result->allowedUpdates = parseJsonAndGetArray<std::string>(
        [](const boost::property_tree::ptree& innerData)->std::string {
            return innerData.get<std::string>("");
        }
        , data, "allowed_updates");
    return result;
}

std::string TgTypeParser::parseWebhookInfo(const WebhookInfo::Ptr& object) const {
    if (!object) {
        return "";
    }
    string result;
    result += '{';
    appendToJson(result, "url", object->url);
    appendToJson(result, "has_custom_certificate", object->hasCustomCertificate);
    appendToJson(result, "pending_update_count", object->pendingUpdateCount);
    appendToJson(result, "last_error_date", object->lastErrorDate);
    appendToJson(result, "last_error_message", object->lastErrorMessage);
    appendToJson(result, "max_connections", object->maxConnections);
    appendToJson(result, "allowed_updates",
        parseArray<std::string>([](const std::string &s)->std::string {
            return s;
        }
        , object->allowedUpdates));
    removeLastComma(result);
    result += '}';
    return result;
}

InputMessageContent::Ptr TgTypeParser::parseJsonAndGetInputMessageContent(const boost::property_tree::ptree& data) const {
    InputMessageContent::Ptr result;
    // define InputMessageContent type

    string tMessageText = data.get<string>("message_text", "");
    float tLatitude = data.get<float>("latitude", 1000); // latitude belong (-90,90)
    string tTitle = data.get<string>("title", "");
    string tPnoneNumber = data.get<string>("phone_number", "");

    if (!tMessageText.empty()) {
        result = static_pointer_cast<InputMessageContent>(parseJsonAndGetInputTextMessageContent(data));
    } else if (!tTitle.empty()) {
        result = static_pointer_cast<InputMessageContent>(parseJsonAndGetInputVenueMessageContent(data));
    } else if (tLatitude != 1000) {
        result = static_pointer_cast<InputMessageContent>(parseJsonAndGetInputLocationMessageContent(data));
    } else if (!tPnoneNumber.empty()) {
        result = static_pointer_cast<InputMessageContent>(parseJsonAndGetInputContactMessageContent(data));
    }

    return result;
}

std::string TgTypeParser::parseInputMessageContent(const InputMessageContent::Ptr& object) const {
    if (!object){
        return "";
    }

    string result;
    result += '{';

    if (object->type == std::string("InputTextMessageContent")) {
        result += parseInputTextMessageContent(static_pointer_cast<InputTextMessageContent>(object));
    }
    else if (object->type == std::string("InputLocationMessageContent")) {
        result += parseInputLocationMessageContent(static_pointer_cast<InputLocationMessageContent>(object));
    }
    else if (object->type == std::string("InputVenueMessageContent")) {
        result += parseInputVenueMessageContent(static_pointer_cast<InputVenueMessageContent>(object));
    }
    else if (object->type == std::string("InputContactMessageContent")) {
        result += parseInputContactMessageContent(static_pointer_cast<InputContactMessageContent>(object));
    }

    removeLastComma(result);
    result += '}';
    return result;
}

InputTextMessageContent::Ptr TgTypeParser::parseJsonAndGetInputTextMessageContent(const boost::property_tree::ptree& data) const {
    // NOTE: This function will be called by parseJsonAndGetInputMessageContent().
    auto result(make_shared<InputTextMessageContent>());
    result->messageText = data.get<string>("message_text");
    result->parseMode = data.get<string>("parse_mode", "");
    result->disableWebPagePreview = data.get<bool>("disable_web_page_preview", false);
    return result;
}

std::string TgTypeParser::parseInputTextMessageContent(const InputTextMessageContent::Ptr& object) const {
    if (!object){
        return "";
    }
    // This function will be called by parseInputMessageContent()
    string result;
    appendToJson(result, "message_text", object->messageText);
    appendToJson(result, "parse_mode", object->parseMode);
    appendToJson(result, "disable_web_page_preview", object->disableWebPagePreview);
    // The last comma will be erased by parseInputMessageContent().
    return result;
}

InputLocationMessageContent::Ptr TgTypeParser::parseJsonAndGetInputLocationMessageContent(const boost::property_tree::ptree& data) const {
    // NOTE: This function will be called by parseJsonAndGetInputMessageContent().
    auto result(make_shared<InputLocationMessageContent>());
    result->latitude = data.get<float>("latitude");
    result->longitude = data.get<float>("longitude");
    return result;
}

std::string TgTypeParser::parseInputLocationMessageContent(const InputLocationMessageContent::Ptr& object) const {
    if (!object){
        return "";
    }
    // This function will be called by parseInputMessageContent()
    string result;
    appendToJson(result, "latitude", object->latitude);
    appendToJson(result, "longitude", object->longitude);
    // The last comma will be erased by parseInputMessageContent().
    return result;
}

InputVenueMessageContent::Ptr TgTypeParser::parseJsonAndGetInputVenueMessageContent(const boost::property_tree::ptree& data) const {
    // NOTE: This function will be called by parseJsonAndGetInputMessageContent().
    auto result(make_shared<InputVenueMessageContent>());
    result->latitude = data.get<float>("latitude");
    result->longitude = data.get<float>("longitude");
    result->title = data.get<string>("title");
    result->address = data.get<string>("address");
    result->foursquareId = data.get<string>("foursquare_id", "");
    result->foursquareType = data.get<string>("foursquare_type", "");
    return result;
}

std::string TgTypeParser::parseInputVenueMessageContent(const InputVenueMessageContent::Ptr& object) const {
    if (!object){
        return "";
    }
    // This function will be called by parseInputMessageContent()
    string result;
    appendToJson(result, "latitude", object->latitude);
    appendToJson(result, "longitude", object->longitude);
    appendToJson(result, "title", object->title);
    appendToJson(result, "address", object->address);
    appendToJson(result, "foursquare_id", object->foursquareId);
    // The last comma will be erased by parseInputMessageContent().
    return result;
}

InputContactMessageContent::Ptr TgTypeParser::parseJsonAndGetInputContactMessageContent(const boost::property_tree::ptree& data) const {
    // NOTE: This function will be called by parseJsonAndGetInputMessageContent().
    auto result(make_shared<InputContactMessageContent>());
    result->phoneNumber = data.get<string>("phone_number");
    result->firstName = data.get<string>("first_name");
    result->lastName = data.get<string>("last_name", "");
    result->vcard = data.get<string>("vcard", "");
    return result;
}

std::string TgTypeParser::parseInputContactMessageContent(const InputContactMessageContent::Ptr& object) const {
    if (!object){
        return "";
    }
    // This function will be called by parseInputMessageContent()
    string result;
    appendToJson(result, "phone_number", object->phoneNumber);
    appendToJson(result, "first_name", object->firstName);
    appendToJson(result, "last_name", object->lastName);
    appendToJson(result, "vcard", object->vcard);
    // The last comma will be erased by parseInputMessageContent().
    return result;
}

Invoice::Ptr TgTypeParser::parseJsonAndGetInvoice(const boost::property_tree::ptree& data) const {
    auto result(make_shared<Invoice>());
    result->title = data.get<string>("title");
    result->description = data.get<string>("description");
    result->startParameter = data.get<string>("start_parameter");
    result->currency = data.get<string>("currency");
    result->totalAmount = data.get<int32_t>("total_amount");
    return result;
}

std::string TgTypeParser::parseInvoice(const Invoice::Ptr& object) const {
    if (!object) {
        return "";
    }
    string result;
    result += '{';
    appendToJson(result, "title", object->title);
    appendToJson(result, "description", object->description);
    appendToJson(result, "start_parameter", object->startParameter);
    appendToJson(result, "currency", object->currency);
    appendToJson(result, "total_amount", object->totalAmount);
    removeLastComma(result);
    result += '}';
    return result;
}

LabeledPrice::Ptr TgTypeParser::parseJsonAndGetLabeledPrice(const boost::property_tree::ptree& data) const {
    auto result(make_shared<LabeledPrice>());
    result->label  = data.get<string>("label");
    result->amount = data.get<int32_t>("amount");
    return result;
}

string TgTypeParser::parseLabeledPrice(const LabeledPrice::Ptr& object) const {
    std::string result;
    result += '{';
    appendToJson(result, "label", object->label);
    appendToJson(result, "amount", object->amount);
    removeLastComma(result);
    result += '}';
    return result;
}

BotCommand::Ptr TgTypeParser::parseJsonAndGetBotCommand(const boost::property_tree::ptree& data) const {
    auto result(make_shared<BotCommand>());
    result->command = data.get("command", "");
    result->description = data.get("description","");
    return result;
}

string TgTypeParser::parseBotCommand(const BotCommand::Ptr& object) const {
    std::string result;
    result += '{';
    appendToJson(result, "command", object->command);
    appendToJson(result, "description", object->description);
    removeLastComma(result);
    result += '}';
    return result;
}

OrderInfo::Ptr TgTypeParser::parseJsonAndGetOrderInfo(const boost::property_tree::ptree& data) const {
    auto result(make_shared<OrderInfo>());
    result->name = data.get<string>("name", "");
    result->phoneNumber = data.get<string>("phone_number", "");
    result->email = data.get<string>("email", "");
    result->shippingAddress = tryParseJson(&TgTypeParser::parseJsonAndGetShippingAddress, data, "shipping_address");
    return result;
}

string TgTypeParser::parseOrderInfo(const OrderInfo::Ptr& object) const {
    if (!object) {
        return "";
    }
    std::string result;
    result += '{';
    if (!object->name.empty()) {
        appendToJson(result, "name", object->name);
    }
    if (!object->phoneNumber.empty()) {
        appendToJson(result, "phone_number", object->phoneNumber);
    }
    if (!object->email.empty()) {
        appendToJson(result, "email", object->email);
    }
    if (!object->shippingAddress) {
        result += R"("shipping_address":)";
        result += parseShippingAddress(object->shippingAddress);
        result += ",";
    }
    removeLastComma(result);
    result += '}';
    return result;
}

PreCheckoutQuery::Ptr TgTypeParser::parseJsonAndGetPreCheckoutQuery(const boost::property_tree::ptree& data) const {
    auto result(make_shared<PreCheckoutQuery>());
    result->id = data.get<string>("id");
    result->from = tryParseJson(&TgTypeParser::parseJsonAndGetUser, data, "user");
    result->currency = data.get<string>("currency");
    result->totalAmount = data.get<int32_t>("total_amount");
    return result;
}

string TgTypeParser::parsePreCheckoutQuery(const PreCheckoutQuery::Ptr& object) const {
    std::string result;
    result += '{';
    appendToJson(result, "id", object->id);
    result += R"("user":)";
    result += parseUser(object->from);
    result += ",";
    appendToJson(result, "currency", object->currency);
    appendToJson(result, "total_amount", object->totalAmount);
    removeLastComma(result);
    result += '}';
    return result;
}

ShippingAddress::Ptr TgTypeParser::parseJsonAndGetShippingAddress(const boost::property_tree::ptree& data) const {
    ShippingAddress::Ptr result;
    result->countryCode = data.get<string>("country_code");
    result->state = data.get<string>("state", "");
    result->city = data.get<string>("city");
    result->streetLine1 = data.get<string>("street_line1");
    result->streetLine2 = data.get<string>("street_line2");
    result->postCode = data.get<string>("post_code");
    return result;
}

string TgTypeParser::parseShippingAddress(const ShippingAddress::Ptr& object) const {
    std::string result;
    result += '{';
    appendToJson(result, "country_code", object->countryCode);
    if (!object->state.empty()) {
        appendToJson(result, "state", object->state);
    }
    appendToJson(result, "city", object->city);
    appendToJson(result, "street_line1", object->streetLine1);
    appendToJson(result, "street_line2", object->streetLine2);
    appendToJson(result, "post_code", object->postCode);
    removeLastComma(result);
    result += '}';
    return result;
}

ShippingOption::Ptr TgTypeParser::parseJsonAndGetShippingOption(const boost::property_tree::ptree& data) const {
    auto result(make_shared<ShippingOption>());
    result->id = data.get<string>("id");
    result->title = data.get<string>("title");
    result->prices = parseJsonAndGetArray<LabeledPrice>(&TgTypeParser::parseJsonAndGetLabeledPrice, data, "prices");
    return result;
}

string TgTypeParser::parseShippingOption(const ShippingOption::Ptr& object) const {
    std::string result;
    result += '{';
    appendToJson(result, "id", object->id);
    appendToJson(result, "title", object->title);
    removeLastComma(result);
    result += R"("prices":)";
    result += parseArray(&TgTypeParser::parseLabeledPrice, object->prices);
    result += '}';
    return result;
}

ShippingQuery::Ptr TgTypeParser::parseJsonAndGetShippingQuery(const boost::property_tree::ptree& data) const {
    auto result(make_shared<ShippingQuery>());
    result->id = data.get<string>("id");
    result->from = tryParseJson(&TgTypeParser::parseJsonAndGetUser, data, "from");
    result->invoicePayload = data.get<string>("invoice_payload");
    result->shippingAddress = tryParseJson(&TgTypeParser::parseJsonAndGetShippingAddress, data, "shipping_address");
    return result;
}

string TgTypeParser::parseShippingQuery(const ShippingQuery::Ptr& object) const {
    string result;
    result += '{';
    appendToJson(result, "id", object->id);
    result += R"("from":)";
    result += parseUser(object->from);
    result += ",";
    appendToJson(result, "invoice_payload", object->invoicePayload);
    result += R"("shipping_address":)";
    result += parseShippingAddress(object->shippingAddress);
    result += ",";
    removeLastComma(result);
    result += '}';
    return result;
}

SuccessfulPayment::Ptr TgTypeParser::parseJsonAndGetSuccessfulPayment(const boost::property_tree::ptree& data) const {
    auto result(make_shared<SuccessfulPayment>());
    result->currency = data.get<string>("currency");
    result->totalAmount = data.get<int32_t>("total_amount");
    result->invoicePayload = data.get<string>("invoice_payload");
    result->shippingOptionId = data.get<string>("shipping_option_id");
    result->orderInfo = tryParseJson(&TgTypeParser::parseJsonAndGetOrderInfo, data, "order_info");
    return result;
}

std::string TgTypeParser::parseSuccessfulPayment(const SuccessfulPayment::Ptr& object) const {
    string result;
    result += '{';
    appendToJson(result, "currency", object->currency);
    appendToJson(result, "total_amount", object->totalAmount);
    appendToJson(result, "invoice_payload", object->invoicePayload);
    appendToJson(result, "shipping_option_id", object->shippingOptionId);
    result += R"("order_info":)";
    result += parseOrderInfo(object->orderInfo);
    result += ",";
    removeLastComma(result);
    result += '}';
    return result;
}


void TgTypeParser::appendToJson(string& json, const string& varName, const string& value) const {
    if (value.empty()) {
        return;
    }
    json += '"';
    json += varName;
    json += R"(":)";
    if (value.front() != '{') {
        json += '"';
    }
    json += value;
    if (value.back() != '}') {
        json += '"';
    }
    json += ',';
}
}
