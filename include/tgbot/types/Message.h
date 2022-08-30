#ifndef TGBOT_CPP_MESSAGE_H
#define TGBOT_CPP_MESSAGE_H

#include "tgbot/types/Chat.h"
#include "tgbot/types/User.h"
#include "tgbot/types/Message.h"
#include "tgbot/types/Audio.h"
#include "tgbot/types/Document.h"
#include "tgbot/types/Animation.h"
#include "tgbot/types/Sticker.h"
#include "tgbot/types/Poll.h"
#include "tgbot/types/Dice.h"
#include "tgbot/types/Video.h"
#include "tgbot/types/Contact.h"
#include "tgbot/types/Location.h"
#include "tgbot/types/Game.h"
#include "tgbot/types/PhotoSize.h"
#include "tgbot/types/MessageEntity.h"
#include "tgbot/types/Venue.h"
#include "tgbot/types/Voice.h"
#include "tgbot/types/VideoNote.h"
#include "tgbot/types/Invoice.h"
#include "tgbot/types/SuccessfulPayment.h"
#include "tgbot/types/InlineKeyboardMarkup.h"

#include <cstdint>
#include <string>
#include <vector>
#include <memory>

namespace TgBot {

/**
 * @brief This object represents a message.
 *
 * @ingroup types
 */
class Message {
public:
    typedef std::shared_ptr<Message> Ptr;

    /**
     * @brief Unique message identifier inside this chat
     */
    std::int32_t messageId;

    /**
     * @brief Optional. Sender, empty for messages sent to channels
     */
    User::Ptr from;

    /**
     * @brief Date the message was sent in Unix time
     */
    std::int32_t date;

    /**
     * @brief Conversation the message belongs to
     */
    Chat::Ptr chat;

    /**
     * @brief Optional. For forwarded messages, sender of the original message
     */
    User::Ptr forwardFrom;

    /**
     * @brief Optional. For messages forwarded from channels, information about the original channel
     */
    Chat::Ptr forwardFromChat;

    /**
     * @brief Optional. For messages forwarded from channels, identifier of the original message in the channel
     */
    std::int32_t forwardFromMessageId;

    /**
     * @brief Optional. For messages forwarded from channels, signature of the post author if present
     */
    std::string forwardSignature;

    /**
     * @brief Optional. Sender's name for messages forwarded from users who disallow adding a link to their account in forwarded messages
     */
    std::string forwardSenderName;

    /**
     * @brief Optional. For forwarded messages, date the original message was sent in Unix time
     */
    std::int32_t forwardDate;

    /**
     * @brief Optional. For replies, the original message.
     * Note that the Message object in this field will not contain further @ref Message::replyToMessage fields even if it itself is a reply.
     */
    Message::Ptr replyToMessage;

    /**
     * @brief Optional. Bot through which the message was sent
     */
    User::Ptr viaBot;

    /**
     * @brief Optional. Date the message was last edited in Unix time
     */
    std::int32_t editDate;

    /**
     * @brief Optional. The unique identifier of a media message group this message belongs to
     */
    std::string mediaGroupId;
    
    /**
     * @brief Optional. Signature of the post author for messages in channels
     */
    std::string authorSignature;

    /**
     * @brief Optional. For text messages, the actual UTF-8 text of the message, 0-4096 characters
     */
    std::string text;

    /**
     * @brief Optional. For text messages, special entities like usernames, URLs, bot commands, etc. that appear in the text
     */
    std::vector<MessageEntity::Ptr> entities;

    /**
     * @brief Optional. For messages with a caption, special entities like usernames, URLs, bot commands, etc. that appear in the caption
     */
    std::vector<MessageEntity::Ptr> captionEntities;

    /**
     * @brief Optional. Message is an audio file, information about the file
     */
    Audio::Ptr audio;

    /**
     * @brief Optional. Message is a general file, information about the file
     */
    Document::Ptr document;

    /**
     * @brief Optional. Message is an animation, information about the animation.
     * For backward compatibility, when this field is set, the document field will also be set
     */
    Animation::Ptr animation;

    /**
     * @brief Optional. Message is a game, information about the game
     */
    Game::Ptr game;

