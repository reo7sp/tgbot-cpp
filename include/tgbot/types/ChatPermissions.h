#ifndef TGBOT_CHATPERMISSIONS_H
#define TGBOT_CHATPERMISSIONS_H

#include <memory>

namespace TgBot {

/**
 * @brief Describes actions that a non-administrator user is allowed to take in a chat.
 *
 * @ingroup types
 */
class ChatPermissions {

public:
    typedef std::shared_ptr<ChatPermissions> Ptr;

    /**
     * @brief Optional. True, if the user is allowed to send text messages, contacts, giveaways, giveaway winners, invoices, locations and venues
     */
    bool canSendMessages;

    /**
     * @brief Optional. True, if the user is allowed to send audios
     */
    bool canSendAudios;

    /**
     * @brief Optional. True, if the user is allowed to send documents
     */
    bool canSendDocuments;

    /**
     * @brief Optional. True, if the user is allowed to send photos
     */
    bool canSendPhotos;

    /**
     * @brief Optional. True, if the user is allowed to send videos
     */
    bool canSendVideos;

    /**
     * @brief Optional. True, if the user is allowed to send video notes
     */
    bool canSendVideoNotes;

    /**
     * @brief Optional. True, if the user is allowed to send voice notes
     */
    bool canSendVoiceNotes;

    /**
     * @brief Optional. True, if the user is allowed to send polls
     */
    bool canSendPolls;

    /**
     * @brief Optional. True, if the user is allowed to send animations, games, stickers and use inline bots
     */
    bool canSendOtherMessages;

    /**
     * @brief Optional. True, if the user is allowed to add web page previews to their messages
     */
    bool canAddWebPagePreviews;

    /**
     * @brief Optional. True, if the user is allowed to change the chat title, photo and other settings.
     *
     * Ignored in public supergroups
     */
    bool canChangeInfo;

    /**
     * @brief Optional. True, if the user is allowed to invite new users to the chat
     */
    bool canInviteUsers;

    /**
     * @brief Optional. True, if the user is allowed to pin messages.
     *
     * Ignored in public supergroups
     */
    bool canPinMessages;

    /**
     * @brief Optional. True, if the user is allowed to create forum topics.
     *
     * If omitted defaults to the value of canPinMessages
     */
    bool canManageTopics;
};
}

#endif //TGBOT_CHATPERMISSIONS_H
