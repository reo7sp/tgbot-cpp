#ifndef TGBOT_API_H
#define TGBOT_API_H

#include "tgbot/TgException.h"
#include "tgbot/TgTypeParser.h"
#include "tgbot/net/HttpClient.h"
#include "tgbot/net/HttpReqArg.h"
#include "tgbot/tools/StringTools.h"
#include "tgbot/types/User.h"
#include "tgbot/types/Message.h"
#include "tgbot/types/MessageId.h"
#include "tgbot/types/GenericReply.h"
#include "tgbot/types/InputFile.h"
#include "tgbot/types/UserProfilePhotos.h"
#include "tgbot/types/Update.h"
#include "tgbot/types/InlineQueryResult.h"
#include "tgbot/types/Venue.h"
#include "tgbot/types/WebhookInfo.h"
#include "tgbot/types/ChatMember.h"
#include "tgbot/types/Sticker.h"
#include "tgbot/types/StickerSet.h"
#include "tgbot/types/File.h"
#include "tgbot/types/InputMedia.h"
#include "tgbot/types/GameHighScore.h"
#include "tgbot/types/SentWebAppMessage.h"
#include "tgbot/types/LabeledPrice.h"
#include "tgbot/types/ShippingOption.h"
#include "tgbot/types/BotCommand.h"
#include "tgbot/types/ForumTopic.h"

#include <boost/property_tree/ptree.hpp>
#include <boost/variant.hpp>

#include <cstdint>
#include <memory>
#include <string>
#include <utility>
#include <vector>

namespace TgBot {

class Bot;

/**
 * @brief This class executes telegram api methods. Telegram docs: <https://core.telegram.org/bots/api#available-methods>
 *
 * @ingroup general
 */
class TGBOT_API Api {

typedef std::shared_ptr<std::vector<std::string>> StringArrayPtr;

friend class Bot;

public:
    Api(std::string token, const HttpClient& httpClient, const std::string& url);

    /**
     * @brief Use this method to receive incoming updates using long polling ([wiki](https://en.wikipedia.org/wiki/Push_technology#Long_polling)).
     *
     * Notes
     * - This method will not work if an outgoing webhook is set up.
     * - In order to avoid getting duplicate updates, recalculate offset after each server response.
     *
     * @param offset Optional. Identifier of the first update to be returned. Must be greater by one than the highest among the identifiers of previously received updates. By default, updates starting with the earliest unconfirmed update are returned. An update is considered confirmed as soon as Api::getUpdates is called with an offset higher than its updateId. The negative offset can be specified to retrieve updates starting from -offset update from the end of the updates queue. All previous updates will be forgotten.
     * @param limit Optional. Limits the number of updates to be retrieved. Values between 1-100 are accepted. Defaults to 100.
     * @param timeout Optional. Timeout in seconds for long polling. Defaults to 0, i.e. usual short polling. Should be positive, short polling should be used for testing purposes only.
     * @param allowedUpdates Optional. A JSON-serialized list of the update types you want your bot to receive. For example, specify ["message", "edited_channel_post", "callback_query"] to only receive updates of these types. See Update for a complete list of available update types. Specify an empty list to receive all update types except chat_member, message_reaction, and message_reaction_count (default). If not specified, the previous setting will be used. Please note that this parameter doesn't affect updates created before the call to the getUpdates, so unwanted updates may be received for a short period of time.
     *
     * @return Returns an Array of Update objects.
     */
    std::vector<Update::Ptr> getUpdates(std::int32_t offset = 0,
                                        std::int32_t limit = 100,
                                        std::int32_t timeout = 0,
                                        const StringArrayPtr& allowedUpdates = nullptr) const;

    /**
     * @brief Use this method to specify a URL and receive incoming updates via an outgoing webhook.
     *
     * Whenever there is an update for the bot, we will send an HTTPS POST request to the specified URL, containing a JSON-serialized Update.
     * In case of an unsuccessful request, we will give up after a reasonable amount of attempts.
     *
     * If you'd like to make sure that the webhook was set by you, you can specify secret data in the parameter secretToken.
     * If specified, the request will contain a header “X-Telegram-Bot-Api-Secret-Token” with the secret token as content.
     *
     * Notes
     * - You will not be able to receive updates using Api::getUpdates for as long as an outgoing webhook is set up.
     * - To use a self-signed certificate, you need to upload your [public key certificate](https://core.telegram.org/bots/self-signed) using certificate parameter. Please upload as InputFile, sending a String will not work.
     * - Ports currently supported for webhooks: 443, 80, 88, 8443.
     *
     * If you're having any trouble setting up webhooks, please check out [this amazing guide to webhooks](https://core.telegram.org/bots/webhooks).
     *
     * @param url HTTPS URL to send updates to. Use an empty string to remove webhook integration
     * @param certificate Optional. Upload your public key certificate so that the root certificate in use can be checked. See our [self-signed guide](https://core.telegram.org/bots/self-signed) for details.
     * @param maxConnections Optional. The maximum allowed number of simultaneous HTTPS connections to the webhook for update delivery, 1-100. Defaults to 40. Use lower values to limit the load on your bot's server, and higher values to increase your bot's throughput.
     * @param allowedUpdates Optional. A JSON-serialized list of the update types you want your bot to receive. For example, specify ["message", "edited_channel_post", "callback_query"] to only receive updates of these types. See Update for a complete list of available update types. Specify an empty list to receive all update types except chat_member, message_reaction, and message_reaction_count (default). If not specified, the previous setting will be used. Please note that this parameter doesn't affect updates created before the call to the setWebhook, so unwanted updates may be received for a short period of time.
     * @param ipAddress Optional. The fixed IP address which will be used to send webhook requests instead of the IP address resolved through DNS
     * @param dropPendingUpdates Optional. Pass True to drop all pending updates
     * @param secretToken Optional. A secret token to be sent in a header “X-Telegram-Bot-Api-Secret-Token” in every webhook request, 1-256 characters. Only characters A-Z, a-z, 0-9, _ and - are allowed. The header is useful to ensure that the request comes from a webhook set by you.
     *
     * @return Returns True on success.
     */
    bool setWebhook(const std::string& url,
                    InputFile::Ptr certificate = nullptr,
                    std::int32_t maxConnections = 40,
                    const StringArrayPtr& allowedUpdates = nullptr,
                    const std::string& ipAddress = "",
                    bool dropPendingUpdates = false,
                    const std::string& secretToken = "") const;

    /**
     * @brief Use this method to remove webhook integration if you decide to switch back to Api::getUpdates.
     *
     * @param dropPendingUpdates Optional. Pass True to drop all pending updates
     *
     * @return Returns True on success.
     */
    bool deleteWebhook(bool dropPendingUpdates = false) const;

    /**
     * @brief Use this method to get current webhook status.
     *
     * Requires no parameters.
     * If the bot is using Api::getUpdates, will return an object with the url field empty.
     *
     * @return On success, returns a WebhookInfo object. If the bot is using getUpdates, will return a nullptr.
     */
    WebhookInfo::Ptr getWebhookInfo() const;

    /**
     * @brief A simple method for testing your bot's authentication token.
     * 
     * Requires no parameters.
     * 
     * @return Returns basic information about the bot in form of a User object.
     */
    User::Ptr getMe() const;

    /**
     * @brief Use this method to log out from the cloud Bot API server before launching the bot locally.
     * 
     * You must log out the bot before running it locally, otherwise there is no guarantee that the bot will receive updates.
     * After a successful call, you can immediately log in on a local server, but will not be able to log in back to the cloud Bot API server for 10 minutes.
     * Requires no parameters.
     *
     * @return Returns True on success.
     */
    bool logOut() const;

    /**
     * @brief Use this method to close the bot instance before moving it from one local server to another.
     *
     * You need to delete the webhook before calling this method to ensure that the bot isn't launched again after server restart.
     * The method will return error 429 in the first 10 minutes after the bot is launched.
     * Requires no parameters.
     *
     * @return Returns True on success.
     */
    bool close() const;

    /**
     * @brief Use this method to send text messages.
     *
     * @param chatId Unique identifier for the target chat or username of the target channel (in the format @channelusername)
     * @param text Text of the message to be sent, 1-4096 characters after entities parsing
     * @param linkPreviewOptions Optional. Link preview generation options for the message
     * @param replyParameters Optional. Description of the message to reply to
     * @param replyMarkup Optional. Additional interface options. A JSON-serialized object for an [inline keyboard](https://core.telegram.org/bots/features#inline-keyboards), [custom reply keyboard](https://core.telegram.org/bots/features#keyboards), instructions to remove a reply keyboard or to force a reply from the user. Not supported for messages sent on behalf of a business account
     * @param parseMode Optional. Mode for parsing entities in the message text. See [formatting options](https://core.telegram.org/bots/api#formatting-options) for more details.
     * @param disableNotification Optional. Sends the message [silently](https://telegram.org/blog/channels-2-0#silent-messages). Users will receive a notification with no sound.
     * @param entities Optional. A JSON-serialized list of special entities that appear in message text, which can be specified instead of parseMode
     * @param messageThreadId Optional. Unique identifier for the target message thread (topic) of the forum; for forum supergroups only
     * @param protectContent Optional. Protects the contents of the sent message from forwarding and saving
     * @param businessConnectionId Optional. Unique identifier of the business connection on behalf of which the message will be sent
     *
     * @return On success, the sent Message is returned.
     */
    Message::Ptr sendMessage(boost::variant<std::int64_t, std::string> chatId,
                             const std::string& text,
                             LinkPreviewOptions::Ptr linkPreviewOptions = nullptr,
                             ReplyParameters::Ptr replyParameters = nullptr,
                             GenericReply::Ptr replyMarkup = nullptr,
                             const std::string& parseMode = "",
                             bool disableNotification = false,
                             const std::vector<MessageEntity::Ptr>& entities = std::vector<MessageEntity::Ptr>(),
                             std::int32_t messageThreadId = 0,
                             bool protectContent = false,
                             const std::string& businessConnectionId = "") const;

    /**
     * @brief Use this method to forward messages of any kind.
     *
     * Service messages and messages with protected content can't be forwarded.
     *
     * @param chatId Unique identifier for the target chat or username of the target channel (in the format @channelusername)
     * @param fromChatId Unique identifier for the chat where the original message was sent (or channel username in the format @channelusername)
     * @param messageId Message identifier in the chat specified in fromChatId
     * @param disableNotification Optional. Sends the message [silently](https://telegram.org/blog/channels-2-0#silent-messages). Users will receive a notification with no sound.
     * @param protectContent Optional. Protects the contents of the forwarded message from forwarding and saving
     * @param messageThreadId Optional. Unique identifier for the target message thread (topic) of the forum; for forum supergroups only
     *
     * @return On success, the sent Message is returned.
     */
    Message::Ptr forwardMessage(boost::variant<std::int64_t, std::string> chatId,
                                boost::variant<std::int64_t, std::string> fromChatId,
                                std::int32_t messageId,
                                bool disableNotification = false,
                                bool protectContent = false,
                                std::int32_t messageThreadId = 0) const;

    /**
     * @brief Use this method to forward multiple messages of any kind.
     *
     * If some of the specified messages can't be found or forwarded, they are skipped.
     * Service messages and messages with protected content can't be forwarded.
     * Album grouping is kept for forwarded messages.
     *
     * @param chatId Unique identifier for the target chat or username of the target channel (in the format @channelusername)
     * @param fromChatId Unique identifier for the chat where the original messages were sent (or channel username in the format @channelusername)
     * @param messageIds A JSON-serialized list of 1-100 identifiers of messages in the chat fromChatId to forward. The identifiers must be specified in a strictly increasing order.
     * @param messageThreadId Optional. Unique identifier for the target message thread (topic) of the forum; for forum supergroups only
     * @param disableNotification Optional. Sends the messages [silently](https://telegram.org/blog/channels-2-0#silent-messages). Users will receive a notification with no sound.
     * @param protectContent Optional. Protects the contents of the forwarded message from forwarding and saving
     *
     * @return On success, an array of MessageId of the sent messages is returned.
     */
    std::vector<MessageId::Ptr> forwardMessages(boost::variant<std::int64_t, std::string> chatId,
                                                boost::variant<std::int64_t, std::string> fromChatId,
                                                const std::vector<std::int32_t>& messageIds,
                                                std::int32_t messageThreadId = 0,
                                                bool disableNotification = false,
                                                bool protectContent = false) const;

    /**
     * @brief Use this method to copy messages of any kind.
     *
     * Service messages, giveaway messages, giveaway winners messages, and invoice messages can't be copied.
     * A quiz Poll can be copied only if the value of the field correctOptionId is known to the bot.
     * The method is analogous to the method Api::forwardMessage, but the copied message doesn't have a link to the original message.
     *
     * @param chatId Unique identifier for the target chat or username of the target channel (in the format @channelusername)
     * @param fromChatId Unique identifier for the chat where the original message was sent (or channel username in the format @channelusername)
     * @param messageId Message identifier in the chat specified in fromChatId
     * @param caption Optional. New caption for media, 0-1024 characters after entities parsing. If not specified, the original caption is kept
     * @param parseMode Optional. Mode for parsing entities in the new caption. See [formatting options](https://core.telegram.org/bots/api#formatting-options) for more details.
     * @param captionEntities Optional. A JSON-serialized list of special entities that appear in the new caption, which can be specified instead of parseMode
     * @param disableNotification Optional. Sends the message [silently](https://telegram.org/blog/channels-2-0#silent-messages). Users will receive a notification with no sound.
     * @param replyParameters Optional. Description of the message to reply to
     * @param replyMarkup Optional. Additional interface options. A JSON-serialized object for an [inline keyboard](https://core.telegram.org/bots/features#inline-keyboards), [custom reply keyboard](https://core.telegram.org/bots/features#keyboards), instructions to remove reply keyboard or to force a reply from the user.
     * @param protectContent Optional. Protects the contents of the sent message from forwarding and saving
     * @param messageThreadId Optional. Unique identifier for the target message thread (topic) of the forum; for forum supergroups only
     *
     * @return Returns the MessageId of the sent message on success.
     */
    MessageId::Ptr copyMessage(boost::variant<std::int64_t, std::string> chatId,
                               boost::variant<std::int64_t, std::string> fromChatId,
                               std::int32_t messageId,
                               const std::string& caption = "",
                               const std::string& parseMode = "",
                               const std::vector<MessageEntity::Ptr>& captionEntities = std::vector<MessageEntity::Ptr>(),
                               bool disableNotification = false,
                               ReplyParameters::Ptr replyParameters = nullptr,
                               GenericReply::Ptr replyMarkup = std::make_shared<GenericReply>(),
                               bool protectContent = false,
                               std::int32_t messageThreadId = 0) const;

