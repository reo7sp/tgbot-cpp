/*
 * Copyright (c) 2015 Oleg Morozenkov
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

#ifndef TGBOT_CPP_API_H
#define TGBOT_CPP_API_H

#include <string>
#include <vector>

#include <boost/property_tree/ptree.hpp>
#include <boost/variant.hpp>

#include "tgbot/TgTypeParser.h"
#include "tgbot/net/HttpClient.h"
#include "tgbot/net/HttpReqArg.h"
#include "tgbot/types/User.h"
#include "tgbot/types/Message.h"
#include "tgbot/types/GenericReply.h"
#include "tgbot/types/InputFile.h"
#include "tgbot/types/UserProfilePhotos.h"
#include "tgbot/types/Update.h"
#include "tgbot/types/InlineQueryResult.h"
#include "tgbot/types/Venue.h"
#include "tgbot/types/WebhookInfo.h"
#include "tgbot/types/ChatMember.h"
#include "tgbot/types/StickerSet.h"
#include "tgbot/types/File.h"
#include "tgbot/types/InputMedia.h"
#include "tgbot/types/GameHighScore.h"
#include "tgbot/types/LabeledPrice.h"
#include "tgbot/types/ShippingOption.h"

namespace TgBot {

class Bot;

/**
 * @brief This class executes telegram api methods. Telegram docs: <https://core.telegram.org/bots/api#available-methods>
 *
 * @ingroup general
 */
class Api {

typedef std::shared_ptr<std::vector<std::string>> StringArrayPtr;

friend class Bot;

public:
    Api(std::string token, const HttpClient& httpClient);

    /**
     * @brief A simple method for testing your bot's auth token.
     * @return Basic information about the bot in form of a User object.
     */
    User::Ptr getMe() const;

    /**
     * @brief Use this method to send text messages.
     * @param chatId Unique identifier for the target chat.
     * @param text Text of the message to be sent.
     * @param disableWebPagePreview Optional. Disables link previews for links in this message.
     * @param replyToMessageId Optional. If the message is a reply, ID of the original message.
     * @param replyMarkup Optional. Additional interface options. An object for a custom reply keyboard, instructions to hide keyboard or to force a reply from the user.
     * @param parseMode Optional. Set it to "Markdown" or "HTML" if you want Telegram apps to show bold, italic, fixed-width text or inline URLs in your bot's message.
     * @param disableNotification Optional. Sends the message silenty.
     * @return On success, the sent message is returned.
     */
    Message::Ptr sendMessage(int64_t chatId, const std::string& text, bool disableWebPagePreview = false, int32_t replyToMessageId = 0,
                             GenericReply::Ptr replyMarkup = std::make_shared<GenericReply>(), const std::string& parseMode = "", bool disableNotification = false) const;

    /**
     * @brief Use this method to forward messages of any kind.
     * @param chatId Unique identifier for the target chat.
     * @param fromChatId Unique identifier for the chat where the original message was sent — User or GroupChat id.
     * @param messageId Unique message identifier.
     * @param disableNotification Optional. Sends the message silenty.
     * @return On success, the sent message is returned.
     */
    Message::Ptr forwardMessage(int64_t chatId, int64_t fromChatId, int32_t messageId, bool disableNotification = false) const;

    /**
     * @brief Use this method to send photos.
     * @param chatId Unique identifier for the target chat.
     * @param photo Photo to send.
     * @param caption Optional. Photo caption.
     * @param replyToMessageId Optional. If the message is a reply, ID of the original message.
     * @param replyMarkup Optional. Additional interface options. An object for a custom reply keyboard, instructions to hide keyboard or to force a reply from the user.
     * @param parseMode Optional. Set it to "Markdown" or "HTML" if you want Telegram apps to show bold, italic, fixed-width text or inline URLs in your bot's message.
     * @param disableNotification Optional. Sends the message silenty.
     * @return On success, the sent message is returned.
     */
    Message::Ptr sendPhoto(int64_t chatId, const boost::variant<InputFile::Ptr, std::string> photo, const std::string& caption = "", int32_t replyToMessageId = 0,
                           GenericReply::Ptr replyMarkup = std::make_shared<GenericReply>(), const std::string& parseMode = "", bool disableNotification = false) const;

    /**
     * @brief Use this method to send audio files, if you want Telegram clients to display the file as a playable voice message. For this to work, your audio must be in an .ogg file encoded with OPUS (other formats may be sent as Document).
     * @param chatId Unique identifier for the target chat.
     * @param audio Audio to send.
     * @param caption Audio caption, 0-200 characters
     * @param duration Duration of sent audio in seconds.
     * @param performer Performer
     * @param title Track name
     * @param thumb Thumbnail of the file sent. The thumbnail should be in JPEG format and less than 200 kB in size. A thumbnail‘s width and height should not exceed 90. Ignored if the file is not uploaded using multipart/form-data. Thumbnails can’t be reused and can be only uploaded as a new file, so you can pass “attach://<file_attach_name>” if the thumbnail was uploaded using multipart/form-data under <file_attach_name>.
     * @param replyToMessageId Optional. If the message is a reply, ID of the original message.
     * @param replyMarkup Optional. Additional interface options. An object for a custom reply keyboard, instructions to hide keyboard or to force a reply from the user.
     * @param parseMode Optional. Set it to "Markdown" or "HTML" if you want Telegram apps to show bold, italic, fixed-width text or inline URLs in your bot's message.
     * @param disableNotification Optional. Sends the message silenty.
     * @return On success, the sent message is returned.
     */
    Message::Ptr sendAudio(int64_t chatId, const boost::variant<InputFile::Ptr, std::string> audio, const std::string &caption = "", int32_t duration = 0,
                           const std::string& performer = "", const std::string& title = "", const boost::variant<InputFile::Ptr, std::string> thumb = "", int32_t replyToMessageId = 0,
                           GenericReply::Ptr replyMarkup = std::make_shared<GenericReply>(), const std::string& parseMode = "", bool disableNotification = false) const;

