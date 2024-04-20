#ifndef TGBOT_CHATMEMBERRESTRICTED_H
#define TGBOT_CHATMEMBERRESTRICTED_H

#include "tgbot/types/ChatMember.h"

#include <cstdint>
#include <memory>

namespace TgBot {

/**
 * @brief Represents a [chat member](https://core.telegram.org/bots/api#chatmember) that is under certain restrictions in the chat.
 *
 * Supergroups only.
 *
 * @ingroup types
 */
class ChatMemberRestricted : public ChatMember {

public:
    static const std::string STATUS;

    typedef std::shared_ptr<ChatMemberRestricted> Ptr;

    ChatMemberRestricted() {
        this->status = STATUS;
    }

    /**
     * @brief True, if the user is a member of the chat at the moment of the request
     */
    bool isMember;

    /**
     * @brief True, if the user is allowed to send text messages, contacts, giveaways, giveaway winners, invoices, locations and venues
     */
    bool canSendMessages;

    /**
     * @brief True, if the user is allowed to send audios
     */
    bool canSendAudios;

    /**
     * @brief True, if the user is allowed to send documents
     */
    bool canSendDocuments;

    /**
     * @brief True, if the user is allowed to send photos
     */
    bool canSendPhotos;

    /**
     * @brief True, if the user is allowed to send videos
     */
    bool canSendVideos;

    /**
     * @brief True, if the user is allowed to send video notes
     */
    bool canSendVideoNotes;

    /**
     * @brief True, if the user is allowed to send voice notes
     */
    bool canSendVoiceNotes;

    /**
     * @brief True, if the user is allowed to send polls
     */
    bool canSendPolls;

    /**
     * @brief True, if the user is allowed to send animations, games, stickers and use inline bots
     */
    bool canSendOtherMessages;

    /**
     * @brief True, if the user is allowed to add web page previews to their messages
     */
    bool canAddWebPagePreviews;

    /**
     * @brief True, if the user is allowed to change the chat title, photo and other settings
     */
    bool canChangeInfo;

    /**
     * @brief True, if the user is allowed to invite new users to the chat
     */
    bool canInviteUsers;

    /**
     * @brief True, if the user is allowed to pin messages
     */
    bool canPinMessages;

    /**
     * @brief True, if the user is allowed to create forum topics
     */
    bool canManageTopics;

    /**
     * @brief Date when restrictions will be lifted for this user; Unix time.
     *
     * If 0, then the user is restricted forever
     */
    std::uint32_t untilDate;
};
}

#endif //TGBOT_CHATMEMBERRESTRICTED_H
