#ifndef TGBOT_MESSAGE_H
#define TGBOT_MESSAGE_H

#include "tgbot/types/User.h"
#include "tgbot/types/Chat.h"
#include "tgbot/types/Message.h"
#include "tgbot/types/MessageEntity.h"
#include "tgbot/types/Animation.h"
#include "tgbot/types/Audio.h"
#include "tgbot/types/Document.h"
#include "tgbot/types/PhotoSize.h"
#include "tgbot/types/Sticker.h"
#include "tgbot/types/Video.h"
#include "tgbot/types/VideoNote.h"
#include "tgbot/types/Voice.h"
#include "tgbot/types/Contact.h"
#include "tgbot/types/Dice.h"
#include "tgbot/types/Game.h"
#include "tgbot/types/Poll.h"
#include "tgbot/types/Venue.h"
#include "tgbot/types/Location.h"
#include "tgbot/types/MessageAutoDeleteTimerChanged.h"
#include "tgbot/types/Invoice.h"
#include "tgbot/types/SuccessfulPayment.h"
#include "tgbot/types/UserShared.h"
#include "tgbot/types/ChatShared.h"
#include "tgbot/types/WriteAccessAllowed.h"
#include "tgbot/types/PassportData.h"
#include "tgbot/types/ProximityAlertTriggered.h"
#include "tgbot/types/ForumTopicCreated.h"
#include "tgbot/types/ForumTopicEdited.h"
#include "tgbot/types/ForumTopicClosed.h"
#include "tgbot/types/ForumTopicReopened.h"
#include "tgbot/types/GeneralForumTopicHidden.h"
#include "tgbot/types/GeneralForumTopicUnhidden.h"
#include "tgbot/types/VideoChatScheduled.h"
#include "tgbot/types/VideoChatStarted.h"
#include "tgbot/types/VideoChatEnded.h"
#include "tgbot/types/VideoChatParticipantsInvited.h"
#include "tgbot/types/WebAppData.h"
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
     * @brief Optional. Unique identifier of a message thread to which the message belongs; for supergroups only
     */
    std::int32_t messageThreadId;

    /**
     * @brief Optional. Sender of the message; empty for messages sent to channels.
     * 
     * For backward compatibility, the field contains a fake sender user in non-channel chats, if the message was sent on behalf of a chat.
     */
    User::Ptr from;

    /**
     * @brief Optional. Sender of the message, sent on behalf of a chat.
     * 
     * For example, the channel itself for channel posts, the supergroup itself for messages from anonymous group administrators, the linked channel for messages automatically forwarded to the discussion group.
     * For backward compatibility, the field from contains a fake sender user in non-channel chats, if the message was sent on behalf of a chat.
     */
    Chat::Ptr senderChat;

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
     * @brief Optional. For messages forwarded from channels or from anonymous administrators, information about the original sender chat
     */
    Chat::Ptr forwardFromChat;

    /**
     * @brief Optional. For messages forwarded from channels, identifier of the original message in the channel
     */
    std::int32_t forwardFromMessageId;

    /**
     * @brief Optional. For forwarded messages that were originally sent in channels or by an anonymous chat administrator, signature of the message sender if present
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
     * @brief Optional. True, if the message is sent to a forum topic
     */
    bool isTopicMessage;

    /**
     * @brief Optional. True, if the message is a channel post that was automatically forwarded to the connected discussion group
     */
    bool isAutomaticForward;

    /**
     * @brief Optional. For replies, the original message.
     * 
     * Note that the Message object in this field will not contain further replyToMessage fields even if it itself is a reply.
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
     * @brief Optional. True, if the message can't be forwarded
     */
    bool hasProtectedContent;

    /**
     * @brief Optional. The unique identifier of a media message group this message belongs to
     */
    std::string mediaGroupId;
    
    /**
     * @brief Optional. Signature of the post author for messages in channels, or the custom title of an anonymous group administrator
     */
    std::string authorSignature;

    /**
     * @brief Optional. For text messages, the actual UTF-8 text of the message
     */
    std::string text;

    /**
     * @brief Optional. For text messages, special entities like usernames, URLs, bot commands, etc. that appear in the text
     */
    std::vector<MessageEntity::Ptr> entities;

    /**
     * @brief Optional. Message is an animation, information about the animation.
     * 
     * For backward compatibility, when this field is set, the document field will also be set
     */
    Animation::Ptr animation;

    /**
     * @brief Optional. Message is an audio file, information about the file
     */
    Audio::Ptr audio;

    /**
     * @brief Optional. Message is a general file, information about the file
     */
    Document::Ptr document;

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
     * @brief Optional. Message is a video note, information about the video message
     */
    VideoNote::Ptr videoNote;

    /**
     * @brief Optional. Message is a voice message, information about the file
     */
    Voice::Ptr voice;

    /**
     * @brief Optional. Caption for the animation, audio, document, photo, video or voice
     */
    std::string caption;
    
    /**
     * @brief Optional. For messages with a caption, special entities like usernames, URLs, bot commands, etc. that appear in the caption
     */
    std::vector<MessageEntity::Ptr> captionEntities;

    /**
     * @brief Optional. True, if the message media is covered by a spoiler animation
     */
    bool hasMediaSpoiler;

    /**
     * @brief Optional. Message is a shared contact, information about the contact
     */
    Contact::Ptr contact;

    /**
     * @brief Optional. Message is a dice with random value
     */
    Dice::Ptr dice;

    /**
     * @brief Optional. Message is a game, information about the game. https://core.telegram.org/bots/api#games
     */
    Game::Ptr game;

    /**
     * @brief Optional. Message is a native poll, information about the poll
     */
    Poll::Ptr poll;

    /**
     * @brief Optional. Message is a venue, information about the venue.
     * 
     * For backward compatibility, when this field is set, the location field will also be set
     */
    Venue::Ptr venue;

    /**
     * @brief Optional. Message is a shared location, information about the location
     */
    Location::Ptr location;

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
     * @brief Optional. Service message: the supergroup has been created.
     * 
     * This field can't be received in a message coming through updates, because bot can't be a member of a supergroup when it is created.
     * It can only be found in replyToMessage if someone replies to a very first message in a directly created supergroup.
     */
    bool supergroupChatCreated;

    /**
     * @brief Optional. Service message: the channel has been created.
     * 
     * This field can't be received in a message coming through updates, because bot can't be a member of a channel when it is created.
     * It can only be found in replyToMessage if someone replies to a very first message in a channel.
     */
    bool channelChatCreated;

    /**
     * @brief Optional. Service message: auto-delete timer settings changed in the chat
     */
    MessageAutoDeleteTimerChanged::Ptr messageAutoDeleteTimerChanged;

    /**
     * @brief Optional. The group has been migrated to a supergroup with the specified identifier.
     *
     * This number may have more than 32 significant bits and some programming languages may have difficulty/silent defects in interpreting it.
     * But it has at most 52 significant bits, so a signed 64-bit integer or double-precision float type are safe for storing this identifier.
     */
    std::int64_t migrateToChatId;

    /**
     * @brief Optional. The supergroup has been migrated from a group with the specified identifier.
     *
     * This number may have more than 32 significant bits and some programming languages may have difficulty/silent defects in interpreting it.
     * But it has at most 52 significant bits, so a signed 64-bit integer or double-precision float type are safe for storing this identifier.
     */
    std::int64_t migrateFromChatId;

    /**
     * @brief Optional. Specified message was pinned.
     * 
     * Note that the Message object in this field will not contain further replyToMessage fields even if it is itself a reply.
     */
    Message::Ptr pinnedMessage;

    /**
     * @brief Optional. Message is an invoice for a payment, information about the invoice.
     * 
     * https://core.telegram.org/bots/api#payments
     */
    Invoice::Ptr invoice;

    /**
     * @brief Optional. Message is a service message about a successful payment, information about the payment.
     * 
     * https://core.telegram.org/bots/api#payments
     */
    SuccessfulPayment::Ptr successfulPayment;

    /**
     * @brief Optional. Service message: a user was shared with the bot
     */
    UserShared::Ptr userShared;

    /**
     * @brief Optional. Service message: a chat was shared with the bot
     */
    ChatShared::Ptr chatShared;

    /**
     * @brief Optional. The domain name of the website on which the user has logged in.
     * 
     * https://core.telegram.org/widgets/login
     */
    std::string connectedWebsite;

    /**
     * @brief Optional. Service message: the user allowed the bot added to the attachment menu to write messages
     */
    WriteAccessAllowed::Ptr writeAccessAllowed;

    /**
     * @brief Optional. Telegram Passport data
     */
    PassportData::Ptr passportData;

    /**
     * @brief Optional. Service message.
     * 
     * A user in the chat triggered another user's proximity alert while sharing Live Location.
     */
    ProximityAlertTriggered::Ptr proximityAlertTriggered;

    /**
     * @brief Optional. Service message: forum topic created
     */
    ForumTopicCreated::Ptr forumTopicCreated;

    /**
     * @brief Optional. Service message: forum topic edited
     */
    ForumTopicEdited::Ptr forumTopicEdited;

    /**
     * @brief Optional. Service message: forum topic closed
     */
    ForumTopicClosed::Ptr forumTopicClosed;

    /**
     * @brief Optional. Service message: forum topic reopened
     */
    ForumTopicReopened::Ptr forumTopicReopened;

    /**
     * @brief Optional. Service message: the 'General' forum topic hidden
     */
    GeneralForumTopicHidden::Ptr generalForumTopicHidden;

    /**
     * @brief Optional. Service message: the 'General' forum topic unhidden
     */
    GeneralForumTopicUnhidden::Ptr generalForumTopicUnhidden;

    /**
     * @brief Optional. Service message: video chat scheduled
     */
    VideoChatScheduled::Ptr videoChatScheduled;

    /**
     * @brief Optional. Service message: video chat started
     */
    VideoChatStarted::Ptr videoChatStarted;

    /**
     * @brief Optional. Service message: video chat ended
     */
    VideoChatEnded::Ptr videoChatEnded;

    /**
     * @brief Optional. Service message: new participants invited to a video chat
     */
    VideoChatParticipantsInvited::Ptr videoChatParticipantsInvited;

    /**
     * @brief Optional. Service message: data sent by a Web App
     */
    WebAppData::Ptr webAppData;

    /**
     * @brief Optional. Inline keyboard attached to the message.
     * 
     * loginUrl buttons are represented as ordinary url buttons.
     */
    InlineKeyboardMarkup::Ptr replyMarkup;
};
}

#endif //TGBOT_MESSAGE_H