    /**
     * @brief Use this method to send general files.
     * @param chatId Unique identifier for the target chat.
     * @param document Document to send.
     * @param thumb Thumbnail of the file sent. The thumbnail should be in JPEG format and less than 200 kB in size. A thumbnail‘s width and height should not exceed 90. Ignored if the file is not uploaded using multipart/form-data. Thumbnails can’t be reused and can be only uploaded as a new file, so you can pass “attach://<file_attach_name>” if the thumbnail was uploaded using multipart/form-data under <file_attach_name>.
     * @param caption Document caption (may also be used when resending documents by file_id), 0-200 characters
     * @param replyToMessageId Optional. If the message is a reply, ID of the original message.
     * @param replyMarkup Optional. Additional interface options. An object for a custom reply keyboard, instructions to hide keyboard or to force a reply from the user.
     * @param parseMode Optional. Set it to "Markdown" or "HTML" if you want Telegram apps to show bold, italic, fixed-width text or inline URLs in your bot's message.
     * @param disableNotification Optional. Sends the message silenty.
     * @return On success, the sent message is returned.
     */
    Message::Ptr sendDocument(int64_t chatId, const boost::variant<InputFile::Ptr, std::string> document, const boost::variant<InputFile::Ptr, std::string> thumb = "", const std::string &caption = "", int32_t replyToMessageId = 0,
                              GenericReply::Ptr replyMarkup = std::make_shared<GenericReply>(), const std::string& parseMode = "", bool disableNotification = false) const;

    /**
     * @brief Use this method to send invoices.
     * @param chatId Unique identifier for the target private chat.
     * @param title Product name, 1-32 characters.
     * @param description Product description, 1-255 characters.
     * @param payload Bot-defined invoice payload, 1-128 bytes. This will not be displayed to the user, use for your internal processes.
     * @param providerToken Payments provider token, obtained via Botfather.
     * @param startParameter Unique deep-linking parameter that can be used to generate this invoice when used as a start parameter.
     * @param currency Three-letter ISO 4217 currency code.
     * @param prices Price breakdown, a list of components (e.g. product price, tax, discount, delivery cost, delivery tax, bonus, etc.)
     * @param providerData Optional. JSON-encoded data about the invoice, which will be shared with the payment provider. A detailed description of required fields should be provided by the payment provider.
     * @param photoUrl Optional. URL of the product photo for the invoice. Can be a photo of the goods or a marketing image for a service. People like it better when they see what they are paying for.
     * @param photoSize Optional. Photo size
     * @param photoWidth Optional. Photo width
     * @param photoHeight Optional. Photo height
     * @param needName Optional. Pass True, if you require the user's full name to complete the order.
     * @param needPhoneNumber Optional. Pass True, if you require the user's phone number to complete the order.
     * @param needEmail Optional. Pass True, if you require the user's email address to complete the order.
     * @param needShippingAddress Optional. Pass True, if you require the user's shipping address to complete the order.
     * @param sendPhoneNumberToProvider Optional. Pass True, if user's phone number should be sent to provider.
     * @param sendEmailToProvider Optional. Pass True, if user's email address should be sent to provider
     * @param isFlexible Optional. Pass True, if the final price depends on the shipping method.
     * @param replyToMessageId Optional. If the message is a reply, ID of the original message.
     * @param replyMarkup Optional. A JSON-serialized object for an inline keyboard. If empty, one 'Pay total price' button will be shown. If not empty, the first button must be a Pay button.
     * @param disableNotification Optional. Sends the message silently. Users will receive a notification with no sound.
     * @return On success, the sent Message is returned.
     */
    Message::Ptr sendInvoice(int64_t chatId, const std::string& title, const std::string& description, const std::string& payload,
                             const std::string& providerToken, const std::string& startParameter, const std::string& currency, const std::vector<LabeledPrice::Ptr>& prices,
                             const std::string& providerData = "", const std::string& photoUrl = "", int32_t photoSize = 0,
                             int32_t photoWidth = 0, int32_t photoHeight = 0, bool needName = false,
                             bool needPhoneNumber = false, bool needEmail = false, bool needShippingAddress = false,
                             bool sendPhoneNumberToProvider = false, bool sendEmailToProvider = false, bool isFlexible = false,
                             int32_t replyToMessageId = 0, GenericReply::Ptr replyMarkup = std::make_shared<GenericReply>(), bool disableNotification = false) const;

    /**
     * @brief Use this method to reply to shipping queries.
     *
     * If you sent an invoice requesting a shipping address and the parameter isFlexible was specified, the Bot API will send an Update with a shipping_query field to the bot.
     *
     * @param shippingQueryId Unique identifier for the query to be answered.
     * @param ok Specify True if delivery to the specified address is possible and False if there are any problems (for example, if delivery to the specified address is not possible)
     * @param shippingOptions Optional. Required if ok is True. A JSON-serialized array of available shipping options.
     * @param errorMessage Optional. Required if ok is False. Error message in human readable form that explains why it is impossible to complete the order (e.g. "Sorry, delivery to your desired address is unavailable'). Telegram will display this message to the user.
     * @return On success, True is returned.
     */
    bool answerShippingQuery(const std::string& shippingQueryId, bool ok, const std::vector<ShippingOption::Ptr>& shippingOptions = std::vector<ShippingOption::Ptr>(), const std::string& errorMessage = "") const;

    /**
     * @brief Use this method to respond to such pre-checkout queries.
     *
     * Once the user has confirmed their payment and shipping details, the Bot API sends the final confirmation in the form of an Update with the field preCheckoutQuery.
     * Note: The Bot API must receive an answer within 10 seconds after the pre-checkout query was sent.
     *
     * @param preCheckoutQueryId Unique identifier for the query to be answered
     * @param ok Specify True if everything is alright (goods are available, etc.) and the bot is ready to proceed with the order. Use False if there are any problems.
     * @param errorMessage Required if ok is False. Error message in human readable form that explains the reason for failure to proceed with the checkout (e.g. "Sorry, somebody just bought the last of our amazing black T-shirts while you were busy filling out your payment details. Please choose a different color or garment!"). Telegram will display this message to the user.
     * @return On success, True is returned.
     */
    bool answerPreCheckoutQuery(const std::string& preCheckoutQueryId, bool ok, const std::string& errorMessage = "") const;