    /**
     * @brief Optional. Message is a photo, available sizes of the photo
     */
    std::vector<PhotoSize::Ptr> photo;

    /**
     * @brief Optional. Message is a sticker, information about the sticker
     */
    Sticker::Ptr sticker;

    /**
     * @brief Optional. Message is a video, information about the video
     */
    Video::Ptr video;

    /**
     * @brief Optional. Message is a voice message, information about the file
     */
    Voice::Ptr voice;

    /**
     * @brief Optional. Message is a video note, information about the video message
     */
    VideoNote::Ptr videoNote;

    /**
     * @brief Optional. Caption for the animation, audio, document, photo, video or voice, 0-1024 characters
     */
    std::string caption;

    /**
     * @brief Optional. Message is a shared contact, information about the contact
     */
    Contact::Ptr contact;

    /**
     * @brief Optional. Message is a shared location, information about the location
     */
    Location::Ptr location;

    /**
     * @brief Optional. Message is a venue, information about the venue
     */
    Venue::Ptr venue;

    /**
     * @brief Optional. Message is a native poll, information about the poll
     */
    Poll::Ptr poll;

    /**
     * @brief Optional. Message is a dice with random value from 1 to 6
     */
    Dice::Ptr dice;

    /**
     * @brief Optional. New members that were added to the group or supergroup and information about them (the bot itself may be one of these members)
     */
    std::vector<User::Ptr> newChatMembers;

    /**
     * @brief Optional. A member was removed from the group, information about them (this member may be the bot itself)
     */
    User::Ptr leftChatMember;

    /**
     * @brief Optional. A chat title was changed to this value
     */
    std::string newChatTitle;

    /**
     * @brief Optional. A chat photo was change to this value
     */
    std::vector<PhotoSize::Ptr> newChatPhoto;

    /**
     * @brief Optional. Service message: the chat photo was deleted
     */
    bool deleteChatPhoto;

    /**
     * @brief Optional. Service message: the group has been created
     */
    bool groupChatCreated;

    /**
     * @brief Optional. Service message: the supergroup has been created
     */
    bool supergroupChatCreated;

    /**
     * @brief Optional. Service message: the channel has been created
     */
    bool channelChatCreated;

    /**
     * @brief Optional. The group has been migrated to a supergroup with the specified identifier.
     *
     * This number may be greater than 32 bits and some programming languages may have difficulty/silent defects in interpreting it.
     * But it is smaller than 52 bits, so a signed 64 bit integer or double-precision float type are safe for storing this identifier.
     */
    std::int64_t migrateToChatId;

    /**
     * @brief Optional. The supergroup has been migrated from a group with the specified identifier.
     *
     * This number may be greater than 32 bits and some programming languages may have difficulty/silent defects in interpreting it.
     * But it is smaller than 52 bits, so a signed 64 bit integer or double-precision float type are safe for storing this identifier.
     */
    std::int64_t migrateFromChatId;

    /**
     * @brief Optional. Specified message was pinned.
     * Note that the Message object in this field will not contain further @ref Message::replyToMessage fields even if it is itself a reply.
     */
    Message::Ptr pinnedMessage;

    /**
     * @brief Optional. Message is an invoice for a payment, information about the invoice
     */
    Invoice::Ptr invoice;

    /**
     * @brief Optional. Message is a service message about a successful payment, information about the payment
     */
    SuccessfulPayment::Ptr successfulPayment;

    /**
     * @brief Optional. The domain name of the website on which the user has logged in
     */
    std::string connectedWebsite;

    /**
     * @brief Optional. Telegram Passport data
     */
    // TODO PassportData::Ptr passportData;

    /**
     * @brief Optional. Inline keyboard attached to the message.
     * @ref InlineKeyboardButton::loginUrl buttons are represented as ordinary @ref InlineKeyboardButton::url buttons.
     */
    InlineKeyboardMarkup::Ptr replyMarkup;

    /**
     * @brief Optional. True, if the message is a channel post that was automatically forwarded to the connected discussion group
     *
     * Note: Added with Bot API 5.5
     */
    bool automaticForward;
};
}

#endif //TGBOT_CPP_MESSAGE_H
