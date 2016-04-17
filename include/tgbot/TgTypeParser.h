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

#ifndef TGBOT_CPP_TGTYPEPARSER_H
#define TGBOT_CPP_TGTYPEPARSER_H

#include <string>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

#include "tgbot/types/User.h"
#include "tgbot/types/Chat.h"
#include "tgbot/types/Message.h"
#include "tgbot/types/PhotoSize.h"
#include "tgbot/types/Audio.h"
#include "tgbot/types/Document.h"
#include "tgbot/types/Sticker.h"
#include "tgbot/types/Video.h"
#include "tgbot/types/Contact.h"
#include "tgbot/types/Location.h"
#include "tgbot/types/Update.h"
#include "tgbot/types/UserProfilePhotos.h"
#include "tgbot/types/ReplyKeyboardMarkup.h"
#include "tgbot/types/ReplyKeyboardHide.h"
#include "tgbot/types/ForceReply.h"
#include "tgbot/types/GenericReply.h"
#include "tgbot/types/InlineQuery.h"
#include "tgbot/types/InlineQueryResult.h"
#include "tgbot/types/InlineQueryResultArticle.h"
#include "tgbot/types/InlineQueryResultPhoto.h"
#include "tgbot/types/InlineQueryResultGif.h"
#include "tgbot/types/InlineQueryResultMpeg4Gif.h"
#include "tgbot/types/InlineQueryResultVideo.h"
#include "tgbot/types/ChosenInlineResult.h"
#include "tgbot/types/CallbackQuery.h"
#include "tgbot/types/InlineKeyboardMarkup.h"
#include "tgbot/types/InlineKeyboardButton.h"

namespace TgBot {

class TgTypeParser {

public:
	template<typename T>
	using JsonToTgTypeFunc = std::shared_ptr<T> (TgTypeParser::*)(const boost::property_tree::ptree&) const;

	template<typename T>
	using TgTypeToJsonFunc = std::string (TgTypeParser::*)(const std::shared_ptr<T>&) const;

	static TgTypeParser& getInstance();

	Chat::Ptr parseJsonAndGetChat(const boost::property_tree::ptree& data) const;
	std::string parseChat(const Chat::Ptr& object) const;
	User::Ptr parseJsonAndGetUser(const boost::property_tree::ptree& data) const;
	std::string parseUser(const User::Ptr& object) const;
	Message::Ptr parseJsonAndGetMessage(const boost::property_tree::ptree& data) const;
	std::string parseMessage(const Message::Ptr& object) const;
	PhotoSize::Ptr parseJsonAndGetPhotoSize(const boost::property_tree::ptree& data) const;
	std::string parsePhotoSize(const PhotoSize::Ptr& object) const;
	Audio::Ptr parseJsonAndGetAudio(const boost::property_tree::ptree& data) const;
	std::string parseAudio(const Audio::Ptr& object) const;
	Document::Ptr parseJsonAndGetDocument(const boost::property_tree::ptree& data) const;
	std::string parseDocument(const Document::Ptr& object) const;
	Sticker::Ptr parseJsonAndGetSticker(const boost::property_tree::ptree& data) const;
	std::string parseSticker(const Sticker::Ptr& object) const;
	Video::Ptr parseJsonAndGetVideo(const boost::property_tree::ptree& data) const;
	std::string parseVideo(const Video::Ptr& object) const;
	Contact::Ptr parseJsonAndGetContact(const boost::property_tree::ptree& data) const;
	std::string parseContact(const Contact::Ptr& object) const;
	Location::Ptr parseJsonAndGetLocation(const boost::property_tree::ptree& data) const;
	std::string parseLocation(const Location::Ptr& object) const;
	Update::Ptr parseJsonAndGetUpdate(const boost::property_tree::ptree& data) const;
	std::string parseUpdate(const Update::Ptr& object) const;
	UserProfilePhotos::Ptr parseJsonAndGetUserProfilePhotos(const boost::property_tree::ptree& data) const;
	std::string parseUserProfilePhotos(const UserProfilePhotos::Ptr& object) const;
	ReplyKeyboardMarkup::Ptr parseJsonAndGetReplyKeyboardMarkup(const boost::property_tree::ptree& data) const;
	std::string parseReplyKeyboardMarkup(const ReplyKeyboardMarkup::Ptr& object) const;
	ReplyKeyboardHide::Ptr parseJsonAndGetReplyKeyboardHide(const boost::property_tree::ptree& data) const;
	std::string parseReplyKeyboardHide(const ReplyKeyboardHide::Ptr& object) const;
	ForceReply::Ptr parseJsonAndGetForceReply(const boost::property_tree::ptree& data) const;
	std::string parseForceReply(const ForceReply::Ptr& object) const;
	GenericReply::Ptr parseJsonAndGetGenericReply(const boost::property_tree::ptree& data) const;
	std::string parseGenericReply(const GenericReply::Ptr& object) const;
	InlineQuery::Ptr parseJsonAndGetInlineQuery(const boost::property_tree::ptree& data) const;
	std::string parseInlineQuery(const InlineQuery::Ptr& object) const;
	InlineQueryResult::Ptr parseJsonAndGetInlineQueryResult(const boost::property_tree::ptree& data) const;
	std::string parseInlineQueryResult(const InlineQueryResult::Ptr& object) const;
	InlineQueryResultArticle::Ptr parseJsonAndGetInlineQueryResultArticle(const boost::property_tree::ptree& data) const;
	std::string parseInlineQueryResultArticle(const InlineQueryResultArticle::Ptr& object) const;
	InlineQueryResultPhoto::Ptr parseJsonAndGetInlineQueryResultPhoto(const boost::property_tree::ptree& data) const;
	std::string parseInlineQueryResultPhoto(const InlineQueryResultPhoto::Ptr& object) const;
	InlineQueryResultGif::Ptr parseJsonAndGetInlineQueryResultGif(const boost::property_tree::ptree& data) const;
	std::string parseInlineQueryResultGif(const InlineQueryResultGif::Ptr& object) const;
	InlineQueryResultMpeg4Gif::Ptr parseJsonAndGetInlineQueryResultMpeg4Gif(const boost::property_tree::ptree& data) const;
	std::string parseInlineQueryResultMpeg4Gif(const InlineQueryResultMpeg4Gif::Ptr& object) const;
	InlineQueryResultVideo::Ptr parseJsonAndGetInlineQueryResultVideo(const boost::property_tree::ptree& data) const;
	std::string parseInlineQueryResultVideo(const InlineQueryResultVideo::Ptr& object) const;
	ChosenInlineResult::Ptr parseJsonAndGetChosenInlineResult(const boost::property_tree::ptree& data) const;
	std::string parseChosenInlineResult(const ChosenInlineResult::Ptr& object) const;
	CallbackQuery::Ptr parseJsonAndGetCallbackQuery(const boost::property_tree::ptree& data) const;
	std::string parseCallbackQuery(const CallbackQuery::Ptr& object) const;
	InlineKeyboardMarkup::Ptr parseJsonAndGetInlineKeyboardMarkup(const boost::property_tree::ptree& data) const;
	std::string parseInlineKeyboardMarkup(const InlineKeyboardMarkup::Ptr& object) const;
	InlineKeyboardButton::Ptr parseJsonAndGetInlineKeyboardButton(const boost::property_tree::ptree& data) const;
	std::string parseInlineKeyboardButton(const InlineKeyboardButton::Ptr& object) const;