    /**
     * @brief Use this method to send .webp stickers.
     * @param chatId Unique identifier for the target chat.
     * @param sticker Sticker to send.
     * @param replyToMessageId Optional. If the message is a reply, ID of the original message.
     * @param replyMarkup Optional. Additional interface options. An object for a custom reply keyboard, instructions to hide keyboard or to force a reply from the user.
     * @param disableNotification Optional. Sends the message silenty.
     * @return On success, the sent message is returned.
     */
    Message::Ptr sendSticker(int64_t chatId, const boost::variant<InputFile::Ptr, std::string> sticker, int32_t replyToMessageId = 0,
                             GenericReply::Ptr replyMarkup = std::make_shared<GenericReply>(), bool disableNotification = false) const;

    /**
     * @brief Use this method to get a sticker set.
     * @param chatId Name of the sticker set.
     * @return On success, a StickerSet object is returned.
     */
    StickerSet::Ptr getStickerSet(const std::string& name) const;

    /**
     * @brief Use this method to upload a .png file with a sticker for later use in createNewStickerSet and addStickerToSet methods (can be used multiple times).
     * @param userId User identifier of sticker file owner.
     * @param pngSticker Png image with the sticker, must be up to 512 kilobytes in size, dimensions must not exceed 512px, and either width or height must be exactly 512px.
     * @return Returns the uploaded File on success.
     */
    File::Ptr uploadStickerFile(int32_t userId, InputFile::Ptr pngSticker) const;

    /**
     * @brief Use this method to create new sticker set owned by a user. The bot will be able to edit the created sticker set.
     * @param userId User identifier of created sticker set owner.
     * @param name Short name of sticker set, to be used in t.me/addstickers/ URLs (e.g., animals). Can contain only english letters, digits and underscores. Must begin with a letter, can't contain consecutive underscores and must end in “_by_<bot username>”. <bot_username> is case insensitive. 1-64 characters.
     * @param title Sticker set title, 1-64 characters.
     * @param pngSticker Png image with the sticker, must be up to 512 kilobytes in size, dimensions must not exceed 512px, and either width or height must be exactly 512px.
     * @param emojis One or more emoji corresponding to the sticker.
     * @param containsMasks Optional. Pass True, if a set of mask stickers should be created.
     * @param maskPosition Optional. A JSON-serialized object for position where the mask should be placed on faces.
     * @return Returns True on success.
     */
    bool createNewStickerSet(int32_t userId, const std::string& name, const std::string& title,
                             boost::variant<InputFile::Ptr, std::string> pngSticker, const std::string& emojis, bool containsMasks = false, MaskPosition::Ptr maskPosition = nullptr) const;

    /**
     * @brief Use this method to add a new sticker to a set created by the bot.
     * @param userId User identifier of created sticker set owner.
     * @param name Sticker set name.
     * @param title Sticker set title, 1-64 characters.
     * @param pngSticker Png image with the sticker, must be up to 512 kilobytes in size, dimensions must not exceed 512px, and either width or height must be exactly 512px.
     * @param emojis One or more emoji corresponding to the sticker.
     * @param maskPosition Optional. A JSON-serialized object for position where the mask should be placed on faces.
     * @return Returns True on success.
     */
    bool addStickerToSet(int32_t userId, const std::string& name, const std::string& title,
                         boost::variant<InputFile::Ptr, std::string> pngSticker, const std::string& emojis, MaskPosition::Ptr maskPosition = nullptr) const;

    /**
     * @brief Use this method to move a sticker in a set created by the bot to a specific position.
     * @param stickers File identifier of the sticker.
     * @param position New sticker position in the set, zero-based.
     * @return Returns True on success.
     */
    bool setStickerPositionInSet(const std::string& sticker, uint32_t position) const;

    /**
     * @brief Use this method to delete a sticker from a set created by the bot.
     * @param stickers File identifier of the sticker.
     * @return Returns True on success.
     */
    bool deleteStickerPositionInSet(const std::string& sticker) const;

    /**
     * @brief Use this method to send video files, Telegram clients support mp4 videos (other formats may be sent as Document).
     * @param chatId Unique identifier for the target chat.
     * @param video Video to send.
     * @param supportsStreaming Optional. Pass True, if the uploaded video is suitable for streaming.
     * @param duration Optional. Duration of sent video in seconds
     * @param width Optional. Video width
     * @param height Optional. Video height
     * @param thumb Thumbnail of the file sent. The thumbnail should be in JPEG format and less than 200 kB in size. A thumbnail‘s width and height should not exceed 90. Ignored if the file is not uploaded using multipart/form-data. Thumbnails can’t be reused and can be only uploaded as a new file, so you can pass “attach://<file_attach_name>” if the thumbnail was uploaded using multipart/form-data under <file_attach_name>.
     * @param caption Optional. Video caption (may also be used when resending videos by file_id), 0-200 characters
     * @param replyToMessageId Optional. If the message is a reply, ID of the original message.
     * @param replyMarkup Optional. Additional interface options. An object for a custom reply keyboard, instructions to hide keyboard or to force a reply from the user.
     * @param parseMode Optional. Set it to "Markdown" or "HTML" if you want Telegram apps to show bold, italic, fixed-width text or inline URLs in your bot's message.
     * @param disableNotification Optional. Sends the message silenty.
     * @return On success, the sent message is returned.
     */
    Message::Ptr sendVideo(int64_t chatId, const boost::variant<InputFile::Ptr, std::string> video, bool supportsStreaming = false, int32_t duration = 0, int32_t width = 0, int32_t height = 0, const boost::variant<InputFile::Ptr, std::string> thumb = "", const std::string& caption = "",
                           int32_t replyToMessageId = 0, GenericReply::Ptr replyMarkup = std::make_shared<GenericReply>(), const std::string& parseMode = "", bool disableNotification = false) const;

