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

#include "Api.h"

#include <boost/property_tree/json_parser.hpp>

#include "tgbot/Bot.h"
#include "tgbot/TgException.h"

using namespace std;
using namespace boost::property_tree;

namespace TgBot {

Api::Api(Bot* const bot) : _bot(bot) {
}

User::Ptr Api::getMe() const {
    return _bot->getParser().parseUser(sendRequest("getMe").find("result")->second);
}

Message::Ptr Api::sendMessage(int32_t chatId, const string& text, bool disableWebPagePreview, int32_t replyToMessageId, const GenericReply::Ptr& replyMarkup) const {
    vector<Http::Argument> args;
    args.push_back(Http::Argument("chat_id", chatId));
    args.push_back(Http::Argument("text", text));
    if (disableWebPagePreview) {
        args.push_back(Http::Argument("disable_web_page_preview", disableWebPagePreview));
    }
    if (replyToMessageId) {
        args.push_back(Http::Argument("reply_to_message_id", replyToMessageId));
    }
    if (replyMarkup) {
        args.push_back(Http::Argument("reply_markup", _bot->getParser().parseGenericReply(replyMarkup)));
    }
    return _bot->getParser().parseMessage(sendRequest("sendMessage", args).find("result")->second);
}

Message::Ptr Api::forwardMessage(int32_t chatId, int32_t fromChatId, int32_t messageId) const {
    vector<Http::Argument> args;
    args.push_back(Http::Argument("chat_id", chatId));
    args.push_back(Http::Argument("from_chat_id", fromChatId));
    args.push_back(Http::Argument("message_id", messageId));
    return _bot->getParser().parseMessage(sendRequest("forwardMessage", args).find("result")->second);
}

Message::Ptr Api::sendPhoto(int32_t chatId, const InputFile::Ptr& photo, const string& caption, int32_t replyToMessageId, const GenericReply::Ptr& replyMarkup) const {
    vector<Http::Argument> args;
    args.push_back(Http::Argument("chat_id", chatId));
    args.push_back(Http::Argument("photo", photo->data, true, photo->mimeType));
    if (!caption.empty()) {
        args.push_back(Http::Argument("caption", caption));
    }
    if (replyToMessageId) {
        args.push_back(Http::Argument("reply_to_message_id", replyToMessageId));
    }
    if (replyMarkup) {
        args.push_back(Http::Argument("reply_markup", _bot->getParser().parseGenericReply(replyMarkup)));
    }
    return _bot->getParser().parseMessage(sendRequest("sendPhoto", args).find("result")->second);
}

Message::Ptr Api::sendPhoto(int32_t chatId, const string& photo, const string& caption, int32_t replyToMessageId, const GenericReply::Ptr& replyMarkup) const {
    vector<Http::Argument> args;
    args.push_back(Http::Argument("chat_id", chatId));
    args.push_back(Http::Argument("photo", photo));
    if (!caption.empty()) {
        args.push_back(Http::Argument("caption", caption));
    }
    if (replyToMessageId) {
        args.push_back(Http::Argument("reply_to_message_id", replyToMessageId));
    }
    if (replyMarkup) {
        args.push_back(Http::Argument("reply_markup", _bot->getParser().parseGenericReply(replyMarkup)));
    }
    return _bot->getParser().parseMessage(sendRequest("sendPhoto", args).find("result")->second);
}

Message::Ptr Api::sendAudio(int32_t chatId, const InputFile::Ptr& audio, int32_t replyToMessageId, const GenericReply::Ptr& replyMarkup) const {
    vector<Http::Argument> args;
    args.push_back(Http::Argument("chat_id", chatId));
    args.push_back(Http::Argument("audio", audio->data, true, audio->mimeType));
    if (replyToMessageId) {
        args.push_back(Http::Argument("reply_to_message_id", replyToMessageId));
    }
    if (replyMarkup) {
        args.push_back(Http::Argument("reply_markup", _bot->getParser().parseGenericReply(replyMarkup)));
    }
    return _bot->getParser().parseMessage(sendRequest("sendAudio", args).find("result")->second);
}

Message::Ptr Api::sendAudio(int32_t chatId, const string& audio, int32_t replyToMessageId, const GenericReply::Ptr& replyMarkup) const {
    vector<Http::Argument> args;
    args.push_back(Http::Argument("chat_id", chatId));
    args.push_back(Http::Argument("audio", audio));
    if (replyToMessageId) {
        args.push_back(Http::Argument("reply_to_message_id", replyToMessageId));
    }
    if (replyMarkup) {
        args.push_back(Http::Argument("reply_markup", _bot->getParser().parseGenericReply(replyMarkup)));
    }
    return _bot->getParser().parseMessage(sendRequest("sendAudio", args).find("result")->second);
}

Message::Ptr Api::sendDocument(int32_t chatId, const InputFile::Ptr& document, int32_t replyToMessageId, const GenericReply::Ptr& replyMarkup) const {
    vector<Http::Argument> args;
    args.push_back(Http::Argument("chat_id", chatId));
    args.push_back(Http::Argument("document", document->data, true, document->mimeType));
    if (replyToMessageId) {
        args.push_back(Http::Argument("reply_to_message_id", replyToMessageId));
    }
    if (replyMarkup) {
        args.push_back(Http::Argument("reply_markup", _bot->getParser().parseGenericReply(replyMarkup)));
    }
    return _bot->getParser().parseMessage(sendRequest("sendDocument", args).find("result")->second);
}

Message::Ptr Api::sendDocument(int32_t chatId, const string& document, int32_t replyToMessageId, const GenericReply::Ptr& replyMarkup) const {
    vector<Http::Argument> args;
    args.push_back(Http::Argument("chat_id", chatId));
    args.push_back(Http::Argument("document", document));
    if (replyToMessageId) {
        args.push_back(Http::Argument("reply_to_message_id", replyToMessageId));
    }
    if (replyMarkup) {
        args.push_back(Http::Argument("reply_markup", _bot->getParser().parseGenericReply(replyMarkup)));
    }
    return _bot->getParser().parseMessage(sendRequest("sendDocument", args).find("result")->second);
}

Message::Ptr Api::sendSticker(int32_t chatId, const InputFile::Ptr& sticker, int32_t replyToMessageId, const GenericReply::Ptr& replyMarkup) const {
    vector<Http::Argument> args;
    args.push_back(Http::Argument("chat_id", chatId));
    args.push_back(Http::Argument("sticker", sticker->data, true, sticker->mimeType));
    if (replyToMessageId) {
        args.push_back(Http::Argument("reply_to_message_id", replyToMessageId));
    }
    if (replyMarkup) {
        args.push_back(Http::Argument("reply_markup", _bot->getParser().parseGenericReply(replyMarkup)));
    }
    return _bot->getParser().parseMessage(sendRequest("sendSticker", args).find("result")->second);
}

Message::Ptr Api::sendSticker(int32_t chatId, const string& sticker, int32_t replyToMessageId, const GenericReply::Ptr& replyMarkup) const {
    vector<Http::Argument> args;
    args.push_back(Http::Argument("chat_id", chatId));
    args.push_back(Http::Argument("sticker", sticker));
    if (replyToMessageId) {
        args.push_back(Http::Argument("reply_to_message_id", replyToMessageId));
    }
    if (replyMarkup) {
        args.push_back(Http::Argument("reply_markup", _bot->getParser().parseGenericReply(replyMarkup)));
    }
    return _bot->getParser().parseMessage(sendRequest("sendSticker", args).find("result")->second);
}

Message::Ptr Api::sendVideo(int32_t chatId, const InputFile::Ptr& video, int32_t replyToMessageId, const GenericReply::Ptr& replyMarkup) const {
    vector<Http::Argument> args;
    args.push_back(Http::Argument("chat_id", chatId));
    args.push_back(Http::Argument("video", video->data, true, video->mimeType));
    if (replyToMessageId) {
        args.push_back(Http::Argument("reply_to_message_id", replyToMessageId));
    }
    if (replyMarkup) {
        args.push_back(Http::Argument("reply_markup", _bot->getParser().parseGenericReply(replyMarkup)));
    }
    return _bot->getParser().parseMessage(sendRequest("sendVideo", args).find("result")->second);
}

Message::Ptr Api::sendVideo(int32_t chatId, const string& video, int32_t replyToMessageId, const GenericReply::Ptr& replyMarkup) const {
    vector<Http::Argument> args;
    args.push_back(Http::Argument("chat_id", chatId));
    args.push_back(Http::Argument("video", video));
    if (replyToMessageId) {
        args.push_back(Http::Argument("reply_to_message_id", replyToMessageId));
    }
    if (replyMarkup) {
        args.push_back(Http::Argument("reply_markup", _bot->getParser().parseGenericReply(replyMarkup)));
    }
    return _bot->getParser().parseMessage(sendRequest("sendVideo", args).find("result")->second);
}

Message::Ptr Api::sendLocation(int32_t chatId, float latitude, float longitude, int32_t replyToMessageId, const GenericReply::Ptr& replyMarkup) const {
    vector<Http::Argument> args;
    args.push_back(Http::Argument("chat_id", chatId));
    args.push_back(Http::Argument("latitude", latitude));
    args.push_back(Http::Argument("longitude", longitude));
    if (replyToMessageId) {
        args.push_back(Http::Argument("reply_to_message_id", replyToMessageId));
    }
    if (replyMarkup) {
        args.push_back(Http::Argument("reply_markup", _bot->getParser().parseGenericReply(replyMarkup)));
    }
    return _bot->getParser().parseMessage(sendRequest("sendLocation", args).find("result")->second);
}

void Api::sendChatAction(int32_t chatId, const string& action) const {
    vector<Http::Argument> args;
    args.push_back(Http::Argument("chat_id", chatId));
    args.push_back(Http::Argument("action", action));
    sendRequest("sendChatAction", args);
}

UserProfilePhotos::Ptr Api::getUserProfilePhotos(int32_t userId, int32_t offset, int32_t limit) const {
    vector<Http::Argument> args;
    args.push_back(Http::Argument("user_id", userId));
    if (offset) {
        args.push_back(Http::Argument("offset", offset));
    }
    limit = max(1, min(100, limit));
    args.push_back(Http::Argument("limit", limit));
    return _bot->getParser().parseUserProfilePhotos(sendRequest("getUserProfilePhotos", args).find("result")->second);
}

vector<Update::Ptr> Api::getUpdates(int32_t offset, int32_t limit, int32_t timeout) const {
    vector<Http::Argument> args;
    if (offset) {
        args.push_back(Http::Argument("offset", offset));
    }
    limit = max(1, min(100, limit));
    args.push_back(Http::Argument("limit", limit));
    if (timeout) {
        args.push_back(Http::Argument("timeout", timeout));
    }
    return _bot->getParser().parseArray<Update>(_bot->getParser().parseUpdate, sendRequest("getUpdates", args), "result");
}

void Api::setWebhook(const string& url) const {
    vector<Http::Argument> args;
    args.push_back(Http::Argument("url", url));
    sendRequest("setWebhook", args);
}

boost::property_tree::ptree Api::sendRequest(const std::string& method, const std::vector<Http::Argument>& args) const {
    std::string url = "https://api.telegram.org/bot";
    url += _bot->getToken();
    url += "/";
    url += method;
    try {
        ptree result = _bot->getParser().parseJson(_bot->getHttp().makeRequest(url, args));
        if (result.get<bool>("ok")) {
            return result;
        } else {
            throw TgException(result.get("description", ""));
        }
    } catch (boost::property_tree::ptree_error& e) {
        return ptree();
    }
}

}