	inline boost::property_tree::ptree parseJson(const std::string& json) const {
		boost::property_tree::ptree tree;
		std::istringstream input(json);
		boost::property_tree::read_json(input, tree);
		return tree;
	}

	template<typename T>
	std::shared_ptr<T> tryParseJson(JsonToTgTypeFunc<T> parseFunc, const boost::property_tree::ptree& data, const std::string& keyName) const {
		auto treeItem = data.find(keyName);
		if (treeItem == data.not_found()) {
			return std::shared_ptr<T>();
		}
		return (this->*parseFunc)(treeItem->second);
	}

	template<typename T>
	std::vector<std::shared_ptr<T>> parseJsonAndGetArray(JsonToTgTypeFunc<T> parseFunc, const boost::property_tree::ptree& data) const {
		std::vector<std::shared_ptr<T>> result;
		for (const std::pair<const std::string, boost::property_tree::ptree>& innerTreeItem : data) {
			result.push_back((this->*parseFunc)(innerTreeItem.second));
		}
		return result;
	}

	template<typename T>
	std::vector<std::shared_ptr<T>> parseJsonAndGetArray(JsonToTgTypeFunc<T> parseFunc, const boost::property_tree::ptree& data, const std::string& keyName) const {
		std::vector<std::shared_ptr<T>> result;
		auto treeItem = data.find(keyName);
		if (treeItem == data.not_found()) {
			return result;
		}
		for (const std::pair<const std::string, boost::property_tree::ptree>& innerTreeItem : treeItem->second) {
			result.push_back((this->*parseFunc)(innerTreeItem.second));
		}
		return result;
	}

	template<typename T>
	std::vector<std::vector<std::shared_ptr<T>>> parseJsonAndGet2DArray(JsonToTgTypeFunc<T> parseFunc, const boost::property_tree::ptree& data, const std::string& keyName) const {
		std::vector<std::vector<std::shared_ptr<T>>> result;
		auto treeItem = data.find(keyName);
		if (treeItem == data.not_found()) {
			return result;
		}
		for (const std::pair<const std::string, boost::property_tree::ptree>& innerTreeItem : treeItem->second) {
			std::vector<std::shared_ptr<T>> innerResult;
			for (const std::pair<const std::string, boost::property_tree::ptree>& innerInnerTreeItem : innerTreeItem.second) {
				innerResult.push_back((this->*parseFunc)(innerInnerTreeItem.second));
			}
			result.push_back(innerResult);
		}
		return result;
	}

	template<typename T>
	std::string parseArray(TgTypeToJsonFunc<T> parseFunc, const std::vector<std::shared_ptr<T>>& objects) const {
		std::string result;
		result += '[';
		for (const std::shared_ptr<T>& item : objects) {
			result += (this->*parseFunc)(item);
			result += ',';
		}
		result.erase(result.length() - 1);
		result += ']';
		return result;
	}

	template<typename T>
	std::string parse2DArray(TgTypeToJsonFunc<T> parseFunc, const std::vector<std::vector<std::shared_ptr<T>>>& objects) const {
		std::string result;
		result += '[';
		for (const std::vector<std::shared_ptr<T>>& item : objects) {
			result += parseArray(parseFunc, item);
			result += ',';
		}
		result.erase(result.length() - 1);
		result += ']';
		return result;
	}

private:
	template<typename T>
	void appendToJson(std::string& json, const std::string& varName, const T& value) const {
		if (value == 0) {
			return;
		}
		json += '"';
		json += varName;
		json += "\":";
		json += value;
		json += ',';
	}

	void appendToJson(std::string& json, const std::string& varName, const bool& value) const {
		if (value == 0) {
			return;
		}
		json += '"';
		json += varName;
		json += "\":";
		json += (value ? "true" : "false");
		json += ',';
	}

	void appendToJson(std::string& json, const std::string& varName, const std::string& value) const;
};

}

#endif //TGBOT_CPP_TGTYPEPARSER_H