    /**
     * @brief Use this method to send animation files (GIF or H.264/MPEG-4 AVC video without sound). 
     * 
     * Bots can currently send animation files of up to 50 MB in size, this limit may be changed in the future.
     * 
     * @param chatId Unique identifier for the target chat.
     * @param animation Animation to send. Pass a file_id as String to send an animation that exists on the Telegram servers (recommended), pass an HTTP URL as a String for Telegram to get an animation from the Internet, or upload a new animation using multipart/form-data. 
     * @param duration Optional. Duration of sent animation in seconds.
     * @param width Optional. Animation width.
     * @param height Optional. Animation height.
     * @param thumb Thumbnail of the file sent. The thumbnail should be in JPEG format and less than 200 kB in size. A thumbnail‘s width and height should not exceed 90. Ignored if the file is not uploaded using multipart/form-data. Thumbnails can’t be reused and can be only uploaded as a new file, so you can pass “attach://<file_attach_name>” if the thumbnail was uploaded using multipart/form-data under <file_attach_name>.
     * @param caption Optional. Animation caption (may also be used when resending animation by file_id), 0-200 characters
     * @param replyToMessageId Optional. If the message is a reply, ID of the original message.
     * @param replyMarkup Optional. Additional interface options. An object for a custom reply keyboard, instructions to hide keyboard or to force a reply from the user.
     * @param parseMode Optional. Set it to "Markdown" or "HTML" if you want Telegram apps to show bold, italic, fixed-width text or inline URLs in your bot's message.
     * @param disableNotification Optional. Sends the message silenty.
     * @return On success, the sent Message is returned.
     */
    Message::Ptr sendAnimation(int64_t chatId, const boost::variant<InputFile::Ptr, std::string> animation, int32_t duration = 0, int32_t width = 0, int32_t height = 0, const boost::variant<InputFile::Ptr, std::string> thumb = "", const std::string &caption = "",
                              int32_t replyToMessageId = 0, GenericReply::Ptr replyMarkup = std::make_shared<GenericReply>(), const std::string& parseMode = "", bool disableNotification = false) const;
    /**
     * @brief Use this method to send video messages. On success, the sent Message is returned.
     * @param chatId Unique identifier for the target chat.
     * @param videoNote Video note to send.
     * @param replyToMessageId If the message is a reply, ID of the original message.
     * @param disableNotification Sends the message silently. Users will receive a notification with no sound.
     * @param duration Duration of sent video in seconds.
     * @param length Video width and height.
     * @param thumb Thumbnail of the file sent. The thumbnail should be in JPEG format and less than 200 kB in size. A thumbnail‘s width and height should not exceed 90. Ignored if the file is not uploaded using multipart/form-data. Thumbnails can’t be reused and can be only uploaded as a new file, so you can pass “attach://<file_attach_name>” if the thumbnail was uploaded using multipart/form-data under <file_attach_name>.
     * @param replyMarkup Additional interface options. A object for an inline keyboard, custom reply keyboard, instructions to remove reply keyboard or to force a reply from the user.
     * @return On success, the sent Message is returned.
     */
    Message::Ptr sendVideoNote(int64_t chatId, const boost::variant<InputFile::Ptr, std::string> videoNote, int64_t replyToMessageId = 0, bool disableNotification = false,
                               int32_t duration = 0, int32_t length = 0, const boost::variant<InputFile::Ptr, std::string> thumb = "", GenericReply::Ptr replyMarkup = std::make_shared<GenericReply>()) const;

    /**
     * @brief Use this method to send a group of photos or videos as an album.
     * @param chatId Unique identifier for the target chat of the target channel.
     * @param media A JSON-serialized array describing photos and videos to be sent, must include 2–10 items.
     * @param disableNotification Optional. Sends the messages silently. Users will receive a notification with no sound.
     * @param replyToMessageId Optional. If the messages are a reply, ID of the original message.
     * @return On success, an array of the sent Messages is returned.
     */
    std::vector<Message::Ptr> sendMediaGroup(int64_t chatId, const std::vector<InputMedia::Ptr>& media,
                                             bool disableNotification = false, int32_t replyToMessageId = 0) const;

    /**
     * @brief Use this method to send audio files, if you want Telegram clients to display the file as a playable voice message.
     * @param chatId Unique identifier for the target chat.
     * @param voice Audio file to send.
     * @param caption Voice message caption, 0-200 characters
     * @param duration Duration of send audio in seconds.
     * @param replyToMessageId Optional. If the message is a reply, ID of the original message.
     * @param replyMarkup Optional. Additional interface options. A object for a custom reply keyboard, instructions to hide keyboard or to force a reply from the user.
     * @param parseMode Optional. Set it to "Markdown" or "HTML" if you want Telegram apps to show bold, italic, fixed-width text or inline URLs in your bot's message.
     * @param disableNotification Optional. Sends the message silenty.
     * @return On success, the sent message is returned.
     */
    Message::Ptr sendVoice(int64_t chatId, const boost::variant<InputFile::Ptr, std::string> voice, const std::string& caption = "", int duration = 0, int32_t replyToMessageId = 0,
                           GenericReply::Ptr replyMarkup = std::make_shared<GenericReply>(), const std::string& parseMode = "", bool disableNotification = false) const;

    /**
     * @brief Use this method to send a game.
     * @param chatId Unique identifier for the target chat.
     * @param gameShortName Short name of the game, serves as the unique identifier for the game. Set up your games via Botfather.
     * @param replyToMessageId Optional. If the message is a reply, ID of the original message.
     * @param replyMarkup Optional. A JSON-serialized object for an inline keyboard. If empty, one ‘Play game_title’ button will be shown. If not empty, the first button must launch the game.
     * @param disableNotification Optional. Sends the message silenty.
     * @return On success, the sent message is returned.
     */
    Message::Ptr sendGame(int64_t chatId, const std::string& gameShortName, int32_t replyToMessageId = 0,
                          InlineKeyboardMarkup::Ptr replyMarkup = std::make_shared<InlineKeyboardMarkup>(), bool disableNotification = false) const;

    /**
     * @brief Use this method to send point on the map.
     * @param chatId Unique identifier for the target chat.
     * @param latitude Latitude of location.
     * @param longitude Longitude of location.
     * @param livePeriod Optional. Period in seconds for which the location will be updated (see Live Locations, should be between 60 and 86400).
     * @param replyToMessageId Optional. If the message is a reply, ID of the original message.
     * @param replyMarkup Optional. Additional interface options. A object for a custom reply keyboard, instructions to hide keyboard or to force a reply from the user.
     * @param disableNotification Optional. Sends the message silenty.
     * @return On success, the sent message is returned.
     */
    Message::Ptr sendLocation(int64_t chatId, float latitude, float longitude, uint32_t livePeriod = 0,
                              int32_t replyToMessageId = 0, GenericReply::Ptr replyMarkup = std::make_shared<GenericReply>(), bool disableNotification = false) const;

