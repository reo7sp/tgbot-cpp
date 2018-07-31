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
#include "tgbot/types/StickerSet.h"
#include "tgbot/types/MaskPosition.h"
#include "tgbot/types/Video.h"
#include "tgbot/types/VideoNote.h"
#include "tgbot/types/Contact.h"
#include "tgbot/types/Location.h"
#include "tgbot/types/Update.h"
#include "tgbot/types/UserProfilePhotos.h"
#include "tgbot/types/File.h"
#include "tgbot/types/ReplyKeyboardMarkup.h"
#include "tgbot/types/KeyboardButton.h"
#include "tgbot/types/ReplyKeyboardRemove.h"
#include "tgbot/types/ForceReply.h"
#include "tgbot/types/ChatMember.h"
#include "tgbot/types/ChatPhoto.h"
#include "tgbot/types/ResponseParameters.h"
#include "tgbot/types/GenericReply.h"
#include "tgbot/types/InlineQuery.h"
#include "tgbot/types/InlineQueryResult.h"
#include "tgbot/types/InlineQueryResultCachedAudio.h"
#include "tgbot/types/InlineQueryResultCachedDocument.h"
#include "tgbot/types/InlineQueryResultCachedGif.h"
#include "tgbot/types/InlineQueryResultCachedMpeg4Gif.h"
#include "tgbot/types/InlineQueryResultCachedPhoto.h"
#include "tgbot/types/InlineQueryResultCachedSticker.h"
#include "tgbot/types/InlineQueryResultCachedVideo.h"
#include "tgbot/types/InlineQueryResultCachedVoice.h"
#include "tgbot/types/InlineQueryResultArticle.h"
#include "tgbot/types/InlineQueryResultAudio.h"
#include "tgbot/types/InlineQueryResultContact.h"
#include "tgbot/types/InlineQueryResultGame.h"
#include "tgbot/types/InlineQueryResultDocument.h"
#include "tgbot/types/InlineQueryResultGif.h"
#include "tgbot/types/InlineQueryResultLocation.h"
#include "tgbot/types/InlineQueryResultMpeg4Gif.h"
#include "tgbot/types/InlineQueryResultPhoto.h"
#include "tgbot/types/InlineQueryResultVenue.h"
#include "tgbot/types/InlineQueryResultVideo.h"
#include "tgbot/types/InlineQueryResultVoice.h"
#include "tgbot/types/ChosenInlineResult.h"
#include "tgbot/types/CallbackGame.h"
#include "tgbot/types/Animation.h"
#include "tgbot/types/Game.h"
#include "tgbot/types/GameHighScore.h"
#include "tgbot/types/CallbackQuery.h"
#include "tgbot/types/InlineKeyboardMarkup.h"
#include "tgbot/types/InlineKeyboardButton.h"
#include "tgbot/types/WebhookInfo.h"
#include "tgbot/types/InputMessageContent.h"
#include "tgbot/types/InputTextMessageContent.h"
#include "tgbot/types/InputLocationMessageContent.h"
#include "tgbot/types/InputVenueMessageContent.h"
#include "tgbot/types/InputContactMessageContent.h"
#include "tgbot/types/Invoice.h"
#include "tgbot/types/OrderInfo.h"
#include "tgbot/types/PreCheckoutQuery.h"
#include "tgbot/types/ShippingAddress.h"
#include "tgbot/types/ShippingQuery.h"
#include "tgbot/types/ShippingOption.h"
#include "tgbot/types/SuccessfulPayment.h"
#include "tgbot/types/LabeledPrice.h"
#include "tgbot/types/InputMedia.h"
#include "tgbot/types/InputMediaPhoto.h"
#include "tgbot/types/InputMediaVideo.h"
#include "tgbot/types/InputMediaAudio.h"
#include "tgbot/types/InputMediaDocument.h"
#include "tgbot/types/InputMediaAnimation.h"

namespace TgBot {

class TgTypeParser {

public:
    template<typename T>
    using JsonToTgTypeFunc = std::shared_ptr<T> (TgTypeParser::*)(const boost::property_tree::ptree&) const;

    template<typename T>
    using TgTypeToJsonFunc = std::string (TgTypeParser::*)(const std::shared_ptr<T>&) const;

    Chat::Ptr parseJsonAndGetChat(const boost::property_tree::ptree& data) const;
    std::string parseChat(const Chat::Ptr& object) const;

    User::Ptr parseJsonAndGetUser(const boost::property_tree::ptree& data) const;
    std::string parseUser(const User::Ptr& object) const;

    MessageEntity::Ptr parseJsonAndGetMessageEntity(const boost::property_tree::ptree& data) const;
    std::string parseMessageEntity(const MessageEntity::Ptr& object) const;

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

