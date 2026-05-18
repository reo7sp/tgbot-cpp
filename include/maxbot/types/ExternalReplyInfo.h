#ifndef TGBOT_EXTERNALREPLYINFO_H
#define TGBOT_EXTERNALREPLYINFO_H

#include "maxbot/types/MessageOrigin.h"
#include "maxbot/types/Chat.h"
#include "maxbot/types/LinkPreviewOptions.h"
#include "maxbot/types/Animation.h"
#include "maxbot/types/Audio.h"
#include "maxbot/types/Document.h"
#include "maxbot/types/PhotoSize.h"
#include "maxbot/types/Sticker.h"
#include "maxbot/types/Story.h"
#include "maxbot/types/Video.h"
#include "maxbot/types/VideoNote.h"
#include "maxbot/types/Voice.h"
#include "maxbot/types/Contact.h"
#include "maxbot/types/Dice.h"
#include "maxbot/types/Game.h"
#include "maxbot/types/Giveaway.h"
#include "maxbot/types/GiveawayWinners.h"
#include "maxbot/types/Invoice.h"
#include "maxbot/types/Location.h"
#include "maxbot/types/Poll.h"
#include "maxbot/types/Venue.h"

#include <cstdint>
#include <memory>
#include <vector>

namespace MaxBot {

/**
 * @brief This object contains information about a message that is being replied to, which may come from another chat or forum topic.
 *
 * @ingroup types
 */
class ExternalReplyInfo {

public:
    typedef std::shared_ptr<ExternalReplyInfo> Ptr;

    /**
     * @brief Origin of the message replied to by the given message
     */
    MessageOrigin::Ptr origin;

    /**
     * @brief Optional. Chat the original message belongs to.
     *
     * Available only if the chat is a supergroup or a channel.
     */
    Chat::Ptr chat;

    /**
     * @brief Optional. Unique message identifier inside the original chat.
     *
     * Available only if the original chat is a supergroup or a channel.
     */
    std::int32_t messageId;

    /**
     * @brief Optional. Options used for link preview generation for the original message, if it is a text message
     */
    LinkPreviewOptions::Ptr linkPreviewOptions;

    /**
     * @brief Optional. Message is an animation, information about the animation
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
     * @brief Optional. Message is a forwarded story
     */
    Story::Ptr story;

    /**
     * @brief Optional. Message is a video, information about the video
     */
    Video::Ptr video;

    /**
     * @brief Optional. Message is a [video note](https://telegram.org/blog/video-messages-and-telescope), information about the video message
     */
    VideoNote::Ptr videoNote;

    /**
     * @brief Optional. Message is a voice message, information about the file
     */
    Voice::Ptr voice;

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
     * @brief Optional. Message is a game, information about the game.
     *
     * [More about games »](https://core.telegram.org/bots/api#games)
     */
    Game::Ptr game;

    /**
     * @brief Optional. Message is a scheduled giveaway, information about the giveaway
     */
    Giveaway::Ptr giveaway;

    /**
     * @brief Optional. A giveaway with public winners was completed
     */
    GiveawayWinners::Ptr giveawayWinners;

    /**
     * @brief Optional. Message is an invoice for a [payment](https://core.telegram.org/bots/api#payments), information about the invoice.
     *
     * [More about payments »](https://core.telegram.org/bots/api#payments)
     */
    Invoice::Ptr invoice;

    /**
     * @brief Optional. Message is a shared location, information about the location
     */
    Location::Ptr location;

    /**
     * @brief Optional. Message is a native poll, information about the poll
     */
    Poll::Ptr poll;

    /**
     * @brief Optional. Message is a venue, information about the venue
     */
    Venue::Ptr venue;
};
}

#endif //TGBOT_EXTERNALREPLYINFO_H