    /**
     * @brief Use this method to edit live location messages sent by the bot or via the bot (for inline bots).
     * @param latitude Latitude of new location.
     * @param longitude Longitude of new location.
     * @param chatId Optional. Required if inlineMessageId is not specified. Unique identifier for the target chat of the target channel.
     * @param messageId Optional. Required if inlineMessageId is not specified. Identifier of the sent message.
     * @param inlineMessageId Optional. Required if chatId and messageId are not specified. Identifier of the inline message.
     * @param replyMarkup Optional. A JSON-serialized object for a new inline keyboard.
     * @return On success, if the edited message was sent by the bot, the edited Message is returned, otherwise nullptr is returned.
     */
    Message::Ptr editMessageLiveLocation(float latitude, float longitude, int64_t chatId = 0, int32_t messageId = 0,
                                         int32_t inlineMessageId = 0, InlineKeyboardMarkup::Ptr replyMarkup = std::make_shared<InlineKeyboardMarkup>()) const;

    /**
     * @brief Use this method to edit live location messages sent by the bot or via the bot (for inline bots).
     * @param chatId Optional. Required if inlineMessageId is not specified. Unique identifier for the target chat of the target channel.
     * @param messageId Optional. Required if inlineMessageId is not specified. Identifier of the sent message.
     * @param inlineMessageId Optional. Required if chatId and messageId are not specified. Identifier of the inline message.
     * @param replyMarkup Optional. A JSON-serialized object for a new inline keyboard.
     * @return On success, if the edited message was sent by the bot, the edited Message is returned, otherwise nullptr is returned.
     */
    Message::Ptr stopMessageLiveLocation(int64_t chatId = 0, int32_t messageId = 0, int32_t inlineMessageId = 0,
                                         InlineKeyboardMarkup::Ptr replyMarkup = std::make_shared<InlineKeyboardMarkup>()) const;


    /**
     * @brief Use this method to send information about a venue. On success, the sent Message is returned.
     * @param chatId Unique identifier for the target chat.
     * @param latitude Latitude of location.
     * @param longitude Longitude of location.
     * @param title Name of the venue.
     * @param address Address of the venue.
     * @param foursquareId Foursquare identifier of the venue.
     * @param foursquareType Foursquare type of the venue, if known. (For example, “arts_entertainment/default”, “arts_entertainment/aquarium” or “food/icecream”.)
     * @param replyToMessageId Optional. If the message is a reply, ID of the original message.
     * @param replyMarkup Optional. Additional interface options. A object for a custom reply keyboard, instructions to hide keyboard or to force a reply from the user.
     * @param disableNotification Optional. Sends the message silenty.
     * @return On success, the sent message is returned.
     */
    Message::Ptr sendVenue(int64_t chatId, float latitude, float longitude, const std::string& title, const std::string& address, const std::string& foursquareId = "", const std::string& foursquareType = "",
                           bool disableNotification = false, int32_t replyToMessageId = 0, GenericReply::Ptr replyMarkup = std::make_shared<GenericReply>()) const;

    /**
     * @brief Use this method to send phone contacts. On success, the sent Message is returned.
     * @param chatId Unique identifier for the target chat.
     * @param phoneNumber Contact's phone number.
     * @param firstName Contact's first name.
     * @param lastName Contact's last name.
     * @param vcard Optional. Additional data about the contact in the form of a vCard, 0-2048 bytes.
     * @param disableNotification Optional. Sends the message silenty.
     * @param replyToMessageId Optional. If the message is a reply, ID of the original message.
     * @param replyMarkup Optional. Additional interface options. A object for a custom reply keyboard, instructions to hide keyboard or to force a reply from the user.
     * @return On success, the sent message is returned.
     */
    Message::Ptr sendContact(int64_t chatId, const std::string& phoneNumber, const std::string& firstName, const std::string& lastName = "", const std::string& vcard = "", bool disableNotification = false,
                            int32_t replyToMessageId = 0, GenericReply::Ptr replyMarkup = std::make_shared<GenericReply>()) const;

    /**
     * @brief Use this method when you need to tell the user that something is happening on the bot's side. The status is set for 5 seconds or less (when a message arrives from your bot, Telegram clients clear its typing status).
     *
     * Example: The ImageBot needs some time to process a request and upload the image. Instead of sending a text message along the lines of “Retrieving image, please wait…”, the bot may use sendChatAction with action = upload_photo. The user will see a “sending photo” status for the bot.
     * We only recommend using this method when a response from the bot will take a noticeable amount of time to arrive.
     *
     * @param chatId Unique identifier for the target chat.
     * @param action Type of action to broadcast. Choose one, depending on what the user is about to receive: typing for text messages, upload_photo for photos, record_video or upload_video for videos, record_audio or upload_audio for audio files, upload_document for general files, find_location for location data.
     */
    void sendChatAction(int64_t chatId, const std::string& action) const;

    /**
     * @brief Use this method to get a list of profile pictures for a user.
     * @param userId Unique identifier of the target user.
     * @param offset Optional. Sequential number of the first photo to be returned. By default, all photos are returned.
     * @param limit Optional. Limits the number of photos to be retrieved. Values between 1—100 are accepted. Defaults to 100.
     * @return A UserProfilePhotos object.
     */
    UserProfilePhotos::Ptr getUserProfilePhotos(int32_t userId, int32_t offset = 0, int32_t limit = 100) const;

    /**
     * @brief Use this method to get basic info about a file and prepare it for downloading. For the moment, bots can download files of up to 20MB in size.
     * @param fileId File identifier to get info about
     * @return A File object.
     */
    File::Ptr getFile(const std::string &fileId) const;

    /**
     * @brief Use this method for your bot to leave a group, supergroup or channel.
     * @param chatId Unique identifier for the target chat of the target supergroup or channel.
     * @return True on success
     */
    bool leaveChat(int64_t chatId) const;