    /**
     * @brief Use this method to copy messages of any kind.
     *
     * If some of the specified messages can't be found or copied, they are skipped.
     * Service messages, giveaway messages, giveaway winners messages, and invoice messages can't be copied.
     * A quiz Poll can be copied only if the value of the field correctOptionId is known to the bot.
     * The method is analogous to the method Api::forwardMessages, but the copied messages don't have a link to the original message.
     * Album grouping is kept for copied messages.
     *
     * @param chatId Unique identifier for the target chat or username of the target channel (in the format @channelusername)
     * @param fromChatId Unique identifier for the chat where the original messages were sent (or channel username in the format @channelusername)
     * @param messageIds A JSON-serialized list of 1-100 identifiers of messages in the chat fromChatId to copy. The identifiers must be specified in a strictly increasing order.
     * @param messageThreadId Optional. Unique identifier for the target message thread (topic) of the forum; for forum supergroups only
     * @param disableNotification Optional. Sends the messages [silently](https://telegram.org/blog/channels-2-0#silent-messages). Users will receive a notification with no sound.
     * @param protectContent Optional. Protects the contents of the sent messages from forwarding and saving
     * @param removeCaption Optional. Pass True to copy the messages without their captions
     *
     * @return On success, an array of MessageId of the sent messages is returned.
     */
    std::vector<MessageId::Ptr> copyMessages(boost::variant<std::int64_t, std::string> chatId,
                                             boost::variant<std::int64_t, std::string> fromChatId,
                                             const std::vector<std::int32_t>& messageIds,
                                             std::int32_t messageThreadId = 0,
                                             bool disableNotification = false,
                                             bool protectContent = false,
                                             bool removeCaption = false) const;

    /**
     * @brief Use this method to send photos.
     *
     * @param chatId Unique identifier for the target chat or username of the target channel (in the format @channelusername)
     * @param photo Photo to send. Pass a fileId as String to send a photo that exists on the Telegram servers (recommended), pass an HTTP URL as a String for Telegram to get a photo from the Internet, or upload a new photo using multipart/form-data. The photo must be at most 10 MB in size. The photo's width and height must not exceed 10000 in total. Width and height ratio must be at most 20. https://core.telegram.org/bots/api#sending-files
     * @param caption Optional. Photo caption (may also be used when resending photos by fileId), 0-1024 characters after entities parsing
     * @param replyParameters Optional. Description of the message to reply to
     * @param replyMarkup Optional. Additional interface options. A JSON-serialized object for an [inline keyboard](https://core.telegram.org/bots/features#inline-keyboards), [custom reply keyboard](https://core.telegram.org/bots/features#keyboards), instructions to remove a reply keyboard or to force a reply from the user. Not supported for messages sent on behalf of a business account
     * @param parseMode Optional. Mode for parsing entities in the photo caption. See https://core.telegram.org/bots/api#formatting-options for more details.
     * @param disableNotification Optional. Sends the message silently. Users will receive a notification with no sound.
     * @param captionEntities Optional. A JSON-serialized list of special entities that appear in the caption, which can be specified instead of parseMode
     * @param messageThreadId Optional. Unique identifier for the target message thread (topic) of the forum; for forum supergroups only
     * @param protectContent Optional. Protects the contents of the sent message from forwarding and saving
     * @param hasSpoiler Optional. Pass True if the photo needs to be covered with a spoiler animation
     * @param businessConnectionId Optional. Unique identifier of the business connection on behalf of which the message will be sent
     *
     * @return On success, the sent Message is returned.
     */
    Message::Ptr sendPhoto(boost::variant<std::int64_t, std::string> chatId,
                           boost::variant<InputFile::Ptr, std::string> photo,
                           const std::string& caption = "",
                           ReplyParameters::Ptr replyParameters = nullptr,
                           GenericReply::Ptr replyMarkup = nullptr,
                           const std::string& parseMode = "",
                           bool disableNotification = false,
                           const std::vector<MessageEntity::Ptr>& captionEntities = std::vector<MessageEntity::Ptr>(),
                           std::int32_t messageThreadId = 0,
                           bool protectContent = false,
                           bool hasSpoiler = false,
                           const std::string& businessConnectionId = "") const;

    /**
     * @brief Use this method to send audio files, if you want Telegram clients to display them in the music player.
     *
     * Your audio must be in the .MP3 or .M4A format.
     * Bots can currently send audio files of up to 50 MB in size, this limit may be changed in the future.
     *
     * For sending voice messages, use the Api::sendVoice method instead.
     *
     * @param chatId Unique identifier for the target chat or username of the target channel (in the format @channelusername)
     * @param audio Audio file to send. Pass a fileId as String to send an audio file that exists on the Telegram servers (recommended), pass an HTTP URL as a String for Telegram to get an audio file from the Internet, or upload a new one using multipart/form-data. https://core.telegram.org/bots/api#sending-files
     * @param caption Optional. Audio caption, 0-1024 characters after entities parsing
     * @param duration Optional. Duration of the audio in seconds
     * @param performer Optional. Performer
     * @param title Optional. Track name
     * @param thumbnail Optional. Thumbnail of the file sent; can be ignored if thumbnail generation for the file is supported server-side. The thumbnail should be in JPEG format and less than 200 kB in size. A thumbnail's width and height should not exceed 320. Ignored if the file is not uploaded using multipart/form-data. Thumbnails can't be reused and can be only uploaded as a new file, so you can pass “attach://<file_attach_name>” if the thumbnail was uploaded using multipart/form-data under <file_attach_name>. https://core.telegram.org/bots/api#sending-files
     * @param replyParameters Optional. Description of the message to reply to
     * @param replyMarkup Optional. Additional interface options. A JSON-serialized object for an [inline keyboard](https://core.telegram.org/bots/features#inline-keyboards), [custom reply keyboard](https://core.telegram.org/bots/features#keyboards), instructions to remove a reply keyboard or to force a reply from the user. Not supported for messages sent on behalf of a business account
     * @param parseMode Optional. Mode for parsing entities in the audio caption. See https://core.telegram.org/bots/api#formatting-options for more details.
     * @param disableNotification Optional. Sends the message silently. Users will receive a notification with no sound.
     * @param captionEntities Optional. A JSON-serialized list of special entities that appear in the caption, which can be specified instead of parseMode
     * @param messageThreadId Optional. Unique identifier for the target message thread (topic) of the forum; for forum supergroups only
     * @param protectContent Optional. Protects the contents of the sent message from forwarding and saving
     * @param businessConnectionId Optional. Unique identifier of the business connection on behalf of which the message will be sent
     *
     * @return On success, the sent Message is returned.
     */
    Message::Ptr sendAudio(boost::variant<std::int64_t, std::string> chatId,
                           boost::variant<InputFile::Ptr, std::string> audio,
                           const std::string& caption = "",
                           std::int32_t duration = 0,
                           const std::string& performer = "",
                           const std::string& title = "",
                           boost::variant<InputFile::Ptr, std::string> thumbnail = "",
                           ReplyParameters::Ptr replyParameters = nullptr,
                           GenericReply::Ptr replyMarkup = nullptr,
                           const std::string& parseMode = "",
                           bool disableNotification = false,
                           const std::vector<MessageEntity::Ptr>& captionEntities = std::vector<MessageEntity::Ptr>(),
                           std::int32_t messageThreadId = 0,
                           bool protectContent = false,
                           const std::string& businessConnectionId = "") const;

    /**
     * @brief Use this method to send general files.
     *
     * Bots can currently send files of any type of up to 50 MB in size, this limit may be changed in the future.
     *
     * @param chatId Unique identifier for the target chat or username of the target channel (in the format @channelusername)
     * @param document File to send. Pass a fileId as String to send a file that exists on the Telegram servers (recommended), pass an HTTP URL as a String for Telegram to get a file from the Internet, or upload a new one using multipart/form-data. https://core.telegram.org/bots/api#sending-files
     * @param thumbnail Optional. Thumbnail of the file sent; can be ignored if thumbnail generation for the file is supported server-side. The thumbnail should be in JPEG format and less than 200 kB in size. A thumbnail's width and height should not exceed 320. Ignored if the file is not uploaded using multipart/form-data. Thumbnails can't be reused and can be only uploaded as a new file, so you can pass “attach://<file_attach_name>” if the thumbnail was uploaded using multipart/form-data under <file_attach_name>. https://core.telegram.org/bots/api#sending-files
     * @param caption Optional. Document caption (may also be used when resending documents by fileId), 0-1024 characters after entities parsing
     * @param replyParameters Optional. Description of the message to reply to
     * @param replyMarkup Optional. Additional interface options. A JSON-serialized object for an [inline keyboard](https://core.telegram.org/bots/features#inline-keyboards), [custom reply keyboard](https://core.telegram.org/bots/features#keyboards), instructions to remove a reply keyboard or to force a reply from the user. Not supported for messages sent on behalf of a business account
     * @param parseMode Optional. Mode for parsing entities in the document caption. See https://core.telegram.org/bots/api#formatting-options for more details.
     * @param disableNotification Optional. Sends the message silently. Users will receive a notification with no sound.
     * @param captionEntities Optional. A JSON-serialized list of special entities that appear in the caption, which can be specified instead of parseMode
     * @param disableContentTypeDetection Optional. Disables automatic server-side content type detection for files uploaded using multipart/form-data
     * @param messageThreadId Optional. Unique identifier for the target message thread (topic) of the forum; for forum supergroups only
     * @param protectContent Optional. Protects the contents of the sent message from forwarding and saving
     * @param businessConnectionId Optional. Unique identifier of the business connection on behalf of which the message will be sent
     *
     * @return On success, the sent Message is returned.
     */
    Message::Ptr sendDocument(boost::variant<std::int64_t, std::string> chatId,
                              boost::variant<InputFile::Ptr, std::string> document,
                              boost::variant<InputFile::Ptr, std::string> thumbnail = "",
                              const std::string& caption = "",
                              ReplyParameters::Ptr replyParameters = nullptr,
                              GenericReply::Ptr replyMarkup = nullptr,
                              const std::string& parseMode = "",
                              bool disableNotification = false,
                              const std::vector<MessageEntity::Ptr>& captionEntities = std::vector<MessageEntity::Ptr>(),
                              bool disableContentTypeDetection = false,
                              std::int32_t messageThreadId = 0,
                              bool protectContent = false,
                              const std::string& businessConnectionId = "") const;

    /**
     * @brief Use this method to send video files, Telegram clients support MPEG4 videos (other formats may be sent as Document).
     *
     * Bots can currently send video files of up to 50 MB in size, this limit may be changed in the future.
     *
     * @param chatId Unique identifier for the target chat or username of the target channel (in the format @channelusername)
     * @param video Video to send. Pass a fileId as String to send a video that exists on the Telegram servers (recommended), pass an HTTP URL as a String for Telegram to get a video from the Internet, or upload a new video using multipart/form-data. https://core.telegram.org/bots/api#sending-files
     * @param supportsStreaming Optional. Pass True if the uploaded video is suitable for streaming
     * @param duration Optional. Duration of sent video in seconds
     * @param width Optional. Video width
     * @param height Optional. Video height
     * @param thumbnail Optional. Thumbnail of the file sent; can be ignored if thumbnail generation for the file is supported server-side. The thumbnail should be in JPEG format and less than 200 kB in size. A thumbnail's width and height should not exceed 320. Ignored if the file is not uploaded using multipart/form-data. Thumbnails can't be reused and can be only uploaded as a new file, so you can pass “attach://<file_attach_name>” if the thumbnail was uploaded using multipart/form-data under <file_attach_name>. https://core.telegram.org/bots/api#sending-files
     * @param caption Optional. Video caption (may also be used when resending videos by fileId), 0-1024 characters after entities parsing
     * @param replyParameters Optional. Description of the message to reply to
     * @param replyMarkup Optional. Additional interface options. A JSON-serialized object for an [inline keyboard](https://core.telegram.org/bots/features#inline-keyboards), [custom reply keyboard](https://core.telegram.org/bots/features#keyboards), instructions to remove a reply keyboard or to force a reply from the user. Not supported for messages sent on behalf of a business account
     * @param parseMode Optional. Mode for parsing entities in the video caption. See https://core.telegram.org/bots/api#formatting-options for more details.
     * @param disableNotification Optional. Sends the message silently. Users will receive a notification with no sound.
     * @param captionEntities Optional. A JSON-serialized list of special entities that appear in the caption, which can be specified instead of parseMode
     * @param messageThreadId Optional. Unique identifier for the target message thread (topic) of the forum; for forum supergroups only
     * @param protectContent Optional. Protects the contents of the sent message from forwarding and saving
     * @param hasSpoiler Optional. Pass True if the video needs to be covered with a spoiler animation
     * @param businessConnectionId Optional. Unique identifier of the business connection on behalf of which the message will be sent
     *
     * @return On success, the sent Message is returned.
     */
    Message::Ptr sendVideo(boost::variant<std::int64_t, std::string> chatId,
                           boost::variant<InputFile::Ptr, std::string> video,
                           bool supportsStreaming = false,
                           std::int32_t duration = 0,
                           std::int32_t width = 0,
                           std::int32_t height = 0,
                           boost::variant<InputFile::Ptr, std::string> thumbnail = "",
                           const std::string& caption = "",
                           ReplyParameters::Ptr replyParameters = nullptr,
                           GenericReply::Ptr replyMarkup = nullptr,
                           const std::string& parseMode = "",
                           bool disableNotification = false,
                           const std::vector<MessageEntity::Ptr>& captionEntities = std::vector<MessageEntity::Ptr>(),
                           std::int32_t messageThreadId = 0,
                           bool protectContent = false,
                           bool hasSpoiler = false,
                           const std::string& businessConnectionId = "") const;

    /**
     * @brief Use this method to send animation files (GIF or H.264/MPEG-4 AVC video without sound).
     *
     * Bots can currently send animation files of up to 50 MB in size, this limit may be changed in the future.
     *
     * @param chatId Unique identifier for the target chat or username of the target channel (in the format @channelusername)
     * @param animation Animation to send. Pass a fileId as String to send an animation that exists on the Telegram servers (recommended), pass an HTTP URL as a String for Telegram to get an animation from the Internet, or upload a new animation using multipart/form-data. https://core.telegram.org/bots/api#sending-files
     * @param duration Optional. Duration of sent animation in seconds
     * @param width Optional. Animation width
     * @param height Optional. Animation height
     * @param thumbnail Optional. Thumbnail of the file sent; can be ignored if thumbnail generation for the file is supported server-side. The thumbnail should be in JPEG format and less than 200 kB in size. A thumbnail's width and height should not exceed 320. Ignored if the file is not uploaded using multipart/form-data. Thumbnails can't be reused and can be only uploaded as a new file, so you can pass “attach://<file_attach_name>” if the thumbnail was uploaded using multipart/form-data under <file_attach_name>. https://core.telegram.org/bots/api#sending-files
     * @param caption Optional. Animation caption (may also be used when resending animation by fileId), 0-1024 characters after entities parsing
     * @param replyParameters Optional. Description of the message to reply to
     * @param replyMarkup Optional. Additional interface options. A JSON-serialized object for an [inline keyboard](https://core.telegram.org/bots/features#inline-keyboards), [custom reply keyboard](https://core.telegram.org/bots/features#keyboards), instructions to remove a reply keyboard or to force a reply from the user. Not supported for messages sent on behalf of a business account
     * @param parseMode Optional. Mode for parsing entities in the animation caption. See https://core.telegram.org/bots/api#formatting-options for more details.
     * @param disableNotification Optional. Sends the message silently. Users will receive a notification with no sound.
     * @param captionEntities Optional. A JSON-serialized list of special entities that appear in the caption, which can be specified instead of parseMode
     * @param messageThreadId Optional. Unique identifier for the target message thread (topic) of the forum; for forum supergroups only
     * @param protectContent Optional. Protects the contents of the sent message from forwarding and saving
     * @param hasSpoiler Optional. Pass True if the animation needs to be covered with a spoiler animation
     * @param businessConnectionId Optional. Unique identifier of the business connection on behalf of which the message will be sent
     *
     * @return On success, the sent Message is returned.
     */
    Message::Ptr sendAnimation(boost::variant<std::int64_t, std::string> chatId,
                               boost::variant<InputFile::Ptr, std::string> animation,
                               std::int32_t duration = 0,
                               std::int32_t width = 0,
                               std::int32_t height = 0,
                               boost::variant<InputFile::Ptr, std::string> thumbnail = "",
                               const std::string& caption = "",
                               ReplyParameters::Ptr replyParameters = nullptr,
                               GenericReply::Ptr replyMarkup = nullptr,
                               const std::string& parseMode = "",
                               bool disableNotification = false,
                               const std::vector<MessageEntity::Ptr>& captionEntities = std::vector<MessageEntity::Ptr>(),
                               std::int32_t messageThreadId = 0,
                               bool protectContent = false,
                               bool hasSpoiler = false,
                               const std::string& businessConnectionId = "") const;

