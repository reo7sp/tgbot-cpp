#ifndef TGBOT_CHAT_H
#define TGBOT_CHAT_H

#include "tgbot/types/ChatPhoto.h"
#include "tgbot/types/ChatPermissions.h"
#include "tgbot/types/ChatLocation.h"

#include <cstdint>
#include <memory>
#include <string>
#include <vector>

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
     * This number may have more than 32 significant bits and some programming languages may have difficulty/silent defects in interpreting it.
     * But it has at most 52 significant bits, so a signed 64-bit integer or double-precision float type are safe for storing this identifier.
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
     * @brief Optional. True, if the supergroup chat is a forum (has topics enabled)
     */
    bool isForum;

    /**
     * @brief Optional. Chat photo.
     * 
     * Returned only in Api::getChat.
     */
    ChatPhoto::Ptr photo;

    /**
     * @brief Optional. If non-empty, the list of all active chat usernames; for private chats, supergroups and channels.
     * 
     * Returned only in Api::getChat.
     */
    std::vector<std::string> activeUsernames;

    /**
     * @brief Optional. Custom emoji identifier of emoji status of the other party in a private chat.
     * 
     * Returned only in Api::getChat.
     */
    std::string emojiStatusCustomEmojiId;

    /**
     * @brief Optional. Bio of the other party in a private chat.
     * 
     * Returned only in Api::getChat.
     */
    std::string bio;

    /**
     * @brief Optional. True, if privacy settings of the other party in the private chat allows to use tg://user?id=<user_id> links only in chats with the user.
     * 
     * Returned only in Api::getChat.
     */
    bool hasPrivateForwards;

    /**
     * @brief Optional. True, if the privacy settings of the other party restrict sending voice and video note messages in the private chat.
     * 
     * Returned only in Api::getChat.
     */
    bool hasRestrictedVoiceAndVideoMessages;

    /**
     * @brief Optional. True, if users need to join the supergroup before they can send messages.
     * 
     * Returned only in Api::getChat.
     */
    bool joinToSendMessages;

    /**
     * @brief Optional. True, if all users directly joining the supergroup need to be approved by supergroup administrators.
     * 
     * Returned only in Api::getChat.
     */
    bool joinByRequest;

    /**
     * @brief Optional. Description, for groups, supergroups and channel chats.
     * 
     * Returned only in Api::getChat.
     */
    std::string description;

    /**
     * @brief Optional. Primary invite link, for groups, supergroups and channel chats.
     * 
     * Returned only in Api::getChat.
     */
    std::string inviteLink;

    /**
     * @brief Optional. The most recent pinned message (by sending date).
     * 
     * Returned only in Api::getChat.
     */
    std::shared_ptr<Message> pinnedMessage;

    /**
     * @brief Optional. Default chat member permissions, for groups and supergroups.
     * 
     * Returned only in Api::getChat.
     */
    ChatPermissions::Ptr permissions;

    /**
     * @brief Optional. For supergroups, the minimum allowed delay between consecutive messages sent by each unpriviledged user; in seconds.
     * 
     * Returned only in Api::getChat.
     */
    std::int32_t slowModeDelay;

    /**
     * @brief Optional. The time after which all messages sent to the chat will be automatically deleted; in seconds.
     * 
     * Returned only in Api::getChat.
     */
    std::int32_t messageAutoDeleteTime;

    /**
     * @brief Optional. True, if aggressive anti-spam checks are enabled in the supergroup.
     * 
     * The field is only available to chat administrators.
     * Returned only in Api::getChat.
     */
    bool hasAggressiveAntiSpamEnabled;

    /**
     * @brief Optional. True, if non-administrators can only get the list of bots and administrators in the chat.
     * 
     * Returned only in Api::getChat.
     */
    bool hasHiddenMembers;

    /**
     * @brief Optional. True, if messages from the chat can't be forwarded to other chats.
     * 
     * Returned only in Api::getChat.
     */
    bool hasProtectedContent;

    /**
     * @brief Optional. For supergroups, name of group sticker set.
     * 
     * Returned only in Api::getChat.
     */
    std::string stickerSetName;

    /**
     * @brief Optional. True, if the bot can change the group sticker set.
     * 
     * Returned only in Api::getChat.
     */
    bool canSetStickerSet;

    /**
     * @brief Optional. Unique identifier for the linked chat, i.e. the discussion group identifier for a channel and vice versa; for supergroups and channel chats.
     * 
     * This identifier may be greater than 32 bits and some programming languages may have difficulty/silent defects in interpreting it.
     * But it is smaller than 52 bits, so a signed 64 bit integer or double-precision float type are safe for storing this identifier.
     * Returned only in Api::getChat.
     */
    std::int64_t linkedChatId;

    /**
     * @brief Optional. For supergroups, the location to which the supergroup is connected.
     * 
     * Returned only in Api::getChat.
     */
    ChatLocation::Ptr location;
};
}

#endif //TGBOT_CHAT_H