    /**
     * @brief Use this method to get up to date information about the chat (current name of the user for one-on-one conversations, current username of a user, group or channel, etc.). Returns a Chat object on success.
     * @param chatId Unique identifier for the target chat of the target supergroup or channel.
     * @return Chat object.
     */
    Chat::Ptr getChat(int64_t chatId) const;

    /**
    * @brief Use this method to get a list of administrators in a chat. On success, returns an Array of ChatMember objects that contains information about all chat administrators except other bots. If the chat is a group or a supergroup and no administrators were appointed, only the creator will be returned.
    * @param chatId Unique identifier for the target chat of the target supergroup or channel.
    * @return ChatMember object.
    */
    std::vector<ChatMember::Ptr> getChatAdministrators(int64_t chatId) const;

    /**
    * @brief Use this method to get the number of members in a chat. Returns Int on success.
    * @param chatId Unique identifier for the target chat of the target supergroup or channel.
    * @return Int.
    */
    int32_t getChatMembersCount(int64_t chatId) const;

    /**
    * @brief Use this method to get information about a member of a chat. Returns a ChatMember object on success.
    * @param chatId Unique identifier for the target chat of the target supergroup or channel.
    * @param userId Unique identifier of the target user
    * @return ChatMember object.
    */
    ChatMember::Ptr getChatMember(int64_t chatId, int32_t userId) const;

    /**
    * @brief Use this method to get information about a member of a chat. Returns a ChatMember object on success.
    * @param chatId Unique identifier for the target chat of the target supergroup or channel.
    * @param stickerSetName Name of the sticker set to be set as the group sticker set.
    * @return Returns True on success.
    */
    bool setChatStickerSet(int64_t chatId, const std::string& stickerSetName) const;

    /**
    * @brief Use this method to get information about a member of a chat. Returns a ChatMember object on success.
    * @param chatId Unique identifier for the target chat of the target supergroup or channel.
    * @return Returns True on success.
    */
    bool deleteChatStickerSet(int64_t chatId) const;


    /**
     * @brief Use this method to send answers to callback queries sent from inline keyboards. The answer will be displayed to the user as a notification at the top of the chat screen or as an alert.
     * @param callbackQueryId Unique identifier for the query to be answered
     * @param text Optional	Text of the notification. If not specified, nothing will be shown to the user, 0-200 characters
     * @param showAlert Optional If true, an alert will be shown by the client instead of a notification at the top of the chat screen. Defaults to false.
     * @param url Optional	URL that will be opened by the user's client. If you have created a Game and accepted the conditions via @Botfather, specify the URL that opens your game – note that this will only work if the query comes from a callback_game button
     * @param cacheTime Optional	The maximum amount of time in seconds that the result of the callback query may be cached client-side. Telegram apps will support caching starting in version 3.14. Defaults to 0.
     * @return True on success
     */
    bool answerCallbackQuery(const std::string & callbackQueryId, const std::string & text="", bool showAlert=false, const std::string &url="", int32_t cacheTime=0) const;

    /**
     * @brief Use this method to edit text and game messages sent by the bot or via the bot (for inline bots)
     * @param text New text of the message
     * @param chatId Optional	Required if inline_message_id is not specified. Unique identifier for the target chat of the target channel.
     * @param messageId Optional	Required if inline_message_id is not specified. Identifier of the sent message
     * @param inlineMessageId Optional	Required if chat_id and message_id are not specified. Identifier of the inline message
     * @param parseMode Optional	Send Markdown or HTML, if you want Telegram apps to show bold, italic, fixed-width text or inline URLs in your bot's message.
     * @param disableWebPagePreview Optional	Disables link previews for links in this message
     * @param replyMarkup Optional	A JSON-serialized object for an inline keyboard.
     * @return Message object on success, otherwise nullptr
     */
    Message::Ptr editMessageText(const std::string& text, int64_t chatId=0, int32_t messageId=0, const std::string& inlineMessageId="",
                                 const std::string& parseMode = "", bool disableWebPagePreview = false, GenericReply::Ptr replyMarkup = std::make_shared<GenericReply>()) const;

    /**
    * @brief Use this method to edit captions of messages sent by the bot or via the bot (for inline bots).
    * @param chatId Optional	Required if inline_message_id is not specified. Unique identifier for the target chat of the target channel.
    * @param messageId Optional	Required if inline_message_id is not specified. Identifier of the sent message
    * @param caption Optional New caption of the message
    * @param inlineMessageId Optional	Required if chat_id and message_id are not specified. Identifier of the inline message
    * @param replyMarkup Optional	A JSON-serialized object for an inline keyboard.
    * @return Message object on success, otherwise nullptr
    */
    Message::Ptr editMessageCaption(int64_t chatId = 0, int32_t messageId = 0, const std::string& caption = "",
                                    const std::string& inlineMessageId = "", GenericReply::Ptr replyMarkup = std::make_shared<GenericReply>()) const;

    /**
     * @brief Use this method to edit audio, document, photo, or video messages.
     * 
     * 
     * If a message is a part of a message album, then it can be edited only to a photo or a video.
     * Otherwise, message type can be changed arbitrarily. When inline message is edited, new file can't be uploaded.
     * Use previously uploaded file via its file_id or specify a URL.
     * 
     * @param media A JSON-serialized object for a new media content of the message.
     * @param chatId Optional	Required if inline_message_id is not specified. Unique identifier for the target chat of the target channel.
     * @param messageId Optional	Required if inline_message_id is not specified. Identifier of the sent message
     * @param inlineMessageId Optional	Required if chat_id and message_id are not specified. Identifier of the inline message
     * @param replyMarkup Optional	A JSON-serialized object for an inline keyboard.
     * @return On success, if the edited message was sent by the bot, the edited Message is returned, otherwise nullptr is returned.
     */
    Message::Ptr editMessageMedia(InputMedia::Ptr media, int64_t chatId = 0, int32_t messageId = 0, const std::string& inlineMessageId = "",
                                  GenericReply::Ptr replyMarkup = std::make_shared<GenericReply>()) const;