    /**
     * @brief Use this method to send audio files, if you want Telegram clients to display the file as a playable voice message.
     *
     * For this to work, your audio must be in an .OGG file encoded with OPUS (other formats may be sent as Audio or Document).
     * Bots can currently send voice messages of up to 50 MB in size, this limit may be changed in the future.
     *
     * @param chatId Unique identifier for the target chat or username of the target channel (in the format @channelusername)
     * @param voice Audio file to send. Pass a fileId as String to send a file that exists on the Telegram servers (recommended), pass an HTTP URL as a String for Telegram to get a file from the Internet, or upload a new one using multipart/form-data. https://core.telegram.org/bots/api#sending-files
     * @param caption Optional. Voice message caption, 0-1024 characters after entities parsing
     * @param duration Optional. Duration of the voice message in seconds
     * @param replyParameters Optional. Description of the message to reply to
     * @param replyMarkup Optional. Additional interface options. A JSON-serialized object for an [inline keyboard](https://core.telegram.org/bots/features#inline-keyboards), [custom reply keyboard](https://core.telegram.org/bots/features#keyboards), instructions to remove a reply keyboard or to force a reply from the user. Not supported for messages sent on behalf of a business account
     * @param parseMode Optional. Mode for parsing entities in the voice message caption. See https://core.telegram.org/bots/api#formatting-options for more details.
     * @param disableNotification Optional. Sends the message silently. Users will receive a notification with no sound.
     * @param captionEntities Optional. A JSON-serialized list of special entities that appear in the caption, which can be specified instead of parseMode
     * @param messageThreadId Optional. Unique identifier for the target message thread (topic) of the forum; for forum supergroups only
     * @param protectContent Optional. Protects the contents of the sent message from forwarding and saving
     * @param businessConnectionId Optional. Unique identifier of the business connection on behalf of which the message will be sent
     *
     * @return On success, the sent Message is returned.
     */
    Message::Ptr sendVoice(boost::variant<std::int64_t, std::string> chatId,
                           boost::variant<InputFile::Ptr, std::string> voice,
                           const std::string& caption = "",
                           std::int32_t duration = 0,
                           ReplyParameters::Ptr replyParameters = nullptr,
                           GenericReply::Ptr replyMarkup = nullptr,
                           const std::string& parseMode = "",
                           bool disableNotification = false,
                           const std::vector<MessageEntity::Ptr>& captionEntities = std::vector<MessageEntity::Ptr>(),
                           std::int32_t messageThreadId = 0,
                           bool protectContent = false,
                           const std::string& businessConnectionId = "") const;

    /**
     * @brief Use this method to send video messages.
     *
     * As of v.4.0, Telegram clients support rounded square MPEG4 videos of up to 1 minute long.
     *
     * @param chatId Unique identifier for the target chat or username of the target channel (in the format @channelusername)
     * @param videoNote Video note to send. Pass a fileId as String to send a video note that exists on the Telegram servers (recommended) or upload a new video using multipart/form-data. https://core.telegram.org/bots/api#sending-files. Sending video notes by a URL is currently unsupported 
     * @param replyParameters Optional. Description of the message to reply to
     * @param disableNotification Optional. Sends the message silently. Users will receive a notification with no sound.
     * @param duration Optional. Duration of sent video in seconds
     * @param length Optional. Video width and height, i.e. diameter of the video message
     * @param thumbnail Optional. Thumbnail of the file sent; can be ignored if thumbnail generation for the file is supported server-side. The thumbnail should be in JPEG format and less than 200 kB in size. A thumbnail's width and height should not exceed 320. Ignored if the file is not uploaded using multipart/form-data. Thumbnails can't be reused and can be only uploaded as a new file, so you can pass “attach://<file_attach_name>” if the thumbnail was uploaded using multipart/form-data under <file_attach_name>. https://core.telegram.org/bots/api#sending-files
     * @param replyMarkup Optional. Additional interface options. A JSON-serialized object for an [inline keyboard](https://core.telegram.org/bots/features#inline-keyboards), [custom reply keyboard](https://core.telegram.org/bots/features#keyboards), instructions to remove a reply keyboard or to force a reply from the user. Not supported for messages sent on behalf of a business account
     * @param messageThreadId Optional. Unique identifier for the target message thread (topic) of the forum; for forum supergroups only
     * @param protectContent Optional. Protects the contents of the sent message from forwarding and saving
     * @param businessConnectionId Optional. Unique identifier of the business connection on behalf of which the message will be sent
     *
     * @return On success, the sent Message is returned.
     */
    Message::Ptr sendVideoNote(boost::variant<std::int64_t, std::string> chatId,
                               boost::variant<InputFile::Ptr, std::string> videoNote,
                               ReplyParameters::Ptr replyParameters = nullptr,
                               bool disableNotification = false,
                               std::int32_t duration = 0,
                               std::int32_t length = 0,
                               boost::variant<InputFile::Ptr, std::string> thumbnail = "",
                               GenericReply::Ptr replyMarkup = nullptr,
                               std::int32_t messageThreadId = 0,
                               bool protectContent = false,
                               const std::string& businessConnectionId = "") const;

    /**
     * @brief Use this method to send a group of photos, videos, documents or audios as an album.
     *
     * Documents and audio files can be only grouped in an album with messages of the same type.
     *
     * @param chatId Unique identifier for the target chat or username of the target channel (in the format @channelusername)
     * @param media A JSON-serialized array describing messages to be sent, must include 2-10 items
     * @param disableNotification Optional. Sends messages silently. Users will receive a notification with no sound.
     * @param replyParameters Optional. Description of the message to reply to
     * @param messageThreadId Optional. Unique identifier for the target message thread (topic) of the forum; for forum supergroups only
     * @param protectContent Optional. Protects the contents of the sent messages from forwarding and saving
     * @param businessConnectionId Optional. Unique identifier of the business connection on behalf of which the message will be sent
     *
     * @return On success, an array of Messages that were sent is returned.
     */
    std::vector<Message::Ptr> sendMediaGroup(boost::variant<std::int64_t, std::string> chatId,
                                             const std::vector<InputMedia::Ptr>& media,
                                             bool disableNotification = false,
                                             ReplyParameters::Ptr replyParameters = nullptr,
                                             std::int32_t messageThreadId = 0,
                                             bool protectContent = false,
                                             const std::string& businessConnectionId = "") const;

    /**
     * @brief Use this method to send point on the map.
     *
     * @param chatId Unique identifier for the target chat or username of the target channel (in the format @channelusername)
     * @param latitude Latitude of the location
     * @param longitude Longitude of the location
     * @param livePeriod Optional. Period in seconds for which the location will be updated (see https://telegram.org/blog/live-locations, should be between 60 and 86400.
     * @param replyParameters Optional. Description of the message to reply to
     * @param replyMarkup Optional. Additional interface options. A JSON-serialized object for an [inline keyboard](https://core.telegram.org/bots/features#inline-keyboards), [custom reply keyboard](https://core.telegram.org/bots/features#keyboards), instructions to remove a reply keyboard or to force a reply from the user. Not supported for messages sent on behalf of a business account
     * @param disableNotification Optional. Sends the message silently. Users will receive a notification with no sound.
     * @param horizontalAccuracy Optional. The radius of uncertainty for the location, measured in meters; 0-1500
     * @param heading Optional. For live locations, a direction in which the user is moving, in degrees. Must be between 1 and 360 if specified.
     * @param proximityAlertRadius Optional. For live locations, a maximum distance for proximity alerts about approaching another chat member, in meters. Must be between 1 and 100000 if specified.
     * @param messageThreadId Optional. Unique identifier for the target message thread (topic) of the forum; for forum supergroups only
     * @param protectContent Optional. Protects the contents of the sent message from forwarding and saving
     * @param businessConnectionId Optional. Unique identifier of the business connection on behalf of which the message will be sent
     *
     * @return On success, the sent Message is returned.
     */
    Message::Ptr sendLocation(boost::variant<std::int64_t, std::string> chatId,
                              float latitude,
                              float longitude,
                              std::int32_t livePeriod = 0,
                              ReplyParameters::Ptr replyParameters = nullptr,
                              GenericReply::Ptr replyMarkup = nullptr,
                              bool disableNotification = false,
                              float horizontalAccuracy = 0,
                              std::int32_t heading = 0,
                              std::int32_t proximityAlertRadius = 0,
                              std::int32_t messageThreadId = 0,
                              bool protectContent = false,
                              const std::string& businessConnectionId = "") const;

    /**
     * @brief Use this method to edit live location messages.
     * 
     * A location can be edited until its livePeriod expires or editing is explicitly disabled by a call to Api::stopMessageLiveLocation.
     * 
     * @param latitude Latitude of new location
     * @param longitude Longitude of new location
     * @param chatId Optional. Required if inlineMessageId is not specified. Unique identifier for the target chat or username of the target channel (in the format @channelusername)
     * @param messageId Optional. Required if inlineMessageId is not specified. Identifier of the message to edit
     * @param inlineMessageId Optional. Required if chatId and messageId are not specified. Identifier of the inline message
     * @param replyMarkup Optional. A JSON-serialized object for a new inline keyboard.
     * @param horizontalAccuracy Optional. The radius of uncertainty for the location, measured in meters; 0-1500
     * @param heading Optional. Direction in which the user is moving, in degrees. Must be between 1 and 360 if specified.
     * @param proximityAlertRadius Optional. The maximum distance for proximity alerts about approaching another chat member, in meters. Must be between 1 and 100000 if specified.
     * 
     * @return On success, the edited Message is returned.
     */
    Message::Ptr editMessageLiveLocation(float latitude,
                                         float longitude,
                                         boost::variant<std::int64_t, std::string> chatId = "",
                                         std::int32_t messageId = 0,
                                         const std::string& inlineMessageId = "",
                                         InlineKeyboardMarkup::Ptr replyMarkup = std::make_shared<InlineKeyboardMarkup>(),
                                         float horizontalAccuracy = 0,
                                         std::int32_t heading = 0,
                                         std::int32_t proximityAlertRadius = 0) const;

    /**
     * @brief Use this method to stop updating a live location message before livePeriod expires.
     * 
     * @param chatId Optional. Required if inlineMessageId is not specified. Unique identifier for the target chat or username of the target channel (in the format @channelusername)
     * @param messageId Optional. Required if inlineMessageId is not specified. Identifier of the message with live location to stop
     * @param inlineMessageId Optional. Required if chatId and messageId are not specified. Identifier of the inline message
     * @param replyMarkup Optional. A JSON-serialized object for a new inline keyboard.
     * 
     * @return On success, the edited Message is returned.
     */
    Message::Ptr stopMessageLiveLocation(boost::variant<std::int64_t, std::string> chatId = "",
                                         std::int32_t messageId = 0,
                                         const std::string& inlineMessageId = "",
                                         InlineKeyboardMarkup::Ptr replyMarkup = std::make_shared<InlineKeyboardMarkup>()) const;

    /**
     * @brief Use this method to send information about a venue.
     *
     * @param chatId Unique identifier for the target chat or username of the target channel (in the format @channelusername)
     * @param latitude Latitude of the venue
     * @param longitude Longitude of the venue
     * @param title Name of the venue
     * @param address Address of the venue
     * @param foursquareId Optional. Foursquare identifier of the venue
     * @param foursquareType Optional. Foursquare type of the venue, if known. (For example, “arts_entertainment/default”, “arts_entertainment/aquarium” or “food/icecream”.)
     * @param disableNotification Optional. Sends the message silently. Users will receive a notification with no sound.
     * @param replyParameters Optional. Description of the message to reply to
     * @param replyMarkup Optional. Additional interface options. A JSON-serialized object for an [inline keyboard](https://core.telegram.org/bots/features#inline-keyboards), [custom reply keyboard](https://core.telegram.org/bots/features#keyboards), instructions to remove a reply keyboard or to force a reply from the user. Not supported for messages sent on behalf of a business account
     * @param googlePlaceId Optional. Google Places identifier of the venue
     * @param googlePlaceType Optional. Google Places type of the venue. (See https://developers.google.com/places/web-service/supported_types)
     * @param messageThreadId Optional. Unique identifier for the target message thread (topic) of the forum; for forum supergroups only
     * @param protectContent Optional. Protects the contents of the sent message from forwarding and saving
     * @param businessConnectionId Optional. Unique identifier of the business connection on behalf of which the message will be sent
     *
     * @return On success, the sent Message is returned.
     */
    Message::Ptr sendVenue(boost::variant<std::int64_t, std::string> chatId,
                           float latitude,
                           float longitude,
                           const std::string& title,
                           const std::string& address,
                           const std::string& foursquareId = "",
                           const std::string& foursquareType = "",
                           bool disableNotification = false,
                           ReplyParameters::Ptr replyParameters = nullptr,
                           GenericReply::Ptr replyMarkup = nullptr,
                           const std::string& googlePlaceId = "",
                           const std::string& googlePlaceType = "",
                           std::int32_t messageThreadId = 0,
                           bool protectContent = false,
                           const std::string& businessConnectionId = "") const;

    /**
     * @brief Use this method to send phone contacts.
     *
     * @param chatId Unique identifier for the target chat or username of the target channel (in the format @channelusername)
     * @param phoneNumber Contact's phone number
     * @param firstName Contact's first name
     * @param lastName Optional. Contact's last name
     * @param vcard Optional. Additional data about the contact in the form of a vCard, 0-2048 bytes
     * @param disableNotification Optional. Sends the message silently. Users will receive a notification with no sound.
     * @param replyParameters Optional. Description of the message to reply to
     * @param replyMarkup Optional. Additional interface options. A JSON-serialized object for an [inline keyboard](https://core.telegram.org/bots/features#inline-keyboards), [custom reply keyboard](https://core.telegram.org/bots/features#keyboards), instructions to remove a reply keyboard or to force a reply from the user. Not supported for messages sent on behalf of a business account
     * @param messageThreadId Optional. Unique identifier for the target message thread (topic) of the forum; for forum supergroups only
     * @param protectContent Optional. Protects the contents of the sent message from forwarding and saving
     * @param businessConnectionId Optional. Unique identifier of the business connection on behalf of which the message will be sent
     *
     * @return On success, the sent Message is returned.
     */
    Message::Ptr sendContact(boost::variant<std::int64_t, std::string> chatId,
                             const std::string& phoneNumber,
                             const std::string& firstName,
                             const std::string& lastName = "",
                             const std::string& vcard = "",
                             bool disableNotification = false,
                             ReplyParameters::Ptr replyParameters = nullptr,
                             GenericReply::Ptr replyMarkup = nullptr,
                             std::int32_t messageThreadId = 0,
                             bool protectContent = false,
                             const std::string& businessConnectionId = "") const;

