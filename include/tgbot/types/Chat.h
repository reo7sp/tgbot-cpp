#ifndef TGBOT_CPP_CHAT_H
#define TGBOT_CPP_CHAT_H

#include "tgbot/types/ChatPhoto.h"
#include "tgbot/types/ChatPermissions.h"

#include <cstdint>
#include <string>
#include <memory>

namespace TgBot {

class Message;
/**
 * @brief This object represents a chat.
 *
 * @ingroup types
 */
class Chat {

public:
    typedef std::shared_ptr<Chat> Ptr;

    /**
     * @brief Enum of possible types of a chat.
     */
    enum class Type {
        Private, Group, Supergroup, Channel
    };

    /**
     * @brief Unique identifier for this chat.
     * 
     * This number may be greater than 32 bits and some programming languages may have difficulty/silent defects in interpreting it.
     * But it is smaller than 52 bits, so a signed 64 bit integer or double-precision float type are safe for storing this identifier.
     */
    std::int64_t id;

    /**
     * @brief Type of chat, can be either “private”, “group”, “supergroup” or “channel”
     */
    Type type;

    /**
     * @brief Optional. Title, for supergroups, channels and group chats
     */
    std::string title;

    /**
     * @brief Optional. Username, for private chats, supergroups and channels if available
     */
    std::string username;

    /**
     * @brief Optional. First name of the other party in a private chat
     */
    std::string firstName;

    /**
     * @brief Optional. Last name of the other party in a private chat
     */
    std::string lastName;

    /**
     * @brief Optional. Chat photo.
     * Returned only in @ref Api::getChat.
     */
    ChatPhoto::Ptr photo;

    /**
     * @brief Optional. Description, for groups, supergroups and channel chats.
     * Returned only in @ref Api::getChat.
     */
    std::string description;

    /**
     * @brief Optional. Chat invite link, for groups, supergroups and channel chats.
     * Each administrator in a chat generates their own invite links, so the bot must first generate the link using @ref Api::exportChatInviteLink.
     * Returned only in @ref Api::getChat.
     */
    std::string inviteLink;

    /**
     * @brief Optional. Pinned message, for groups, supergroups and channels.
     * Returned only in @ref Api::getChat.
     */
    std::shared_ptr<Message> pinnedMessage;

    /**
     * @brief Optional. Default chat member permissions, for groups and supergroups.
     * Returned only in @ref Api::getChat.
     */
    ChatPermissions::Ptr permissions;

    /**
     * @brief Optional. For supergroups, the minimum allowed delay between consecutive messages sent by each unpriviledged user.
     * Returned only in @ref Api::getChat.
     */
    std::int32_t slowModeDelay;

    /**
     * @brief Optional. For supergroups, name of group sticker set.
     * Returned only in @ref Api::getChat.
     */
    std::string stickerSetName;

    /**
     * @brief Optional. True, if the bot can change the group sticker set.
     * Returned only in @ref Api::getChat.
     */
    bool canSetStickerSet;
};
}

#endif //TGBOT_CPP_CHAT_H
