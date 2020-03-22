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
