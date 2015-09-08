/*
 * Copyright (c) 2015 Oleg Morozenkov
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
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

#include "tgbot/Api.h"

#include "tgbot/TgTypeParser.h"
#include "tgbot/TgException.h"
#include "tgbot/net/HttpClient.h"

using namespace std;
using namespace boost::property_tree;

namespace TgBot {

Api::Api(const string& token) : _token(token) {
}

User::Ptr Api::getMe() const {
	return TgTypeParser::getInstance().parseJsonAndGetUser(sendRequest("getMe"));
}

Message::Ptr Api::sendMessage(int32_t chatId, const string& text, bool disableWebPagePreview, int32_t replyToMessageId, const GenericReply::Ptr& replyMarkup) const {
	vector<HttpReqArg> args;
	args.push_back(HttpReqArg("chat_id", chatId));
	args.push_back(HttpReqArg("text", text));
	if (disableWebPagePreview) {
		args.push_back(HttpReqArg("disable_web_page_preview", disableWebPagePreview));
	}
	if (replyToMessageId) {
		args.push_back(HttpReqArg("reply_to_message_id", replyToMessageId));
	}
	if (replyMarkup) {
		args.push_back(HttpReqArg("reply_markup", TgTypeParser::getInstance().parseGenericReply(replyMarkup)));
	}
	return TgTypeParser::getInstance().parseJsonAndGetMessage(sendRequest("sendMessage", args));
}

Message::Ptr Api::forwardMessage(int32_t chatId, int32_t fromChatId, int32_t messageId) const {
	vector<HttpReqArg> args;
	args.push_back(HttpReqArg("chat_id", chatId));
	args.push_back(HttpReqArg("from_chat_id", fromChatId));
	args.push_back(HttpReqArg("message_id", messageId));
	return TgTypeParser::getInstance().parseJsonAndGetMessage(sendRequest("forwardMessage", args));
}

Message::Ptr Api::sendPhoto(int32_t chatId, const InputFile::Ptr& photo, const string& caption, int32_t replyToMessageId, const GenericReply::Ptr& replyMarkup) const {
	vector<HttpReqArg> args;
	args.push_back(HttpReqArg("chat_id", chatId));
	args.push_back(HttpReqArg("photo", photo->data, true, photo->mimeType));
	if (!caption.empty()) {
		args.push_back(HttpReqArg("caption", caption));
	}
	if (replyToMessageId) {
		args.push_back(HttpReqArg("reply_to_message_id", replyToMessageId));
	}
	if (replyMarkup) {
		args.push_back(HttpReqArg("reply_markup", TgTypeParser::getInstance().parseGenericReply(replyMarkup)));
	}
	return TgTypeParser::getInstance().parseJsonAndGetMessage(sendRequest("sendPhoto", args));
}

Message::Ptr Api::sendPhoto(int32_t chatId, const string& photo, const string& caption, int32_t replyToMessageId, const GenericReply::Ptr& replyMarkup) const {
	vector<HttpReqArg> args;
	args.push_back(HttpReqArg("chat_id", chatId));
	args.push_back(HttpReqArg("photo", photo));
	if (!caption.empty()) {
		args.push_back(HttpReqArg("caption", caption));
	}
	if (replyToMessageId) {
		args.push_back(HttpReqArg("reply_to_message_id", replyToMessageId));
	}
	if (replyMarkup) {
		args.push_back(HttpReqArg("reply_markup", TgTypeParser::getInstance().parseGenericReply(replyMarkup)));
	}
	return TgTypeParser::getInstance().parseJsonAndGetMessage(sendRequest("sendPhoto", args));
}

Message::Ptr Api::sendAudio(int32_t chatId, const InputFile::Ptr& audio, int32_t duration, int32_t replyToMessageId, const GenericReply::Ptr& replyMarkup) const {
	vector<HttpReqArg> args;
	args.push_back(HttpReqArg("chat_id", chatId));
	args.push_back(HttpReqArg("audio", audio->data, true, audio->mimeType));
	if (duration) {
		args.push_back(HttpReqArg("duration", duration));
	}
	if (replyToMessageId) {
		args.push_back(HttpReqArg("reply_to_message_id", replyToMessageId));
	}
	if (replyMarkup) {
		args.push_back(HttpReqArg("reply_markup", TgTypeParser::getInstance().parseGenericReply(replyMarkup)));
	}
	return TgTypeParser::getInstance().parseJsonAndGetMessage(sendRequest("sendAudio", args));
}

Message::Ptr Api::sendAudio(int32_t chatId, const string& audio, int32_t duration, int32_t replyToMessageId, const GenericReply::Ptr& replyMarkup) const {
	vector<HttpReqArg> args;
	args.push_back(HttpReqArg("chat_id", chatId));
	args.push_back(HttpReqArg("audio", audio));
	if (duration) {
		args.push_back(HttpReqArg("duration", duration));
	}
	if (replyToMessageId) {
		args.push_back(HttpReqArg("reply_to_message_id", replyToMessageId));
	}
	if (replyMarkup) {
		args.push_back(HttpReqArg("reply_markup", TgTypeParser::getInstance().parseGenericReply(replyMarkup)));
	}
	return TgTypeParser::getInstance().parseJsonAndGetMessage(sendRequest("sendAudio", args));
}

Message::Ptr Api::sendDocument(int32_t chatId, const InputFile::Ptr& document, int32_t replyToMessageId, const GenericReply::Ptr& replyMarkup) const {
	vector<HttpReqArg> args;
	args.push_back(HttpReqArg("chat_id", chatId));
	args.push_back(HttpReqArg("document", document->data, true, document->mimeType));
	if (replyToMessageId) {
		args.push_back(HttpReqArg("reply_to_message_id", replyToMessageId));
	}
	if (replyMarkup) {
		args.push_back(HttpReqArg("reply_markup", TgTypeParser::getInstance().parseGenericReply(replyMarkup)));
	}
	return TgTypeParser::getInstance().parseJsonAndGetMessage(sendRequest("sendDocument", args));
}

Message::Ptr Api::sendDocument(int32_t chatId, const string& document, int32_t replyToMessageId, const GenericReply::Ptr& replyMarkup) const {
	vector<HttpReqArg> args;
	args.push_back(HttpReqArg("chat_id", chatId));
	args.push_back(HttpReqArg("document", document));
	if (replyToMessageId) {
		args.push_back(HttpReqArg("reply_to_message_id", replyToMessageId));
	}
	if (replyMarkup) {
		args.push_back(HttpReqArg("reply_markup", TgTypeParser::getInstance().parseGenericReply(replyMarkup)));
	}
	return TgTypeParser::getInstance().parseJsonAndGetMessage(sendRequest("sendDocument", args));
}

Message::Ptr Api::sendSticker(int32_t chatId, const InputFile::Ptr& sticker, int32_t replyToMessageId, const GenericReply::Ptr& replyMarkup) const {
	vector<HttpReqArg> args;
	args.push_back(HttpReqArg("chat_id", chatId));
	args.push_back(HttpReqArg("sticker", sticker->data, true, sticker->mimeType));
	if (replyToMessageId) {
		args.push_back(HttpReqArg("reply_to_message_id", replyToMessageId));
	}
	if (replyMarkup) {
		args.push_back(HttpReqArg("reply_markup", TgTypeParser::getInstance().parseGenericReply(replyMarkup)));
	}
	return TgTypeParser::getInstance().parseJsonAndGetMessage(sendRequest("sendSticker", args));
}

Message::Ptr Api::sendSticker(int32_t chatId, const string& sticker, int32_t replyToMessageId, const GenericReply::Ptr& replyMarkup) const {
	vector<HttpReqArg> args;
	args.push_back(HttpReqArg("chat_id", chatId));
	args.push_back(HttpReqArg("sticker", sticker));
	if (replyToMessageId) {
		args.push_back(HttpReqArg("reply_to_message_id", replyToMessageId));
	}
	if (replyMarkup) {
		args.push_back(HttpReqArg("reply_markup", TgTypeParser::getInstance().parseGenericReply(replyMarkup)));
	}
	return TgTypeParser::getInstance().parseJsonAndGetMessage(sendRequest("sendSticker", args));
}

Message::Ptr Api::sendVideo(int32_t chatId, const InputFile::Ptr& video, int32_t replyToMessageId, const GenericReply::Ptr& replyMarkup) const {
	vector<HttpReqArg> args;
	args.push_back(HttpReqArg("chat_id", chatId));
	args.push_back(HttpReqArg("video", video->data, true, video->mimeType));
	if (replyToMessageId) {
		args.push_back(HttpReqArg("reply_to_message_id", replyToMessageId));
	}
	if (replyMarkup) {
		args.push_back(HttpReqArg("reply_markup", TgTypeParser::getInstance().parseGenericReply(replyMarkup)));
	}
	return TgTypeParser::getInstance().parseJsonAndGetMessage(sendRequest("sendVideo", args));
}

Message::Ptr Api::sendVideo(int32_t chatId, const string& video, int32_t replyToMessageId, const GenericReply::Ptr& replyMarkup) const {
	vector<HttpReqArg> args;
	args.push_back(HttpReqArg("chat_id", chatId));
	args.push_back(HttpReqArg("video", video));
	if (replyToMessageId) {
		args.push_back(HttpReqArg("reply_to_message_id", replyToMessageId));
	}
	if (replyMarkup) {
		args.push_back(HttpReqArg("reply_markup", TgTypeParser::getInstance().parseGenericReply(replyMarkup)));
	}
	return TgTypeParser::getInstance().parseJsonAndGetMessage(sendRequest("sendVideo", args));
}

Message::Ptr Api::sendLocation(int32_t chatId, float latitude, float longitude, int32_t replyToMessageId, const GenericReply::Ptr& replyMarkup) const {
	vector<HttpReqArg> args;
	args.push_back(HttpReqArg("chat_id", chatId));
	args.push_back(HttpReqArg("latitude", latitude));
	args.push_back(HttpReqArg("longitude", longitude));
	if (replyToMessageId) {
		args.push_back(HttpReqArg("reply_to_message_id", replyToMessageId));
	}
	if (replyMarkup) {
		args.push_back(HttpReqArg("reply_markup", TgTypeParser::getInstance().parseGenericReply(replyMarkup)));
	}
	return TgTypeParser::getInstance().parseJsonAndGetMessage(sendRequest("sendLocation", args));
}

void Api::sendChatAction(int32_t chatId, const string& action) const {
	vector<HttpReqArg> args;
	args.push_back(HttpReqArg("chat_id", chatId));
	args.push_back(HttpReqArg("action", action));
	sendRequest("sendChatAction", args);
}

UserProfilePhotos::Ptr Api::getUserProfilePhotos(int32_t userId, int32_t offset, int32_t limit) const {
	vector<HttpReqArg> args;
	args.push_back(HttpReqArg("user_id", userId));
	if (offset) {
		args.push_back(HttpReqArg("offset", offset));
	}
	limit = max(1, min(100, limit));
	args.push_back(HttpReqArg("limit", limit));
	return TgTypeParser::getInstance().parseJsonAndGetUserProfilePhotos(sendRequest("getUserProfilePhotos", args));
}

vector<Update::Ptr> Api::getUpdates(int32_t offset, int32_t limit, int32_t timeout) const {
	vector<HttpReqArg> args;
	if (offset) {
		args.push_back(HttpReqArg("offset", offset));
	}
	limit = max(1, min(100, limit));
	args.push_back(HttpReqArg("limit", limit));
	if (timeout) {
		args.push_back(HttpReqArg("timeout", timeout));
	}
	return TgTypeParser::getInstance().parseJsonAndGetArray<Update>(&TgTypeParser::parseJsonAndGetUpdate, sendRequest("getUpdates", args), "result");
}

void Api::setWebhook(const string& url) const {
	vector<HttpReqArg> args;
	args.push_back(HttpReqArg("url", url));
	sendRequest("setWebhook", args);
}

ptree Api::sendRequest(const string& method, const vector<HttpReqArg>& args) const {
	string url = "https://api.telegram.org/bot";
	url += _token;
	url += "/";
	url += method;
	string serverResponse = HttpClient::getInstance().makeRequest(url, args);
	if (serverResponse.find("<html>") != serverResponse.npos) {
		throw TgException("Bad request");
	}
	ptree result = TgTypeParser::getInstance().parseJson(serverResponse);
	try {
		if (result.get<bool>("ok")) {
            if(method != "getMe" && method != "sendMessage")
                return result;
            else
                return result.find("result")->second;
		} else {
			throw TgException(result.get("description", ""));
		}
	} catch (boost::property_tree::ptree_error& e) {
		throw TgException("");
	}
}

}
