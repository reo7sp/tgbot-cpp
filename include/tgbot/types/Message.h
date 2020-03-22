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
#include "tgbot/types/Video.h"
#include "tgbot/types/Contact.h"
#include "tgbot/types/Location.h"
#include "tgbot/types/Game.h"
#include "tgbot/types/PhotoSize.h"
#include "tgbot/types/MessageEntity.h"
#include "tgbot/types/Venue.h"
#include "tgbot/types/Voice.h"
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
     * @brief Unique message identifier.
     */
    std::int32_t messageId;

    /**
     * @brief Optional. Sender, can be empty for messages sent to channels.
     */
    User::Ptr from;

    /**
     * @brief Date the message was sent in Unix time.
     */
    std::int32_t date;

    /**
     * @brief Conversation the message belongs to.
     */
    Chat::Ptr chat;

    /**
     * @brief Optional. For forwarded messages, sender of the original message.
     */
    User::Ptr forwardFrom;

    /**
     * @brief Optional. For messages forwarded from a channel, information about the original channel
     */
    Chat::Ptr forwardFromChat;

    /**
     * @brief Optional. For forwarded channel posts, identifier of the original message in the channel
     */
    std::int32_t forwardFromMessageId;

    /**
     * @brief Optional. For messages forwarded from channels, signature of the post author if present.
     */
    std::string forwardSignature;

    /**
     * @brief Optional. Sender's name for messages forwarded from users who disallow adding a link to their account in forwarded messages.
     */
    std::string forwardSenderName;

    /**
     * @brief Optional. For forwarded messages, date the original message was sent in Unix time.
     */
    std::int32_t forwardDate;

    /**
     * @brief Optional. For replies, the original message. Note that the Message object in this field will not contain further reply_to_message fields even if it itself is a reply.
     */
    Message::Ptr replyToMessage;

    /**
     * @brief Optional. Date the message was last edited in Unix time.
     */
    std::int32_t editDate;

    /**
     * @brief Optional. Signature of the post author for messages in channels.
     */
    std::string authorSignature;

    /**
     * @brief Optional. For text messages, the actual UTF-8 text of the message.
     */
    std::string text;

    /**
     * @brief Optional. For text messages, special entities like usernames, URLs, bot commands, etc. that appear in the text.
     */
    std::vector<MessageEntity::Ptr> entities;

    /**
     * @brief Optional. For messages with a caption, special entities like usernames, URLs, bot commands, etc. that appear in the caption
     */
    std::vector<MessageEntity::Ptr> captionEntities;

    /**
     * @brief Optional. Message is an audio file, information about the file.
     */
    Audio::Ptr audio;

    /**
     * @brief Optional. Message is a general file, information about the file.
     */
    Document::Ptr document;

    /**
     * @brief Optional. Message is an animation, information about the animation.
     *
     * For backward compatibility, when this field is set, the document field will also be set.
     */
    Animation::Ptr animation;

    /**
     * @brief Optional. Message is a game, information about the game.
     */
    Game::Ptr game;

    /**
     * @brief Optional. Message is a photo, available sizes of the photo.
     */
    std::vector<PhotoSize::Ptr> photo;

    /**
     * @brief Optional. Message is a sticker, information about the sticker.
     */
    Sticker::Ptr sticker;

    /**
     * @brief Optional. Message is a video, information about the video.
     */
    Video::Ptr video;

    /**
     * @brief Optional. Message is a voice message, information about the file.
     */
    Voice::Ptr voice;

    /**
     * @brief Optional. Caption for the document, photo or video, 0-200 characters.
     */
    std::string caption;

    /**
     * @brief Optional. Message is a shared contact, information about the contact.
     */
    Contact::Ptr contact;

    /**
     * @brief Optional. Message is a shared location, information about the location.
     */
    Location::Ptr location;

    /**
     * @brief Optional. Message is a venue, information about the venue.
     */
    Venue::Ptr venue;

    /**
     * @brief Optional. Message is a poll, information about the poll.
     */
    Poll::Ptr poll;

    /**
     * @brief Optional. A new member was added to the group, information about them (this member may be bot itself).
     */
    User::Ptr newChatMember;

    /**
     * @brief Optional. New members that were added to the group or supergroup and information about them (the bot itself may be one of these members)
     */
    std::vector<User::Ptr> newChatMembers;

    /**
     * @brief Optional. A member was removed from the group, information about them (this member may be bot itself).
     */
    User::Ptr leftChatMember;

    /**
     * @brief Optional. A group title was changed to this value.
     */
    std::string newChatTitle;

    /**
     * @brief Optional. A group photo was change to this value.
     */
    std::vector<PhotoSize::Ptr> newChatPhoto;

    /**
     * @brief Optional. Informs that the group photo was deleted.
     */
    bool deleteChatPhoto = false;

    /**
     * @brief Optional. Informs that the group has been created.
     */
    bool groupChatCreated = false;

    /**
     * @brief Optional. Service message: the supergroup has been created.
     */
    bool supergroupChatCreated = false;

    /**
     * @brief Optional. Service message: the channel has been created.
     */
    bool channelChatCreated = false;

    /**
     * @brief Optional. The group has been migrated to a supergroup with the specified identifier, not exceeding 1e13 by absolute value.
     */
    std::int64_t migrateToChatId = 0;

    /**
     * @brief Optional. The supergroup has been migrated from a group with the specified identifier, not exceeding 1e13 by absolute value
     */
    std::int64_t migrateFromChatId = 0;

    /**
     * @brief Optional. Specified message was pinned. Note that the Message object in this field will not contain further reply_to_message fields even if it is itself a reply.
     */
    Message::Ptr pinnedMessage;

    /**
     * @brief Optional. Message is an invoice for a payment, information about the invoice.
     */
    Invoice::Ptr invoice;

    /**
     * @brief Optional. Message is a service message about a successful payment, information about the payment.
     */
    SuccessfulPayment::Ptr successfulPayment;

    /**
     * @brief Optional. The domain name of the website on which the user has logged in.
     */
    std::string connectedWebsite;

    /**
     * @brief Optional. Inline keyboard attached to the message. login_url buttons are represented as ordinary url buttons.
     */
    InlineKeyboardMarkup::Ptr replyMarkup;
};

}

#endif //TGBOT_CPP_MESSAGE_H
