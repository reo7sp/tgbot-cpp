#ifndef TGBOT_CPP_API_H
#define TGBOT_CPP_API_H

#include "tgbot/TgTypeParser.h"
#include "tgbot/net/HttpClient.h"
#include "tgbot/net/HttpReqArg.h"
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
#include "tgbot/types/StickerSet.h"
#include "tgbot/types/File.h"
#include "tgbot/types/InputMedia.h"
#include "tgbot/types/GameHighScore.h"
#include "tgbot/types/LabeledPrice.h"
#include "tgbot/types/ShippingOption.h"
#include "tgbot/types/BotCommand.h"

#include <boost/property_tree/ptree.hpp>
#include <boost/variant.hpp>

#include <cstdint>
#include <memory>
#include <string>
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
    std::vector<Update::Ptr> getUpdates(std::int32_t offset = 0, std::int32_t limit = 100, std::int32_t timeout = 0, const StringArrayPtr& allowedUpdates = nullptr) const;

    /**
     * @brief Use this method to specify a url and receive incoming updates via an outgoing webhook.
     * Whenever there is an update for the bot, we will send an HTTPS POST request to the specified url, containing a JSON-serialized @ref Update.
     * In case of an unsuccessful request, we will give up after a reasonable amount of attempts.
     *
     * If you'd like to make sure that the Webhook request comes from Telegram, we recommend using a secret path in the URL, e.g. https://www.example.com/<token>.
     * Since nobody else knows your bot's token, you can be pretty sure it's us.
     * 
     * You will not be able to receive updates using @ref Api::getUpdates for as long as an outgoing webhook is set up.
     * 
     * To use a self-signed certificate, you need to upload your public key certificate using certificate parameter.
     * Please upload as InputFile, sending a String will not work.
     * 
     * Ports currently supported for Webhooks: 443, 80, 88, 8443.
     * 
     * If you're having any trouble setting up webhooks, please check out https://core.telegram.org/bots/webhooks.
     *
     * @param url HTTPS url to send updates to. Use an empty string to remove webhook integration
     * @param certificate Optional. Upload your public key certificate so that the root certificate in use can be checked. See https://core.telegram.org/bots/self-signed for details.
     * @param ipAddress Optional. The fixed IP address which will be used to send webhook requests instead of the IP address resolved through DNS
     * @param maxConnection Optional. Maximum allowed number of simultaneous HTTPS connections to the webhook for update delivery, 1-100. Use lower values to limit the load on your bot's server, and higher values to increase your bot's throughput.
     * @param allowedUpdates Optional. A JSON-serialized list of the update types you want your bot to receive. For example, specify [“message”, “edited_channel_post”, “callback_query”] to only receive updates of these types. See Update for a complete list of available update types. Specify an empty list to receive all updates regardless of type (default). If not specified, the previous setting will be used. Please note that this parameter doesn't affect updates created before the call to the setWebhook, so unwanted updates may be received for a short period of time.
     * @param dropPendingUpdates Optional. Pass True to drop all pending updates
     * 
     * @return True on success.
     */
    bool setWebhook(const std::string& url, InputFile::Ptr certificate = nullptr, const std::string& ipAddress = "",
                    std::int32_t maxConnection = 40, const StringArrayPtr& allowedUpdates = nullptr, bool dropPendingUpdates = false) const;

    /**
     * @brief Use this method to remove webhook integration if you decide to switch back to @ref Api::getUpdates.
     *
     * @param dropPendingUpdates Optional. Pass True to drop all pending updates
     *
     * @return True on success.
     */
    bool deleteWebhook(bool dropPendingUpdates = false) const;

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
     * @brief A simple method for testing your bot's auth token.
     * @return Basic information about the bot in form of a User object.
     */
    User::Ptr getMe() const;

    /**
     * @brief Use this method to send text messages.
     *
     * @param chatId Unique identifier for the target chat or username of the target channel (in the format @channelusername)
     * @param text Text of the message to be sent, 1-4096 characters after entities parsing
     * @param parseMode Optional. Mode for parsing entities in the message text. See https://core.telegram.org/bots/api#formatting-options for more details.
     * @param entities Optional. List of special entities that appear in message text, which can be specified instead of parseMode
     * @param disableWebPagePreview Optional. Disables link previews for links in this message
     * @param disableNotification Optional. Sends the message silently. Users will receive a notification with no sound.
     * @param replyToMessageId Optional. If the message is a reply, ID of the original message
     * @param allowSendingWithoutReply Optional. Pass True, if the message should be sent even if the specified replied-to message is not found
     * @param replyMarkup Optional. Additional interface options. A JSON-serialized object for an inline keyboard, custom reply keyboard, instructions to remove reply keyboard or to force a reply from the user.
     * 
     * @return On success, the sent Message is returned.
     */
    Message::Ptr sendMessage(boost::variant<std::int64_t, const std::string&> chatId, const std::string& text, const std::string& parseMode = "",
                             const std::vector<MessageEntity::Ptr>& entities = std::vector<MessageEntity::Ptr>(), bool disableWebPagePreview = false, bool disableNotification = false,
                             std::int32_t replyToMessageId = 0, bool allowSendingWithoutReply = false, GenericReply::Ptr replyMarkup = std::make_shared<GenericReply>()) const;

    /**
     * @brief Use this method to forward messages of any kind.
     * @param chatId Unique identifier for the target chat.
     * @param fromChatId Unique identifier for the chat where the original message was sent — User or GroupChat id.
     * @param messageId Unique message identifier.
     * @param disableNotification Optional. Sends the message silenty.
     * @return On success, the sent message is returned.
     */
    Message::Ptr forwardMessage(std::int64_t chatId, std::int64_t fromChatId, std::int32_t messageId, bool disableNotification = false) const;

    /**
     * @brief Use this method to copy messages of any kind.
     * The method is analogous to the method Api::forwardMessages, but the copied message doesn't have a link to the original message.
     * 
     * @param chatId Unique identifier for the target chat or username of the target channel (in the format @channelusername)
     * @param fromChatId Unique identifier for the chat where the original message was sent (or channel username in the format @channelusername)
     * @param messageId Message identifier in the chat specified in fromChatId
     * @param caption Optional. New caption for media, 0-1024 characters after entities parsing. If not specified, the original caption is kept
     * @param parseMode Optional. Mode for parsing entities in the new caption. See https://core.telegram.org/bots/api#formatting-options for more details.
     * @param captionEntities Optional. List of special entities that appear in the new caption, which can be specified instead of parseMode
     * @param disableNotification Optional. Sends the message silently. Users will receive a notification with no sound.
     * @param replyToMessageId Optional. If the message is a reply, ID of the original message
     * @param allowSendingWithoutReply Optional. Pass True, if the message should be sent even if the specified replied-to message is not found
     * @param replyMarkup Optional. Additional interface options. A JSON-serialized object for an inline keyboard, custom reply keyboard, instructions to remove reply keyboard or to force a reply from the user.
     * 
     * @return the MessageId of the sent message on success.
     */
    MessageId::Ptr copyMessage(std::int64_t chatId, std::int64_t fromChatId, std::int32_t messageId,
                               const std::string& caption = "", const std::string& parseMode = "", const std::vector<MessageEntity::Ptr>& captionEntities = std::vector<MessageEntity::Ptr>(),
                               bool disableNotification = false, std::int32_t replyToMessageId = 0, bool allowSendingWithoutReply = false,
                               GenericReply::Ptr replyMarkup = std::make_shared<GenericReply>()) const;

    /**
     * @brief Use this method to send photos.
     * 
     * @param chatId Unique identifier for the target chat or username of the target channel (in the format @channelusername)
     * @param photo Photo to send. Pass a fileId as String to send a photo that exists on the Telegram servers (recommended), pass an HTTP URL as a String for Telegram to get a photo from the Internet, or upload a new photo using multipart/form-data. https://core.telegram.org/bots/api#sending-files
     * @param caption Optional. Photo caption (may also be used when resending photos by fileId), 0-1024 characters after entities parsing
     * @param parseMode Optional. Mode for parsing entities in the photo caption. See https://core.telegram.org/bots/api#formatting-options for more details.
     * @param captionEntities Optional. List of special entities that appear in the caption, which can be specified instead of parseMode
     * @param disableNotification Optional.Sends the message silently. Users will receive a notification with no sound.
     * @param replyToMessageId Optional. If the message is a reply, ID of the original message
     * @param allowSendingWithoutReply Optional. Pass True, if the message should be sent even if the specified replied-to message is not found
     * @param replyMarkup Optional. Additional interface options. A JSON-serialized object for an inline keyboard, custom reply keyboard, instructions to remove reply keyboard or to force a reply from the user.
     * 
     * @return On success, the sent Message is returned.
     */
    Message::Ptr sendPhoto(std::int64_t chatId, boost::variant<InputFile::Ptr, std::string> photo, const std::string& caption = "",
                           const std::string& parseMode = "", const std::vector<MessageEntity::Ptr>& captionEntities = std::vector<MessageEntity::Ptr>(), bool disableNotification = false,
                           std::int32_t replyToMessageId = 0, bool allowSendingWithoutReply = false, GenericReply::Ptr replyMarkup = std::make_shared<GenericReply>()) const;

    /**
     * @brief Use this method to send audio files, if you want Telegram clients to display them in the music player. 
     * Your audio must be in the .MP3 or .M4A format.
     * Bots can currently send audio files of up to 50 MB in size, this limit may be changed in the future.
     * 
     * For sending voice messages, use the Api::sendVoice method instead.
     * 
     * @param chatId Unique identifier for the target chat or username of the target channel (in the format @channelusername)
     * @param audio Audio file to send. Pass a fileId as String to send an audio file that exists on the Telegram servers (recommended), pass an HTTP URL as a String for Telegram to get an audio file from the Internet, or upload a new one using multipart/form-data. https://core.telegram.org/bots/api#sending-files
     * @param caption Optional. Audio caption, 0-1024 characters after entities parsing
     * @param parseMode Optional. Mode for parsing entities in the audio caption. See https://core.telegram.org/bots/api#formatting-options for more details.
     * @param captionEntities Optional. List of special entities that appear in the caption, which can be specified instead of parseMode
     * @param duration Optional. Duration of the audio in seconds
     * @param performer Optional. Performer
     * @param title Optional. Track name
     * @param thumb Optional. Thumbnail of the file sent; can be ignored if thumbnail generation for the file is supported server-side. The thumbnail should be in JPEG format and less than 200 kB in size. A thumbnail's width and height should not exceed 320. Ignored if the file is not uploaded using multipart/form-data. Thumbnails can't be reused and can be only uploaded as a new file, so you can pass “attach://<file_attach_name>” if the thumbnail was uploaded using multipart/form-data under <file_attach_name>. https://core.telegram.org/bots/api#sending-files
     * @param disableNotification Optional. Sends the message silently. Users will receive a notification with no sound.
     * @param replyToMessageId Optional. If the message is a reply, ID of the original message
     * @param allowSendingWithoutReply Optional. Pass True, if the message should be sent even if the specified replied-to message is not found
     * @param replyMarkup Optional. Additional interface options. A JSON-serialized object for an inline keyboard, custom reply keyboard, instructions to remove reply keyboard or to force a reply from the user.
     * 
     * @return On success, the sent Message is returned.
     */
    Message::Ptr sendAudio(std::int64_t chatId,
                           boost::variant<InputFile::Ptr, std::string> audio,
                           const std::string& caption = "",
                           const std::string& parseMode = "",
                           const std::vector<MessageEntity::Ptr>& captionEntities = std::vector<MessageEntity::Ptr>(),
                           std::int32_t duration = 0,
                           const std::string& performer = "",
                           const std::string& title = "",
                           boost::variant<InputFile::Ptr, std::string> thumb = "",
                           bool disableNotification = false,
                           std::int32_t replyToMessageId = 0,
                           bool allowSendingWithoutReply = false,
                           GenericReply::Ptr replyMarkup = std::make_shared<GenericReply>()) const;

    /**
     * @brief Use this method to send general files.
     * Bots can currently send files of any type of up to 50 MB in size, this limit may be changed in the future.
     * 
     * @param chatId Unique identifier for the target chat or username of the target channel (in the format @channelusername)
     * @param document File to send. Pass a fileId as String to send a file that exists on the Telegram servers (recommended), pass an HTTP URL as a String for Telegram to get a file from the Internet, or upload a new one using multipart/form-data. https://core.telegram.org/bots/api#sending-files
     * @param thumb Optional. Thumbnail of the file sent; can be ignored if thumbnail generation for the file is supported server-side. The thumbnail should be in JPEG format and less than 200 kB in size. A thumbnail's width and height should not exceed 320. Ignored if the file is not uploaded using multipart/form-data. Thumbnails can't be reused and can be only uploaded as a new file, so you can pass “attach://<file_attach_name>” if the thumbnail was uploaded using multipart/form-data under <file_attach_name>. https://core.telegram.org/bots/api#sending-files
     * @param caption Optional. Document caption (may also be used when resending documents by fileId), 0-1024 characters after entities parsing
     * @param parseMode Optional. Mode for parsing entities in the document caption. See https://core.telegram.org/bots/api#formatting-options for more details.
     * @param captionEntities Optional. List of special entities that appear in the caption, which can be specified instead of parseMode
     * @param disableContentTypeDetection Optional. Disables automatic server-side content type detection for files uploaded using multipart/form-data
     * @param disableNotification Optional. Sends the message silently. Users will receive a notification with no sound.
     * @param replyToMessageId Optional. If the message is a reply, ID of the original message
     * @param allowSendingWithoutReply Optional. Pass True, if the message should be sent even if the specified replied-to message is not found
     * @param replyMarkup Optional. Additional interface options. A JSON-serialized object for an inline keyboard, custom reply keyboard, instructions to remove reply keyboard or to force a reply from the user.
     * 
     * @return On success, the sent Message is returned.
     */
    Message::Ptr sendDocument(std::int64_t chatId,
                              boost::variant<InputFile::Ptr, std::string> document,
                              boost::variant<InputFile::Ptr, std::string> thumb = "",
                              const std::string& caption = "",
                              const std::string& parseMode = "",
                              const std::vector<MessageEntity::Ptr>& captionEntities = std::vector<MessageEntity::Ptr>(),
                              bool disableContentTypeDetection = false,
                              bool disableNotification = false,
                              std::int32_t replyToMessageId = 0,
                              bool allowSendingWithoutReply = false,
                              GenericReply::Ptr replyMarkup = std::make_shared<GenericReply>()) const;

    /**
     * @brief Use this method to send video files, Telegram clients support mp4 videos (other formats may be sent as Document).
     * Bots can currently send video files of up to 50 MB in size, this limit may be changed in the future.
     * 
     * @param chatId Unique identifier for the target chat or username of the target channel (in the format @channelusername)
     * @param video Video to send. Pass a fileId as String to send a video that exists on the Telegram servers (recommended), pass an HTTP URL as a String for Telegram to get a video from the Internet, or upload a new video using multipart/form-data. https://core.telegram.org/bots/api#sending-files
     * @param duration Optional. Duration of sent video in seconds
     * @param width Optional. Video width
     * @param height Optional. Video height
     * @param thumb Optional Thumbnail of the file sent; can be ignored if thumbnail generation for the file is supported server-side. The thumbnail should be in JPEG format and less than 200 kB in size. A thumbnail's width and height should not exceed 320. Ignored if the file is not uploaded using multipart/form-data. Thumbnails can't be reused and can be only uploaded as a new file, so you can pass “attach://<file_attach_name>” if the thumbnail was uploaded using multipart/form-data under <file_attach_name>. https://core.telegram.org/bots/api#sending-files
     * @param caption Optional. Video caption (may also be used when resending videos by fileId), 0-1024 characters after entities parsing
     * @param parseMode Optional. Mode for parsing entities in the video caption. See https://core.telegram.org/bots/api#formatting-options for more details.
     * @param captionEntities Optional. List of special entities that appear in the caption, which can be specified instead of parseMode
     * @param supportsStreaming Optional. Pass True, if the uploaded video is suitable for streaming
     * @param disableNotification Optional. Sends the message silently. Users will receive a notification with no sound.
     * @param replyToMessageId Optional. If the message is a reply, ID of the original message
     * @param allowSendingWithoutReply Optional. Pass True, if the message should be sent even if the specified replied-to message is not found
     * @param replyMarkup Optional. Additional interface options. A JSON-serialized object for an inline keyboard, custom reply keyboard, instructions to remove reply keyboard or to force a reply from the user.
     * 
     * @return On success, the sent Message is returned.
     */
    Message::Ptr sendVideo(std::int64_t chatId,
                           boost::variant<InputFile::Ptr, std::string> video,
                           std::int32_t duration = 0,
                           std::int32_t width = 0,
                           std::int32_t height = 0,
                           boost::variant<InputFile::Ptr, std::string> thumb = "",
                           const std::string& caption = "",
                           const std::string& parseMode = "",
                           const std::vector<MessageEntity::Ptr>& captionEntities = std::vector<MessageEntity::Ptr>(),
                           bool supportsStreaming = false,
                           bool disableNotification = false,
                           std::int32_t replyToMessageId = 0,
                           bool allowSendingWithoutReply = false,
                           GenericReply::Ptr replyMarkup = std::make_shared<GenericReply>()) const;

    /**
     * @brief Use this method to send animation files (GIF or H.264/MPEG-4 AVC video without sound).
     * Bots can currently send animation files of up to 50 MB in size, this limit may be changed in the future.
     *
     * @param chatId Unique identifier for the target chat or username of the target channel (in the format @channelusername)
     * @param animation Animation to send. Pass a fileId as String to send an animation that exists on the Telegram servers (recommended), pass an HTTP URL as a String for Telegram to get an animation from the Internet, or upload a new animation using multipart/form-data. https://core.telegram.org/bots/api#sending-files
     * @param duration Optional. Duration of sent animation in seconds
     * @param width Optional. Animation width
     * @param height Optional. Animation height
     * @param thumb Optional. Thumbnail of the file sent; can be ignored if thumbnail generation for the file is supported server-side. The thumbnail should be in JPEG format and less than 200 kB in size. A thumbnail's width and height should not exceed 320. Ignored if the file is not uploaded using multipart/form-data. Thumbnails can't be reused and can be only uploaded as a new file, so you can pass “attach://<file_attach_name>” if the thumbnail was uploaded using multipart/form-data under <file_attach_name>. https://core.telegram.org/bots/api#sending-files
     * @param caption Optional. Animation caption (may also be used when resending animation by fileId), 0-1024 characters after entities parsing
     * @param parseMode Optional. Mode for parsing entities in the animation caption. See https://core.telegram.org/bots/api#formatting-options for more details.
     * @param captionEntities Optional. List of special entities that appear in the caption, which can be specified instead of parseMode
     * @param disableNotification Optional. Sends the message silently. Users will receive a notification with no sound.
     * @param replyToMessageId Optional. If the message is a reply, ID of the original message
     * @param allowSendingWithoutReply Optional. Pass True, if the message should be sent even if the specified replied-to message is not found
     * @param replyMarkup Optional. Additional interface options. A JSON-serialized object for an inline keyboard, custom reply keyboard, instructions to remove reply keyboard or to force a reply from the user.
     * 
     * @return On success, the sent Message is returned.
     */
    Message::Ptr sendAnimation(std::int64_t chatId,
                               boost::variant<InputFile::Ptr, std::string> animation,
                               std::int32_t duration = 0,
                               std::int32_t width = 0,
                               std::int32_t height = 0,
                               boost::variant<InputFile::Ptr, std::string> thumb = "",
                               const std::string& caption = "",
                               const std::string& parseMode = "",
                               const std::vector<MessageEntity::Ptr>& captionEntities = std::vector<MessageEntity::Ptr>(),
                               bool disableNotification = false,
                               std::int32_t replyToMessageId = 0,
                               bool allowSendingWithoutReply = false,
                               GenericReply::Ptr replyMarkup = std::make_shared<GenericReply>()) const;

    /**
     * @brief Use this method to send audio files, if you want Telegram clients to display the file as a playable voice message.
     * For this to work, your audio must be in an .OGG file encoded with OPUS (other formats may be sent as Audio or Document).
     * Bots can currently send voice messages of up to 50 MB in size, this limit may be changed in the future.
     * 
     * @param chatId Unique identifier for the target chat or username of the target channel (in the format @channelusername)
     * @param voice Audio file to send. Pass a fileId as String to send a file that exists on the Telegram servers (recommended), pass an HTTP URL as a String for Telegram to get a file from the Internet, or upload a new one using multipart/form-data. https://core.telegram.org/bots/api#sending-files
     * @param caption Optional. Voice message caption, 0-1024 characters after entities parsing
     * @param parseMode Optional. Mode for parsing entities in the voice message caption. See https://core.telegram.org/bots/api#formatting-options for more details.
     * @param captionEntities Optional. List of special entities that appear in the caption, which can be specified instead of parseMode
     * @param duration Optional. Duration of the voice message in seconds
     * @param disableNotification Optional. Sends the message silently. Users will receive a notification with no sound.
     * @param replyToMessageId Optional. If the message is a reply, ID of the original message
     * @param allowSendingWithoutReply Optional. Pass True, if the message should be sent even if the specified replied-to message is not found
     * @param replyMarkup Optional. Additional interface options. A JSON-serialized object for an inline keyboard, custom reply keyboard, instructions to remove reply keyboard or to force a reply from the user.
     * 
     * @return On success, the sent Message is returned.
     */
    Message::Ptr sendVoice(std::int64_t chatId,
                           boost::variant<InputFile::Ptr, std::string> voice,
                           const std::string& caption = "",
                           const std::string& parseMode = "",
                           const std::vector<MessageEntity::Ptr>& captionEntities = std::vector<MessageEntity::Ptr>(),
                           std::int32_t duration = 0,
                           bool disableNotification = false,
                           std::int32_t replyToMessageId = 0,
                           bool allowSendingWithoutReply = false,
                           GenericReply::Ptr replyMarkup = std::make_shared<GenericReply>()) const;

    /**
     * @brief As of v.4.0, Telegram clients support rounded square mp4 videos of up to 1 minute long.
     * Use this method to send video messages.
     * 
     * @param chatId Unique identifier for the target chat or username of the target channel (in the format @channelusername)
     * @param videoNote Video note to send. Pass a fileId as String to send a video note that exists on the Telegram servers (recommended) or upload a new video using multipart/form-data. Sending video notes by a URL is currently unsupported. https://core.telegram.org/bots/api#sending-files
     * @param duration Optional. Duration of sent video in seconds
     * @param length Optional. Video width and height, i.e. diameter of the video message
     * @param thumb Optional. Thumbnail of the file sent; can be ignored if thumbnail generation for the file is supported server-side. The thumbnail should be in JPEG format and less than 200 kB in size. A thumbnail's width and height should not exceed 320. Ignored if the file is not uploaded using multipart/form-data. Thumbnails can't be reused and can be only uploaded as a new file, so you can pass “attach://<file_attach_name>” if the thumbnail was uploaded using multipart/form-data under <file_attach_name>. https://core.telegram.org/bots/api#sending-files
     * @param disableNotification Optional. Sends the message silently. Users will receive a notification with no sound.
     * @param replyToMessageId Optional. If the message is a reply, ID of the original message
     * @param allowSendingWithoutReply Optional. Pass True, if the message should be sent even if the specified replied-to message is not found
     * @param replyMarkup Optional. Additional interface options. A JSON-serialized object for an inline keyboard, custom reply keyboard, instructions to remove reply keyboard or to force a reply from the user.
     * 
     * @return On success, the sent Message is returned.
     */
    Message::Ptr sendVideoNote(std::int64_t chatId,
                               boost::variant<InputFile::Ptr, std::string> videoNote,
                               std::int32_t duration = 0,
                               std::int32_t length = 0,
                               boost::variant<InputFile::Ptr, std::string> thumb = "",
                               bool disableNotification = false,
                               std::int32_t replyToMessageId = 0,
                               bool allowSendingWithoutReply = false,
                               GenericReply::Ptr replyMarkup = std::make_shared<GenericReply>()) const;

    /**
     * @brief Use this method to send a group of photos, videos, documents or audios as an album.
     * Documents and audio files can be only group in an album with messages of the same type.
     * 
     * @param chatId Unique identifier for the target chat or username of the target channel (in the format @channelusername)
     * @param media A JSON-serialized array describing messages to be sent, must include 2-10 items
     * @param disableNotification Optional. Sends messages silently. Users will receive a notification with no sound.
     * @param replyToMessageId Optional. If the messages are a reply, ID of the original message
     * @param allowSendingWithoutReply Optional. Pass True, if the message should be sent even if the specified replied-to message is not found
     * 
     * @return On success, an array of Messages that were sent is returned.
     */
    std::vector<Message::Ptr> sendMediaGroup(std::int64_t chatId,
                                             const std::vector<InputMedia::Ptr>& media,
                                             bool disableNotification = false,
                                             std::int32_t replyToMessageId = 0,
                                             bool allowSendingWithoutReply = false) const;

    /**
     * @brief Use this method to send point on the map.
     * 
     * @param chatId Unique identifier for the target chat or username of the target channel (in the format @channelusername)
     * @param latitude Latitude of the location
     * @param longitude Longitude of the location
     * @param horizontalAccuracy Optional. The radius of uncertainty for the location, measured in meters; 0-1500
     * @param livePeriod Optional. Period in seconds for which the location will be updated (see Live Locations, should be between 60 and 86400.
     * @param heading Optional. For live locations, a direction in which the user is moving, in degrees. Must be between 1 and 360 if specified.
     * @param proximityAlertRadius Optional. For live locations, a maximum distance for proximity alerts about approaching another chat member, in meters. Must be between 1 and 100000 if specified.
     * @param disableNotification Optional. Sends the message silently. Users will receive a notification with no sound.
     * @param replyToMessageId Optional. If the message is a reply, ID of the original message
     * @param allowSendingWithoutReply Optional. Pass True, if the message should be sent even if the specified replied-to message is not found
     * @param replyMarkup Optional. Additional interface options. A JSON-serialized object for an inline keyboard, custom reply keyboard, instructions to remove reply keyboard or to force a reply from the user.
     * 
     * @return On success, the sent Message is returned.
     */
    Message::Ptr sendLocation(std::int64_t chatId,
                              float latitude,
                              float longitude,
                              float horizontalAccuracy = 0,
                              std::uint32_t livePeriod = 0,
                              std::uint32_t heading = 0,
                              std::uint32_t proximityAlertRadius = 0,
                              bool disableNotification = false,
                              std::int32_t replyToMessageId = 0,
                              bool allowSendingWithoutReply = false,
                              GenericReply::Ptr replyMarkup = std::make_shared<GenericReply>()) const;

    /**
     * @brief Use this method to edit live location messages.
     * A location can be edited until its livePeriod expires or editing is explicitly disabled by a call to Api::stopMessageLiveLocation.
     * 
     * @param latitude Latitude of new location
     * @param longitude Longitude of new location
     * @param chatId Optional. Required if inlineMessageId is not specified. Unique identifier for the target chat or username of the target channel (in the format @channelusername)
     * @param messageId Optional. Required if inlineMessageId is not specified. Identifier of the message to edit
     * @param inlineMessageId Optional. Required if chatId and messageId are not specified. Identifier of the inline message
     * @param horizontalAccuracy Optional. The radius of uncertainty for the location, measured in meters; 0-1500
     * @param heading Optional. Direction in which the user is moving, in degrees. Must be between 1 and 360 if specified.
     * @param proximityAlertRadius Optional. Maximum distance for proximity alerts about approaching another chat member, in meters. Must be between 1 and 100000 if specified.
     * @param replyMarkup Optional. A JSON-serialized object for a new inline keyboard.
     * 
     * @return On success, if the edited message is not an inline message, the edited Message is returned, otherwise True is returned.
     */
    Message::Ptr editMessageLiveLocation(float latitude, float longitude, std::int64_t chatId = 0,
                                         std::int32_t messageId = 0, std::int32_t inlineMessageId = 0, float horizontalAccuracy = 0,
                                         std::int32_t heading = 0, std::int32_t proximityAlertRadius = 0, InlineKeyboardMarkup::Ptr replyMarkup = std::make_shared<InlineKeyboardMarkup>()) const;

    /**
     * @brief Use this method to edit live location messages sent by the bot or via the bot (for inline bots).
     * @param chatId Optional. Required if inlineMessageId is not specified. Unique identifier for the target chat of the target channel.
     * @param messageId Optional. Required if inlineMessageId is not specified. Identifier of the sent message.
     * @param inlineMessageId Optional. Required if chatId and messageId are not specified. Identifier of the inline message.
     * @param replyMarkup Optional. A JSON-serialized object for a new inline keyboard.
     * @return On success, if the edited message was sent by the bot, the edited Message is returned, otherwise nullptr is returned.
     */
    Message::Ptr stopMessageLiveLocation(std::int64_t chatId = 0, std::int32_t messageId = 0, std::int32_t inlineMessageId = 0,
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
     * @param googlePlaceId Optional. Google Places identifier of the venue
     * @param googlePlaceType Optional. Google Places type of the venue. (See https://developers.google.com/places/web-service/supported_types)
     * @param disableNotification Optional. Sends the message silently. Users will receive a notification with no sound.
     * @param replyToMessageId Optional. If the message is a reply, ID of the original message
     * @param allowSendingWithoutReply Optional. Pass True, if the message should be sent even if the specified replied-to message is not found
     * @param replyMarkup Optional. Additional interface options. A JSON-serialized object for an inline keyboard, custom reply keyboard, instructions to remove reply keyboard or to force a reply from the user.
     * 
     * @return On success, the sent Message is returned.
     */
    Message::Ptr sendVenue(std::int64_t chatId,
                           float latitude,
                           float longitude,
                           const std::string& title,
                           const std::string& address,
                           const std::string& foursquareId = "",
                           const std::string& foursquareType = "",
                           const std::string& googlePlaceId = "",
                           const std::string& googlePlaceType = "",
                           bool disableNotification = false,
                           std::int32_t replyToMessageId = 0,
                           bool allowSendingWithoutReply = false,
                           GenericReply::Ptr replyMarkup = std::make_shared<GenericReply>()) const;

    /**
     * @brief Use this method to send phone contacts.
     * 
     * @param chatId Unique identifier for the target chat or username of the target channel (in the format @channelusername)
     * @param phoneNumber Contact's phone number
     * @param firstName Contact's first name
     * @param lastName Optional. Contact's last name
     * @param vcard Optional. Additional data about the contact in the form of a vCard, 0-2048 bytes
     * @param disableNotification Optional. Sends the message silently. Users will receive a notification with no sound.
     * @param replyToMessageId Optional. If the message is a reply, ID of the original message
     * @param allowSendingWithoutReply Optional. Pass True, if the message should be sent even if the specified replied-to message is not found
     * @param replyMarkup Optional. Additional interface options. A JSON-serialized object for an inline keyboard, custom reply keyboard, instructions to remove keyboard or to force a reply from the user.
     * 
     * @return On success, the sent Message is returned.
     */
    Message::Ptr sendContact(std::int64_t chatId,
                             const std::string& phoneNumber,
                             const std::string& firstName,
                             const std::string& lastName = "",
                             const std::string& vcard = "",
                             bool disableNotification = false,
                             std::int32_t replyToMessageId = 0,
                             bool allowSendingWithoutReply = false,
                             GenericReply::Ptr replyMarkup = std::make_shared<GenericReply>()) const;

    /**
     * @brief Use this method to send a native poll.
     *
     * @param chatId Unique identifier for the target chat or username of the target channel (in the format @channelusername)
     * @param question Poll question, 1-300 characters
     * @param options A JSON-serialized list of answer options, 2-10 strings 1-100 characters each
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
     * @param disableNotification Optional. Sends the message silently. Users will receive a notification with no sound.
     * @param replyToMessageId Optional. If the message is a reply, ID of the original message
     * @param allowSendingWithoutReply Optional. Pass True, if the message should be sent even if the specified replied-to message is not found
     * @param replyMarkup Optional. Additional interface options. A JSON-serialized object for an inline keyboard, custom reply keyboard, instructions to remove reply keyboard or to force a reply from the user.
     *
     * @return On success, the sent Message is returned.
     */
    Message::Ptr sendPoll(std::int64_t chatId,
                          const std::string& question,
                          const std::vector<std::string>& options,
                          bool isAnonymous = true,
                          const std::string& type = "",
                          bool allowsMultipleAnswers = false,
                          std::int32_t correctOptionId = 0,
                          const std::string& explanation = "",
                          const std::string& explanationParseMode = "",
                          const std::vector<MessageEntity::Ptr>& explanationEntities = std::vector<MessageEntity::Ptr>(),
                          std::int32_t openPeriod = 0,
                          std::int32_t closeDate = 0,
                          bool isClosed = false,
                          bool disableNotification = false,
                          std::int32_t replyToMessageId = 0,
                          bool allowSendingWithoutReply = false,
                          GenericReply::Ptr replyMarkup = std::make_shared<GenericReply>()) const;

    /**
     * @brief Use this method to send an animated emoji that will display a random value.
     *
     * @param chatId Unique identifier for the target chat or username of the target channel (in the format @channelusername)
     * @param emoji Optional. Emoji on which the dice throw animation is based. Currently, must be one of “🎲”, “🎯”, “🏀”, “⚽”, or “🎰”. Dice can have values 1-6 for “🎲” and “🎯”, values 1-5 for “🏀” and “⚽”, and values 1-64 for “🎰”. Defaults to “🎲”
     * @param disableNotification Optional. Sends the message silently. Users will receive a notification with no sound.
     * @param replyToMessageId Optional. If the message is a reply, ID of the original message
     * @param allowSendingWithoutReply Optional. Pass True, if the message should be sent even if the specified replied-to message is not found
     * @param replyMarkup Optional. Additional interface options. A JSON-serialized object for an inline keyboard, custom reply keyboard, instructions to remove reply keyboard or to force a reply from the user.
     *
     * @return On success, the sent Message is returned.
     */
    Message::Ptr sendDice(std::int64_t chatId,
                          const std::string& emoji = "",
                          bool disableNotification = false,
                          std::int32_t replyToMessageId = 0,
                          bool allowSendingWithoutReply = false,
                          GenericReply::Ptr replyMarkup = std::make_shared<GenericReply>()) const;

    /**
     * @brief Use this method when you need to tell the user that something is happening on the bot's side. The status is set for 5 seconds or less (when a message arrives from your bot, Telegram clients clear its typing status).
     *
     * Example: The ImageBot needs some time to process a request and upload the image. Instead of sending a text message along the lines of “Retrieving image, please wait…”, the bot may use sendChatAction with action = upload_photo. The user will see a “sending photo” status for the bot.
     * We only recommend using this method when a response from the bot will take a noticeable amount of time to arrive.
     *
     * @param chatId Unique identifier for the target chat.
     * @param action Type of action to broadcast. Choose one, depending on what the user is about to receive: typing for text messages, upload_photo for photos, record_video or upload_video for videos, record_audio or upload_audio for audio files, upload_document for general files, find_location for location data.
     */
    void sendChatAction(std::int64_t chatId, const std::string& action) const;

    /**
     * @brief Use this method to get a list of profile pictures for a user.
     * @param userId Unique identifier of the target user.
     * @param offset Optional. Sequential number of the first photo to be returned. By default, all photos are returned.
     * @param limit Optional. Limits the number of photos to be retrieved. Values between 1—100 are accepted. Defaults to 100.
     * @return A UserProfilePhotos object.
     */
    UserProfilePhotos::Ptr getUserProfilePhotos(std::int64_t userId, std::int32_t offset = 0, std::int32_t limit = 100) const;

    /**
     * @brief Use this method to get basic info about a file and prepare it for downloading. For the moment, bots can download files of up to 20MB in size.
     * @param fileId File identifier to get info about
     * @return A File object.
     */
    File::Ptr getFile(const std::string& fileId) const;

    /**
     * @brief Downloads file from Telegram and saves it in memory.
     * @param filePath Telegram file path.
     * @param args Additional api parameters.
     * @return File contents in a string.
     */
    std::string downloadFile(const std::string& filePath, const std::vector<HttpReqArg>& args = std::vector<HttpReqArg>()) const;

    /**
     * @brief Use this method to kick a user from a group or a supergroup.
     * @param chatId Unique identifier for the target group.
     * @param userId Unique identifier of the target user.
     * @param untilDate Optional. Date when the user will be unbanned, unix time. If user is banned for more than 366 days or less than 30 seconds from the current time they are considered to be banned forever.
     * @return True on success
     */
    bool kickChatMember(std::int64_t chatId, std::int64_t userId, std::uint64_t untilDate = 0) const;

    /**
     * @brief Use this method to unban a previously kicked user in a supergroup or channel.
     * 
     * The user will not return to the group or channel automatically, but will be able to join via link, etc.
     * The bot must be an administrator for this to work.
     * By default, this method guarantees that after the call the user is not a member of the chat, but will be able to join it.
     * So if the user is a member of the chat they will also be removed from the chat.
     * If you don't want this, use the parameter only_if_banned.
     * 
     * @param chatId Unique identifier for the target group or username of the target supergroup or channel (in the format @username)
     * @param userId Unique identifier of the target user
     * @param onlyIfBanned Optional. True = Do nothing if the user is not banned
     * 
     * @return True on success
     */
    bool unbanChatMember(std::int64_t chatId, std::int64_t userId, bool onlyIfBanned = false) const;

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
    bool restrictChatMember(std::int64_t chatId, std::int64_t userId, ChatPermissions::Ptr permissions, std::uint64_t untilDate = 0) const;

    /**
     * @brief Use this method to promote or demote a user in a supergroup or a channel.
     * The bot must be an administrator in the chat for this to work and must have the appropriate admin rights.
     * Pass False for all boolean parameters to demote a user.
     * 
     * @param chatId Unique identifier for the target chat or username of the target channel (in the format @channelusername)
     * @param userId Unique identifier of the target user
     * @param isAnonymous Optional. Pass True, if the administrator's presence in the chat is hidden
     * @param canChangeInfo Optional. Pass True, if the administrator can change chat title, photo and other settings
     * @param canPostMessages Optional. Pass True, if the administrator can create channel posts, channels only
     * @param canEditMessages Optional. Pass True, if the administrator can edit messages of other users and can pin messages, channels only
     * @param canDeleteMessages Optional. Pass True, if the administrator can delete messages of other users
     * @param canInviteUsers Optional. Pass True, if the administrator can invite new users to the chat
     * @param canRestrictMembers Optional. Pass True, if the administrator can restrict, ban or unban chat members
     * @param canPinMessages Optional. Pass True, if the administrator can pin messages, supergroups only
     * @param canPromoteMembers Optional. Pass True, if the administrator can add new administrators with a subset of their own privileges or demote administrators that he has promoted, directly or indirectly (promoted by administrators that were appointed by him)
     * 
     * @return True on success.
     */
    bool promoteChatMember(std::int64_t chatId, std::int64_t userId, bool isAnonymous = false,
                           bool canChangeInfo = false, bool canPostMessages = false, bool canEditMessages = false,
                           bool canDeleteMessages = false, bool canInviteUsers = false, bool canRestrictMembers = false,
                           bool canPinMessages = false, bool canPromoteMembers = false) const;

    /**
     * @brief Use this method to set a custom title for an administrator in a supergroup promoted by the bot.
     *
     * @param chatId Unique identifier for the target chat or username of the target supergroup (in the format @supergroupusername)
     * @param userId Unique identifier of the target user
     * @param customTitle New custom title for the administrator; 0-16 characters, emoji are not allowed
     *
     * @return True on success
     */
    bool setChatAdministratorCustomTitle(std::int64_t chatId, std::int64_t userId, const std::string& customTitle) const;

    /**
     * @brief Use this method to set default chat permissions for all members. The bot must be an administrator in the group or a supergroup for this to work and must have the can_restrict_members admin rights. Returns True on success.
     * @param chatId Unique identifier for the target chat of the target supergroup.
     * @param permissions New default chat permissions.
     * @return True on success
     */
    bool setChatPermissions(std::int64_t chatId, ChatPermissions::Ptr permissions) const;

    /**
     * @brief Use this method to generate a new invite link for a chat; any previously generated link is revoked.
     * @param chatId Unique identifier for the target chat.
     * @return The new invite link as String on success.
     */
    std::string exportChatInviteLink(std::int64_t chatId) const;

    /**
     * @brief Use this method to set a new profile photo for the chat.
     *
     * Photos can't be changed for private chats.
     *
     * @param chatId Unique identifier for the target chat.
     * @param photo New chat photo.
     * @return True on success
     */
    bool setChatPhoto(std::int64_t chatId, InputFile::Ptr photo) const;

    /**
     * @brief Use this method to delete a chat photo.
     *
     * Photos can't be changed for private chats.
     *
     * @param chatId Unique identifier for the target chat.
     * @return True on success
     */
    bool deleteChatPhoto(std::int64_t chatId) const;

    /**
     * @brief Use this method to change the title of a chat.
     *
     * Titles can't be changed for private chats.
     *
     * @param chatId Unique identifier for the target chat.
     * @param title New chat title, 1-255 characters.
     * @return True on success
     */
    bool setChatTitle(std::int64_t chatId, const std::string& title) const;

    /**
     * @brief Use this method to change the description of a supergroup or a channel.
     * @param chatId Unique identifier for the target chat.
     * @param description New chat description, 1-255 characters.
     * @return True on success
     */
    bool setChatDescription(std::int64_t chatId, const std::string& description) const;

    /**
     * @brief Use this method to pin a message in a group, a supergroup, or a channel.
     * @param chatId Unique identifier for the target chat or username of the target channel.
     * @param messageId Identifier of a message to pin.
     * @param disableNotification Optional. Pass True, if it is not necessary to send a notification to all chat members about the new pinned message. Notifications are always disabled in channels.
     * @return True on success
     */
    bool pinChatMessage(std::int64_t chatId, std::int32_t messageId, bool disableNotification = false) const;

    /**
     * @brief Use this method to remove a message from the list of pinned messages in a chat.
     * If the chat is not a private chat, the bot must be an administrator in the chat for this to work and must have the 'can_pin_messages' admin right in a supergroup or 'can_edit_messages' admin right in a channel.
     * 
     * @param chatId Unique identifier for the target chat or username of the target channel (in the format @channelusername)
     * @param messageId Optional. Identifier of a message to unpin. If not specified, the most recent pinned message (by sending date) will be unpinned.
     * 
     * @return True on success.
     */
    bool unpinChatMessage(std::int64_t chatId, std::int32_t messageId = 0) const;

    /**
     * @brief Use this method to clear the list of pinned messages in a chat.
     * If the chat is not a private chat, the bot must be an administrator in the chat for this to work and must have the 'can_pin_messages' admin right in a supergroup or 'can_edit_messages' admin right in a channel.
     *
     * @param chatId Unique identifier for the target chat or username of the target channel (in the format @channelusername)
     *
     * @return True on success.
     */
    bool unpinAllChatMessages(std::int64_t chatId) const;

    /**
     * @brief Use this method for your bot to leave a group, supergroup or channel.
     * @param chatId Unique identifier for the target chat of the target supergroup or channel.
     * @return True on success
     */
    bool leaveChat(std::int64_t chatId) const;

    /**
     * @brief Use this method to get up to date information about the chat (current name of the user for one-on-one conversations, current username of a user, group or channel, etc.).
     * 
     * @param chatId Unique identifier for the target chat or username of the target supergroup or channel (in the format @channelusername)
     * 
     * @return @ref Chat object on success.
     */
    Chat::Ptr getChat(std::int64_t chatId) const;

    /**
    * @brief Use this method to get a list of administrators in a chat. On success, returns an Array of ChatMember objects that contains information about all chat administrators except other bots. If the chat is a group or a supergroup and no administrators were appointed, only the creator will be returned.
    * @param chatId Unique identifier for the target chat of the target supergroup or channel.
    * @return ChatMember object.
    */
    std::vector<ChatMember::Ptr> getChatAdministrators(std::int64_t chatId) const;

    /**
    * @brief Use this method to get the number of members in a chat. Returns Int on success.
    * @param chatId Unique identifier for the target chat of the target supergroup or channel.
    * @return Int.
    */
    std::int32_t getChatMembersCount(std::int64_t chatId) const;

    /**
    * @brief Use this method to get information about a member of a chat. Returns a ChatMember object on success.
    * @param chatId Unique identifier for the target chat of the target supergroup or channel.
    * @param userId Unique identifier of the target user
    * @return ChatMember object.
    */
    ChatMember::Ptr getChatMember(std::int64_t chatId, std::int64_t userId) const;

    /**
    * @brief Use this method to get information about a member of a chat. Returns a ChatMember object on success.
    * @param chatId Unique identifier for the target chat of the target supergroup or channel.
    * @param stickerSetName Name of the sticker set to be set as the group sticker set.
    * @return Returns True on success.
    */
    bool setChatStickerSet(std::int64_t chatId, const std::string& stickerSetName) const;

    /**
    * @brief Use this method to get information about a member of a chat. Returns a ChatMember object on success.
    * @param chatId Unique identifier for the target chat of the target supergroup or channel.
    * @return Returns True on success.
    */
    bool deleteChatStickerSet(std::int64_t chatId) const;

    /**
     * @brief Use this method to send answers to callback queries sent from inline keyboards. The answer will be displayed to the user as a notification at the top of the chat screen or as an alert.
     * @param callbackQueryId Unique identifier for the query to be answered
     * @param text Optional	Text of the notification. If not specified, nothing will be shown to the user, 0-200 characters
     * @param showAlert Optional If true, an alert will be shown by the client instead of a notification at the top of the chat screen. Defaults to false.
     * @param url Optional	URL that will be opened by the user's client. If you have created a Game and accepted the conditions via @Botfather, specify the URL that opens your game – note that this will only work if the query comes from a callback_game button
     * @param cacheTime Optional	The maximum amount of time in seconds that the result of the callback query may be cached client-side. Telegram apps will support caching starting in version 3.14. Defaults to 0.
     * @return True on success
     */
    bool answerCallbackQuery(const std::string& callbackQueryId, const std::string& text = "", bool showAlert = false, const std::string& url = "", std::int32_t cacheTime = 0) const;

    /**
     * @brief Use this method to change the list of the bot's commands.
     * @param commands A JSON-serialized list of bot commands to be set as the list of the bot's commands. At most 100 commands can be specified.
     * @return True on success.
     */
    bool setMyCommands(const std::vector<BotCommand::Ptr>& commands) const;

    /**
     * @brief Use this method to get the current list of the bot's commands.
     * @return Array of @ref BotCommand on success.
     */
    std::vector<BotCommand::Ptr> getMyCommands() const;

    /**
     * @brief Use this method to edit text and game messages.
     * 
     * @param text New text of the message, 1-4096 characters after entities parsing
     * @param chatId Optional. Required if inlineMessageId is not specified. Unique identifier for the target chat or username of the target channel (in the format @channelusername)
     * @param messageId Optional. Required if inlineMessageId is not specified. Identifier of the message to edit
     * @param inlineMessageId Optional.	Required if chatId and messageId are not specified. Identifier of the inline message
     * @param parseMode Optional. Mode for parsing entities in the message text. See https://core.telegram.org/bots/api#formatting-options for more details.
     * @param entities Optional. List of special entities that appear in message text, which can be specified instead of parseMode
     * @param disableWebPagePreview Optional. Disables link previews for links in this message
     * @param replyMarkup Optional. A JSON-serialized object for an inline keyboard.
     * 
     * @return On success, the edited Message is returned.
     */
    Message::Ptr editMessageText(const std::string& text,
                                 std::int64_t chatId = 0,
                                 std::int32_t messageId = 0,
                                 const std::string& inlineMessageId = "",
                                 const std::string& parseMode = "",
                                 const std::vector<MessageEntity::Ptr>& entities = std::vector<MessageEntity::Ptr>(),
                                 bool disableWebPagePreview = false,
                                 GenericReply::Ptr replyMarkup = std::make_shared<GenericReply>()) const;

    /**
     * @brief Use this method to edit captions of messages.
     * 
     * @param chatId Optional. Required if inlineMessageId is not specified. Unique identifier for the target chat or username of the target channel (in the format @channelusername)
     * @param messageId Optional. Required if inlineMessageId is not specified. Identifier of the message to edit
     * @param inlineMessageId Optional. Required if chatId and messageId are not specified. Identifier of the inline message
     * @param caption Optional. New caption of the message, 0-1024 characters after entities parsing
     * @param parseMode Optional. Mode for parsing entities in the message caption. See https://core.telegram.org/bots/api#formatting-options for more details.
     * @param captionEntities Optional. List of special entities that appear in the caption, which can be specified instead of parseMode
     * @param replyMarkup Optional. A JSON-serialized object for an inline keyboard.
     * 
     * @return On success, the edited Message is returned.
     */
    Message::Ptr editMessageCaption(std::int64_t chatId = 0,
                                    std::int32_t messageId = 0,
                                    const std::string& inlineMessageId = "",
                                    const std::string& caption = "",
                                    const std::string& parseMode = "",
                                    const std::vector<MessageEntity::Ptr>& captionEntities = std::vector<MessageEntity::Ptr>(),
                                    GenericReply::Ptr replyMarkup = std::make_shared<GenericReply>()) const;

    /**
     * @brief Use this method to edit audio, document, photo, or video messages.
     *
     *
     * If a message is a part of a message album, then it can be edited only to a photo or a video.
     * Otherwise, message type can be changed arbitrarily. When inline message is edited, new file can't be uploaded.
     * Use previously uploaded file via its fileId or specify a URL.
     *
     * @param media A JSON-serialized object for a new media content of the message.
     * @param chatId Optional	Required if inline_message_id is not specified. Unique identifier for the target chat of the target channel.
     * @param messageId Optional	Required if inline_message_id is not specified. Identifier of the sent message
     * @param inlineMessageId Optional	Required if chat_id and message_id are not specified. Identifier of the inline message
     * @param replyMarkup Optional	A JSON-serialized object for an inline keyboard.
     * @return On success, if the edited message was sent by the bot, the edited Message is returned, otherwise nullptr is returned.
     */
    Message::Ptr editMessageMedia(InputMedia::Ptr media, std::int64_t chatId = 0, std::int32_t messageId = 0, const std::string& inlineMessageId = "",
                                  GenericReply::Ptr replyMarkup = std::make_shared<GenericReply>()) const;

    /**
    * @brief Use this method to edit only the reply markup of messages sent by the bot or via the bot (for inline bots).
    * @param chatId Optional	Required if inline_message_id is not specified. Unique identifier for the target chat of the target channel.
    * @param messageId Optional	Required if inline_message_id is not specified. Identifier of the sent message
    * @param inlineMessageId Optional	Required if chat_id and message_id are not specified. Identifier of the inline message
    * @param replyMarkup Optional	A JSON-serialized object for an inline keyboard.
    * @return Message object on success, otherwise nullptr
    */
    Message::Ptr editMessageReplyMarkup(std::int64_t chatId = 0, std::int32_t messageId = 0, const std::string& inlineMessageId = "",
                                        GenericReply::Ptr replyMarkup = std::make_shared<GenericReply>()) const;

    /**
     * @brief Use this method to stop a poll which was sent by the bot.
     * @param chatId Unique identifier for the target chat or username of the target channel.
     * @param messageId Identifier of the original message with the poll.
     * @param replyMarkup Optional. A JSON-serialized object for a new message inline keyboard.
     *
     * @return On success, the stopped Poll with the final results is returned.
     */

    Poll::Ptr stopPoll(std::int64_t chatId, std::int64_t messageId, InlineKeyboardMarkup::Ptr replyMarkup = std::make_shared<InlineKeyboardMarkup>()) const;

    /**
     * @brief Use this method to delete messages sent by bot (or by other users if bot is admin).
     * @param chatId	Unique identifier for the target chat or username of the target channel.
     * @param messageId	Unique identifier for the target message.
     */
    void deleteMessage(std::int64_t chatId, std::int32_t messageId) const;

    /**
     * @brief Use this method to send static .WEBP or animated .TGS stickers.
     * 
     * @param chatId Unique identifier for the target chat or username of the target channel (in the format @channelusername)
     * @param sticker Sticker to send. Pass a fileId as String to send a file that exists on the Telegram servers (recommended), pass an HTTP URL as a String for Telegram to get a .WEBP file from the Internet, or upload a new one using multipart/form-data. https://core.telegram.org/bots/api#sending-files
     * @param disableNotification Optional. Sends the message silently. Users will receive a notification with no sound.
     * @param replyToMessageId Optional. If the message is a reply, ID of the original message
     * @param allowSendingWithoutReply Optional. Pass True, if the message should be sent even if the specified replied-to message is not found
     * @param replyMarkup Optional. Additional interface options. A JSON-serialized object for an inline keyboard, custom reply keyboard, instructions to remove reply keyboard or to force a reply from the user.
     * 
     * @return On success, the sent Message is returned.
     */
    Message::Ptr sendSticker(std::int64_t chatId,
                             boost::variant<InputFile::Ptr, std::string> sticker,
                             bool disableNotification = false,
                             std::int32_t replyToMessageId = 0,
                             bool allowSendingWithoutReply = false,
                             GenericReply::Ptr replyMarkup = std::make_shared<GenericReply>()) const;

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
    File::Ptr uploadStickerFile(std::int64_t userId, InputFile::Ptr pngSticker) const;

    /**
     * @brief Use this method to create a new sticker set owned by a user. The bot will be able to edit the sticker set thus created. You must use exactly one of the fields pngSticker or tgsSticker.
     *
     * @param userId User identifier of created sticker set owner
     * @param name Short name of sticker set, to be used in t.me/addstickers/ URLs (e.g., animals). Can contain only english letters, digits and underscores. Must begin with a letter, can't contain consecutive underscores and must end in “_by_<bot username>”. <bot_username> is case insensitive. 1-64 characters.
     * @param title Sticker set title, 1-64 characters
     * @param emojis One or more emoji corresponding to the sticker
     * @param pngSticker Optional. PNG image with the sticker, must be up to 512 kilobytes in size, dimensions must not exceed 512px, and either width or height must be exactly 512px. Pass a fileId as a String to send a file that already exists on the Telegram servers, pass an HTTP URL as a String for Telegram to get a file from the Internet, or upload a new one using multipart/form-data.
     * @param tgsSticker Optional. TGS animation with the sticker, uploaded using multipart/form-data. See https://core.telegram.org/animated_stickers#technical-requirements for technical requirements
     * @param containsMasks Optional. Pass True, if a set of mask stickers should be created
     * @param maskPosition Optional. A JSON-serialized object for position where the mask should be placed on faces
     *
     * @return Returns True on success.
     */
    bool createNewStickerSet(std::int64_t userId, const std::string& name, const std::string& title,
                             const std::string& emojis, boost::variant<InputFile::Ptr, std::string> pngSticker = "", boost::variant<InputFile::Ptr, std::string> tgsSticker = "",
                             bool containsMasks = false, MaskPosition::Ptr maskPosition = nullptr) const;

    /**
     * @brief Use this method to add a new sticker to a set created by the bot. You must use exactly one of the fields png_sticker or tgs_sticker. Animated stickers can be added to animated sticker sets and only to them. Animated sticker sets can have up to 50 stickers. Static sticker sets can have up to 120 stickers.
     *
     * @param userId User identifier of sticker set owner
     * @param name Sticker set name
     * @param emojis One or more emoji corresponding to the sticker
     * @param pngSticker Optional. PNG image with the sticker, must be up to 512 kilobytes in size, dimensions must not exceed 512px, and either width or height must be exactly 512px. Pass a fileId as a String to send a file that already exists on the Telegram servers, pass an HTTP URL as a String for Telegram to get a file from the Internet, or upload a new one using multipart/form-data.
     * @param tgsSticker Optional. TGS animation with the sticker, uploaded using multipart/form-data. See https://core.telegram.org/animated_stickers#technical-requirements for technical requirements
     * @param maskPosition Optional. A JSON-serialized object for position where the mask should be placed on faces
     *
     * @return Returns True on success.
     */
    bool addStickerToSet(std::int64_t userId, const std::string& name, const std::string& emojis,
                         boost::variant<InputFile::Ptr, std::string> pngSticker = "", boost::variant<InputFile::Ptr, std::string> tgsSticker = "", MaskPosition::Ptr maskPosition = nullptr) const;

    /**
     * @brief Use this method to move a sticker in a set created by the bot to a specific position.
     * @param stickers File identifier of the sticker.
     * @param position New sticker position in the set, zero-based.
     * @return Returns True on success.
     */
    bool setStickerPositionInSet(const std::string& sticker, std::uint32_t position) const;

    /**
     * @brief Use this method to delete a sticker from a set created by the bot.
     * @param stickers File identifier of the sticker.
     * @return Returns True on success.
     */
    bool deleteStickerFromSet(const std::string& sticker) const;

    /**
     * @brief Use this method to set the thumbnail of a sticker set. Animated thumbnails can be set for animated sticker sets only.
     *
     * @param name Sticker set name
     * @param userId User identifier of the sticker set owner
     * @param thumb Optional. A PNG image with the thumbnail, must be up to 128 kilobytes in size and have width and height exactly 100px, or a TGS animation with the thumbnail up to 32 kilobytes in size; see https://core.telegram.org/animated_stickers#technical-requirements for animated sticker technical requirements. Pass a fileId as a String to send a file that already exists on the Telegram servers, pass an HTTP URL as a String for Telegram to get a file from the Internet, or upload a new one using multipart/form-data. Animated sticker set thumbnail can't be uploaded via HTTP URL.
     *
     * @return Returns True on success.
     */
    bool setStickerSetThumb(const std::string& name, std::int64_t userId, boost::variant<InputFile::Ptr, std::string> thumb = "") const;

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
                           std::int32_t cacheTime = 300, bool isPersonal = false, const std::string& nextOffset = "", const std::string& switchPmText = "", const std::string& switchPmParameter = "") const;

    /**
     * @brief Use this method to send invoices.
     * 
     * @param chatId Unique identifier for the target private chat
     * @param title Product name, 1-32 characters
     * @param description Product description, 1-255 characters
     * @param payload Bot-defined invoice payload, 1-128 bytes. This will not be displayed to the user, use for your internal processes.
     * @param providerToken Payments provider token, obtained via Botfather
     * @param startParameter Unique deep-linking parameter that can be used to generate this invoice when used as a start parameter
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
     * @param disableNotification Optional. Sends the message silently. Users will receive a notification with no sound.
     * @param replyToMessageId Optional. If the message is a reply, ID of the original message
     * @param allowSendingWithoutReply Optional. Pass True, if the message should be sent even if the specified replied-to message is not found
     * @param replyMarkup Optional. A JSON-serialized object for an inline keyboard. If empty, one 'Pay total price' button will be shown. If not empty, the first button must be a Pay button.
     * 
     * @return On success, the sent Message is returned.
     */
    Message::Ptr sendInvoice(std::int64_t chatId,
                             const std::string& title,
                             const std::string& description,
                             const std::string& payload,
                             const std::string& providerToken,
                             const std::string& startParameter,
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
                             bool disableNotification = false,
                             std::int32_t replyToMessageId = 0,
                             bool allowSendingWithoutReply = false,
                             GenericReply::Ptr replyMarkup = std::make_shared<GenericReply>()) const;

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
     * @return True on success.
     */
    bool setPassportDataErrors(std::int64_t userId, const std::vector<PassportElementError::Ptr>& errors) const;

    /**
     * @brief Use this method to send a game.
     * 
     * @param chatId Unique identifier for the target chat
     * @param gameShortName Short name of the game, serves as the unique identifier for the game. Set up your games via Botfather.
     * @param disableNotification Optional. Sends the message silently. Users will receive a notification with no sound.
     * @param replyToMessageId Optional. If the message is a reply, ID of the original message
     * @param allowSendingWithoutReply Optional. Pass True, if the message should be sent even if the specified replied-to message is not found
     * @param replyMarkup Optional. A JSON-serialized object for an inline keyboard. If empty, one 'Play game_title' button will be shown. If not empty, the first button must launch the game.
     * 
     * @return On success, the sent Message is returned.
     */
    Message::Ptr sendGame(std::int64_t chatId,
                          const std::string& gameShortName,
                          bool disableNotification = false,
                          std::int32_t replyToMessageId = 0,
                          bool allowSendingWithoutReply = false,
                          InlineKeyboardMarkup::Ptr replyMarkup = std::make_shared<InlineKeyboardMarkup>()) const;

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
    Message::Ptr setGameScore(std::int64_t userId, std::int32_t score, bool force = false, bool disableEditMessage = false,
                              std::int64_t chatId = 0, std::int32_t messageId = 0, const std::string& inlineMessageId = "") const;

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
    std::vector<GameHighScore::Ptr> getGameHighScores(std::int64_t userId, std::int32_t score, bool force = false,
                                                      bool disableEditMessage = false, std::int64_t chatId = 0, std::int32_t messageId = 0, const std::string& inlineMessageId = "") const;
    
private:
    boost::property_tree::ptree sendRequest(const std::string& method, const std::vector<HttpReqArg>& args = std::vector<HttpReqArg>()) const;

    const std::string _token;
    const HttpClient& _httpClient;
    const TgTypeParser _tgTypeParser;
    const std::string _url;
};
}

#endif //TGBOT_CPP_API_H
