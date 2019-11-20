/*
 * Copyright (c) 2019 Marcel Alexandru
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

#ifndef TGBOT_CPP_CHATPERMISSIONS_H
#define TGBOT_CPP_CHATPERMISSIONS_H

#include <memory>
#include <string>


namespace TgBot {

    /**
     * @brief This object describes actions that a non-administrator user is allowed to take in a chat.
     * @ingroup types
     */

    class ChatPermissions {
    public:
        typedef std::shared_ptr<ChatPermissions> Ptr;

        /**
         * @brief Optional. True, if the user is allowed to send text messages, contacts, locations and venues.
         */
        bool canSendMessages = false;

        /**
         * @brief Optional. True, if the user is allowed to send audios, documents, photos, videos, video notes and voice notes, implies can_send_messages.
         */
        bool canSendMediaMessages = false;

        /**
         * @brief Optional. True, if the user is allowed to send polls, implies can_send_messages.
         */
        bool canSendPolls = false;

        /**
         * @brief Optional. True, if the user is allowed to send animations, games, stickers and use inline bots, implies can_send_media_messages.
         */
        bool canSendOtherMessages = false;

        /**
         * @brief Optional. True, if the user is allowed to add web page previews to their messages, implies can_send_media_messages.
         */
        bool canAddWebPagePreviews = false;

        /**
         * @brief Optional. True, if the user is allowed to change the chat title, photo and other settings. Ignored in public supergroups.
         */
        bool canChangeInfo = false;

        /**
         * @brief Optional. True, if the user is allowed to invite new users to the chat.
         */
        bool canInviteUsers = false;

        /**
         * @brief Optional. True, if the user is allowed to pin messages. Ignored in public supergroups.
         */
        bool canPinMessages = false;



    };
}

#endif //TGBOT_CPP_CHATPERMISSIONS_H