    StickerSet::Ptr parseJsonAndGetStickerSet(const boost::property_tree::ptree& data) const;
    std::string parseStickerSet(const StickerSet::Ptr& object) const;

    MaskPosition::Ptr parseJsonAndGetMaskPosition(const boost::property_tree::ptree& data) const;
    std::string parseMaskPosition(const MaskPosition::Ptr& object) const;

    Video::Ptr parseJsonAndGetVideo(const boost::property_tree::ptree& data) const;
    std::string parseVideo(const Video::Ptr& object) const;

    VideoNote::Ptr parseJsonAndGetVideoNote(const boost::property_tree::ptree& data) const;
    std::string parseVideoNote(const VideoNote::Ptr& object) const;

    Game::Ptr parseJsonAndGetGame(const boost::property_tree::ptree& data) const;
    std::string parseGame(const Game::Ptr& object) const;

    GameHighScore::Ptr parseJsonAndGetGameHighScore(const boost::property_tree::ptree& data) const;
    std::string parseGameHighScore(const GameHighScore::Ptr& object) const;

    Animation::Ptr parseJsonAndGetAnimation(const boost::property_tree::ptree& data) const;
    std::string parseAnimation(const Animation::Ptr& object) const;

    Contact::Ptr parseJsonAndGetContact(const boost::property_tree::ptree& data) const;
    std::string parseContact(const Contact::Ptr& object) const;

    Location::Ptr parseJsonAndGetLocation(const boost::property_tree::ptree& data) const;
    std::string parseLocation(const Location::Ptr& object) const;

    Update::Ptr parseJsonAndGetUpdate(const boost::property_tree::ptree& data) const;
    std::string parseUpdate(const Update::Ptr& object) const;

    UserProfilePhotos::Ptr parseJsonAndGetUserProfilePhotos(const boost::property_tree::ptree& data) const;
    std::string parseUserProfilePhotos(const UserProfilePhotos::Ptr& object) const;

    InputMedia::Ptr parseJsonAndGetInputMedia(const boost::property_tree::ptree& data) const;
    std::string parseInputMedia(const InputMedia::Ptr& object) const;

    File::Ptr parseJsonAndGetFile(const boost::property_tree::ptree& data) const;
    std::string parseFile(const File::Ptr& object) const;

    ReplyKeyboardMarkup::Ptr parseJsonAndGetReplyKeyboardMarkup(const boost::property_tree::ptree& data) const;
    std::string parseReplyKeyboardMarkup(const ReplyKeyboardMarkup::Ptr& object) const;

    KeyboardButton::Ptr parseJsonAndGetKeyboardButton(const boost::property_tree::ptree& data) const;
    std::string parseKeyboardButton(const KeyboardButton::Ptr& object) const;

    ReplyKeyboardRemove::Ptr parseJsonAndGetReplyKeyboardRemove(const boost::property_tree::ptree& data) const;
    std::string parseReplyKeyboardRemove(const ReplyKeyboardRemove::Ptr& object) const;

    ForceReply::Ptr parseJsonAndGetForceReply(const boost::property_tree::ptree& data) const;
    std::string parseForceReply(const ForceReply::Ptr& object) const;

    ChatMember::Ptr parseJsonAndGetChatMember(const boost::property_tree::ptree& data) const;
    std::string parseChatMember(const ChatMember::Ptr& object) const;

    ChatPhoto::Ptr parseJsonAndGetChatPhoto(const boost::property_tree::ptree& data) const;
    std::string parseChatPhoto(const ChatPhoto::Ptr& object) const;

    ResponseParameters::Ptr parseJsonAndGetResponseParameters(const boost::property_tree::ptree& data) const;
    std::string parseResponseParameters(const ResponseParameters::Ptr& object) const;

    GenericReply::Ptr parseJsonAndGetGenericReply(const boost::property_tree::ptree& data) const;
    std::string parseGenericReply(const GenericReply::Ptr& object) const;

    InlineQuery::Ptr parseJsonAndGetInlineQuery(const boost::property_tree::ptree& data) const;
    std::string parseInlineQuery(const InlineQuery::Ptr& object) const;

    InlineQueryResult::Ptr parseJsonAndGetInlineQueryResult(const boost::property_tree::ptree& data) const;
    std::string parseInlineQueryResult(const InlineQueryResult::Ptr& object) const;

    InlineQueryResultCachedAudio::Ptr parseJsonAndGetInlineQueryResultCachedAudio(const boost::property_tree::ptree& data) const;
    std::string parseInlineQueryResultCachedAudio(const InlineQueryResultCachedAudio::Ptr& object) const;

