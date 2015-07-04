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

#ifndef TGBOT_CPP_MESSAGE_H
#define TGBOT_CPP_MESSAGE_H

#include <string>
#include <vector>
#include <memory>

#include "tgbot/types/User.h"
#include "tgbot/types/GenericChat.h"
#include "tgbot/types/Message.h"
#include "tgbot/types/Audio.h"
#include "tgbot/types/Document.h"
#include "tgbot/types/Sticker.h"
#include "tgbot/types/Video.h"
#include "tgbot/types/Contact.h"
#include "tgbot/types/Location.h"
#include "tgbot/types/PhotoSize.h"

namespace TgBot {

class Message {

public:
    typedef std::shared_ptr<Message> Ptr;

    int32_t messageId;
    User::Ptr from;
    int32_t date;
    GenericChat::Ptr chat;
    User::Ptr forwardFrom;
    int32_t forwardDate;
    Message::Ptr replyToMessage;
    std::string text;
    Audio::Ptr audio;
    Document::Ptr document;
    std::vector<PhotoSize::Ptr> photo;
    Sticker::Ptr sticker;
    Video::Ptr video;
    Contact::Ptr contact;
    Location::Ptr location;
    User::Ptr newChatParticipant;
    User::Ptr leftChatParticipant;
    std::string newChatTitle;
    std::vector<PhotoSize::Ptr> newChatPhoto;
    bool deleteChatPhoto;
    bool groupChatCreated;
};

}

#endif //TGBOT_CPP_MESSAGE_H