    /**
     * @brief Use this method to send a native poll.
     *
     * @param chatId Unique identifier for the target chat or username of the target channel (in the format @channelusername)
     * @param question Poll question, 1-300 characters
     * @param options A JSON-serialized list of answer options, 2-10 strings 1-100 characters each
     * @param disableNotification Optional. Sends the message silently. Users will receive a notification with no sound.
     * @param replyParameters Optional. Description of the message to reply to
     * @param replyMarkup Optional. Additional interface options. A JSON-serialized object for an [inline keyboard](https://core.telegram.org/bots/features#inline-keyboards), [custom reply keyboard](https://core.telegram.org/bots/features#keyboards), instructions to remove a reply keyboard or to force a reply from the user. Not supported for messages sent on behalf of a business account
     * @param isAnonymous Optional. True, if the poll needs to be anonymous, defaults to True
     * @param type Optional. Poll type, “quiz” or “regular”, defaults to “regular”
     * @param allowsMultipleAnswers Optional. True, if the poll allows multiple answers, ignored for polls in quiz mode, defaults to False
     * @param correctOptionId Optional. 0-based identifier of the correct answer option, required for polls in quiz mode
     * @param explanation Optional. Text that is shown when a user chooses an incorrect answer or taps on the lamp icon in a quiz-style poll, 0-200 characters with at most 2 line feeds after entities parsing
     * @param explanationParseMode Optional. Mode for parsing entities in the explanation. See https://core.telegram.org/bots/api#formatting-options for more details.
     * @param explanationEntities Optional. List of special entities that appear in the poll explanation, which can be specified instead of parseMode
     * @param openPeriod Optional. Amount of time in seconds the poll will be active after creation, 5-600. Can't be used together with closeDate.
     * @param closeDate Optional. Point in time (Unix timestamp) when the poll will be automatically closed. Must be at least 5 and no more than 600 seconds in the future. Can't be used together with openPeriod.
     * @param isClosed Optional. Pass True, if the poll needs to be immediately closed. This can be useful for poll preview.
     * @param messageThreadId Optional. Unique identifier for the target message thread (topic) of the forum; for forum supergroups only
     * @param protectContent Optional. Protects the contents of the sent message from forwarding and saving
     * @param businessConnectionId Optional. Unique identifier of the business connection on behalf of which the message will be sent
     *
     * @return On success, the sent Message is returned.
     */
    Message::Ptr sendPoll(boost::variant<std::int64_t, std::string> chatId,
                          const std::string& question,
                          const std::vector<std::string>& options,
                          bool disableNotification = false,
                          ReplyParameters::Ptr replyParameters = nullptr,
                          GenericReply::Ptr replyMarkup = nullptr,
                          bool isAnonymous = true,
                          const std::string& type = "",
                          bool allowsMultipleAnswers = false,
                          std::int32_t correctOptionId = -1,
                          const std::string& explanation = "",
                          const std::string& explanationParseMode = "",
                          const std::vector<MessageEntity::Ptr>& explanationEntities = std::vector<MessageEntity::Ptr>(),
                          std::int32_t openPeriod = 0,
                          std::int32_t closeDate = 0,
                          bool isClosed = false,
                          std::int32_t messageThreadId = 0,
                          bool protectContent = false,
                          const std::string& businessConnectionId = "") const;

    /**
     * @brief Use this method to send an animated emoji that will display a random value.
     *
     * @param chatId Unique identifier for the target chat or username of the target channel (in the format @channelusername)
     * @param disableNotification Optional. Sends the message silently. Users will receive a notification with no sound.
     * @param replyParameters Optional. Description of the message to reply to
     * @param replyMarkup Optional. Additional interface options. A JSON-serialized object for an [inline keyboard](https://core.telegram.org/bots/features#inline-keyboards), [custom reply keyboard](https://core.telegram.org/bots/features#keyboards), instructions to remove a reply keyboard or to force a reply from the user. Not supported for messages sent on behalf of a business account
     * @param emoji Optional. Emoji on which the dice throw animation is based. Currently, must be one of “🎲”, “🎯”, “🏀”, “⚽”, “🎳”, or “🎰”. Dice can have values 1-6 for “🎲”, “🎯” and “🎳”, values 1-5 for “🏀” and “⚽”, and values 1-64 for “🎰”. Defaults to “🎲”
     * @param messageThreadId Optional. Unique identifier for the target message thread (topic) of the forum; for forum supergroups only
     * @param protectContent Optional. Protects the contents of the sent message from forwarding
     * @param businessConnectionId Optional. Unique identifier of the business connection on behalf of which the message will be sent
     *
     * @return On success, the sent Message is returned.
     */
    Message::Ptr sendDice(boost::variant<std::int64_t, std::string> chatId,
                          bool disableNotification = false,
                          ReplyParameters::Ptr replyParameters = nullptr,
                          GenericReply::Ptr replyMarkup = nullptr,
                          const std::string& emoji = "",
                          std::int32_t messageThreadId = 0,
                          bool protectContent = false,
                          const std::string& businessConnectionId = "") const;

    /**
     * @brief Use this method to change the chosen reactions on a message.
     *
     * Service messages can't be reacted to.
     * Automatically forwarded messages from a channel to its discussion group have the same available reactions as messages in the channel.
     *
     * @param chatId Unique identifier for the target chat or username of the target channel (in the format @channelusername)
     * @param messageId Identifier of the target message. If the message belongs to a media group, the reaction is set to the first non-deleted message in the group instead.
     * @param reaction Optional. A JSON-serialized list of reaction types to set on the message. Currently, as non-premium users, bots can set up to one reaction per message. A custom emoji reaction can be used if it is either already present on the message or explicitly allowed by chat administrators.
     * @param isBig Optional. Pass True to set the reaction with a big animation
     *
     * @return Returns True on success.
     */
    bool setMessageReaction(boost::variant<std::int64_t, std::string> chatId,
                            std::int32_t messageId = 0,
                            const std::vector<ReactionType::Ptr>& reaction = std::vector<ReactionType::Ptr>(),
                            bool isBig = false) const;

    /**
     * @brief Use this method when you need to tell the user that something is happening on the bot's side.
     *
     * The status is set for 5 seconds or less (when a message arrives from your bot, Telegram clients clear its typing status).
     *
     * Example: The [ImageBot](https://t.me/imagebot) needs some time to process a request and upload the image.
     * Instead of sending a text message along the lines of “Retrieving image, please wait…”, the bot may use Api::sendChatAction with action = upload_photo.
     * The user will see a “sending photo” status for the bot.
     *
     * We only recommend using this method when a response from the bot will take a noticeable amount of time to arrive.
     *
     * @param chatId Unique identifier for the target chat or username of the target channel (in the format @channelusername)
     * @param action Type of action to broadcast. Choose one, depending on what the user is about to receive: typing for text messages, upload_photo for photos, record_video or upload_video for videos, record_voice or upload_voice for voice notes, upload_document for general files, choose_sticker for stickers, find_location for location data, record_video_note or upload_video_note for video notes.
     * @param messageThreadId Optional. Unique identifier for the target message thread; for supergroups only
     * @param businessConnectionId Optional. Unique identifier of the business connection on behalf of which the action will be sent
     * 
     * @return Returns True on success.
     */
    bool sendChatAction(std::int64_t chatId,
                        const std::string& action,
                        std::int32_t messageThreadId = 0,
                        const std::string& businessConnectionId = "") const;

    /**
     * @brief Use this method to get a list of profile pictures for a user.
     * 
     * @param userId Unique identifier of the target user
     * @param offset Optional. Sequential number of the first photo to be returned. By default, all photos are returned.
     * @param limit Optional. Limits the number of photos to be retrieved. Values between 1-100 are accepted. Defaults to 100.
     * 
     * @return Returns a UserProfilePhotos object.
     */
    UserProfilePhotos::Ptr getUserProfilePhotos(std::int64_t userId,
                                                std::int32_t offset = 0,
                                                std::int32_t limit = 100) const;

    /**
     * @brief Use this method to get basic information about a file and prepare it for downloading.
     * 
     * For the moment, bots can download files of up to 20MB in size.
     * The file can then be downloaded via Api::downloadFile or via the link https://api.telegram.org/file/bot<token>/<filePath>, where filePath is taken from the response.
     * It is guaranteed that the filePath will be valid for at least 1 hour.
     * When the link expires, a new one can be requested by calling Api::getFile again.
     * 
     * This function may not preserve the original file name and MIME type.
     * You should save the file's MIME type and name (if available) when the File object is received.
     * 
     * @param fileId File identifier to get information about
     * 
     * @return On success, a File object is returned.
     */
    File::Ptr getFile(const std::string& fileId) const;

    /**
     * @brief Use this method to ban a user in a group, a supergroup or a channel.
     * 
     * In the case of supergroups and channels, the user will not be able to return to the chat on their own using invite links, etc., unless unbanned first.
     * The bot must be an administrator in the chat for this to work and must have the appropriate administrator rights.
     * 
     * @param chatId Unique identifier for the target group or username of the target supergroup or channel (in the format @channelusername)
     * @param userId Unique identifier of the target user
     * @param untilDate Optional. Date when the user will be unbanned, unix time. If user is banned for more than 366 days or less than 30 seconds from the current time they are considered to be banned forever. Applied for supergroups and channels only.
     * @param revokeMessages Optional. Pass True to delete all messages from the chat for the user that is being removed. If False, the user will be able to see messages in the group that were sent before the user was removed. Always True for supergroups and channels.
     * 
     * @return Returns True on success.
     */
    bool banChatMember(boost::variant<std::int64_t, std::string> chatId,
                       std::int64_t userId,
                       std::int32_t untilDate = 0,
                       bool revokeMessages = true) const;

    /**
     * @brief Use this method to unban a previously banned user in a supergroup or channel.
     * 
     * The user will not return to the group or channel automatically, but will be able to join via link, etc.
     * The bot must be an administrator for this to work.
     * By default, this method guarantees that after the call the user is not a member of the chat, but will be able to join it.
     * So if the user is a member of the chat they will also be removed from the chat.
     * If you don't want this, use the parameter onlyIfBanned.
     * 
     * @param chatId Unique identifier for the target group or username of the target supergroup or channel (in the format @channelusername)
     * @param userId Unique identifier of the target user
     * @param onlyIfBanned Optional. Pass True to do nothing if the user is not banned
     * 
     * @return Returns True on success.
     */
    bool unbanChatMember(boost::variant<std::int64_t, std::string> chatId,
                         std::int64_t userId,
                         bool onlyIfBanned = false) const;

    /**
     * @brief Use this method to restrict a user in a supergroup.
     * 
     * The bot must be an administrator in the supergroup for this to work and must have the appropriate administrator rights.
     * Pass True for all permissions to lift restrictions from a user.
     * 
     * @param chatId Unique identifier for the target chat or username of the target supergroup (in the format @supergroupusername)
     * @param userId Unique identifier of the target user
     * @param permissions A JSON-serialized object for new user permissions
     * @param untilDate Optional. Date when restrictions will be lifted for the user; Unix time. If user is restricted for more than 366 days or less than 30 seconds from the current time, they are considered to be restricted forever
     * @param useIndependentChatPermissions Optional. Pass True if chat permissions are set independently. Otherwise, the canSendOtherMessages and canAddWebPagPreviews permissions will imply the canSendMessages, canSendAudios, canSendDocuments, canSendPhotos, canSendVideos, canSendVideoNotes, and canSendVoiceNotes permissions; the canSendPolls permission will imply the canSendMessages permission.
     * 
     * @return Returns True on success.
     */
    bool restrictChatMember(boost::variant<std::int64_t, std::string> chatId,
                            std::int64_t userId,
                            ChatPermissions::Ptr permissions,
                            std::uint32_t untilDate = 0,
                            bool useIndependentChatPermissions = false) const;

    /**
     * @brief Use this method to promote or demote a user in a supergroup or a channel.
     *
     * The bot must be an administrator in the chat for this to work and must have the appropriate administrator rights.
     * Pass False for all boolean parameters to demote a user.
     *
     * @param chatId Unique identifier for the target chat or username of the target channel (in the format @channelusername)
     * @param userId Unique identifier of the target user
     * @param canChangeInfo Optional. Pass True if the administrator can change chat title, photo and other settings
     * @param canPostMessages Optional. Pass True if the administrator can post messages in the channel, or access channel statistics; for channels only
     * @param canEditMessages Optional. Pass True if the administrator can edit messages of other users and can pin messages; for channels only
     * @param canDeleteMessages Optional. Pass True if the administrator can delete messages of other users
     * @param canInviteUsers Optional. Pass True if the administrator can invite new users to the chat
     * @param canPinMessages Optional. Pass True if the administrator can pin messages; for supergroups only
     * @param canPromoteMembers Optional. Pass True if the administrator can add new administrators with a subset of their own privileges or demote administrators that they have promoted, directly or indirectly (promoted by administrators that were appointed by him)
     * @param isAnonymous Optional. Pass True if the administrator's presence in the chat is hidden
     * @param canManageChat Optional. Pass True if the administrator can access the chat event log, get boost list, see hidden supergroup and channel members, report spam messages and ignore slow mode. Implied by any other administrator privilege.
     * @param canManageVideoChats Optional. Pass True if the administrator can manage video chats
     * @param canRestrictMembers Optional. Pass True if the administrator can restrict, ban or unban chat members, or access supergroup statistics
     * @param canManageTopics Optional. Pass True if the user is allowed to create, rename, close, and reopen forum topics; for supergroups only
     * @param canPostStories Optional. Pass True if the administrator can post stories to the chat
     * @param canEditStories Optional. Pass True if the administrator can edit stories posted by other users
     * @param canDeleteStories Optional. Pass True if the administrator can delete stories posted by other users
     *
     * @return Returns True on success.
     */
    bool promoteChatMember(boost::variant<std::int64_t, std::string> chatId,
                           std::int64_t userId,
                           bool canChangeInfo = false,
                           bool canPostMessages = false,
                           bool canEditMessages = false,
                           bool canDeleteMessages = false,
                           bool canInviteUsers = false,
                           bool canPinMessages = false,
                           bool canPromoteMembers = false,
                           bool isAnonymous = false,
                           bool canManageChat = false,
                           bool canManageVideoChats = false,
                           bool canRestrictMembers = false,
                           bool canManageTopics = false,
                           bool canPostStories = false,
                           bool canEditStories = false,
                           bool canDeleteStories = false) const;

    /**
     * @brief Use this method to set a custom title for an administrator in a supergroup promoted by the bot.
     *
     * @param chatId Unique identifier for the target chat or username of the target supergroup (in the format @supergroupusername)
     * @param userId Unique identifier of the target user
     * @param customTitle New custom title for the administrator; 0-16 characters, emoji are not allowed
     *
     * @return Returns True on success.
     */
    bool setChatAdministratorCustomTitle(boost::variant<std::int64_t, std::string> chatId,
                                         std::int64_t userId,
                                         const std::string& customTitle) const;

    /**
     * @brief Use this method to ban a channel chat in a supergroup or a channel.
     * 
     * Until the chat is unbanned, the owner of the banned chat won't be able to send messages on behalf of any of their channels.
     * The bot must be an administrator in the supergroup or channel for this to work and must have the appropriate administrator rights.
     *
     * @param chatId Unique identifier for the target chat or username of the target channel (in the format @channelusername)
     * @param senderChatId Unique identifier of the target sender chat
     *
     * @return Returns True on success.
     */
    bool banChatSenderChat(boost::variant<std::int64_t, std::string> chatId,
                           std::int64_t senderChatId) const;

