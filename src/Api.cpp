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

#include <utility>

#include "tgbot/TgTypeParser.h"
#include "tgbot/TgException.h"

using namespace std;
using namespace boost::property_tree;

namespace TgBot {

Api::Api(string token, const HttpClient& httpClient)
    : _token(std::move(token)), _httpClient(httpClient), _tgTypeParser() {
}

User::Ptr Api::getMe() const {
    return _tgTypeParser.parseJsonAndGetUser(sendRequest("getMe"));
}

Message::Ptr Api::sendMessage(int64_t chatId, const string& text, bool disableWebPagePreview, int32_t replyToMessageId, const GenericReply::Ptr replyMarkup, const string& parseMode, bool disableNotification) const {
    vector<HttpReqArg> args;
    args.reserve(7);
    args.emplace_back("chat_id", chatId);
    args.emplace_back("text", text);
    if (disableWebPagePreview) {
        args.emplace_back("disable_web_page_preview", disableWebPagePreview);
    }
    if (disableNotification){
        args.emplace_back("disable_notification", disableNotification);
    }
    if (replyToMessageId) {
        args.emplace_back("reply_to_message_id", replyToMessageId);
    }
    if (replyMarkup) {
        args.emplace_back("reply_markup", _tgTypeParser.parseGenericReply(replyMarkup));
    }
    if (!parseMode.empty()) {
        args.emplace_back("parse_mode", parseMode);
    }
    return _tgTypeParser.parseJsonAndGetMessage(sendRequest("sendMessage", args));
}

Message::Ptr Api::forwardMessage(int64_t chatId, int64_t fromChatId, int32_t messageId, bool disableNotification) const {
    vector<HttpReqArg> args;
    args.reserve(4);
    args.emplace_back("chat_id", chatId);
    args.emplace_back("from_chat_id", fromChatId);
    args.emplace_back("message_id", messageId);
    if (disableNotification){
        args.emplace_back("disable_notification", disableNotification);
    }
    return _tgTypeParser.parseJsonAndGetMessage(sendRequest("forwardMessage", args));
}

Message::Ptr Api::sendPhoto(int64_t chatId, const boost::variant<InputFile::Ptr, std::string> photo, const string& caption, int32_t replyToMessageId, const GenericReply::Ptr replyMarkup, const string& parseMode, bool disableNotification) const {
    vector<HttpReqArg> args;
    args.reserve(7);
    args.emplace_back("chat_id", chatId);
    if (photo.which() == 0 /* InputFile::Ptr */) {
        auto file = boost::get<InputFile::Ptr>(photo);
        args.emplace_back("photo", file->data, true, file->mimeType, file->fileName);
    } else /* std::string */ {
        args.emplace_back("photo", boost::get<std::string>(photo));
    }
    if (!caption.empty()) {
        args.emplace_back("caption", caption);
    }
    if (replyToMessageId) {
        args.emplace_back("reply_to_message_id", replyToMessageId);
    }
    if (replyMarkup) {
        args.emplace_back("reply_markup", _tgTypeParser.parseGenericReply(replyMarkup));
    }
    if (!parseMode.empty()) {
        args.emplace_back("parse_mode", parseMode);
    }
    if (disableNotification){
        args.emplace_back("disable_notification", disableNotification);
    }
    return _tgTypeParser.parseJsonAndGetMessage(sendRequest("sendPhoto", args));
}

Message::Ptr Api::sendAudio(int64_t chatId, const boost::variant<InputFile::Ptr, std::string> audio, const string &caption, int32_t duration, const string& performer, const string& title, const boost::variant<InputFile::Ptr, std::string> thumb, int32_t replyToMessageId, const GenericReply::Ptr replyMarkup, const string& parseMode, bool disableNotification) const {
    vector<HttpReqArg> args;
    args.reserve(11);
    args.emplace_back("chat_id", chatId);
    if (audio.which() == 0 /* InputFile::Ptr */) {
        auto file = boost::get<InputFile::Ptr>(audio);
        args.emplace_back("audio", file->data, true, file->mimeType, file->fileName);
    } else /* std::string */ {
        args.emplace_back("audio", boost::get<std::string>(audio));
    }
    if (!caption.empty()) {
        args.emplace_back("caption", caption);
    }
    if (duration) {
        args.emplace_back("duration", duration);
    }
    if (!performer.empty()){
        args.emplace_back("performer", performer);
    }
    if (!title.empty()){
        args.emplace_back("title", title);
    }
    if (thumb.which() == 0 /* InputFile::Ptr */) {
        auto file = boost::get<InputFile::Ptr>(thumb);
        args.emplace_back("thumb", file->data, true, file->mimeType, file->fileName);
    } else /* std::string */ {
        auto thumbStr = boost::get<std::string>(thumb);
        if (!thumbStr.empty()) {
            args.emplace_back("thumb", thumbStr);
        }
    }
    if (replyToMessageId) {
        args.emplace_back("reply_to_message_id", replyToMessageId);
    }
    if (replyMarkup) {
        args.emplace_back("reply_markup", _tgTypeParser.parseGenericReply(replyMarkup));
    }
    if (!parseMode.empty()) {
        args.emplace_back("parse_mode", parseMode);
    }
    if (disableNotification){
        args.emplace_back("disable_notification", disableNotification);
    }
    return _tgTypeParser.parseJsonAndGetMessage(sendRequest("sendAudio", args));
}

Message::Ptr Api::sendDocument(int64_t chatId, const boost::variant<InputFile::Ptr, std::string> document, const boost::variant<InputFile::Ptr, std::string> thumb, const string &caption, int32_t replyToMessageId, const GenericReply::Ptr replyMarkup, const string& parseMode, bool disableNotification) const {
    vector<HttpReqArg> args;
    args.reserve(8);
    args.emplace_back("chat_id", chatId);
    if (document.which() == 0 /* InputFile::Ptr */) {
        auto file = boost::get<InputFile::Ptr>(document);
        args.emplace_back("document", file->data, true, file->mimeType, file->fileName);
    } else /* std::string */ {
        args.emplace_back("document", boost::get<std::string>(document));
    }
    if (thumb.which() == 0 /* InputFile::Ptr */) {
        auto file = boost::get<InputFile::Ptr>(thumb);
        args.emplace_back("thumb", file->data, true, file->mimeType, file->fileName);
    } else /* std::string */ {
        auto thumbStr = boost::get<std::string>(thumb);
        if (!thumbStr.empty()) {
            args.emplace_back("thumb", thumbStr);
        }
    }
    if (!caption.empty()) {
        args.emplace_back("caption", caption);
    }
    if (replyToMessageId) {
        args.emplace_back("reply_to_message_id", replyToMessageId);
    }
    if (replyMarkup) {
        args.emplace_back("reply_markup", _tgTypeParser.parseGenericReply(replyMarkup));
    }
    if (!parseMode.empty()) {
        args.emplace_back("parse_mode", parseMode);
    }
    if (disableNotification){
        args.emplace_back("disable_notification", disableNotification);
    }
    return _tgTypeParser.parseJsonAndGetMessage(sendRequest("sendDocument", args));
}

Message::Ptr Api::sendInvoice(int64_t chatId, const std::string& title, const std::string& description, const std::string& payload,
                             const std::string& providerToken, const std::string& startParameter, const std::string& currency, const std::vector<LabeledPrice::Ptr>& prices,
                             const std::string& providerData, const std::string& photoUrl, int32_t photoSize,
                             int32_t photoWidth, int32_t photoHeight, bool needName,
                             bool needPhoneNumber, bool needEmail, bool needShippingAddress,
                             bool sendPhoneNumberToProvider, bool sendEmailToProvider, bool isFlexible,
                             int32_t replyToMessageId, const GenericReply::Ptr replyMarkup, bool disableNotification) const {
    vector<HttpReqArg> args;
    args.reserve(23);
    args.emplace_back("chat_id", chatId);
    args.emplace_back("title", title);
    args.emplace_back("description", description);
    args.emplace_back("payload", payload);
    args.emplace_back("provider_token", providerToken);
    args.emplace_back("start_parameter", startParameter);
    args.emplace_back("currency", currency);
    args.emplace_back("prices", _tgTypeParser.parseArray<LabeledPrice>(&TgTypeParser::parseLabeledPrice, prices));
    if (!providerData.empty()) {
        args.emplace_back("provider_data", providerData);
    }
    if (!photoUrl.empty()) {
        args.emplace_back("photo_url", photoUrl);
    }
    if (photoSize) {
        args.emplace_back("photo_size", photoSize);
    }
    if (photoWidth) {
        args.emplace_back("photo_width", photoWidth);
    }
    if (photoHeight) {
        args.emplace_back("photo_height", photoHeight);
    }
    if (needName) {
        args.emplace_back("need_name", needName);
    }
    if (needPhoneNumber) {
        args.emplace_back("need_phone_number", needPhoneNumber);
    }
    if (needEmail) {
        args.emplace_back("need_email", needEmail);
    }
    if (needShippingAddress) {
        args.emplace_back("need_shipping_address", needShippingAddress);
    }
    if (sendPhoneNumberToProvider) {
        args.emplace_back("send_phone_number_to_provider", sendPhoneNumberToProvider);
    }
    if (sendEmailToProvider) {
        args.emplace_back("send_email_to_provider", sendEmailToProvider);
    }
    if (isFlexible) {
        args.emplace_back("is_flexible", isFlexible);
    }
    if (replyToMessageId) {
        args.emplace_back("reply_to_message_id", replyToMessageId);
    }
    if (replyMarkup) {
        args.emplace_back("reply_markup", _tgTypeParser.parseGenericReply(replyMarkup));
    }
    if (disableNotification){
        args.emplace_back("disable_notification", disableNotification);
    }
    return _tgTypeParser.parseJsonAndGetMessage(sendRequest("sendInvoice", args));
}

bool Api::answerShippingQuery(const std::string& shippingQueryId, bool ok, const std::vector<ShippingOption::Ptr>& shippingOptions, const std::string& errorMessage) const {
    vector<HttpReqArg> args;
    args.reserve(4);
    args.emplace_back("shipping_query_id", shippingQueryId);
    args.emplace_back("ok", ok);
    if (!shippingOptions.empty()) {
        args.emplace_back("shipping_options", _tgTypeParser.parseArray<ShippingOption>(&TgTypeParser::parseShippingOption, shippingOptions));
    }
    if (!errorMessage.empty()) {
        args.emplace_back("error_message", errorMessage);
    }
    return sendRequest("answerShippingQuery", args).get<bool>("", false);
}

bool Api::answerPreCheckoutQuery(const std::string& preCheckoutQueryId, bool ok, const std::string& errorMessage) const {
    vector<HttpReqArg> args;
    args.reserve(3);
    args.emplace_back("pre_checkout_query_id", preCheckoutQueryId);
    args.emplace_back("ok", ok);
    if (!errorMessage.empty()) {
        args.emplace_back("error_message", errorMessage);
    }
    return sendRequest("answerPreCheckoutQuery", args).get<bool>("", false);
}

Message::Ptr Api::sendSticker(int64_t chatId, const boost::variant<InputFile::Ptr, std::string> sticker, int32_t replyToMessageId, const GenericReply::Ptr replyMarkup, bool disableNotification) const {
    vector<HttpReqArg> args;
    args.reserve(5);
    args.emplace_back("chat_id", chatId);
    if (sticker.which() == 0 /* InputFile::Ptr */) {
        auto file = boost::get<InputFile::Ptr>(sticker);
        args.emplace_back("sticker", file->data, true, file->mimeType, file->fileName);
    } else /* std::string */ {
        args.emplace_back("sticker", boost::get<std::string>(sticker));
    }
    if (replyToMessageId) {
        args.emplace_back("reply_to_message_id", replyToMessageId);
    }
    if (replyMarkup) {
        args.emplace_back("reply_markup", _tgTypeParser.parseGenericReply(replyMarkup));
    }
    if (disableNotification){
        args.emplace_back("disable_notification", disableNotification);
    }
    return _tgTypeParser.parseJsonAndGetMessage(sendRequest("sendSticker", args));
}

StickerSet::Ptr Api::getStickerSet(const string& name) const {
    vector<HttpReqArg> args;
    args.reserve(1);
    args.emplace_back("name", name);
    return _tgTypeParser.parseJsonAndGetStickerSet(sendRequest("getStickerSet", args));
}

File::Ptr Api::uploadStickerFile(int32_t userId, const InputFile::Ptr pngSticker) const {
    vector<HttpReqArg> args;
    args.reserve(2);
    args.emplace_back("user_id", userId);
    args.emplace_back("png_sticker", pngSticker->data, true, pngSticker->mimeType, pngSticker->fileName);
    return _tgTypeParser.parseJsonAndGetFile(sendRequest("uploadStickerFile", args));
}

bool Api::createNewStickerSet(int32_t userId, const string& name, const string& title, const boost::variant<InputFile::Ptr, std::string> pngSticker, const string& emojis, bool containsMasks, MaskPosition::Ptr maskPosition) const {
    vector<HttpReqArg> args;
    args.reserve(7);
    args.emplace_back("user_id", userId);
    args.emplace_back("name", name);
    args.emplace_back("title", title);
    if (pngSticker.which() == 0 /* InputFile::Ptr */) {
        auto file = boost::get<InputFile::Ptr>(pngSticker);
        args.emplace_back("png_sticker", file->data, true, file->mimeType, file->fileName);
    } else /* std::string */ {
        args.emplace_back("png_sticker", boost::get<std::string>(pngSticker));
    }
    args.emplace_back("emojis", emojis);
    if (containsMasks) {
        args.emplace_back("contains_mask", containsMasks);
    }
    if (maskPosition != nullptr) {
        args.emplace_back("mask_position", _tgTypeParser.parseMaskPosition(maskPosition));
    }
    return sendRequest("createNewStickerSet", args).get<bool>("", false);
}

bool Api::addStickerToSet(int32_t userId, const string& name, const string& title, const boost::variant<InputFile::Ptr, std::string> pngSticker, const string& emojis, MaskPosition::Ptr maskPosition) const {
    vector<HttpReqArg> args;
    args.reserve(6);
    args.emplace_back("user_id", userId);
    args.emplace_back("name", name);
    args.emplace_back("title", title);
    if (pngSticker.which() == 0 /* InputFile::Ptr */) {
        auto file = boost::get<InputFile::Ptr>(pngSticker);
        args.emplace_back("png_sticker", file->data, true, file->mimeType, file->fileName);
    } else /* std::string */ {
        args.emplace_back("png_sticker", boost::get<std::string>(pngSticker));
    }
    args.emplace_back("emojis", emojis);
    if (maskPosition != nullptr) {
        args.emplace_back("mask_position", _tgTypeParser.parseMaskPosition(maskPosition));
    }
    return sendRequest("addStickerToSet", args).get<bool>("", false);
}

bool Api::setStickerPositionInSet(const string& sticker, uint32_t position) const {
    vector<HttpReqArg> args;
    args.reserve(2);
    args.emplace_back("sticker", sticker);
    args.emplace_back("position", position);
    return sendRequest("setStickerPositionInSet", args).get<bool>("", false);
}

bool Api::deleteStickerPositionInSet(const string& sticker) const {
    vector<HttpReqArg> args;
    args.reserve(1);
    args.emplace_back("sticker", sticker);
    return sendRequest("setStickerPositionInSet", args).get<bool>("", false);
}

Message::Ptr Api::sendVideo(int64_t chatId, const boost::variant<InputFile::Ptr, std::string> video, bool supportsStreaming, int32_t duration, int32_t width, int32_t height, const boost::variant<InputFile::Ptr, std::string> thumb, const string &caption, int32_t replyToMessageId, const GenericReply::Ptr replyMarkup, const string& parseMode, bool disableNotification) const {
    vector<HttpReqArg> args;
    args.reserve(12);
    args.emplace_back("chat_id", chatId);
    if (video.which() == 0 /* InputFile::Ptr */) {
        auto file = boost::get<InputFile::Ptr>(video);
        args.emplace_back("video", file->data, true, file->mimeType, file->fileName);
    } else /* std::string */ {
        args.emplace_back("video", boost::get<std::string>(video));
    }
    if (supportsStreaming) {
        args.emplace_back("supports_streaming", supportsStreaming);
    }
    if (duration) {
        args.emplace_back("duration", duration);
    }
    if (width) {
        args.emplace_back("width", width);
    }
    if (height) {
        args.emplace_back("height", height);
    }
    if (thumb.which() == 0 /* InputFile::Ptr */) {
        auto file = boost::get<InputFile::Ptr>(thumb);
        args.emplace_back("thumb", file->data, true, file->mimeType, file->fileName);
    } else /* std::string */ {
        auto thumbStr = boost::get<std::string>(thumb);
        if (!thumbStr.empty()) {
            args.emplace_back("thumb", thumbStr);
        }
    }
    if (!caption.empty()) {
        args.emplace_back("caption", caption);
    }
    if (replyToMessageId) {
        args.emplace_back("reply_to_message_id", replyToMessageId);
    }
    if (replyMarkup) {
        args.emplace_back("reply_markup", _tgTypeParser.parseGenericReply(replyMarkup));
    }
    if (!parseMode.empty()) {
        args.emplace_back("parse_mode", parseMode);
    }
    if (disableNotification){
        args.emplace_back("disable_notification", disableNotification);
    }
    return _tgTypeParser.parseJsonAndGetMessage(sendRequest("sendVideo", args));
}

Message::Ptr Api::sendAnimation(int64_t chatId, const boost::variant<InputFile::Ptr, std::string> animation, int32_t duration, int32_t width, int32_t height, const boost::variant<InputFile::Ptr, std::string> thumb, const string& caption, int32_t replyToMessageId, GenericReply::Ptr replyMarkup, const string& parseMode, bool disableNotification) const {
    vector<HttpReqArg> args;
    args.reserve(11);
    args.emplace_back("chat_id", chatId);
    if (animation.which() == 0 /* InputFile::Ptr */) {
        auto file = boost::get<InputFile::Ptr>(animation);
        args.emplace_back("animation", file->data, true, file->mimeType, file->fileName);
    } else /* std::string */ {
        args.emplace_back("animation", boost::get<std::string>(animation));
    }
    if (duration) {
        args.emplace_back("duration", duration);
    }
    if (width) {
        args.emplace_back("width", width);
    }
    if (height) {
        args.emplace_back("height", height);
    }
    if (thumb.which() == 0 /* InputFile::Ptr */) {
        auto file = boost::get<InputFile::Ptr>(thumb);
        args.emplace_back("thumb", file->data, true, file->mimeType, file->fileName);
    } else /* std::string */ {
        auto thumbStr = boost::get<std::string>(thumb);
        if (!thumbStr.empty()) {
            args.emplace_back("thumb", thumbStr);
        }
    }
    if (!caption.empty()) {
        args.emplace_back("caption", caption);
    }
    if (replyToMessageId) {
        args.emplace_back("reply_to_message_id", replyToMessageId);
    }
    if (replyMarkup) {
        args.emplace_back("reply_markup", _tgTypeParser.parseGenericReply(replyMarkup));
    }
    if (!parseMode.empty()) {
        args.emplace_back("parse_mode", parseMode);
    }
    if (disableNotification){
        args.emplace_back("disable_notification", disableNotification);
    }
    return _tgTypeParser.parseJsonAndGetMessage(sendRequest("sendAnimation", args));
}

Message::Ptr Api::sendVideoNote(int64_t chatId, const boost::variant<InputFile::Ptr, std::string> videoNote, int64_t replyToMessageId, bool disableNotification, int32_t duration, int32_t length, const boost::variant<InputFile::Ptr, std::string> thumb, const GenericReply::Ptr replyMarkup) const {
    vector<HttpReqArg> args;
    args.reserve(8);
    args.emplace_back("chat_id", chatId);
    if (videoNote.which() == 0 /* InputFile::Ptr */) {
        auto file = boost::get<InputFile::Ptr>(videoNote);
        args.emplace_back("video_note", file->data, true, file->mimeType, file->fileName);
    } else /* std::string */ {
        args.emplace_back("video_note", boost::get<std::string>(videoNote));
    }
    if (disableNotification) {
        args.emplace_back("disable_notification", disableNotification);
    }
    if (duration) {
        args.emplace_back("duration", duration);
    }
    if (length) {
        args.emplace_back("length", length);
    }
    if (thumb.which() == 0 /* InputFile::Ptr */) {
        auto file = boost::get<InputFile::Ptr>(thumb);
        args.emplace_back("thumb", file->data, true, file->mimeType, file->fileName);
    } else /* std::string */ {
        auto thumbStr = boost::get<std::string>(thumb);
        if (!thumbStr.empty()) {
            args.emplace_back("thumb", thumbStr);
        }
    }
    if (replyMarkup) {
        args.emplace_back("reply_markup", _tgTypeParser.parseGenericReply(replyMarkup));
    }
    if (replyToMessageId) {
        args.emplace_back("reply_to_message_id", replyToMessageId);
    }
    return _tgTypeParser.parseJsonAndGetMessage(sendRequest("sendVideoNote", args));
}

vector<Message::Ptr> Api::sendMediaGroup(int64_t chatId, const vector<InputMedia::Ptr>& media, bool disableNotification, int32_t replyToMessageId) const {
    vector<HttpReqArg> args;
    args.reserve(4);
    args.emplace_back("chat_id", chatId);
    string mediaJson = _tgTypeParser.parseArray<InputMedia>(&TgTypeParser::parseInputMedia, media);
    args.emplace_back("media", mediaJson);
    args.emplace_back("disable_notification", disableNotification);
    args.emplace_back("reply_to_message_id", replyToMessageId);
    return _tgTypeParser.parseJsonAndGetArray<Message>(&TgTypeParser::parseJsonAndGetMessage, sendRequest("sendMediaGroup", args));
}

Message::Ptr Api::sendVoice(int64_t chatId, const boost::variant<InputFile::Ptr, std::string> voice, const string &caption, int duration, int32_t replyToMessageId, const GenericReply::Ptr replyMarkup, const string& parseMode, bool disableNotification) const {
    vector<HttpReqArg> args;
    args.reserve(8);
    args.emplace_back("chat_id", chatId);
    if (voice.which() == 0 /* InputFile::Ptr */) {
        auto file = boost::get<InputFile::Ptr>(voice);
        args.emplace_back("voice", file->data, true, file->mimeType, file->fileName);
    } else /* std::string */ {
        args.emplace_back("voice", boost::get<std::string>(voice));
    }
    if (!caption.empty()) {
        args.emplace_back("caption", caption);
    }
    if (duration){
        args.emplace_back("duration", duration);
    }
    if (replyToMessageId) {
        args.emplace_back("reply_to_message_id", replyToMessageId);
    }
    if (replyMarkup) {
        args.emplace_back("reply_markup", _tgTypeParser.parseGenericReply(replyMarkup));
    }
    if (!parseMode.empty()) {
        args.emplace_back("parse_mode", parseMode);
    }
    if (disableNotification){
        args.emplace_back("disable_notification", disableNotification);
    }
    return _tgTypeParser.parseJsonAndGetMessage(sendRequest("sendVoice", args));
}

Message::Ptr Api::sendGame(int64_t chatId, const std::string& gameShortName, int32_t replyToMessageId, const InlineKeyboardMarkup::Ptr replyMarkup, bool disableNotification) const {
    vector<HttpReqArg> args;
    args.reserve(5);
    args.emplace_back("chat_id", chatId);
    args.emplace_back("game_short_name", gameShortName);
    if (replyToMessageId) {
        args.emplace_back("reply_to_message_id", replyToMessageId);
    }
    if (replyMarkup) {
        args.emplace_back("reply_markup", _tgTypeParser.parseGenericReply(replyMarkup));
    }
    if (disableNotification){
        args.emplace_back("disable_notification", disableNotification);
    }
    return _tgTypeParser.parseJsonAndGetMessage(sendRequest("sendGame", args));
}

Message::Ptr Api::sendLocation(int64_t chatId, float latitude, float longitude, uint32_t livePeriod, int32_t replyToMessageId, const GenericReply::Ptr replyMarkup, bool disableNotification) const {
    vector<HttpReqArg> args;
    args.reserve(7);
    args.emplace_back("chat_id", chatId);
    args.emplace_back("latitude", latitude);
    args.emplace_back("longitude", longitude);
    if (livePeriod) {
        args.emplace_back("live_period", livePeriod);
    }
    if (replyToMessageId) {
        args.emplace_back("reply_to_message_id", replyToMessageId);
    }
    if (replyMarkup) {
        args.emplace_back("reply_markup", _tgTypeParser.parseGenericReply(replyMarkup));
    }
    if (disableNotification){
        args.emplace_back("disable_notification", disableNotification);
    }
    return _tgTypeParser.parseJsonAndGetMessage(sendRequest("sendLocation", args));
}

Message::Ptr Api::editMessageLiveLocation(float latitude, float longitude, int64_t chatId, int32_t messageId, int32_t inlineMessageId, const InlineKeyboardMarkup::Ptr replyMarkup) const {
    vector<HttpReqArg> args;
    args.reserve(6);
    args.emplace_back("latitude", latitude);
    args.emplace_back("longitude", longitude);
    if (chatId) {
        args.emplace_back("chat_id", chatId);
    }
    if (messageId) {
        args.emplace_back("message_id", messageId);
    }
    if (inlineMessageId) {
        args.emplace_back("inline_message_id", inlineMessageId);
    }
    if (replyMarkup) {
        args.emplace_back("reply_markup", _tgTypeParser.parseInlineKeyboardMarkup(replyMarkup));
    }
    return _tgTypeParser.parseJsonAndGetMessage(sendRequest("editMessageLiveLocation", args));
}

Message::Ptr Api::stopMessageLiveLocation(int64_t chatId, int32_t messageId, int32_t inlineMessageId, const InlineKeyboardMarkup::Ptr replyMarkup) const {
    vector<HttpReqArg> args;
    args.reserve(4);
    if (chatId) {
        args.emplace_back("chat_id", chatId);
    }
    if (messageId) {
        args.emplace_back("message_id", messageId);
    }
    if (inlineMessageId) {
        args.emplace_back("inline_message_id", inlineMessageId);
    }
    if (replyMarkup) {
        args.emplace_back("reply_markup", _tgTypeParser.parseInlineKeyboardMarkup(replyMarkup));
    }
    return _tgTypeParser.parseJsonAndGetMessage(sendRequest("editMessageLiveLocation", args));
}

bool Api::setChatStickerSet(int64_t chatId, const string& stickerSetName) const {
    vector<HttpReqArg> args;
    args.reserve(2);
    args.emplace_back("chat_id", chatId);
    args.emplace_back("sticker_set_name	", stickerSetName);
    return sendRequest("setChatStickerSet", args).get<bool>("", false);
}

bool Api::deleteChatStickerSet(int64_t chatId) const {
    vector<HttpReqArg> args;
    args.reserve(1);
    args.emplace_back("chat_id", chatId);
    return sendRequest("deleteChatStickerSet", args).get<bool>("", false);
}

Message::Ptr Api::sendVenue(int64_t chatId, float latitude, float longitude, const string& title, const string& address, const string& foursquareId, const string& foursquareType, bool disableNotification, int32_t replyToMessageId, const GenericReply::Ptr replyMarkup) const {
    vector<HttpReqArg> args;
    args.reserve(10);
    args.emplace_back("chat_id", chatId);
    args.emplace_back("latitude", latitude);
    args.emplace_back("longitude", longitude);
    args.emplace_back("title", title);
    args.emplace_back("address", address);
    if (!foursquareId.empty()) {
        args.emplace_back("foursquare_id", foursquareId);
    }
    if (!foursquareType.empty()) {
        args.emplace_back("foursquare_type", foursquareType);
    }
    if (replyToMessageId) {
        args.emplace_back("reply_to_message_id", replyToMessageId);
    }
    if (replyMarkup) {
        args.emplace_back("reply_markup", _tgTypeParser.parseGenericReply(replyMarkup));
    }
    if (disableNotification){
        args.emplace_back("disable_notification", disableNotification);
    }
    return _tgTypeParser.parseJsonAndGetMessage(sendRequest("sendVenue", args));
}

Message::Ptr Api::sendContact(int64_t chatId, const string& phoneNumber, const string& firstName, const string& lastName, const string& vcard, bool disableNotification, int32_t replyToMessageId, const GenericReply::Ptr replyMarkup) const {
    vector<HttpReqArg> args;
    args.reserve(8);
    args.emplace_back("chat_id", chatId);
    args.emplace_back("phone_number", phoneNumber);
    args.emplace_back("first_name", firstName);
    if (!lastName.empty()) {
        args.emplace_back("last_name", lastName);
    }
    if (!vcard.empty()) {
        args.emplace_back("vcard", vcard);
    }
    if (replyToMessageId) {
        args.emplace_back("reply_to_message_id", replyToMessageId);
    }
    if (replyMarkup) {
        args.emplace_back("reply_markup", _tgTypeParser.parseGenericReply(replyMarkup));
    }
    if (disableNotification){
        args.emplace_back("disable_notification", disableNotification);
    }
    return _tgTypeParser.parseJsonAndGetMessage(sendRequest("sendContact", args));
}

void Api::sendChatAction(int64_t chatId, const string& action) const {
    vector<HttpReqArg> args;
    args.reserve(2);
    args.emplace_back("chat_id", chatId);
    args.emplace_back("action", action);
    sendRequest("sendChatAction", args);
}

UserProfilePhotos::Ptr Api::getUserProfilePhotos(int32_t userId, int32_t offset, int32_t limit) const {
    vector<HttpReqArg> args;
    args.reserve(3);
    args.emplace_back("user_id", userId);
    if (offset) {
        args.emplace_back("offset", offset);
    }
    limit = max(1, min(100, limit));
    args.emplace_back("limit", limit);
    return _tgTypeParser.parseJsonAndGetUserProfilePhotos(sendRequest("getUserProfilePhotos", args));
}

File::Ptr Api::getFile(const string &fileId) const {
    vector<HttpReqArg> args;
    args.reserve(1);
    args.emplace_back("file_id", fileId);
    return _tgTypeParser.parseJsonAndGetFile(sendRequest("getFile", args));
}

bool Api::leaveChat(int64_t chatId) const {
    vector<HttpReqArg> args;
    args.reserve(1);
    args.emplace_back("chat_id", chatId);
    return sendRequest("leaveChat", args).get<bool>("", false);
}

Chat::Ptr Api::getChat(int64_t chatId) const {
    vector<HttpReqArg> args;
    args.reserve(1);
    args.emplace_back("chat_id", chatId);
    return _tgTypeParser.parseJsonAndGetChat(sendRequest("getChat", args));
}

vector<ChatMember::Ptr> Api::getChatAdministrators(int64_t chatId) const {
    vector<HttpReqArg> args;
    args.reserve(1);
    args.emplace_back("chat_id", chatId);
    return _tgTypeParser.parseJsonAndGetArray<ChatMember>(&TgTypeParser::parseJsonAndGetChatMember, sendRequest("getChatAdministrators", args));
}

int32_t Api::getChatMembersCount(int64_t chatId) const {
    vector<HttpReqArg> args;
    args.reserve(1);
    args.emplace_back("chat_id", chatId);
    return sendRequest("getChatMembersCount", args).get<int32_t>("", 0);
}

bool Api::answerCallbackQuery(const string & callbackQueryId, const string & text, bool showAlert, const string &url, int32_t cacheTime) const {
    vector<HttpReqArg> args;
    args.reserve(5);
    args.emplace_back("callback_query_id", callbackQueryId);
    if (!text.empty()) {
        args.emplace_back("text", text);
    }
    if (showAlert) {
        args.emplace_back("show_alert", showAlert);
    }
    if (!url.empty()) {
        args.emplace_back("url", url);
    }
    if (cacheTime) {
        args.emplace_back("cache_time", cacheTime);
    }
    return sendRequest("answerCallbackQuery", args).get<bool>("", false);
}

Message::Ptr Api::editMessageText(const string& text, int64_t chatId, int32_t messageId, const string& inlineMessageId,
    const string& parseMode, bool disableWebPagePreview, const GenericReply::Ptr replyMarkup) const {

    vector<HttpReqArg> args;
    args.reserve(7);
    args.emplace_back("text", text);
    if (chatId) {
        args.emplace_back("chat_id", chatId);
    }
    if (messageId) {
        args.emplace_back("message_id", messageId);
    }
    if (!inlineMessageId.empty()) {
        args.emplace_back("inline_message_id", inlineMessageId);
    }
    if (!parseMode.empty()) {
        args.emplace_back("parse_mode", parseMode);
    }
    if (disableWebPagePreview) {
        args.emplace_back("disable_web_page_preview", disableWebPagePreview);
    }
    if (replyMarkup) {
        args.emplace_back("reply_markup", _tgTypeParser.parseGenericReply(replyMarkup));
    }
    ptree p = sendRequest("editMessageText", args);
    if (p.get_child_optional("message_id")) {
        return _tgTypeParser.parseJsonAndGetMessage(p);
    } else {
        return nullptr;
    }
}

Message::Ptr Api::editMessageCaption(int64_t chatId, int32_t messageId, const string& caption,
                                     const string& inlineMessageId, const GenericReply::Ptr replyMarkup) const {

    vector<HttpReqArg> args;
    args.reserve(5);
    if (chatId) {
        args.emplace_back("chat_id", chatId);
    }
    if (messageId) {
        args.emplace_back("message_id", messageId);
    }
    if (!caption.empty()) {
        args.emplace_back("caption", caption);
    }
    if (!inlineMessageId.empty()) {
        args.emplace_back("inline_message_id", inlineMessageId);
    }
    if (replyMarkup) {
        args.emplace_back("reply_markup", _tgTypeParser.parseGenericReply(replyMarkup));
    }
    ptree p = sendRequest("editMessageCaption", args);
    if (p.get_child_optional("message_id")) {
        return _tgTypeParser.parseJsonAndGetMessage(p);
    } else {
        return nullptr;
    }
}

Message::Ptr Api::editMessageReplyMarkup(int64_t chatId, int32_t messageId, const string& inlineMessageId,
                                         const GenericReply::Ptr replyMarkup) const {

    vector<HttpReqArg> args;
    args.reserve(4);
    if (chatId) {
        args.emplace_back("chat_id", chatId);
    }
    if (messageId) {
        args.emplace_back("message_id", messageId);
    }
    if (!inlineMessageId.empty()) {
        args.emplace_back("inline_message_id", inlineMessageId);
    }
    if (replyMarkup) {
        args.emplace_back("reply_markup", _tgTypeParser.parseGenericReply(replyMarkup));
    }
    ptree p = sendRequest("editMessageReplyMarkup", args);
    if (p.get_child_optional("message_id")) {
        return _tgTypeParser.parseJsonAndGetMessage(p);
    } else {
        return nullptr;
    }
}

Message::Ptr Api::editMessageMedia(InputMedia::Ptr media, int64_t chatId, int32_t messageId, const std::string& inlineMessageId,
                                  GenericReply::Ptr replyMarkup) const {

    vector<HttpReqArg> args;
    args.reserve(5);
    args.emplace_back("media", _tgTypeParser.parseInputMedia(media));
    if (chatId) {
        args.emplace_back("chat_id", chatId);
    }
    if (messageId) {
        args.emplace_back("message_id", messageId);
    }
    if (!inlineMessageId.empty()) {
        args.emplace_back("inline_message_id", inlineMessageId);
    }
    if (replyMarkup) {
        args.emplace_back("reply_markup", _tgTypeParser.parseGenericReply(replyMarkup));
    }
    ptree p = sendRequest("editMessageMedia", args);
    if (p.get_child_optional("message_id")) {
        return _tgTypeParser.parseJsonAndGetMessage(p);
    } else {
        return nullptr;
    }
}

ChatMember::Ptr Api::getChatMember(int64_t chatId, int32_t userId) const {
    vector<HttpReqArg> args;
    args.reserve(2);
    args.emplace_back("chat_id", chatId);
    args.emplace_back("user_id", userId);
    return _tgTypeParser.parseJsonAndGetChatMember(sendRequest("getChatMember", args));
}

vector<Update::Ptr> Api::getUpdates(int32_t offset, int32_t limit, int32_t timeout, const StringArrayPtr &allowedUpdates) const {
    vector<HttpReqArg> args;
    args.reserve(4);
    if (offset) {
        args.emplace_back("offset", offset);
    }
    limit = max(1, min(100, limit));
    args.emplace_back("limit", limit);
    if (timeout) {
        args.emplace_back("timeout", timeout);
    }
    if (allowedUpdates != nullptr) {
        string allowedUpdatesJson = _tgTypeParser.parseArray<string>(
            [](const string &s)->string {
            return s;
        }, *allowedUpdates);
        args.emplace_back("allowed_updates", allowedUpdatesJson);
    }
    return _tgTypeParser.parseJsonAndGetArray<Update>(&TgTypeParser::parseJsonAndGetUpdate, sendRequest("getUpdates", args));
}

void Api::setWebhook(const string& url, const InputFile::Ptr certificate, int32_t maxConnection, const StringArrayPtr &allowedUpdates) const {
    vector<HttpReqArg> args;
    args.reserve(4);
    if (!url.empty()) {
        args.emplace_back("url", url);
    }
    if (certificate != nullptr) {
        args.emplace_back("certificate", certificate->data, true, certificate->mimeType, certificate->fileName);
    }
    if (maxConnection != 40) {
        args.emplace_back("max_connections", maxConnection);
    }
    if (allowedUpdates != nullptr) {
        auto allowedUpdatesJson = _tgTypeParser.parseArray<string>(
            [](const string &s)->string {
                return s;
            }, *allowedUpdates);
        args.emplace_back("allowed_updates", allowedUpdatesJson);
    }

    sendRequest("setWebhook", args);
}

bool Api::deleteWebhook() const {
    return sendRequest("deleteWebhook").get<bool>("", false);
}

WebhookInfo::Ptr Api::getWebhookInfo() const {
    ptree p = sendRequest("getWebhookInfo");

    if (!p.get_child_optional("url")) {
        return nullptr;
    }
    if (p.get<string>("url","") != string("")) {
        return _tgTypeParser.parseJsonAndGetWebhookInfo(p);
    }
    else {
        return nullptr;
    }
}

bool Api::answerInlineQuery(const string& inlineQueryId, const std::vector<InlineQueryResult::Ptr>& results,
                            int32_t cacheTime, bool isPersonal, const string& nextOffset, const string& switchPmText, const string& switchPmParameter) const {
    vector<HttpReqArg> args;
    args.reserve(7);
    args.emplace_back("inline_query_id", inlineQueryId);
    string resultsJson = _tgTypeParser.parseArray<InlineQueryResult>(&TgTypeParser::parseInlineQueryResult, results);
    args.emplace_back("results", resultsJson);
    if (cacheTime) {
        args.emplace_back("cache_time", cacheTime);
    }
    if (isPersonal) {
        args.emplace_back("is_personal", isPersonal);
    }
    if (!nextOffset.empty()) {
        args.emplace_back("next_offset", nextOffset);
    }
    if (!switchPmText.empty()) {
        args.emplace_back("switch_pm_text", switchPmText);
    }
    if (!switchPmParameter.empty()) {
        args.emplace_back("switch_pm_parameter", switchPmParameter);
    }
    return sendRequest("answerInlineQuery", args).get<bool>("", false);
}

bool Api::kickChatMember(int64_t chatId, int32_t userId, uint64_t untilDate) const {
    vector<HttpReqArg> args;
    args.reserve(3);
    args.emplace_back("chat_id", chatId);
    args.emplace_back("user_id", userId);
    if (untilDate) {
        args.emplace_back("until_date", untilDate);
    }
    return sendRequest("kickChatMember", args).get<bool>("", false);
}

bool Api::unbanChatMember(int64_t chatId, int32_t userId) const {
    vector<HttpReqArg> args;
    args.reserve(2);
    args.emplace_back("chat_id", chatId);
    args.emplace_back("user_id", userId);
    return sendRequest("unbanChatMember", args).get<bool>("", false);
}

bool Api::restrictChatMember(int64_t chatId, int32_t userId, uint64_t untilDate, bool canSendMessages,
                             bool canSendMediaMessages, bool canSendOtherMessages, bool canAddWebPagePreviews) const {
    vector<HttpReqArg> args;
    args.reserve(7);
    args.emplace_back("chat_id", chatId);
    args.emplace_back("user_id", userId);
    if (untilDate) {
        args.emplace_back("until_date", untilDate);
    }
    if (canSendMessages) {
        args.emplace_back("can_send_messages", canSendMessages);
    }
    if (canSendMediaMessages) {
        args.emplace_back("can_send_media_messages", canSendMediaMessages);
    }
    if (canSendOtherMessages) {
        args.emplace_back("can_send_other_messages", canSendOtherMessages);
    }
    if (canAddWebPagePreviews) {
        args.emplace_back("can_add_web_page_previews", canAddWebPagePreviews);
    }
    return sendRequest("restrictChatMember", args).get<bool>("", false);
}

bool Api::promoteChatMember(int64_t chatId, int32_t userId, bool canChangeInfo, bool canPostMessages,
                            bool canEditMessages, bool canDeleteMessages, bool canInviteUsers, bool canPinMessages, bool canPromoteMembers) const {
    vector<HttpReqArg> args;
    args.reserve(9);
    args.emplace_back("chat_id", chatId);
    args.emplace_back("user_id", userId);
    if (canChangeInfo) {
        args.emplace_back("can_change_info", canChangeInfo);
    }
    if (canPostMessages) {
        args.emplace_back("can_post_messages", canPostMessages);
    }
    if (canEditMessages) {
        args.emplace_back("can_edit_messages", canEditMessages);
    }
    if (canDeleteMessages) {
        args.emplace_back("can_delete_messages", canDeleteMessages);
    }
    if (canInviteUsers) {
        args.emplace_back("can_invite_users", canInviteUsers);
    }
    if (canPinMessages) {
        args.emplace_back("can_pin_messages", canPinMessages);
    }
    if (canPromoteMembers) {
        args.emplace_back("can_promote_members", canPromoteMembers);
    }
    return sendRequest("promoteChatMember", args).get<bool>("", false);
}

string Api::exportChatInviteLink(int64_t chatId) const {
    vector<HttpReqArg> args;
    args.reserve(1);
    args.emplace_back("chat_id", chatId);
    return sendRequest("exportChatInviteLink", args).get("", "");
}

bool Api::setChatPhoto(int64_t chatId, const InputFile::Ptr photo) const {
    vector<HttpReqArg> args;
    args.reserve(2);
    args.emplace_back("chat_id", chatId);
    args.emplace_back("photo", photo->data, true, photo->mimeType, photo->fileName);
    return sendRequest("setChatPhoto", args).get<bool>("", false);
}

bool Api::deleteChatPhoto(int64_t chatId) const {
    vector<HttpReqArg> args;
    args.reserve(1);
    args.emplace_back("chat_id", chatId);
    return sendRequest("deleteChatPhoto", args).get<bool>("", false);
}

bool Api::setChatTitle(int64_t chatId, const string& title) const {
    vector<HttpReqArg> args;
    args.reserve(2);
    args.emplace_back("chat_id", chatId);
    args.emplace_back("title", title);
    return sendRequest("setChatTitle", args).get<bool>("", false);
}

bool Api::setChatDescription(int64_t chatId, const string& description) const {
    vector<HttpReqArg> args;
    args.reserve(2);
    args.emplace_back("chat_id", chatId);
    args.emplace_back("description", description);
    return sendRequest("setChatDescription", args).get<bool>("", false);
}

bool Api::pinChatMessage(int64_t chatId, int32_t messageId, bool disableNotification) const {
    vector<HttpReqArg> args;
    args.reserve(3);
    args.emplace_back("chat_id", chatId);
    args.emplace_back("message_id", messageId);
    if (disableNotification) {
        args.emplace_back("disable_notification", disableNotification);
    }
    return sendRequest("pinChatMessage", args).get<bool>("", false);
}

bool Api::unpinChatMessage(int64_t chatId) const {
    vector<HttpReqArg> args;
    args.reserve(1);
    args.emplace_back("chat_id", chatId);
    return sendRequest("unpinChatMessage", args).get<bool>("", false);
}

Message::Ptr Api::setGameScore(int32_t userId, int32_t score, bool force, bool disableEditMessage, int64_t chatId, int32_t messageId, const std::string& inlineMessageId) const {
    vector<HttpReqArg> args;
    args.reserve(7);
    args.emplace_back("user_id", userId);
    args.emplace_back("score", score);
    if (force) {
        args.emplace_back("force", force);
    }
    if (disableEditMessage) {
        args.emplace_back("disable_edit_message", disableEditMessage);
    }
    if (chatId){
        args.emplace_back("chat_id", chatId);
    }
    if (messageId){
        args.emplace_back("message_id", messageId);
    }
    if (!inlineMessageId.empty()){
        args.emplace_back("inline_message_id", inlineMessageId);
    }
    return _tgTypeParser.parseJsonAndGetMessage(sendRequest("setGameScore", args));
}

vector<GameHighScore::Ptr> Api::getGameHighScores(int32_t userId, int32_t score, bool force, bool disableEditMessage, int64_t chatId, int32_t messageId, const std::string& inlineMessageId) const {
    vector<HttpReqArg> args;
    args.reserve(7);
    args.emplace_back("user_id", userId);
    args.emplace_back("score", score);
    if (force) {
        args.emplace_back("force", force);
    }
    if (disableEditMessage) {
        args.emplace_back("disable_edit_message", disableEditMessage);
    }
    if (chatId) {
        args.emplace_back("chat_id", chatId);
    }
    if (messageId) {
        args.emplace_back("message_id", messageId);
    }
    if (!inlineMessageId.empty()){
        args.emplace_back("inline_message_id", inlineMessageId);
    }
    return _tgTypeParser.parseJsonAndGetArray<GameHighScore>(&TgTypeParser::parseJsonAndGetGameHighScore, sendRequest("getGameHighScores", args));
}

void Api::deleteMessage(int64_t chatId, int32_t messageId) const {
    sendRequest("deleteMessage", { HttpReqArg("chat_id", chatId), HttpReqArg("message_id", messageId) });
}

ptree Api::sendRequest(const string& method, const vector<HttpReqArg>& args) const {
    string url = "https://api.telegram.org/bot";
    url += _token;
    url += "/";
    url += method;

    string serverResponse = _httpClient.makeRequest(url, args);
    if (!serverResponse.compare(0, 6, "<html>")) {
        throw TgException("tgbot-cpp library have got html page instead of json response. Maybe you entered wrong bot token.");
    }

    ptree result = _tgTypeParser.parseJson(serverResponse);
    try {
        if (result.get<bool>("ok", false)) {
            return result.get_child("result");
        } else {
            throw TgException(result.get("description", ""));
        }
    } catch (boost::property_tree::ptree_error& e) {
        throw TgException("tgbot-cpp library can't parse json response. " + string(e.what()));
    }
}

string Api::downloadFile(const string& filePath, const std::vector<HttpReqArg>& args) const {
    string url = "https://api.telegram.org/file/bot";
    url += _token;
    url += "/";
    url += filePath;

    string serverResponse = _httpClient.makeRequest(url, args);

    return serverResponse;
}

}
