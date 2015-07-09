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

#ifndef TGBOT_CPP_API_H
#define TGBOT_CPP_API_H

#include <string>
#include <vector>

#include <boost/property_tree/ptree.hpp>

#include "tgbot/net/HttpReqArg.h"
#include "tgbot/types/User.h"
#include "tgbot/types/Message.h"
#include "tgbot/types/GenericReply.h"
#include "tgbot/types/InputFile.h"
#include "tgbot/types/UserProfilePhotos.h"
#include "tgbot/types/Update.h"

namespace TgBot {

class Bot;

class Api {

friend Bot;

public:
    Api(const std::string& token);

    User::Ptr getMe() const;
    Message::Ptr sendMessage(int32_t chatId, const std::string& text, bool disableWebPagePreview = false, int32_t replyToMessageId = 0, const GenericReply::Ptr& replyMarkup = GenericReply::Ptr()) const;
    Message::Ptr forwardMessage(int32_t chatId, int32_t fromChatId, int32_t messageId) const;
    Message::Ptr sendPhoto(int32_t chatId, const InputFile::Ptr& photo, const std::string& caption = "", int32_t replyToMessageId = 0, const GenericReply::Ptr& replyMarkup = GenericReply::Ptr()) const;
    Message::Ptr sendPhoto(int32_t chatId, const std::string& photo, const std::string& caption = "", int32_t replyToMessageId = 0, const GenericReply::Ptr& replyMarkup = GenericReply::Ptr()) const;
    Message::Ptr sendAudio(int32_t chatId, const InputFile::Ptr& audio, int32_t replyToMessageId = 0, const GenericReply::Ptr& replyMarkup = GenericReply::Ptr()) const;
    Message::Ptr sendAudio(int32_t chatId, const std::string& audio, int32_t replyToMessageId = 0, const GenericReply::Ptr& replyMarkup = GenericReply::Ptr()) const;
    Message::Ptr sendDocument(int32_t chatId, const InputFile::Ptr& document, int32_t replyToMessageId = 0, const GenericReply::Ptr& replyMarkup = GenericReply::Ptr()) const;
    Message::Ptr sendDocument(int32_t chatId, const std::string& document, int32_t replyToMessageId = 0, const GenericReply::Ptr& replyMarkup = GenericReply::Ptr()) const;
    Message::Ptr sendSticker(int32_t chatId, const InputFile::Ptr& sticker, int32_t replyToMessageId = 0, const GenericReply::Ptr& replyMarkup = GenericReply::Ptr()) const;
    Message::Ptr sendSticker(int32_t chatId, const std::string& sticker, int32_t replyToMessageId = 0, const GenericReply::Ptr& replyMarkup = GenericReply::Ptr()) const;
    Message::Ptr sendVideo(int32_t chatId, const InputFile::Ptr& video, int32_t replyToMessageId = 0, const GenericReply::Ptr& replyMarkup = GenericReply::Ptr()) const;
    Message::Ptr sendVideo(int32_t chatId, const std::string& video, int32_t replyToMessageId = 0, const GenericReply::Ptr& replyMarkup = GenericReply::Ptr()) const;
    Message::Ptr sendLocation(int32_t chatId, float latitude, float longitude, int32_t replyToMessageId = 0, const GenericReply::Ptr& replyMarkup = GenericReply::Ptr()) const;
    void sendChatAction(int32_t chatId, const std::string& action) const;
    UserProfilePhotos::Ptr getUserProfilePhotos(int32_t userId, int32_t offset = 0, int32_t limit = 100) const;
    std::vector<Update::Ptr> getUpdates(int32_t offset = 0, int32_t limit = 100, int32_t timeout = 0) const;
    void setWebhook(const std::string& url = "") const;

private:
    boost::property_tree::ptree sendRequest(const std::string& method, const std::vector<HttpReqArg>& args = std::vector<HttpReqArg>()) const;

    const std::string _token;
};

}

#endif //TGBOT_CPP_API_H