    /**
     * @brief Use this method to unban a previously banned channel chat in a supergroup or channel.
     * 
     * The bot must be an administrator for this to work and must have the appropriate administrator rights.
     *
     * @param chatId Unique identifier for the target chat or username of the target channel (in the format @channelusername)
     * @param senderChatId Unique identifier of the target sender chat
     *
     * @return Returns True on success.
     */
    bool unbanChatSenderChat(boost::variant<std::int64_t, std::string> chatId,
                             std::int64_t senderChatId) const;

    /**
     * @brief Use this method to set default chat permissions for all members.
     * 
     * The bot must be an administrator in the group or a supergroup for this to work and must have the canRestrictMembers administrator rights.
     * 
     * @param chatId Unique identifier for the target chat or username of the target supergroup (in the format @supergroupusername)
     * @param permissions A JSON-serialized object for new default chat permissions
     * @param useIndependentChatPermissions Optional. Pass True if chat permissions are set independently. Otherwise, the canSendOtherMessages and canAddWebPagPreviews permissions will imply the canSendMessages, canSendAudios, canSendDocuments, canSendPhotos, canSendVideos, canSendVideoNotes, and canSendVoiceNotes permissions; the canSendPolls permission will imply the canSendMessages permission.
     * 
     * @return Returns True on success.
     */
    bool setChatPermissions(boost::variant<std::int64_t, std::string> chatId,
                            ChatPermissions::Ptr permissions,
                            bool useIndependentChatPermissions = false) const;

    /**
     * @brief Use this method to generate a new primary invite link for a chat; any previously generated primary link is revoked.
     * 
     * The bot must be an administrator in the chat for this to work and must have the appropriate administrator rights.
     * 
     * Each administrator in a chat generates their own invite links.
     * Bots can't use invite links generated by other administrators.
     * If you want your bot to work with invite links, it will need to generate its own link using Api::exportChatInviteLink or by calling the Api::getChat method.
     * If your bot needs to generate a new primary invite link replacing its previous one, use Api::exportChatInviteLink again.
     * 
     * @param chatId Unique identifier for the target chat or username of the target channel (in the format @channelusername)
     * 
     * @return Returns the new invite link as String on success.
     */
    std::string exportChatInviteLink(boost::variant<std::int64_t, std::string> chatId) const;

    /**
     * @brief Use this method to create an additional invite link for a chat.
     * 
     * The bot must be an administrator in the chat for this to work and must have the appropriate administrator rights.
     * The link can be revoked using the method Api::revokeChatInviteLink.
     * 
     * @param chatId Unique identifier for the target chat or username of the target channel (in the format @channelusername)
     * @param expireDate Optional. Point in time (Unix timestamp) when the link will expire
     * @param memberLimit Optional. The maximum number of users that can be members of the chat simultaneously after joining the chat via this invite link; 1-99999
     * @param name Optional. Invite link name; 0-32 characters
     * @param createsJoinRequest Optional. True, if users joining the chat via the link need to be approved by chat administrators. If True, memberLimit can't be specified
     * 
     * @return Returns the new invite link as ChatInviteLink object.
     */
    ChatInviteLink::Ptr createChatInviteLink(boost::variant<std::int64_t, std::string> chatId,
                                             std::int32_t expireDate = 0,
                                             std::int32_t memberLimit = 0,
                                             const std::string& name = "",
                                             bool createsJoinRequest = false) const;

    /**
     * @brief Use this method to edit a non-primary invite link created by the bot.
     * 
     * The bot must be an administrator in the chat for this to work and must have the appropriate administrator rights.
     *
     * @param chatId Unique identifier for the target chat or username of the target channel (in the format @channelusername)
     * @param inviteLink The invite link to edit
     * @param expireDate Optional. Point in time (Unix timestamp) when the link will expire
     * @param memberLimit Optional. Maximum number of users that can be members of the chat simultaneously after joining the chat via this invite link; 1-99999
     * @param name Optional. Invite link name; 0-32 characters
     * @param createsJoinRequest Optional. True, if users joining the chat via the link need to be approved by chat administrators. If True, memberLimit can't be specified
     *
     * @return Returns the edited invite link as a ChatInviteLink object.
     */
    ChatInviteLink::Ptr editChatInviteLink(boost::variant<std::int64_t, std::string> chatId,
                                           const std::string& inviteLink,
                                           std::int32_t expireDate = 0,
                                           std::int32_t memberLimit = 0,
                                           const std::string& name = "",
                                           bool createsJoinRequest = false) const;

    /**
     * @brief Use this method to revoke an invite link created by the bot.
     * 
     * If the primary link is revoked, a new link is automatically generated.
     * The bot must be an administrator in the chat for this to work and must have the appropriate administrator rights.
     *
     * @param chatId Unique identifier of the target chat or username of the target channel (in the format @channelusername)
     * @param inviteLink The invite link to revoke
     *
     * @return Returns the revoked invite link as ChatInviteLink object.
     */
    ChatInviteLink::Ptr revokeChatInviteLink(boost::variant<std::int64_t, std::string> chatId,
                                             const std::string& inviteLink) const;

    /**
     * @brief Use this method to approve a chat join request.
     * 
     * The bot must be an administrator in the chat for this to work and must have the canInviteUsers administrator right.
     *
     * @param chatId Unique identifier for the target chat or username of the target channel (in the format @channelusername)
     * @param userId Unique identifier of the target user
     *
     * @return Returns True on success.
     */
    bool approveChatJoinRequest(boost::variant<std::int64_t, std::string> chatId,
                                std::int64_t userId) const;

    /**
     * @brief Use this method to decline a chat join request.
     * 
     * The bot must be an administrator in the chat for this to work and must have the canInviteUsers administrator right.
     *
     * @param chatId Unique identifier for the target chat or username of the target channel (in the format @channelusername)
     * @param userId Unique identifier of the target user
     *
     * @return True on success.
     */
    bool declineChatJoinRequest(boost::variant<std::int64_t, std::string> chatId,
                                std::int64_t userId) const;

    /**
     * @brief Use this method to set a new profile photo for the chat.
     *
     * Photos can't be changed for private chats.
     * The bot must be an administrator in the chat for this to work and must have the appropriate administrator rights.
     *
     * @param chatId Unique identifier for the target chat or username of the target channel (in the format @channelusername)
     * @param photo New chat photo, uploaded using multipart/form-data
     * 
     * @return Returns True on success.
     */
    bool setChatPhoto(boost::variant<std::int64_t, std::string> chatId,
                      InputFile::Ptr photo) const;

    /**
     * @brief Use this method to delete a chat photo.
     *
     * Photos can't be changed for private chats.
     * The bot must be an administrator in the chat for this to work and must have the appropriate administrator rights.
     *
     * @param chatId Unique identifier for the target chat or username of the target channel (in the format @channelusername)
     * 
     * @return Returns True on success.
     */
    bool deleteChatPhoto(boost::variant<std::int64_t, std::string> chatId) const;

    /**
     * @brief Use this method to change the title of a chat.
     *
     * Titles can't be changed for private chats.
     * The bot must be an administrator in the chat for this to work and must have the appropriate administrator rights.
     *
     * @param chatId Unique identifier for the target chat or username of the target channel (in the format @channelusername)
     * @param title New chat title, 1-255 characters
     * 
     * @return Returns True on success.
     */
    bool setChatTitle(boost::variant<std::int64_t, std::string> chatId,
                      const std::string& title) const;

    /**
     * @brief Use this method to change the description of a group, a supergroup or a channel.
     * 
     * The bot must be an administrator in the chat for this to work and must have the appropriate administrator rights.
     * 
     * @param chatId Unique identifier for the target chat or username of the target channel (in the format @channelusername)
     * @param description New chat description, 0-255 characters
     * 
     * @return Returns True on success.
     */
    bool setChatDescription(boost::variant<std::int64_t, std::string> chatId,
                            const std::string& description = "") const;

    /**
     * @brief Use this method to add a message to the list of pinned messages in a chat.
     * 
     * If the chat is not a private chat, the bot must be an administrator in the chat for this to work and must have the 'canPinMessages' administrator right in a supergroup or 'canEditMessages' administrator right in a channel.
     * 
     * @param chatId Unique identifier for the target chat or username of the target channel (in the format @channelusername)
     * @param messageId Identifier of a message to pin
     * @param disableNotification Optional. Pass True if it is not necessary to send a notification to all chat members about the new pinned message. Notifications are always disabled in channels and private chats.
     * 
     * @return Returns True on success.
     */
    bool pinChatMessage(boost::variant<std::int64_t, std::string> chatId,
                        std::int32_t messageId,
                        bool disableNotification = false) const;

    /**
     * @brief Use this method to remove a message from the list of pinned messages in a chat.
     * 
     * If the chat is not a private chat, the bot must be an administrator in the chat for this to work and must have the 'canPinMessages' administrator right in a supergroup or 'canEditMessages' administrator right in a channel.
     * 
     * @param chatId Unique identifier for the target chat or username of the target channel (in the format @channelusername)
     * @param messageId Optional. Identifier of a message to unpin. If not specified, the most recent pinned message (by sending date) will be unpinned.
     * 
     * @return Returns True on success.
     */
    bool unpinChatMessage(boost::variant<std::int64_t, std::string> chatId,
                          std::int32_t messageId = 0) const;

    /**
     * @brief Use this method to clear the list of pinned messages in a chat.
     * 
     * If the chat is not a private chat, the bot must be an administrator in the chat for this to work and must have the 'canPinMessages' administrator right in a supergroup or 'canEditMessages' administrator right in a channel.
     *
     * @param chatId Unique identifier for the target chat or username of the target channel (in the format @channelusername)
     *
     * @return Returns True on success.
     */
    bool unpinAllChatMessages(boost::variant<std::int64_t, std::string> chatId) const;

    /**
     * @brief Use this method for your bot to leave a group, supergroup or channel.
     * 
     * @param chatId Unique identifier for the target chat or username of the target supergroup or channel (in the format @channelusername)
     * 
     * @return Returns True on success.
     */
    bool leaveChat(boost::variant<std::int64_t, std::string> chatId) const;

    /**
     * @brief Use this method to get up to date information about the chat.
     *
     * @param chatId Unique identifier for the target chat or username of the target supergroup or channel (in the format @channelusername)
     *
     * @return Returns a Chat object on success.
     */
    Chat::Ptr getChat(boost::variant<std::int64_t, std::string> chatId) const;

    /**
     * @brief Use this method to get a list of administrators in a chat, which aren't bots.
     * 
     * @param chatId Unique identifier for the target chat or username of the target supergroup or channel (in the format @channelusername)
     * 
     * @return Returns an Array of ChatMember objects.
     */
    std::vector<ChatMember::Ptr> getChatAdministrators(boost::variant<std::int64_t, std::string> chatId) const;

    /**
     * @brief Use this method to get the number of members in a chat.
     * 
     * @param chatId Unique identifier for the target chat or username of the target supergroup or channel (in the format @channelusername)
     * 
     * @return Returns Int on success.
     */
    std::int32_t getChatMemberCount(boost::variant<std::int64_t, std::string> chatId) const;

    /**
     * @brief Use this method to get information about a member of a chat.
     * 
     * The method is only guaranteed to work for other users if the bot is an administrator in the chat.
     * 
     * @param chatId Unique identifier for the target chat or username of the target supergroup or channel (in the format @channelusername)
     * @param userId Unique identifier of the target user
     * 
     * @return Returns a ChatMember object on success.
     */
    ChatMember::Ptr getChatMember(boost::variant<std::int64_t, std::string> chatId,
                                  std::int64_t userId) const;

    /**
     * @brief Use this method to set a new group sticker set for a supergroup.
     * 
     * The bot must be an administrator in the chat for this to work and must have the appropriate administrator rights.
     * Use the field canSetStickerSet optionally returned in Api::getChat requests to check if the bot can use this method.
     * 
     * @param chatId Unique identifier for the target chat or username of the target supergroup (in the format @supergroupusername)
     * @param stickerSetName Name of the sticker set to be set as the group sticker set
     * 
     * @return Returns True on success.
     */
    bool setChatStickerSet(boost::variant<std::int64_t, std::string> chatId,
                           const std::string& stickerSetName) const;

    /**
     * @brief Use this method to delete a group sticker set from a supergroup.
     * 
     * The bot must be an administrator in the chat for this to work and must have the appropriate administrator rights.
     * Use the field canSetSticker_set optionally returned in Api::getChat requests to check if the bot can use this method.
     * 
     * @param chatId Unique identifier for the target chat or username of the target supergroup (in the format @supergroupusername)
     * 
     * @return Returns True on success.
     */
    bool deleteChatStickerSet(boost::variant<std::int64_t, std::string> chatId) const;

    /**
     * @brief Use this method to get custom emoji stickers, which can be used as a forum topic icon by any user.
     * 
     * @return Returns an Array of Sticker objects.
     */
    std::vector<Sticker::Ptr> getForumTopicIconStickers() const;

    /**
     * @brief Use this method to create a topic in a forum supergroup chat.
     * 
     * The bot must be an administrator in the chat for this to work and must have the canManageTopics administrator rights.
     * 
     * @param chatId Unique identifier for the target chat or username of the target supergroup (in the format @supergroupusername)
     * @param name Topic name, 1-128 characters
     * @param iconColor Optional. Color of the topic icon in RGB format. Currently, must be one of 7322096 (0x6FB9F0), 16766590 (0xFFD67E), 13338331 (0xCB86DB), 9367192 (0x8EEE98), 16749490 (0xFF93B2), or 16478047 (0xFB6F5F)
     * @param iconCustomEmojiId Optional. Unique identifier of the custom emoji shown as the topic icon. Use Api::getForumTopicIconStickers to get all allowed custom emoji identifiers.
     * 
     * @return Returns information about the created topic as a ForumTopic object.
     */
    ForumTopic::Ptr createForumTopic(boost::variant<std::int64_t, std::string> chatId,
                                     const std::string& name,
                                     std::int32_t iconColor = 0,
                                     const std::string& iconCustomEmojiId = "") const;

    /**
     * @brief Use this method to edit name and icon of a topic in a forum supergroup chat.
     * 
     * The bot must be an administrator in the chat for this to work and must have canManageTopics administrator rights, unless it is the creator of the topic.
     * 
     * @param chatId Unique identifier for the target chat or username of the target supergroup (in the format @supergroupusername)
     * @param messageThreadId Unique identifier for the target message thread of the forum topic
     * @param name Optional. New topic name, 0-128 characters. If not specified or empty, the current name of the topic will be kept
     * @param iconCustomEmojiId Optional. New unique identifier of the custom emoji shown as the topic icon. Use Api::getForumTopicIconStickers to get all allowed custom emoji identifiers. Pass an empty string to remove the icon. If not specified, the current icon will be kept
     * 
     * @return Returns True on success.
     */
    bool editForumTopic(boost::variant<std::int64_t, std::string> chatId,
                        std::int32_t messageThreadId,
                        const std::string& name = "",
                        boost::variant<std::int32_t, std::string> iconCustomEmojiId = 0) const;

    /**
     * @brief Use this method to close an open topic in a forum supergroup chat.
     * 
     * The bot must be an administrator in the chat for this to work and must have the canManageTopics administrator rights, unless it is the creator of the topic.
     * 
     * @param chatId Unique identifier for the target chat or username of the target supergroup (in the format @supergroupusername)
     * @param messageThreadId Unique identifier for the target message thread of the forum topic
     * 
     * @return Returns True on success.
     */
    bool closeForumTopic(boost::variant<std::int64_t, std::string> chatId,
                         std::int32_t messageThreadId) const;