    /**
    * @brief Use this method to edit only the reply markup of messages sent by the bot or via the bot (for inline bots).
    * @param chatId Optional	Required if inline_message_id is not specified. Unique identifier for the target chat of the target channel.
    * @param messageId Optional	Required if inline_message_id is not specified. Identifier of the sent message
    * @param inlineMessageId Optional	Required if chat_id and message_id are not specified. Identifier of the inline message
    * @param replyMarkup Optional	A JSON-serialized object for an inline keyboard.
    * @return Message object on success, otherwise nullptr
    */
    Message::Ptr editMessageReplyMarkup(int64_t chatId = 0, int32_t messageId = 0, const std::string& inlineMessageId = "",
                                        const GenericReply::Ptr replyMarkup = std::make_shared<GenericReply>()) const;

    /**
     * @brief Use this method to delete messages sent by bot (or by other users if bot is admin).
     * @param chatId	Unique identifier for the target chat.
     * @param messageId	Unique identifier for the target message.
     */
    void deleteMessage(int64_t chatId, int32_t messageId) const;

    /**
     * @brief Use this method to receive incoming updates using long polling.
     *
     * This method will not work if an outgoing webhook is set up.
     * In order to avoid getting duplicate updates, recalculate offset after each server response.
     *
     * @param offset Optional. Identifier of the first update to be returned. Must be greater by one than the highest among the identifiers of previously received updates. By default, updates starting with the earliest unconfirmed update are returned. An update is considered confirmed as soon as getUpdates is called with an offset higher than its update_id.
     * @param limit Optional. Limits the number of updates to be retrieved. Values between 1—100 are accepted. Defaults to 100.
     * @param timeout Optional. Timeout in seconds for long polling. Defaults to 0, i.e. usual short polling.
     * @param allowed_updates Optional. List the types of updates you want your bot to receive. For example, specify [“message”, “edited_channel_post”, “callback_query”] to only receive updates of these types. See Update for a complete list of available update types. Specify an empty list to receive all updates regardless of type (default). If not specified, the previous setting will be used.
     * @return An Array of Update objects
     */
    std::vector<Update::Ptr> getUpdates(int32_t offset = 0, int32_t limit = 100, int32_t timeout = 0, const StringArrayPtr &allowedUpdates = nullptr) const;

    /**
     * @brief Use this method to specify a url and receive incoming updates via an outgoing webhook. Whenever there is an update for the bot, we will send an HTTPS POST request to the specified url, containing a JSON-serialized Update. In case of an unsuccessful request, we will give up after a reasonable amount of attempts.
     *
     * If you'd like to make sure that the Webhook request comes from Telegram, we recommend using a secret path in the URL, e.g. www.example.com/<token>. Since nobody else knows your bot‘s token, you can be pretty sure it’s us.
     * You will not be able to receive updates using getUpdates for as long as an outgoing webhook is set up.
     * We currently do not support self-signed certificates.
     * Ports currently supported for Webhooks: 443, 80, 88, 8443.
     *
     * @param url Optional. HTTPS url to send updates to. Use an empty string to remove webhook integration.
     */
    void setWebhook(const std::string& url = "", InputFile::Ptr certificate = nullptr, int32_t maxConnection = 40, const StringArrayPtr &allowedUpdates = nullptr) const;

    /**
     * @brief Use this method to remove webhook integration if you decide to switch back to getUpdates.
     *
     * Requires no parameters.
     *
     * @return Returns True on success.
     */
    bool deleteWebhook() const;

    /**
     * @brief Use this method to get current webhook status.
     *
     * Requires no parameters.
     * If the bot is using getUpdates, will return an object with the url field empty.
     *
     * @return On success, returns a WebhookInfo object.
     */
    WebhookInfo::Ptr getWebhookInfo() const;

    /**
     * @brief Use this method to send answers to an inline query.
     * No mode that 50 results per query are allowed.
     * @param inlineQueryId Unique identifier for the answered query.
     * @param results Array of results for the inline query.
     * @param cacheTime The maximum amount of time in seconds that the result of the inline query may be cached on the server. Defaults to 300.
     * @param isPersonal Pass True, if results may be cached on the server side only for the user that sent the query. By default, results may be returned to any user who sends the same query.
     * @param nextOffset Pass the offset that a client should send in the next query with the same text to receive more results. Pass an empty string if there are no more results or if you don‘t support pagination. Offset length can’t exceed 64 bytes.
     * @param switchPmText If passed, clients will display a button with specified text that switches the user to a private chat with the bot and sends the bot a start message with the parameter switch_pm_parameter
     * @param switchPmParameter Parameter for the start message sent to the bot when user presses the switch button
     * @return True on success
     */
    bool answerInlineQuery(const std::string& inlineQueryId, const std::vector<InlineQueryResult::Ptr>& results,
                            int32_t cacheTime = 300, bool isPersonal = false, const std::string& nextOffset = "", const std::string& switchPmText = "", const std::string& switchPmParameter = "") const;

    /**
     * @brief Use this method to kick a user from a group or a supergroup.
     * @param chatId Unique identifier for the target group.
     * @param userId Unique identifier of the target user.
     * @param untilDate Optional. Date when the user will be unbanned, unix time. If user is banned for more than 366 days or less than 30 seconds from the current time they are considered to be banned forever.
     * @return True on success
     */
    bool kickChatMember(int64_t chatId, int32_t userId, uint64_t untilDate = 0) const;

    /**
     * @brief Use this method to unban a previously kicked user in a supergroup.
     * @param chatId Unique identifier for the target group.
     * @param userId Unique identifier of the target user.
     * @return True on success
     */
    bool unbanChatMember(int64_t chatId, int32_t userId) const;

    /**
     * @brief Use this method to restrict a user in a supergroup.
     * @param chatId Unique identifier for the target chat of the target supergroup.
     * @param userId Unique identifier of the target user.
     * @param untilDate Optional. Date when restrictions will be lifted for the user, unix time. If user is restricted for more than 366 days or less than 30 seconds from the current time, they are considered to be restricted forever.
     * @param canSendMessages Optional. Pass True, if the user can send text messages, contacts, locations and venues.
     * @param canSendMediaMessages Optional. Pass True, if the user can send audios, documents, photos, videos, video notes and voice notes, implies can_send_messages.
     * @param canSendOtherMessages Optional. Pass True, if the user can send animations, games, stickers and use inline bots, implies can_send_media_messages.
     * @param canAddWebPagePreviews Optional. Pass True, if the user may add web page previews to their messages, implies can_send_media_messages.
     * @return True on success
     */
    bool restrictChatMember(int64_t chatId, int32_t userId, uint64_t untilDate = 0, bool canSendMessages = false,
                            bool canSendMediaMessages = false, bool canSendOtherMessages = false, bool canAddWebPagePreviews = false) const;