    InlineQueryResultCachedDocument::Ptr parseJsonAndGetInlineQueryResultCachedDocument(const boost::property_tree::ptree& data) const;
    std::string parseInlineQueryResultCachedDocument(const InlineQueryResultCachedDocument::Ptr& object) const;

    InlineQueryResultCachedGif::Ptr parseJsonAndGetInlineQueryResultCachedGif(const boost::property_tree::ptree& data) const;
    std::string parseInlineQueryResultCachedGif(const InlineQueryResultCachedGif::Ptr& object) const;

    InlineQueryResultCachedMpeg4Gif::Ptr parseJsonAndGetInlineQueryResultCachedMpeg4Gif(const boost::property_tree::ptree& data) const;
    std::string parseInlineQueryResultCachedMpeg4Gif(const InlineQueryResultCachedMpeg4Gif::Ptr& object) const;

    InlineQueryResultCachedPhoto::Ptr parseJsonAndGetInlineQueryResultCachedPhoto(const boost::property_tree::ptree& data) const;
    std::string parseInlineQueryResultCachedPhoto(const InlineQueryResultCachedPhoto::Ptr& object) const;

    InlineQueryResultCachedSticker::Ptr parseJsonAndGetInlineQueryResultCachedSticker(const boost::property_tree::ptree& data) const;
    std::string parseInlineQueryResultCachedSticker(const InlineQueryResultCachedSticker::Ptr& object) const;

    InlineQueryResultCachedVideo::Ptr parseJsonAndGetInlineQueryResultCachedVideo(const boost::property_tree::ptree& data) const;
    std::string parseInlineQueryResultCachedVideo(const InlineQueryResultCachedVideo::Ptr& object) const;

    InlineQueryResultCachedVoice::Ptr parseJsonAndGetInlineQueryResultCachedVoice(const boost::property_tree::ptree& data) const;
    std::string parseInlineQueryResultCachedVoice(const InlineQueryResultCachedVoice::Ptr& object) const;

    InlineQueryResultArticle::Ptr parseJsonAndGetInlineQueryResultArticle(const boost::property_tree::ptree& data) const;
    std::string parseInlineQueryResultArticle(const InlineQueryResultArticle::Ptr& object) const;

    InlineQueryResultAudio::Ptr parseJsonAndGetInlineQueryResultAudio(const boost::property_tree::ptree& data) const;
    std::string parseInlineQueryResultAudio(const InlineQueryResultAudio::Ptr& object) const;

    InlineQueryResultContact::Ptr parseJsonAndGetInlineQueryResultContact(const boost::property_tree::ptree& data) const;
    std::string parseInlineQueryResultContact(const InlineQueryResultContact::Ptr& object) const;

    InlineQueryResultGame::Ptr parseJsonAndGetInlineQueryResultGame(const boost::property_tree::ptree& data) const;
    std::string parseInlineQueryResultGame(const InlineQueryResultGame::Ptr& object) const;

    InlineQueryResultDocument::Ptr parseJsonAndGetInlineQueryResultDocument(const boost::property_tree::ptree& data) const;
    std::string parseInlineQueryResultDocument(const InlineQueryResultDocument::Ptr& object) const;

    InlineQueryResultLocation::Ptr parseJsonAndGetInlineQueryResultLocation(const boost::property_tree::ptree& data) const;
    std::string parseInlineQueryResultLocation(const InlineQueryResultLocation::Ptr& object) const;

    InlineQueryResultVenue::Ptr parseJsonAndGetInlineQueryResultVenue(const boost::property_tree::ptree& data) const;
    std::string parseInlineQueryResultVenue(const InlineQueryResultVenue::Ptr& object) const;

    InlineQueryResultVoice::Ptr parseJsonAndGetInlineQueryResultVoice(const boost::property_tree::ptree& data) const;
    std::string parseInlineQueryResultVoice(const InlineQueryResultVoice::Ptr& object) const;

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

    WebhookInfo::Ptr parseJsonAndGetWebhookInfo(const boost::property_tree::ptree& data) const;
    std::string parseWebhookInfo(const WebhookInfo::Ptr& object) const;

    InputMessageContent::Ptr parseJsonAndGetInputMessageContent(const boost::property_tree::ptree& data) const;
    std::string parseInputMessageContent(const InputMessageContent::Ptr& object) const;

    InputTextMessageContent::Ptr parseJsonAndGetInputTextMessageContent(const boost::property_tree::ptree& data) const;
    std::string parseInputTextMessageContent(const InputTextMessageContent::Ptr& object) const;

