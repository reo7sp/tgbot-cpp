/*
 * Copyright (c) 2015 Oleg Morozenkov
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software", "to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include "tgbot/TgTypeParser.h"

using namespace std;
using namespace boost::property_tree;

namespace TgBot {

TgTypeParser& TgTypeParser::getInstance() {
	static TgTypeParser result;
	return result;
}

Chat::Ptr TgTypeParser::parseJsonAndGetChat(const ptree& data) const {
	Chat::Ptr result(new Chat);
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
	result->firstName = data.get<string>("first_name", "");
	result->lastName = data.get("last_name", "");

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
	result.erase(result.length() - 1);
	result += '}';
	return result;
}

User::Ptr TgTypeParser::parseJsonAndGetUser(const ptree& data) const {
	User::Ptr result(new User);
	result->id = data.get<int32_t>("id");
	result->firstName = data.get<string>("first_name");
	result->lastName = data.get("last_name", "");
	result->username = data.get("username", "");
	return result;
}

string TgTypeParser::parseUser(const User::Ptr& object) const {
	if (!object) {
		return "";
	}
	string result;
	result += '{';
	appendToJson(result, "id", object->id);
	appendToJson(result, "first_name", object->firstName);
	appendToJson(result, "last_name", object->lastName);
	appendToJson(result, "username", object->username);
	result.erase(result.length() - 1);
	result += '}';
	return result;
}

MessageEntity::Ptr TgTypeParser::parseJsonAndGetEntity(const ptree& data) const{
	MessageEntity::Ptr result(new MessageEntity);
	result->type=data.get<string>("type");
	result->offset=data.get<int32_t>("offset");
	result->length=data.get<int32_t>("length");
	result->url=data.get<string>("url", "");
	return result;
}	

Message::Ptr TgTypeParser::parseJsonAndGetMessage(const ptree& data) const {
	Message::Ptr result(new Message);
	result->messageId = data.get<int32_t>("message_id");
	result->from = tryParseJson<User>(&TgTypeParser::parseJsonAndGetUser, data, "from");
	result->date = data.get<int32_t>("date");
	result->chat = parseJsonAndGetChat(data.find("chat")->second);
	result->forwardFrom = tryParseJson<User>(&TgTypeParser::parseJsonAndGetUser, data, "forward_from");
	result->forwardDate = data.get("forward_date", 0);
	result->replyToMessage = tryParseJson<Message>(&TgTypeParser::parseJsonAndGetMessage, data, "reply_to_message");
	result->text = data.get("text", "");
	result->entities = parseJsonAndGetArray<MessageEntity>(&TgTypeParser::parseJsonAndGetEntity, data, "entities");
	result->audio = tryParseJson<Audio>(&TgTypeParser::parseJsonAndGetAudio, data, "audio");
	result->document = tryParseJson<Document>(&TgTypeParser::parseJsonAndGetDocument, data, "document");
	result->photo = parseJsonAndGetArray<PhotoSize>(&TgTypeParser::parseJsonAndGetPhotoSize, data, "photo");
	result->sticker = tryParseJson<Sticker>(&TgTypeParser::parseJsonAndGetSticker, data, "sticker");
	result->video = tryParseJson<Video>(&TgTypeParser::parseJsonAndGetVideo, data, "video");
	result->contact = tryParseJson<Contact>(&TgTypeParser::parseJsonAndGetContact, data, "contact");
	result->location = tryParseJson<Location>(&TgTypeParser::parseJsonAndGetLocation, data, "location");
	result->newChatMember = tryParseJson<User>(&TgTypeParser::parseJsonAndGetUser, data, "new_chat_participant");
	result->leftChatMember = tryParseJson<User>(&TgTypeParser::parseJsonAndGetUser, data, "left_chat_participant");
	result->newChatTitle = data.get("new_chat_title", "");
	result->newChatPhoto = parseJsonAndGetArray<PhotoSize>(&TgTypeParser::parseJsonAndGetPhotoSize, data, "new_chat_photo");
	result->deleteChatPhoto = data.get("delete_chat_photo", false);
	result->groupChatCreated = data.get("group_chat_created", false);
	result->caption = data.get("caption", false);
	result->supergroupChatCreated = data.get("supergroup_chat_created", false);
	result->channelChatCreated = data.get("channel_chat_created", false);
	result->migrateToChatId = data.get<int64_t>("migrate_to_chat_id", 0);
	result->migrateFromChatId = data.get<int64_t>("migrate_from_chat_id", 0);
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
	appendToJson(result, "forward_date", object->forwardDate);
	appendToJson(result, "reply_to_message", parseMessage(object->replyToMessage));
	appendToJson(result, "text", object->text);
	appendToJson(result, "audio", parseAudio(object->audio));
	appendToJson(result, "document", parseDocument(object->document));
	appendToJson(result, "photo", parseArray(&TgTypeParser::parsePhotoSize, object->photo));
	appendToJson(result, "sticker", parseSticker(object->sticker));
	appendToJson(result, "video", parseVideo(object->video));
	appendToJson(result, "contact", parseContact(object->contact));
	appendToJson(result, "location", parseLocation(object->location));
	appendToJson(result, "new_chat_member", parseUser(object->newChatMember));
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
	result.erase(result.length() - 1);
	result += '}';
	return result;
}

PhotoSize::Ptr TgTypeParser::parseJsonAndGetPhotoSize(const ptree& data) const {
	PhotoSize::Ptr result(new PhotoSize);
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
	result.erase(result.length() - 1);
	result += '}';
	return result;
}

Audio::Ptr TgTypeParser::parseJsonAndGetAudio(const ptree& data) const {
	Audio::Ptr result(new Audio);
	result->fileId = data.get<string>("file_id");
	result->duration = data.get<int32_t>("duration");
	result->mimeType = data.get("mime_type", "");
	result->fileSize = data.get("file_size", 0);
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
	result.erase(result.length() - 1);
	result += '}';
	return result;
}

Document::Ptr TgTypeParser::parseJsonAndGetDocument(const ptree& data) const {
	Document::Ptr result(new Document);
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
	result.erase(result.length() - 1);
	result += '}';
	return result;
}

Sticker::Ptr TgTypeParser::parseJsonAndGetSticker(const ptree& data) const {
	Sticker::Ptr result(new Sticker);
	result->fileId = data.get<string>("file_id");
	result->width = data.get<int32_t>("width");
	result->height = data.get<int32_t>("height");
	result->thumb = tryParseJson<PhotoSize>(&TgTypeParser::parseJsonAndGetPhotoSize, data, "thumb");
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
	appendToJson(result, "thumb", parsePhotoSize(object->thumb));
	appendToJson(result, "file_size", object->fileSize);
	result.erase(result.length() - 1);
	result += '}';
	return result;
}

Video::Ptr TgTypeParser::parseJsonAndGetVideo(const ptree& data) const {
	Video::Ptr result(new Video);
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
	result.erase(result.length() - 1);
	result += '}';
	return result;
}

Contact::Ptr TgTypeParser::parseJsonAndGetContact(const ptree& data) const {
	Contact::Ptr result(new Contact);
	result->phoneNumber = data.get<string>("phone_number");
	result->firstName = data.get<string>("first_name");
	result->lastName = data.get("last_name", "");
	result->userId = data.get("user_id", "");
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
	result.erase(result.length() - 1);
	result += '}';
	return result;
}

Location::Ptr TgTypeParser::parseJsonAndGetLocation(const ptree& data) const {
	Location::Ptr result(new Location);
	result->longitude = data.get<float>("longitude");
	result->latitude = data.get<float>("latitude");
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
	result.erase(result.length() - 1);
	result += '}';
	return result;
}

Update::Ptr TgTypeParser::parseJsonAndGetUpdate(const ptree& data) const {
	Update::Ptr result(new Update);
	result->updateId = data.get<int32_t>("update_id");
	result->message = tryParseJson<Message>(&TgTypeParser::parseJsonAndGetMessage, data, "message");
	result->inlineQuery = tryParseJson<InlineQuery>(&TgTypeParser::parseJsonAndGetInlineQuery, data, "inline_query");
	result->chosenInlineResult = tryParseJson<ChosenInlineResult>(&TgTypeParser::parseJsonAndGetChosenInlineResult, data, "chosen_inline_result");
	result->callbackQuery = tryParseJson<CallbackQuery>(&TgTypeParser::parseJsonAndGetCallbackQuery, data, "callback_query");
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
	appendToJson(result, "inline_query", parseInlineQuery(object->inlineQuery));
	appendToJson(result, "chosen_inline_result", parseChosenInlineResult(object->chosenInlineResult));
	appendToJson(result, "callback_query", parseCallbackQuery(object->callbackQuery));
	result.erase(result.length() - 1);
	result += '}';
	return result;
}

UserProfilePhotos::Ptr TgTypeParser::parseJsonAndGetUserProfilePhotos(const ptree& data) const {
	UserProfilePhotos::Ptr result(new UserProfilePhotos);
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
	result.erase(result.length() - 1);
	result += '}';
	return result;
}

ReplyKeyboardMarkup::Ptr TgTypeParser::parseJsonAndGetReplyKeyboardMarkup(const boost::property_tree::ptree& data) const {
	ReplyKeyboardMarkup::Ptr result(new ReplyKeyboardMarkup);
	for (const pair<const string, ptree>& item : data.find("keyboard")->second) {
		vector<string> array;
		for (const pair<const string, ptree>& innerItem : item.second) {
			array.push_back(innerItem.second.data());
		}
		result->keyboard.push_back(array);
	}
	result->resizeKeyboard = data.get<bool>("resize_keyboard");
	result->oneTimeKeyboard = data.get<bool>("one_time_keyboard");
	result->selective = data.get<bool>("selective");
	return result;
}

std::string TgTypeParser::parseReplyKeyboardMarkup(const ReplyKeyboardMarkup::Ptr& object) const {
	if (!object) {
		return "";
	}
	string result;
	result += '{';
	result += "\"keyboard\":[";
	for (vector<string>& item : object->keyboard) {
		result += '[';
		for (string& innerItem : item) {
			result += '"';
			result += innerItem;
			result += "\",";
		}
		result.erase(result.length() - 1);
		result += "],";
	}
	result.erase(result.length() - 1);
	result += "],";
	appendToJson(result, "resize_keyboard", object->resizeKeyboard);
	appendToJson(result, "one_time_keyboard", object->oneTimeKeyboard);
	appendToJson(result, "selective", object->selective);
	result.erase(result.length() - 1);
	result += '}';
	return result;
}

ReplyKeyboardHide::Ptr TgTypeParser::parseJsonAndGetReplyKeyboardHide(const boost::property_tree::ptree& data) const {
	ReplyKeyboardHide::Ptr result(new ReplyKeyboardHide);
	result->selective = data.get<bool>("selective");
	return result;
}

std::string TgTypeParser::parseReplyKeyboardHide(const ReplyKeyboardHide::Ptr& object) const {
	if (!object) {
		return "";
	}
	string result;
	result += '{';
	appendToJson(result, "hide_keyboard", object->hideKeyboard);
	appendToJson(result, "selective", object->selective);
	result.erase(result.length() - 1);
	result += '}';
	return result;
}

ForceReply::Ptr TgTypeParser::parseJsonAndGetForceReply(const boost::property_tree::ptree& data) const {
	ForceReply::Ptr result(new ForceReply);
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
	result.erase(result.length() - 1);
	result += '}';
	return result;
}

GenericReply::Ptr TgTypeParser::parseJsonAndGetGenericReply(const boost::property_tree::ptree& data) const {
	if (data.find("force_reply") != data.not_found()) {
		return static_pointer_cast<GenericReply>(parseJsonAndGetForceReply(data));
	} else if (data.find("hide_keyboard") != data.not_found()) {
		return static_pointer_cast<GenericReply>(parseJsonAndGetReplyKeyboardHide(data));
	} else if (data.find("keyboard") != data.not_found()) {
		return static_pointer_cast<GenericReply>(parseJsonAndGetReplyKeyboardMarkup(data));
	} else if (data.find("inline_keyboard") != data.not_found()) {
		return static_pointer_cast<GenericReply>(parseJsonAndGetInlineKeyboardMarkup(data));
	}
}

std::string TgTypeParser::parseGenericReply(const GenericReply::Ptr& object) const {
	if (!object) {
		return "";
	}
	if (dynamic_pointer_cast<ForceReply>(object) != nullptr) {
		return parseForceReply(static_pointer_cast<ForceReply>(object));
	} else if (dynamic_pointer_cast<ReplyKeyboardHide>(object) != nullptr) {
		return parseReplyKeyboardHide(static_pointer_cast<ReplyKeyboardHide>(object));
	} else if (dynamic_pointer_cast<ReplyKeyboardMarkup>(object) != nullptr){
		return parseReplyKeyboardMarkup(static_pointer_cast<ReplyKeyboardMarkup>(object));
	} else if (dynamic_pointer_cast<InlineKeyboardMarkup>(object) != nullptr){
		return parseInlineKeyboardMarkup(static_pointer_cast<InlineKeyboardMarkup>(object));
	}
}

InlineQuery::Ptr TgTypeParser::parseJsonAndGetInlineQuery(const boost::property_tree::ptree& data) const {
	InlineQuery::Ptr result(new InlineQuery);
	result->id = data.get<string>("id");
	result->from = tryParseJson<User>(&TgTypeParser::parseJsonAndGetUser, data, "from");
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
	appendToJson(result, "query", object->query);
	appendToJson(result, "offset", object->offset);
	result.erase(result.length() - 1);
	result += '}';
	return result;
}

InlineQueryResult::Ptr TgTypeParser::parseJsonAndGetInlineQueryResult(const boost::property_tree::ptree& data) const {
	string type = data.get<string>("type");
	InlineQueryResult::Ptr result;

	if (type == InlineQueryResultArticle::TYPE) {
		result = static_pointer_cast<InlineQueryResult>(parseJsonAndGetInlineQueryResultArticle(data));
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
	result->messageText = data.get<string>("message_text", "");
	result->parseMode = data.get<string>("parse_mode", "");
	result->disableWebPagePreview = data.get("disable_web_page_preview", false);
	result->thumbUrl = data.get<string>("thumb_url", "");

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
	appendToJson(result, "message_text", object->messageText);
	appendToJson(result, "parse_mode", object->parseMode);
	appendToJson(result, "disable_web_page_preview", object->disableWebPagePreview);
	appendToJson(result, "thumb_url", object->thumbUrl);

	if (object->type == InlineQueryResultArticle::TYPE){
		result += parseInlineQueryResultArticle(static_pointer_cast<InlineQueryResultArticle>(object));
	} else if (object->type == InlineQueryResultPhoto::TYPE){
		result += parseInlineQueryResultPhoto(static_pointer_cast<InlineQueryResultPhoto>(object));
	} else if (object->type == InlineQueryResultGif::TYPE){
		result += parseInlineQueryResultGif(static_pointer_cast<InlineQueryResultGif>(object));
	} else if (object->type == InlineQueryResultMpeg4Gif::TYPE){
		result += parseInlineQueryResultMpeg4Gif(static_pointer_cast<InlineQueryResultMpeg4Gif>(object));
	} else if (object->type == InlineQueryResultVideo::TYPE){
		result += parseInlineQueryResultVideo(static_pointer_cast<InlineQueryResultVideo>(object));
	}

	result.erase(result.length() - 1);
	result += '}';
	return result;
}

InlineQueryResultArticle::Ptr TgTypeParser::parseJsonAndGetInlineQueryResultArticle(const boost::property_tree::ptree& data) const {
	// NOTE: This function will be called by parseJsonAndGgetInlineQueryResult().
	InlineQueryResultArticle::Ptr result(new InlineQueryResultArticle);
	result->url = data.get<string>("url", "");
	result->hideUrl = data.get("hide_url", false);
	result->description = data.get<string>("description", "");
	result->thumbWidth = data.get("thumb_width", 0);
	result->thumbHeight = data.get("thumb_height", 0);
	return result;
}

std::string TgTypeParser::parseInlineQueryResultArticle(const InlineQueryResultArticle::Ptr& object) const {
	if (!object){
		return " ";
	}
	// This function will be called by parseInlineQueryResult(), so I don't add
	// curly brackets to the result string.
	string result;
	appendToJson(result, "url", object->url);
	appendToJson(result, "hide_url", object->hideUrl);
	appendToJson(result, "description", object->description);
	appendToJson(result, "thumb_width", object->thumbWidth);
	appendToJson(result, "thumb_height", object->thumbHeight);
	// The last comma will be erased by parseInlineQueryResult().
	return result;
}

InlineQueryResultPhoto::Ptr TgTypeParser::parseJsonAndGetInlineQueryResultPhoto(const boost::property_tree::ptree& data) const {
	// NOTE: This function will be called by parseJsonAndGgetInlineQueryResult().
	InlineQueryResultPhoto::Ptr result(new InlineQueryResultPhoto);
	result->photoUrl = data.get<string>("photo_url", "");
	result->photoWidth = data.get("photo_width", 0);
	result->photoHeight = data.get("photo_height", 0);
	result->description = data.get<string>("description", "");
	result->caption = data.get<string>("caption", "");
	return result;
}

std::string TgTypeParser::parseInlineQueryResultPhoto(const InlineQueryResultPhoto::Ptr& object) const{
	if (!object){
		return " ";
	}
	// This function will be called by parseInlineQueryResult(), so I don't add
	// curly brackets to the result string.
	string result;
	appendToJson(result, "photo_url", object->photoUrl);
	appendToJson(result, "photo_width", object->photoWidth);
	appendToJson(result, "photo_height", object->photoHeight);
	appendToJson(result, "description", object->description);
	appendToJson(result, "caption", object->caption);
	// The last comma will be erased by parseInlineQueryResult().
	return result;
}

InlineQueryResultGif::Ptr TgTypeParser::parseJsonAndGetInlineQueryResultGif(const boost::property_tree::ptree& data) const {
	// NOTE: This function will be called by parseJsonAndGgetInlineQueryResult().
	InlineQueryResultGif::Ptr result(new InlineQueryResultGif);
	result->gifUrl = data.get<string>("gif_url", "");
	result->gifWidth = data.get("gif_width", 0);
	result->gifHeight = data.get("gif_height", 0);
	result->caption = data.get<string>("caption", "");
	return result;
}
std::string TgTypeParser::parseInlineQueryResultGif(const InlineQueryResultGif::Ptr& object) const {
	if (!object){
		return " ";
	}
	// This function will be called by parseInlineQueryResult(), so I don't add
	// curly brackets to the result string.
	string result;
	appendToJson(result, "gif_url", object->gifUrl);
	appendToJson(result, "gif_width", object->gifWidth);
	appendToJson(result, "gif_height", object->gifHeight);
	appendToJson(result, "caption", object->caption);
	// The last comma will be erased by parseInlineQueryResult().
	return result;
}

InlineQueryResultMpeg4Gif::Ptr TgTypeParser::parseJsonAndGetInlineQueryResultMpeg4Gif(const boost::property_tree::ptree& data) const {
	// NOTE: This function will be called by parseJsonAndGgetInlineQueryResult().
	InlineQueryResultMpeg4Gif::Ptr result(new InlineQueryResultMpeg4Gif);
	result->mpeg4Url = data.get<string>("mpeg4_url");
	result->mpeg4Width = data.get("mpeg4_width", 0);
	result->mpeg4Height = data.get("mpeg4_height", 0);
	result->caption = data.get("caption", "");
	return result;
}

std::string TgTypeParser::parseInlineQueryResultMpeg4Gif(const InlineQueryResultMpeg4Gif::Ptr& object) const {
	if (!object){
		return " ";
	}
	// This function will be called by parseInlineQueryResult(), so I don't add
	// curly brackets to the result string.
	string result;
	appendToJson(result, "mpeg4_url", object->mpeg4Url);
	appendToJson(result, "mpeg4_width", object->mpeg4Width);
	appendToJson(result, "mpeg4_height", object->mpeg4Height);
	appendToJson(result, "caption", object->caption);
	// The last comma will be erased by parseInlineQueryResult().
	return result;
}

InlineQueryResultVideo::Ptr TgTypeParser::parseJsonAndGetInlineQueryResultVideo(const boost::property_tree::ptree& data) const {
	// NOTE: This function will be called by parseJsonAndGgetInlineQueryResult().
	InlineQueryResultVideo::Ptr result(new InlineQueryResultVideo);
	result->videoUrl = data.get<string>("video_url");
	result->mimeType = data.get<string>("mime_type");
	result->videoWidth = data.get("video_height", 0);
	result->videoHeight = data.get("video_height", 0);
	result->videoDuration = data.get("video_duration", 0);
	result->description = data.get<string>("description", "");
	return result;
}

std::string TgTypeParser::parseInlineQueryResultVideo(const InlineQueryResultVideo::Ptr& object) const {
	if (!object){
		return " ";
	}
	// This function will be called by parseInlineQueryResult(), so I don't add
	// curly brackets to the result string.
	string result;
	appendToJson(result, "video_url", object->videoUrl);
	appendToJson(result, "mime_type", object->mimeType);
	appendToJson(result, "video_width", object->videoWidth);
	appendToJson(result, "video_height", object->videoHeight);
	appendToJson(result, "video_duration", object->videoDuration);
	appendToJson(result, "description", object->description);
	// The last comma will be erased by parseInlineQueryResult().
	return result;
}

ChosenInlineResult::Ptr TgTypeParser::parseJsonAndGetChosenInlineResult(const boost::property_tree::ptree& data) const {
	ChosenInlineResult::Ptr result(new ChosenInlineResult);
	result->resultId = data.get<string>("result_id");
	result->from = tryParseJson<User>(&TgTypeParser::parseJsonAndGetUser, data, "from");
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
	result.erase(result.length() - 1);
	result += '}';
	return result;
}

CallbackQuery::Ptr TgTypeParser::parseJsonAndGetCallbackQuery(const boost::property_tree::ptree& data) const {
	CallbackQuery::Ptr result(new CallbackQuery);
	result->id = data.get<string>("id");
	result->from = tryParseJson<User>(&TgTypeParser::parseJsonAndGetUser, data, "from");
	result->message = tryParseJson<Message>(&TgTypeParser::parseJsonAndGetMessage, data, "message");
	result->inlineMessageId = data.get<string>("inline_message_id", "");
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
	appendToJson(result, "data", object->data);
	result.erase(result.length() - 1);
	result += '}';
	return result;
}

InlineKeyboardMarkup::Ptr TgTypeParser::parseJsonAndGetInlineKeyboardMarkup(const boost::property_tree::ptree& data) const {
	InlineKeyboardMarkup::Ptr result(new InlineKeyboardMarkup);
	for (const boost::property_tree::ptree::value_type& item : data.find("inline_keyboard")->second){
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
	result += "\"inline_keyboard\":[";
	for (vector<InlineKeyboardButton::Ptr>& item : object->inlineKeyboard){
		result += '[';
		for (InlineKeyboardButton::Ptr& innerItem : item){
			result += parseInlineKeyboardButton(innerItem);
			result += ',';
		}
		result.erase(result.length() - 1);
		result += "],";
	}
	result.erase(result.length() - 1);
	result += "]}";
	return result;
}

InlineKeyboardButton::Ptr TgTypeParser::parseJsonAndGetInlineKeyboardButton(const boost::property_tree::ptree& data) const {
	InlineKeyboardButton::Ptr result(new InlineKeyboardButton);
	result->text = data.get<string>("text");
	result->url = data.get<string>("url", "");
	result->callbackData = data.get<string>("callback_data", "");
	result->switchInlineQuery = data.get<string>("switch_inline_query", "");
	return result;
}
std::string TgTypeParser::parseInlineKeyboardButton(const InlineKeyboardButton::Ptr& object) const {
	if (!object){
		return "";
	}
	string result;
	result += '{';
	appendToJson(result, "text", object->text);
	appendToJson(result, "url", object->url);
	appendToJson(result, "callback_data", object->callbackData);
	appendToJson(result, "switch_inline_query", object->switchInlineQuery);
	result.erase(result.length() - 1);
	result += '}';
	return result;
}

void TgTypeParser::appendToJson(string& json, const string& varName, const string& value) const {
	if (value.empty()) {
		return;
	}
	json += '"';
	json += varName;
	json += "\":";
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