    /**
     * @brief Use this method to reopen a closed topic in a forum supergroup chat.
     * 
     * The bot must be an administrator in the chat for this to work and must have the canManageTopics administrator rights, unless it is the creator of the topic.
     * 
     * @param chatId Unique identifier for the target chat or username of the target supergroup (in the format @supergroupusername)
     * @param messageThreadId Unique identifier for the target message thread of the forum topic
     * 
     * @return Returns True on success.
     */
    bool reopenForumTopic(boost::variant<std::int64_t, std::string> chatId,
                          std::int32_t messageThreadId) const;

    /**
     * @brief Use this method to delete a forum topic along with all its messages in a forum supergroup chat.
     * 
     * The bot must be an administrator in the chat for this to work and must have the canDeleteMessages administrator rights.
     * 
     * @param chatId Unique identifier for the target chat or username of the target supergroup (in the format @supergroupusername)
     * @param messageThreadId Unique identifier for the target message thread of the forum topic
     * 
     * @return Returns True on success.
     */
    bool deleteForumTopic(boost::variant<std::int64_t, std::string> chatId,
                          std::int32_t messageThreadId) const;

    /**
     * @brief Use this method to clear the list of pinned messages in a forum topic.
     * 
     * The bot must be an administrator in the chat for this to work and must have the canPinMessages administrator right in the supergroup.
     * 
     * @param chatId Unique identifier for the target chat or username of the target supergroup (in the format @supergroupusername)
     * @param messageThreadId Unique identifier for the target message thread of the forum topic
     * 
     * @return Returns True on success.
     */
    bool unpinAllForumTopicMessages(boost::variant<std::int64_t, std::string> chatId,
                                    std::int32_t messageThreadId) const;

    /**
     * @brief Use this method to edit the name of the 'General' topic in a forum supergroup chat.
     * 
     * The bot must be an administrator in the chat for this to work and must have canManageTopics administrator rights.
     * 
     * @param chatId Unique identifier for the target chat or username of the target supergroup (in the format @supergroupusername)
     * @param name New topic name, 1-128 characters
     * 
     * @return Returns True on success.
     */
    bool editGeneralForumTopic(boost::variant<std::int64_t, std::string> chatId,
                               std::string name) const;

    /**
     * @brief Use this method to close an open 'General' topic in a forum supergroup chat.
     * 
     * The bot must be an administrator in the chat for this to work and must have the canManageTopics administrator rights.
     * 
     * @param chatId Unique identifier for the target chat or username of the target supergroup (in the format @supergroupusername)
     * 
     * @return Returns True on success.
     */
    bool closeGeneralForumTopic(boost::variant<std::int64_t, std::string> chatId) const;

    /**
     * @brief Use this method to reopen a closed 'General' topic in a forum supergroup chat.
     * 
     * The bot must be an administrator in the chat for this to work and must have the canManageTopics administrator rights.
     * The topic will be automatically unhidden if it was hidden.
     * 
     * @param chatId Unique identifier for the target chat or username of the target supergroup (in the format @supergroupusername)
     * 
     * @return Returns True on success.
     */
    bool reopenGeneralForumTopic(boost::variant<std::int64_t, std::string> chatId) const;

    /**
     * @brief Use this method to hide the 'General' topic in a forum supergroup chat.
     * 
     * The bot must be an administrator in the chat for this to work and must have the canManageTopics administrator rights.
     * The topic will be automatically closed if it was open.
     * 
     * @param chatId Unique identifier for the target chat or username of the target supergroup (in the format @supergroupusername)
     * 
     * @return Returns True on success.
     */
    bool hideGeneralForumTopic(boost::variant<std::int64_t, std::string> chatId) const;

    /**
     * @brief Use this method to unhide the 'General' topic in a forum supergroup chat.
     * 
     * The bot must be an administrator in the chat for this to work and must have the canManageTopics administrator rights.
     * 
     * @param chatId Unique identifier for the target chat or username of the target supergroup (in the format @supergroupusername)
     * 
     * @return Returns True on success.
     */
    bool unhideGeneralForumTopic(boost::variant<std::int64_t, std::string> chatId) const;

    /**
     * @brief Use this method to clear the list of pinned messages in a General forum topic.
     * 
     * The bot must be an administrator in the chat for this to work and must have the canPinMessages administrator right in the supergroup.
     * 
     * @param chatId Unique identifier for the target chat or username of the target supergroup (in the format @supergroupusername)
     * 
     * @return Returns True on success.
     */
    bool unpinAllGeneralForumTopicMessages(boost::variant<std::int64_t, std::string> chatId) const;

    /**
     * @brief Use this method to send answers to callback queries sent from inline keyboards.
     * 
     * The answer will be displayed to the user as a notification at the top of the chat screen or as an alert.
     * 
     * Alternatively, the user can be redirected to the specified Game URL.
     * For this option to work, you must first create a game for your bot via @BotFather and accept the terms.
     * Otherwise, you may use links like t.me/your_bot?start=XXXX that open your bot with a parameter.
     * 
     * @param callbackQueryId Unique identifier for the query to be answered
     * @param text Optional. Text of the notification. If not specified, nothing will be shown to the user, 0-200 characters
     * @param showAlert Optional. If True, an alert will be shown by the client instead of a notification at the top of the chat screen. Defaults to false.
     * @param url Optional. URL that will be opened by the user's client. If you have created a Game and accepted the conditions via @BotFather, specify the URL that opens your game - note that this will only work if the query comes from an InlineKeyboardButton button.
     * @param cacheTime Optional. The maximum amount of time in seconds that the result of the callback query may be cached client-side. Telegram apps will support caching starting in version 3.14. Defaults to 0.
     * 
     * @return On success, True is returned.
     */
    bool answerCallbackQuery(const std::string& callbackQueryId,
                             const std::string& text = "",
                             bool showAlert = false,
                             const std::string& url = "",
                             std::int32_t cacheTime = 0) const;

    /**
     * @brief Use this method to get the list of boosts added to a chat by a user.
     *
     * Requires administrator rights in the chat.
     *
     * @param chatId Unique identifier for the chat or username of the channel (in the format @channelusername)
     * @param userId Unique identifier of the target user
     *
     * @return Returns a UserChatBoosts object.
     */
    UserChatBoosts::Ptr getUserChatBoosts(boost::variant<std::int64_t, std::string> chatId,
                                          std::int32_t userId) const;

    /**
     * @brief Use this method to get information about the connection of the bot with a business account.
     *
     * @param businessConnectionId Unique identifier of the business connection
     *
     * @return Returns a BusinessConnection object on success.
     */
    BusinessConnection::Ptr getBusinessConnection(const std::string& businessConnectionId) const;

    /**
     * @brief Use this method to change the list of the bot's commands.
     * 
     * See https://core.telegram.org/bots#commands for more details about bot commands.
     * 
     * @param commands A JSON-serialized list of bot commands to be set as the list of the bot's commands. At most 100 commands can be specified.
     * @param scope Optional. A JSON-serialized object, describing scope of users for which the commands are relevant. Defaults to BotCommandScopeDefault.
     * @param languageCode Optional. A two-letter ISO 639-1 language code. If empty, commands will be applied to all users from the given scope, for whose language there are no dedicated commands
     * 
     * @return Returns True on success.
     */
    bool setMyCommands(const std::vector<BotCommand::Ptr>& commands,
                       BotCommandScope::Ptr scope = nullptr,
                       const std::string& languageCode = "") const;

    /**
     * @brief Use this method to delete the list of the bot's commands for the given scope and user language.
     * 
     * After deletion, higher level commands will be shown to affected users.
     *
     * @param scope Optional. A JSON-serialized object, describing scope of users for which the commands are relevant. Defaults to BotCommandScopeDefault.
     * @param languageCode Optional. A two-letter ISO 639-1 language code. If empty, commands will be applied to all users from the given scope, for whose language there are no dedicated commands
     *
     * @return Returns True on success.
     */
    bool deleteMyCommands(BotCommandScope::Ptr scope = nullptr,
                          const std::string& languageCode = "") const;

    /**
     * @brief Use this method to get the current list of the bot's commands for the given scope and user language.
     * 
     * @param scope Optional. A JSON-serialized object, describing scope of users. Defaults to BotCommandScopeDefault.
     * @param languageCode Optional. A two-letter ISO 639-1 language code or an empty string
     * 
     * @return Returns an Array of BotCommand objects. If commands aren't set, an empty list is returned.
     */
    std::vector<BotCommand::Ptr> getMyCommands(BotCommandScope::Ptr scope = nullptr,
                                               const std::string& languageCode = "") const;

    /**
     * @brief Use this method to change the bot's name.
     * 
     * @param name Optional. New bot name; 0-64 characters. Pass an empty string to remove the dedicated name for the given language.
     * @param languageCode Optional. A two-letter ISO 639-1 language code. If empty, the name will be shown to all users for whose language there is no dedicated name.
     * 
     * @return Returns True on success.
     */
    bool setMyName(const std::string& name = "",
                   const std::string& languageCode = "") const;

    /**
     * @brief Use this method to get the current bot name for the given user language.
     * 
     * @param languageCode Optional. A two-letter ISO 639-1 language code or an empty string
     * 
     * @return Returns BotName on success.
     */
    BotName::Ptr getMyName(const std::string& languageCode = "") const;

    /**
     * @brief Use this method to change the bot's description, which is shown in the chat with the bot if the chat is empty.
     * 
     * @param description Optional. New bot description; 0-512 characters. Pass an empty string to remove the dedicated description for the given language.
     * @param languageCode Optional. A two-letter ISO 639-1 language code. If empty, the description will be applied to all users for whose language there is no dedicated description.
     * 
     * @return Returns True on success.
     */
    bool setMyDescription(const std::string& description = "",
                          const std::string& languageCode = "") const;

    /**
     * @brief Use this method to get the current bot description for the given user language.
     * 
     * @param languageCode Optional. A two-letter ISO 639-1 language code or an empty string
     * 
     * @return Returns BotDescription on success.
     */
    BotDescription::Ptr getMyDescription(const std::string& languageCode = "") const;

    /**
     * @brief Use this method to change the bot's short description, which is shown on the bot's profile page and is sent together with the link when users share the bot.
     * 
     * @param shortDescription Optional. New short description for the bot; 0-120 characters. Pass an empty string to remove the dedicated short description for the given language.
     * @param languageCode Optional. A two-letter ISO 639-1 language code. If empty, the short description will be applied to all users for whose language there is no dedicated short description.
     * 
     * @return Returns True on success.
     */
    bool setMyShortDescription(const std::string& shortDescription = "",
                               const std::string& languageCode = "") const;

    /**
     * @brief Use this method to get the current bot short description for the given user language.
     * 
     * @param languageCode Optional. A two-letter ISO 639-1 language code or an empty string
     * 
     * @return Returns BotShortDescription on success.
     */
    BotShortDescription::Ptr getMyShortDescription(const std::string& languageCode = "") const;

    /**
     * @brief Use this method to change the bot's menu button in a private chat, or the default menu button.
     * 
     * @param chatId Optional. Unique identifier for the target private chat. If not specified, default bot's menu button will be changed
     * @param menuButton Optional. A JSON-serialized object for the bot's new menu button. Defaults to MenuButtonDefault
     * 
     * @return Returns True on success.
     */
    bool setChatMenuButton(std::int64_t chatId = 0,
                           MenuButton::Ptr menuButton = nullptr) const;

    /**
     * @brief Use this method to get the current value of the bot's menu button in a private chat, or the default menu button.
     * 
     * @param chatId Optional. Unique identifier for the target private chat. If not specified, default bot's menu button will be returned
     * 
     * @return Returns MenuButton on success.
     */
    MenuButton::Ptr getChatMenuButton(std::int64_t chatId = 0) const;

    /**
     * @brief Use this method to change the default administrator rights requested by the bot when it's added as an administrator to groups or channels.
     * 
     * These rights will be suggested to users, but they are free to modify the list before adding the bot.
     *
     * @param rights Optional. A JSON-serialized object describing new default administrator rights. If not specified, the default administrator rights will be cleared.
     * @param forChannels Optional. Pass True to change the default administrator rights of the bot in channels. Otherwise, the default administrator rights of the bot for groups and supergroups will be changed.
     *
     * @return Returns True on success.
     */
    bool setMyDefaultAdministratorRights(ChatAdministratorRights::Ptr rights = nullptr,
                                         bool forChannels = false) const;

    /**
     * @brief Use this method to get the current default administrator rights of the bot.
     *
     * @param forChannels Optional. Pass True to get default administrator rights of the bot in channels. Otherwise, default administrator rights of the bot for groups and supergroups will be returned.
     *
     * @return Returns ChatAdministratorRights on success.
     */
    ChatAdministratorRights::Ptr getMyDefaultAdministratorRights(bool forChannels = false) const;

    /**
     * @brief Use this method to edit text and [game](https://core.telegram.org/bots/api#games) messages.
     *
     * @param text New text of the message, 1-4096 characters after entities parsing
     * @param chatId Optional. Required if inlineMessageId is not specified. Unique identifier for the target chat or username of the target channel (in the format @channelusername)
     * @param messageId Optional. Required if inlineMessageId is not specified. Identifier of the message to edit
     * @param inlineMessageId Optional.	Required if chatId and messageId are not specified. Identifier of the inline message
     * @param parseMode Optional. Mode for parsing entities in the message text. See https://core.telegram.org/bots/api#formatting-options for more details.
     * @param linkPreviewOptions Optional. Link preview generation options for the message
     * @param replyMarkup Optional. A JSON-serialized object for an inline keyboard.
     * @param entities Optional. List of special entities that appear in message text, which can be specified instead of parseMode
     *
     * @return On success, if the edited message is not an inline message, the edited Message is returned, otherwise nullptr is returned.
     */
    Message::Ptr editMessageText(const std::string& text,
                                 boost::variant<std::int64_t, std::string> chatId = 0,
                                 std::int32_t messageId = 0,
                                 const std::string& inlineMessageId = "",
                                 const std::string& parseMode = "",
                                 LinkPreviewOptions::Ptr linkPreviewOptions = nullptr,
                                 InlineKeyboardMarkup::Ptr replyMarkup = nullptr,
                                 const std::vector<MessageEntity::Ptr>& entities = std::vector<MessageEntity::Ptr>()) const;

    /**
     * @brief Use this method to edit captions of messages.
     * 
     * @param chatId Optional. Required if inlineMessageId is not specified. Unique identifier for the target chat or username of the target channel (in the format @channelusername)
     * @param messageId Optional. Required if inlineMessageId is not specified. Identifier of the message to edit
     * @param caption Optional. New caption of the message, 0-1024 characters after entities parsing
     * @param inlineMessageId Optional. Required if chatId and messageId are not specified. Identifier of the inline message
     * @param replyMarkup Optional. A JSON-serialized object for an inline keyboard.
     * @param parseMode Optional. Mode for parsing entities in the message caption. See https://core.telegram.org/bots/api#formatting-options for more details.
     * @param captionEntities Optional. List of special entities that appear in the caption, which can be specified instead of parseMode
     * 
     * @return On success, if the edited message is not an inline message, the edited Message is returned, otherwise nullptr is returned.
     */
    Message::Ptr editMessageCaption(boost::variant<std::int64_t, std::string> chatId = 0,
                                    std::int32_t messageId = 0,
                                    const std::string& caption = "",
                                    const std::string& inlineMessageId = "",
                                    GenericReply::Ptr replyMarkup = nullptr,
                                    const std::string& parseMode = "",
                                    const std::vector<MessageEntity::Ptr>& captionEntities = std::vector<MessageEntity::Ptr>()) const;