    /**
     * @brief Use this method to promote or demote a user in a supergroup or a channel.
     * @param chatId Unique identifier for the target chat of the target supergroup or channal.
     * @param userId Unique identifier of the target user.
     * @param canChangeInfo Optional. Pass True, if the administrator can change chat title, photo and other settings.
     * @param canPostMessages Optional. Pass True, if the administrator can create channel posts, channels only.
     * @param canEditMessages Optional. Pass True, if the administrator can edit messages of other users and can pin messages, channels only.
     * @param canDeleteMessages Optional. Pass True, if the administrator can delete messages of other users.
     * @param canInviteUsers Optional. Pass True, if the administrator can invite new users to the chat.
     * @param canRestrictMembers Optional. Pass True, if the administrator can restrict, ban or unban chat members.
     * @param canPinMessages Optional. Pass True, if the administrator can pin messages, supergroups only.
     * @param canPromoteMembers Optional. Pass True, if the administrator can add new administrators with a subset of his own privileges or demote administrators that he has promoted, directly or indirectly (promoted by administrators that were appointed by him).
     * @return True on success
     */
    bool promoteChatMember(int64_t chatId, int32_t userId, bool canChangeInfo = false, bool canPostMessages = false,
                           bool canEditMessages = false, bool canDeleteMessages = false, bool canInviteUsers = false, bool canPinMessages = false, bool canPromoteMembers = false) const;

    /**
     * @brief Use this method to generate a new invite link for a chat; any previously generated link is revoked.
     * @param chatId Unique identifier for the target chat.
     * @return The new invite link as String on success.
     */
    std::string exportChatInviteLink(int64_t chatId) const;

    /**
     * @brief Use this method to set a new profile photo for the chat.
     *
     * Photos can't be changed for private chats.
     *
     * @param chatId Unique identifier for the target chat.
     * @param photo New chat photo.
     * @return True on success
     */
    bool setChatPhoto(int64_t chatId, InputFile::Ptr photo) const;

    /**
     * @brief Use this method to delete a chat photo.
     *
     * Photos can't be changed for private chats.
     *
     * @param chatId Unique identifier for the target chat.
     * @return True on success
     */
    bool deleteChatPhoto(int64_t chatId) const;

    /**
     * @brief Use this method to change the title of a chat.
     *
     * Titles can't be changed for private chats.
     *
     * @param chatId Unique identifier for the target chat.
     * @param title New chat title, 1-255 characters.
     * @return True on success
     */
    bool setChatTitle(int64_t chatId, const std::string& title) const;

    /**
     * @brief Use this method to change the description of a supergroup or a channel.
     * @param chatId Unique identifier for the target chat.
     * @param description New chat description, 1-255 characters.
     * @return True on success
     */
    bool setChatDescription(int64_t chatId, const std::string& description) const;

    /**
     * @brief Use this method to pin a message in a supergroup or a channel.
     * @param chatId Unique identifier for the target chat.
     * @param messageId Identifier of a message to pin.
     * @param disableNotification Optional. Pass True, if it is not necessary to send a notification to all chat members about the new pinned message. Notifications are always disabled in channels.
     * @return True on success
     */
    bool pinChatMessage(int64_t chatId, int32_t messageId, bool disableNotification = false) const;

    /**
     * @brief Use this method to unpin a message in a supergroup or a channel.
     * @param chatId Unique identifier for the target chat.
     * @return True on success
     */
    bool unpinChatMessage(int64_t chatId) const;

    /**
     * @brief Use this method to set the score of the specified user in a game.
     *
     * Returns an error, if the new score is not greater than the user's current score in the chat and force is False.
     *
     * @param userId User identifier.
     * @param score New score, must be non-negative.
     * @param force Optional. Pass True, if the high score is allowed to decrease. This can be useful when fixing mistakes or banning cheaters.
     * @param disableEditMessage Optional. Pass True, if the game message should not be automatically edited to include the current scoreboard.
     * @param chatId Optional. Required if inlineMessageId is not specified. Unique identifier for the target chat
     * @param messageId Optional. Required if inlineMessageId is not specified. Identifier of the sent message
     * @param inlineMessageId Optional. Required if chatId and messageId are not specified. Identifier of the inline message
     * @return On success, if the message was sent by the bot, returns the edited Message, otherwise returns nullptr.
     */
    Message::Ptr setGameScore(int32_t userId, int32_t score, bool force = false, bool disableEditMessage = false,
                              int64_t chatId = 0, int32_t messageId = 0, const std::string& inlineMessageId = "") const;

    /**
     * @brief Use this method to get data for high score tables.
     *
     * Will return the score of the specified user and several of his neighbors in a game.
     *
     * @param userId User identifier.
     * @param chatId Optional. Required if inlineMessageId is not specified. Unique identifier for the target chat
     * @param messageId Optional. Required if inlineMessageId is not specified. Identifier of the sent message
     * @param inlineMessageId Optional. Required if chatId and messageId are not specified. Identifier of the inline message
     * @return On success, returns an Array of GameHighScore objects.
     */
    std::vector<GameHighScore::Ptr> getGameHighScores(int32_t userId, int32_t score, bool force = false,
                                                      bool disableEditMessage = false, int64_t chatId = 0, int32_t messageId = 0, const std::string& inlineMessageId = "") const;


    /**
     * @brief Downloads file from Telegram and saves it in memory.
     * @param filePath Telegram file path.
     * @param args Additional api parameters.
     * @return File contents in a string.
     */
    std::string downloadFile(const std::string& filePath, const std::vector<HttpReqArg>& args = std::vector<HttpReqArg>()) const;

private:
    boost::property_tree::ptree sendRequest(const std::string& method, const std::vector<HttpReqArg>& args = std::vector<HttpReqArg>()) const;

    const std::string _token;
    const HttpClient& _httpClient;
    const TgTypeParser _tgTypeParser;
};

}

#endif //TGBOT_CPP_API_H