    InputLocationMessageContent::Ptr parseJsonAndGetInputLocationMessageContent(const boost::property_tree::ptree& data) const;
    std::string parseInputLocationMessageContent(const InputLocationMessageContent::Ptr& object) const;

    InputVenueMessageContent::Ptr parseJsonAndGetInputVenueMessageContent(const boost::property_tree::ptree& data) const;
    std::string parseInputVenueMessageContent(const InputVenueMessageContent::Ptr& object) const;

    InputContactMessageContent::Ptr parseJsonAndGetInputContactMessageContent(const boost::property_tree::ptree& data) const;
    std::string parseInputContactMessageContent(const InputContactMessageContent::Ptr& object) const;

    Invoice::Ptr parseJsonAndGetInvoice(const boost::property_tree::ptree& data) const;
    std::string parseInvoice(const Invoice::Ptr& object) const;

    LabeledPrice::Ptr parseJsonAndGetLabeledPrice(const boost::property_tree::ptree& data) const;
    std::string parseLabeledPrice(const LabeledPrice::Ptr& object) const;

    OrderInfo::Ptr parseJsonAndGetOrderInfo(const boost::property_tree::ptree& data) const;
    std::string parseOrderInfo(const OrderInfo::Ptr& object) const;

    PreCheckoutQuery::Ptr parseJsonAndGetPreCheckoutQuery(const boost::property_tree::ptree& data) const;
    std::string parsePreCheckoutQuery(const PreCheckoutQuery::Ptr& object) const;

    ShippingAddress::Ptr parseJsonAndGetShippingAddress(const boost::property_tree::ptree& data) const;
    std::string parseShippingAddress(const ShippingAddress::Ptr& object) const;

    ShippingOption::Ptr parseJsonAndGetShippingOption(const boost::property_tree::ptree& data) const;
    std::string parseShippingOption(const ShippingOption::Ptr& object) const;

    ShippingQuery::Ptr parseJsonAndGetShippingQuery(const boost::property_tree::ptree& data) const;
    std::string parseShippingQuery(const ShippingQuery::Ptr& object) const;

    SuccessfulPayment::Ptr parseJsonAndGetSuccessfulPayment(const boost::property_tree::ptree& data) const;
    std::string parseSuccessfulPayment(const SuccessfulPayment::Ptr& object) const;

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
        result.reserve(data.size());
        for (const std::pair<const std::string, boost::property_tree::ptree>& innerTreeItem : data) {
            result.push_back((this->*parseFunc)(innerTreeItem.second));
        }
        return result;
    }

    template<typename T>
    std::vector<T> parseJsonAndGetArray(std::function<T(const boost::property_tree::ptree&)> parseFunc, const boost::property_tree::ptree& data, const std::string& keyName) const {
        std::vector<T> result;
        auto treeItem = data.find(keyName);
        if (treeItem == data.not_found()) {
            return result;
        }
        result.reserve(treeItem->second.size());
        for (const std::pair<const std::string, boost::property_tree::ptree>& innerTreeItem : treeItem->second) {
            result.push_back(parseFunc(innerTreeItem.second));
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
        result.reserve(treeItem->second.size());
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
        result.reserve(treeItem->second.size());
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
        if (objects.empty())
            return "";
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
    std::string parseArray(std::function<T(const T&)> parseFunc, const std::vector<T>& objects) const {
        if (objects.empty())
            return "";
        std::string result;
        result += '[';
        for (const T& item : objects) {
            result += parseFunc(item);
            result += ',';
        }
        result.erase(result.length() - 1);
        result += ']';
        return result;
    }

    template<typename T>
    std::string parse2DArray(TgTypeToJsonFunc<T> parseFunc, const std::vector<std::vector<std::shared_ptr<T>>>& objects) const {
        if (objects.empty())
            return "";
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
    inline void removeLastComma(std::string& input) const {
        input.erase(input.length() - 1);
    }

    template<typename T>
    inline void appendToJson(std::string& json, const std::string& varName, const std::shared_ptr<T>& value) const {
        if (value == nullptr) {
            return;
        }
        json += '"';
        json += varName;
        json += R"(":)";
        json += value;
        json += ',';
    }

    template<typename T>
    inline void appendToJson(std::string& json, const std::string& varName, const T& value) const {
        json += '"';
        json += varName;
        json += R"(":)";
        json += value;
        json += ',';
    }

    inline void appendToJson(std::string& json, const std::string& varName, const bool& value) const {
        json += '"';
        json += varName;
        json += R"(":)";
        json += (value ? "true" : "false");
        json += ',';
    }

    void appendToJson(std::string& json, const std::string& varName, const std::string& value) const;
};

}

#endif //TGBOT_CPP_TGTYPEPARSER_H