    /**
     * @brief Use this method to edit animation, audio, document, photo, or video messages.
     *
     * If a message is part of a message album, then it can be edited only to an audio for audio albums, only to a document for document albums and to a photo or a video otherwise.
     * When an inline message is edited, a new file can't be uploaded; use a previously uploaded file via its fileId or specify a URL.
     *
     * @param media A JSON-serialized object for a new media content of the message
     * @param chatId Optional. Required if inlineMessageId is not specified. Unique identifier for the target chat or username of the target channel (in the format @channelusername)
     * @param messageId Optional. Required if inlineMessageId is not specified. Identifier of the message to edit
     * @param inlineMessageId Optional. Required if chatId and messageId are not specified. Identifier of the inline message
     * @param replyMarkup Optional. A JSON-serialized object for a new inline keyboard.
     * 
     * @return On success, if the edited message is not an inline message, the edited Message is returned, otherwise nullptr is returned.
     */
    Message::Ptr editMessageMedia(InputMedia::Ptr media,
                                  boost::variant<std::int64_t, std::string> chatId = 0,
                                  std::int32_t messageId = 0,
                                  const std::string& inlineMessageId = "",
                                  GenericReply::Ptr replyMarkup = nullptr) const;

    /**
     * @brief Use this method to edit only the reply markup of messages.
     * 
     * @param chatId Optional. Required if inlineMessageId is not specified. Unique identifier for the target chat or username of the target channel (in the format @channelusername)
     * @param messageId Optional. Required if inlineMessageId is not specified. Identifier of the message to edit
     * @param inlineMessageId Optional. Required if chatId and messageId are not specified. Identifier of the inline message
     * @param replyMarkup Optional. A JSON-serialized object for an inline keyboard.
     * 
     * @return On success, if the edited message is not an inline message, the edited Message is returned, otherwise nullptr is returned.
     */
    Message::Ptr editMessageReplyMarkup(boost::variant<std::int64_t, std::string> chatId = 0,
                                        std::int32_t messageId = 0,
                                        const std::string& inlineMessageId = "",
                                        GenericReply::Ptr replyMarkup = nullptr) const;

    /**
     * @brief Use this method to stop a poll which was sent by the bot.
     * 
     * @param chatId Unique identifier for the target chat or username of the target channel (in the format @channelusername)
     * @param messageId Identifier of the original message with the poll
     * @param replyMarkup Optional. A JSON-serialized object for a new message inline keyboard.
     *
     * @return On success, the stopped Poll is returned.
     */
    Poll::Ptr stopPoll(boost::variant<std::int64_t, std::string> chatId,
                       std::int64_t messageId,
                       InlineKeyboardMarkup::Ptr replyMarkup = std::make_shared<InlineKeyboardMarkup>()) const;

    /**
     * @brief Use this method to delete a message, including service messages, with the following limitations:
     * 
     * - A message can only be deleted if it was sent less than 48 hours ago.
     * - Service messages about a supergroup, channel, or forum topic creation can't be deleted.
     * - A dice message in a private chat can only be deleted if it was sent more than 24 hours ago.
     * - Bots can delete outgoing messages in private chats, groups, and supergroups.
     * - Bots can delete incoming messages in private chats.
     * - Bots granted canPostMessages permissions can delete outgoing messages in channels.
     * - If the bot is an administrator of a group, it can delete any message there.
     * - If the bot has canDeleteMessages permission in a supergroup or a channel, it can delete any message there.
     * 
     * @param chatId Unique identifier for the target chat or username of the target channel (in the format @channelusername)
     * @param messageId Identifier of the message to delete
     * 
     * @return Returns True on success.
     */
    bool deleteMessage(boost::variant<std::int64_t, std::string> chatId,
                       std::int32_t messageId) const;

    /**
     * @brief Use this method to delete multiple messages simultaneously.
     *
     * If some of the specified messages can't be found, they are skipped.
     *
     * @param chatId Unique identifier for the target chat or username of the target channel (in the format @channelusername)
     * @param messageIds A JSON-serialized list of 1-100 identifiers of messages to delete. See Api::deleteMessage for limitations on which messages can be deleted
     * 
     * @return Returns True on success.
     */
    bool deleteMessages(boost::variant<std::int64_t, std::string> chatId,
                        const std::vector<std::int32_t>& messageIds) const;

    /**
     * @brief Use this method to send static .WEBP, [animated](https://telegram.org/blog/animated-stickers) .TGS, or [video](https://telegram.org/blog/video-stickers-better-reactions) .WEBM stickers.
     *
     * @param chatId Unique identifier for the target chat or username of the target channel (in the format @channelusername)
     * @param sticker Sticker to send. Pass a fileId as String to send a file that exists on the Telegram servers (recommended), pass an HTTP URL as a String for Telegram to get a .WEBP sticker from the Internet, or upload a new .WEBP, .TGS, or .WEBM sticker using multipart/form-data. [More information on Sending Files »](https://core.telegram.org/bots/api#sending-files). Video and animated stickers can't be sent via an HTTP URL.
     * @param replyParameters Optional. Description of the message to reply to
     * @param replyMarkup Optional. Additional interface options. A JSON-serialized object for an [inline keyboard](https://core.telegram.org/bots/features#inline-keyboards), [custom reply keyboard](https://core.telegram.org/bots/features#keyboards), instructions to remove a reply keyboard or to force a reply from the user. Not supported for messages sent on behalf of a business account
     * @param disableNotification Optional. Sends the message silently. Users will receive a notification with no sound.
     * @param messageThreadId Optional. Unique identifier for the target message thread (topic) of the forum; for forum supergroups only
     * @param protectContent Optional. Protects the contents of the sent message from forwarding and saving
     * @param emoji Optional. Emoji associated with the sticker; only for just uploaded stickers
     * @param businessConnectionId Optional. Unique identifier of the business connection on behalf of which the message will be sent
     *
     * @return On success, the sent Message is returned.
     */
    Message::Ptr sendSticker(boost::variant<std::int64_t, std::string> chatId,
                             boost::variant<InputFile::Ptr, std::string> sticker,
                             ReplyParameters::Ptr replyParameters = nullptr,
                             GenericReply::Ptr replyMarkup = nullptr,
                             bool disableNotification = false,
                             std::int32_t messageThreadId = 0,
                             bool protectContent = false,
                             const std::string& emoji = "",
                             const std::string& businessConnectionId = "") const;

    /**
     * @brief Use this method to get a sticker set.
     * 
     * @param name Name of the sticker set
     * 
     * @return On success, a StickerSet object is returned.
     */
    StickerSet::Ptr getStickerSet(const std::string& name) const;

    /**
     * @brief Use this method to get information about custom emoji stickers by their identifiers.
     *
     * @param customEmojiIds A JSON-serialized list of custom emoji identifiers. At most 200 custom emoji identifiers can be specified.
     *
     * @return Returns an Array of Sticker objects.
     */
    std::vector<Sticker::Ptr> getCustomEmojiStickers(const std::vector<std::string>& customEmojiIds) const;

    /**
     * @brief Use this method to upload a file with a sticker for later use in the Api::createNewStickerSet, Api::addStickerToSet, or Api::replaceStickerInSet methods (the file can be used multiple times).
     *
     * @param userId User identifier of sticker file owner
     * @param sticker A file with the sticker in .WEBP, .PNG, .TGS, or .WEBM format. See https://core.telegram.org/stickers for technical requirements. https://core.telegram.org/bots/api#sending-files
     * @param stickerFormat Format of the sticker, must be one of “static”, “animated”, “video”
     *
     * @return Returns the uploaded File on success.
     */
    File::Ptr uploadStickerFile(std::int64_t userId,
                                InputFile::Ptr sticker,
                                const std::string& stickerFormat) const;

    /**
     * @brief Use this method to create a new sticker set owned by a user.
     *
     * The bot will be able to edit the sticker set thus created.
     *
     * @param userId User identifier of created sticker set owner
     * @param name Short name of sticker set, to be used in t.me/addstickers/ URLs (e.g., animals). Can contain only English letters, digits and underscores. Must begin with a letter, can't contain consecutive underscores and must end in "_by_<bot_username>". <bot_username> is case insensitive. 1-64 characters.
     * @param title Sticker set title, 1-64 characters
     * @param stickers A JSON-serialized list of 1-50 initial stickers to be added to the sticker set
     * @param stickerType Optional. Type of stickers in the set, pass “regular”, “mask”, or “custom_emoji”. By default, a regular sticker set is created.
     * @param needsRepainting Optional. Pass True if stickers in the sticker set must be repainted to the color of text when used in messages, the accent color if used as emoji status, white on chat photos, or another appropriate color based on context; for custom emoji sticker sets only
     *
     * @return Returns True on success.
     */
    bool createNewStickerSet(std::int64_t userId,
                             const std::string& name,
                             const std::string& title,
                             const std::vector<InputSticker::Ptr>& stickers,
                             Sticker::Type stickerType = Sticker::Type::Regular,
                             bool needsRepainting = false) const;

    /**
     * @brief Use this method to add a new sticker to a set created by the bot.
     *
     * Emoji sticker sets can have up to 200 stickers.
     * Other sticker sets can have up to 120 stickers.
     *
     * @param userId User identifier of sticker set owner
     * @param name Sticker set name
     * @param sticker A JSON-serialized object with information about the added sticker. If exactly the same sticker had already been added to the set, then the set isn't changed.
     *
     * @return Returns True on success.
     */
    bool addStickerToSet(std::int64_t userId,
                         const std::string& name,
                         InputSticker::Ptr sticker) const;

    /**
     * @brief Use this method to move a sticker in a set created by the bot to a specific position.
     * 
     * @param sticker File identifier of the sticker
     * @param position New sticker position in the set, zero-based
     * 
     * @return Returns True on success.
     */
    bool setStickerPositionInSet(const std::string& sticker,
                                 std::int32_t position) const;

    /**
     * @brief Use this method to delete a sticker from a set created by the bot.
     * 
     * @param sticker File identifier of the sticker
     * 
     * @return Returns True on success.
     */
    bool deleteStickerFromSet(const std::string& sticker) const;

    /**
     * @brief Use this method to replace an existing sticker in a sticker set with a new one.
     *
     * The method is equivalent to calling Api::deleteStickerFromSet, then Api::addStickerToSet, then Api::setStickerPositionInSet.
     *
     * @param userId User identifier of the sticker set owner
     * @param name Sticker set name
     * @param oldSticker File identifier of the replaced sticker
     * @param sticker A JSON-serialized object with information about the added sticker. If exactly the same sticker had already been added to the set, then the set remains unchanged.
     *
     * @return Returns True on success.
     */
    bool replaceStickerInSet(std::int64_t userId,
                             const std::string& name,
                             const std::string& oldSticker,
                             InputSticker::Ptr sticker) const;

    /**
     * @brief Use this method to change the list of emoji assigned to a regular or custom emoji sticker.
     * 
     * The sticker must belong to a sticker set created by the bot.
     * 
     * @param sticker File identifier of the sticker
     * @param emojiList A JSON-serialized list of 1-20 emoji associated with the sticker
     * 
     * @return Returns True on success.
     */
    bool setStickerEmojiList(const std::string& sticker,
                             const std::vector<std::string>& emojiList) const;

    /**
     * @brief Use this method to change search keywords assigned to a regular or custom emoji sticker.
     * 
     * The sticker must belong to a sticker set created by the bot.
     * 
     * @param sticker File identifier of the sticker
     * @param keywords Optional. A JSON-serialized list of 0-20 search keywords for the sticker with total length of up to 64 characters
     * 
     * @return Returns True on success.
     */
    bool setStickerKeywords(const std::string& sticker,
                            const std::vector<std::string>& keywords = std::vector<std::string>()) const;

    /**
     * @brief Use this method to change the mask position of a mask sticker.
     * 
     * The sticker must belong to a sticker set that was created by the bot.
     * 
     * @param sticker File identifier of the sticker
     * @param maskPosition A JSON-serialized object with the position where the mask should be placed on faces. Omit the parameter to remove the mask position.
     * 
     * @return Returns True on success.
     */
    bool setStickerMaskPosition(const std::string& sticker,
                                MaskPosition::Ptr maskPosition = nullptr) const;

    /**
     * @brief Use this method to set the title of a created sticker set.
     * 
     * @param name Sticker set name
     * @param title Sticker set title, 1-64 characters
     * 
     * @return Returns True on success.
     */
    bool setStickerSetTitle(const std::string& name,
                            const std::string& title) const;

    /**
     * @brief Use this method to set the thumbnail of a regular or mask sticker set.
     *
     * The format of the thumbnail file must match the format of the stickers in the set.
     *
     * @param name Sticker set name
     * @param userId User identifier of the sticker set owner
     * @param format Format of the thumbnail, must be one of “static” for a .WEBP or .PNG image, “animated” for a .TGS animation, or “video” for a WEBM video
     * @param thumbnail Optional. A .WEBP or .PNG image with the thumbnail, must be up to 128 kilobytes in size and have a width and height of exactly 100px, or a .TGS animation with a thumbnail up to 32 kilobytes in size (see https://core.telegram.org/stickers#animated-sticker-requirements for animated sticker technical requirements), or a WEBM video with the thumbnail up to 32 kilobytes in size; see https://core.telegram.org/stickers#video-sticker-requirements for video sticker technical requirements. Pass a fileId as a String to send a file that already exists on the Telegram servers, pass an HTTP URL as a String for Telegram to get a file from the Internet, or upload a new one using multipart/form-data. https://core.telegram.org/bots/api#sending-files. Animated and video sticker set thumbnails can't be uploaded via HTTP URL. If omitted, then the thumbnail is dropped and the first sticker is used as the thumbnail.
     *
     * @return Returns True on success.
     */
    bool setStickerSetThumbnail(const std::string& name,
                                std::int64_t userId,
                                const std::string& format,
                                boost::variant<InputFile::Ptr, std::string> thumbnail = "") const;

    /**
     * @brief Use this method to set the thumbnail of a custom emoji sticker set.
     *
     * @param name Sticker set name
     * @param customEmojiId Optional. Custom emoji identifier of a sticker from the sticker set; pass an empty string to drop the thumbnail and use the first sticker as the thumbnail.
     *
     * @return Returns True on success.
     */
    bool setCustomEmojiStickerSetThumbnail(const std::string& name,
                                           const std::string& customEmojiId = "") const;

    /**
     * @brief Use this method to delete a sticker set that was created by the bot.
     *
     * @param name Sticker set name
     *
     * @return Returns True on success.
     */
    bool deleteStickerSet(const std::string& name) const;

    /**
     * @brief Use this method to send answers to an inline query.
     * 
     * No more than 50 results per query are allowed.
     * 
     * @param inlineQueryId Unique identifier for the answered query
     * @param results A JSON-serialized array of results for the inline query
     * @param cacheTime Optional. The maximum amount of time in seconds that the result of the inline query may be cached on the server. Defaults to 300.
     * @param isPersonal Optional. Pass True if results may be cached on the server side only for the user that sent the query. By default, results may be returned to any user who sends the same query.
     * @param nextOffset Optional. Pass the offset that a client should send in the next query with the same text to receive more results. Pass an empty string if there are no more results or if you don't support pagination. Offset length can't exceed 64 bytes.
     * @param button Optional. A JSON-serialized object describing a button to be shown above inline query results
     * 
     * @return On success, True is returned.
     */
    bool answerInlineQuery(const std::string& inlineQueryId,
                           const std::vector<InlineQueryResult::Ptr>& results,
                           std::int32_t cacheTime = 300,
                           bool isPersonal = false,
                           const std::string& nextOffset = "",
                           InlineQueryResultsButton::Ptr button = nullptr) const;

