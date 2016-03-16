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
	result->audio = tryParseJson<Audio>(&TgTypeParser::parseJsonAndGetAudio, data, "audio");
	result->document = tryParseJson<Document>(&TgTypeParser::parseJsonAndGetDocument, data, "document");
	result->photo = parseJsonAndGetArray<PhotoSize>(&TgTypeParser::parseJsonAndGetPhotoSize, data, "photo");
	result->sticker = tryParseJson<Sticker>(&TgTypeParser::parseJsonAndGetSticker, data, "sticker");
	result->video = tryParseJson<Video>(&TgTypeParser::parseJsonAndGetVideo, data, "video");
	result->contact = tryParseJson<Contact>(&TgTypeParser::parseJsonAndGetContact, data, "contact");
	result->location = tryParseJson<Location>(&TgTypeParser::parseJsonAndGetLocation, data, "location");
	result->newChatParticipant = tryParseJson<User>(&TgTypeParser::parseJsonAndGetUser, data, "new_chat_participant");
	result->leftChatParticipant = tryParseJson<User>(&TgTypeParser::parseJsonAndGetUser, data, "left_chat_participant");
	result->newChatTitle = data.get("new_chat_title", "");
	result->newChatPhoto = parseJsonAndGetArray<PhotoSize>(&TgTypeParser::parseJsonAndGetPhotoSize, data, "new_chat_photo");
	result->deleteChatPhoto = data.get("delete_chat_photo", false);
	result->groupChatCreated = data.get("group_chat_created", false);
	result->caption = data.get("caption", false);
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
	appendToJson(result, "new_chat_participant", parseUser(object->newChatParticipant));
	appendToJson(result, "left_chat_participant", parseUser(object->leftChatParticipant));
	appendToJson(result, "new_chat_title", object->newChatTitle);
	appendToJson(result, "new_chat_photo", parseArray(&TgTypeParser::parsePhotoSize, object->newChatPhoto));
	appendToJson(result, "delete_chat_photo", object->deleteChatPhoto);
	appendToJson(result, "group_chat_created", object->groupChatCreated);
	appendToJson(result, "caption", object->caption);
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
	result->message = parseJsonAndGetMessage(data.find("message")->second);
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
	} else {
		return static_pointer_cast<GenericReply>(parseJsonAndGetReplyKeyboardMarkup(data));
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
	} else {
		return parseReplyKeyboardMarkup(static_pointer_cast<ReplyKeyboardMarkup>(object));
	}
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