    /**
     * @brief Use this method to set the result of an interaction with a Web App and send a corresponding message on behalf of the user to the chat from which the query originated.
     * 
     * @param webAppQueryId Unique identifier for the query to be answered
     * @param result A JSON-serialized object describing the message to be sent
     * 
     * @return On success, a SentWebAppMessage object is returned.
     */
    SentWebAppMessage::Ptr answerWebAppQuery(const std::string& webAppQueryId,
                                             InlineQueryResult::Ptr result) const;

    /**
     * @brief Use this method to send invoices.
     *
     * @param chatId Unique identifier for the target chat or username of the target channel (in the format @channelusername)
     * @param title Product name, 1-32 characters
     * @param description Product description, 1-255 characters
     * @param payload Bot-defined invoice payload, 1-128 bytes. This will not be displayed to the user, use for your internal processes.
     * @param providerToken Payments provider token, obtained via Botfather
     * @param currency Three-letter ISO 4217 currency code, see https://core.telegram.org/bots/payments#supported-currencies
     * @param prices Price breakdown, a JSON-serialized list of components (e.g. product price, tax, discount, delivery cost, delivery tax, bonus, etc.)
     * @param providerData Optional. A JSON-serialized data about the invoice, which will be shared with the payment provider. A detailed description of required fields should be provided by the payment provider.
     * @param photoUrl Optional. URL of the product photo for the invoice. Can be a photo of the goods or a marketing image for a service. People like it better when they see what they are paying for.
     * @param photoSize Optional. Photo size
     * @param photoWidth Optional. Photo width
     * @param photoHeight Optional. Photo height
     * @param needName Optional. Pass True, if you require the user's full name to complete the order
     * @param needPhoneNumber Optional. Pass True, if you require the user's phone number to complete the order
     * @param needEmail Optional. Pass True, if you require the user's email address to complete the order
     * @param needShippingAddress Optional. Pass True, if you require the user's shipping address to complete the order
     * @param sendPhoneNumberToProvider Optional. Pass True, if user's phone number should be sent to provider
     * @param sendEmailToProvider Optional. Pass True, if user's email address should be sent to provider
     * @param isFlexible Optional. Pass True, if the final price depends on the shipping method
     * @param replyParameters Optional. Description of the message to reply to
     * @param replyMarkup Optional. A JSON-serialized object for an inline keyboard. If empty, one 'Pay total price' button will be shown. If not empty, the first button must be a Pay button.
     * @param disableNotification Optional. Sends the message silently. Users will receive a notification with no sound.
     * @param messageThreadId Optional. Unique identifier for the target message thread (topic) of the forum; for forum supergroups only
     * @param maxTipAmount Optional. The maximum accepted amount for tips in the smallest units of the currency (integer, not float/double). For example, for a maximum tip of US$ 1.45 pass max_tip_amount = 145. See the exp parameter in https://core.telegram.org/bots/payments/currencies.json, it shows the number of digits past the decimal point for each currency (2 for the majority of currencies). Defaults to 0
     * @param suggestedTipAmounts Optional. A JSON-serialized array of suggested amounts of tips in the smallest units of the currency (integer, not float/double). At most 4 suggested tip amounts can be specified. The suggested tip amounts must be positive, passed in a strictly increased order and must not exceed maxTipAmount.
     * @param startParameter Optional. Unique deep-linking parameter. If left empty, forwarded copies of the sent message will have a Pay button, allowing multiple users to pay directly from the forwarded message, using the same invoice. If non-empty, forwarded copies of the sent message will have a URL button with a deep link to the bot (instead of a Pay button), with the value used as the start parameter
     * @param protectContent Optional. Protects the contents of the sent message from forwarding and saving
     *
     * @return On success, the sent Message is returned.
     */
    Message::Ptr sendInvoice(boost::variant<std::int64_t, std::string> chatId,
                             const std::string& title,
                             const std::string& description,
                             const std::string& payload,
                             const std::string& providerToken,
                             const std::string& currency,
                             const std::vector<LabeledPrice::Ptr>& prices,
                             const std::string& providerData = "",
                             const std::string& photoUrl = "",
                             std::int32_t photoSize = 0,
                             std::int32_t photoWidth = 0,
                             std::int32_t photoHeight = 0,
                             bool needName = false,
                             bool needPhoneNumber = false,
                             bool needEmail = false,
                             bool needShippingAddress = false,
                             bool sendPhoneNumberToProvider = false,
                             bool sendEmailToProvider = false,
                             bool isFlexible = false,
                             ReplyParameters::Ptr replyParameters = nullptr,
                             GenericReply::Ptr replyMarkup = nullptr,
                             bool disableNotification = false,
                             std::int32_t messageThreadId = 0,
                             std::int32_t maxTipAmount = 0,
                             const std::vector<std::int32_t>& suggestedTipAmounts = std::vector<std::int32_t>(),
                             const std::string& startParameter = "",
                             bool protectContent = false) const;

    /**
     * @brief Use this method to create a link for an invoice.
     *
     * @param title Product name, 1-32 characters
     * @param description Product description, 1-255 characters
     * @param payload Bot-defined invoice payload, 1-128 bytes. This will not be displayed to the user, use for your internal processes.
     * @param providerToken Payment provider token, obtained via BotFather
     * @param currency Three-letter ISO 4217 currency code, see https://core.telegram.org/bots/payments#supported-currencies
     * @param prices Price breakdown, a JSON-serialized list of components (e.g. product price, tax, discount, delivery cost, delivery tax, bonus, etc.)
     * @param maxTipAmount Optional. The maximum accepted amount for tips in the smallest units of the currency (integer, not float/double). For example, for a maximum tip of US$ 1.45 pass maxTipAmount = 145. See the exp parameter in https://core.telegram.org/bots/payments/currencies.json, it shows the number of digits past the decimal point for each currency (2 for the majority of currencies). Defaults to 0
     * @param suggestedTipAmounts Optional. A JSON-serialized array of suggested amounts of tips in the smallest units of the currency (integer, not float/double). At most 4 suggested tip amounts can be specified. The suggested tip amounts must be positive, passed in a strictly increased order and must not exceed maxTipAmount.
     * @param providerData Optional. JSON-serialized data about the invoice, which will be shared with the payment provider. A detailed description of required fields should be provided by the payment provider.
     * @param photoUrl Optional. URL of the product photo for the invoice. Can be a photo of the goods or a marketing image for a service.
     * @param photoSize Optional. Photo size in bytes
     * @param photoWidth Optional. Photo width
     * @param photoHeight Optional. Photo height
     * @param needName Optional. Pass True, if you require the user's full name to complete the order
     * @param needPhoneNumber Optional. Pass True, if you require the user's phone number to complete the order
     * @param needEmail Optional. Pass True, if you require the user's email address to complete the order
     * @param needShippingAddress Optional. Pass True, if you require the user's shipping address to complete the order
     * @param sendPhoneNumberToProvider Optional. Pass True, if the user's phone number should be sent to the provider
     * @param sendEmailToProvider Optional. Pass True, if the user's email address should be sent to the provider
     * @param isFlexible Optional. Pass True, if the final price depends on the shipping method
     *
     * @return Returns the created invoice link as String on success.
     */
    std::string createInvoiceLink(const std::string& title,
                                  const std::string& description,
                                  const std::string& payload,
                                  const std::string& providerToken,
                                  const std::string& currency,
                                  const std::vector<LabeledPrice::Ptr>& prices,
                                  std::int32_t maxTipAmount = 0,
                                  const std::vector<std::int32_t>& suggestedTipAmounts = std::vector<std::int32_t>(),
                                  const std::string& providerData = "",
                                  const std::string& photoUrl = "",
                                  std::int32_t photoSize = 0,
                                  std::int32_t photoWidth = 0,
                                  std::int32_t photoHeight = 0,
                                  bool needName = false,
                                  bool needPhoneNumber = false,
                                  bool needEmail = false,
                                  bool needShippingAddress = false,
                                  bool sendPhoneNumberToProvider = false,
                                  bool sendEmailToProvider = false,
                                  bool isFlexible = false) const;

    /**
     * @brief Use this method to reply to shipping queries.
     *
     * If you sent an invoice requesting a shipping address and the parameter isFlexible was specified, the Bot API will send an Update with a shippingQuery field to the bot.
     *
     * @param shippingQueryId Unique identifier for the query to be answered
     * @param ok Pass True if delivery to the specified address is possible and False if there are any problems (for example, if delivery to the specified address is not possible)
     * @param shippingOptions Optional. Required if ok is True. A JSON-serialized array of available shipping options.
     * @param errorMessage Optional. Required if ok is False. Error message in human readable form that explains why it is impossible to complete the order (e.g. "Sorry, delivery to your desired address is unavailable'). Telegram will display this message to the user.
     * 
     * @return On success, True is returned.
     */
    bool answerShippingQuery(const std::string& shippingQueryId,
                             bool ok,
                             const std::vector<ShippingOption::Ptr>& shippingOptions = std::vector<ShippingOption::Ptr>(),
                             const std::string& errorMessage = "") const;

    /**
     * @brief Use this method to respond to such pre-checkout queries.
     *
     * Once the user has confirmed their payment and shipping details, the Bot API sends the final confirmation in the form of an Update with the field preCheckoutQuery.
     * Note: The Bot API must receive an answer within 10 seconds after the pre-checkout query was sent.
     *
     * @param preCheckoutQueryId Unique identifier for the query to be answered
     * @param ok Specify True if everything is alright (goods are available, etc.) and the bot is ready to proceed with the order. Use False if there are any problems.
     * @param errorMessage Required if ok is False. Error message in human readable form that explains the reason for failure to proceed with the checkout (e.g. "Sorry, somebody just bought the last of our amazing black T-shirts while you were busy filling out your payment details. Please choose a different color or garment!"). Telegram will display this message to the user.
     * 
     * @return On success, True is returned.
     */
    bool answerPreCheckoutQuery(const std::string& preCheckoutQueryId,
                                bool ok,
                                const std::string& errorMessage = "") const;

    /**
     * @brief Informs a user that some of the Telegram Passport elements they provided contains errors.
     * 
     * The user will not be able to re-submit their Passport to you until the errors are fixed (the contents of the field for which you returned the error must change).
     * Use this if the data submitted by the user doesn't satisfy the standards your service requires for any reason.
     * For example, if a birthday date seems invalid, a submitted document is blurry, a scan shows evidence of tampering, etc.
     * Supply some details in the error message to make sure the user knows how to correct the issues.
     *
     * @param userId User identifier
     * @param errors A JSON-serialized array describing the errors
     * 
     * @return Returns True on success.
     */
    bool setPassportDataErrors(std::int64_t userId,
                               const std::vector<PassportElementError::Ptr>& errors) const;

    /**
     * @brief Use this method to send a game.
     *
     * @param chatId Unique identifier for the target chat
     * @param gameShortName Short name of the game, serves as the unique identifier for the game. Set up your games via @BotFather.
     * @param replyParameters Optional. Description of the message to reply to
     * @param replyMarkup Optional. A JSON-serialized object for an [inline keyboard](https://core.telegram.org/bots/features#inline-keyboards). If empty, one 'Play gameTitle' button will be shown. If not empty, the first button must launch the game. Not supported for messages sent on behalf of a business account.
     * @param disableNotification Optional. Sends the message silently. Users will receive a notification with no sound.
     * @param messageThreadId Optional. Unique identifier for the target message thread (topic) of the forum; for forum supergroups only
     * @param protectContent Optional. Protects the contents of the sent message from forwarding and saving
     * @param businessConnectionId Optional. Unique identifier of the business connection on behalf of which the message will be sent
     *
     * @return On success, the sent Message is returned.
     */
    Message::Ptr sendGame(std::int64_t chatId,
                          const std::string& gameShortName,
                          ReplyParameters::Ptr replyParameters = nullptr,
                          InlineKeyboardMarkup::Ptr replyMarkup = std::make_shared<InlineKeyboardMarkup>(),
                          bool disableNotification = false,
                          std::int32_t messageThreadId = 0,
                          bool protectContent = false,
                          const std::string& businessConnectionId = "") const;

    /**
     * @brief Use this method to set the score of the specified user in a game message.
     *
     * Returns an error, if the new score is not greater than the user's current score in the chat and force is False.
     *
     * @param userId User identifier
     * @param score New score, must be non-negative
     * @param force Optional. Pass True if the high score is allowed to decrease. This can be useful when fixing mistakes or banning cheaters
     * @param disableEditMessage Optional. Pass True if the game message should not be automatically edited to include the current scoreboard
     * @param chatId Optional. Required if inlineMessageId is not specified. Unique identifier for the target chat
     * @param messageId Optional. Required if inlineMessageId is not specified. Identifier of the sent message
     * @param inlineMessageId Optional. Required if chatId and messageId are not specified. Identifier of the inline message
     * 
     * @return On success, if the message is not an inline message, the Message is returned, otherwise nullptr is returned.
     */
    Message::Ptr setGameScore(std::int64_t userId,
                              std::int32_t score,
                              bool force = false,
                              bool disableEditMessage = false,
                              std::int64_t chatId = 0,
                              std::int32_t messageId = 0,
                              const std::string& inlineMessageId = "") const;

    /**
     * @brief Use this method to get data for high score tables.
     * 
     * Will return the score of the specified user and several of their neighbors in a game.
     *
     * This method will currently return scores for the target user, plus two of their closest neighbors on each side.
     * Will also return the top three users if the user and their neighbors are not among them.
     * Please note that this behavior is subject to change.
     * 
     * @param userId Target user id
     * @param chatId Optional. Required if inlineMessageId is not specified. Unique identifier for the target chat
     * @param messageId Optional. Required if inlineMessageId is not specified. Identifier of the sent message
     * @param inlineMessageId Optional. Required if chatId and messageId are not specified. Identifier of the inline message
     * 
     * @return Returns an Array of GameHighScore objects.
     */
    std::vector<GameHighScore::Ptr> getGameHighScores(std::int64_t userId,
                                                      std::int64_t chatId = 0,
                                                      std::int32_t messageId = 0,
                                                      const std::string& inlineMessageId = "") const;

    /**
     * @brief Download a file from Telegram and save it in memory.
     *
     * @param filePath Telegram file path from Api::getFile
     * @param args Additional api parameters
     *
     * @return File content in a string.
     */
    std::string downloadFile(const std::string& filePath,
                             const std::vector<HttpReqArg>& args = std::vector<HttpReqArg>()) const;

    /**
     * @brief Check if user has blocked the bot
     *
     * @param chatId Unique identifier for the target chat
     *
     * @return Returns True if bot is blocked by user
     */
    bool blockedByUser(std::int64_t chatId) const;

    const HttpClient& _httpClient;
    
protected:
    boost::property_tree::ptree sendRequest(const std::string& method, const std::vector<HttpReqArg>& args = std::vector<HttpReqArg>()) const;

    const std::string _token;
    const TgTypeParser _tgTypeParser;
    const std::string _url;
};
}

#endif //TGBOT_API_H
