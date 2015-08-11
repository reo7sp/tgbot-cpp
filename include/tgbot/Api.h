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

#include "tgbot/net/HttpReqArg.h"
#include "tgbot/types/User.h"
#include "tgbot/types/Message.h"
#include "tgbot/types/GenericReply.h"
#include "tgbot/types/InputFile.h"
#include "tgbot/types/UserProfilePhotos.h"
#include "tgbot/types/Update.h"

namespace TgBot {

class Bot;

/**
 * This class executes telegram api methods. Telegram docs: <https://core.telegram.org/bots/api#available-methods>
 * @ingroup general
 */
class Api {

friend Bot;

public:
	Api(const std::string& token);

	/**
	 * A simple method for testing your bot's auth token.
	 * @return Basic information about the bot in form of a User object.
	 */
	User::Ptr getMe() const;

	/**
	 * Use this method to send text messages.
	 * @param chatId Unique identifier for the message recipient — User or GroupChat id.
	 * @param text Text of the message to be sent.
	 * @param disableWebPagePreview Optional. Disables link previews for links in this message.
	 * @param replyToMessageId Optional. If the message is a reply, ID of the original message.
	 * @param replyMarkup Optional. Additional interface options. An object for a custom reply keyboard, instructions to hide keyboard or to force a reply from the user.
	 * @return On success, the sent message is returned.
	 */
	Message::Ptr sendMessage(int32_t chatId, const std::string& text, bool disableWebPagePreview = false, int32_t replyToMessageId = 0, const GenericReply::Ptr& replyMarkup = GenericReply::Ptr()) const;

	/**
	 * Use this method to forward messages of any kind.
	 * @param chatId Unique identifier for the message recipient — User or GroupChat id.
	 * @param fromChatId Unique identifier for the chat where the original message was sent — User or GroupChat id.
	 * @param messageId Unique message identifier.
	 * @return On success, the sent message is returned.
	 */
	Message::Ptr forwardMessage(int32_t chatId, int32_t fromChatId, int32_t messageId) const;

	/**
	 * Use this method to send photos.
	 * @param chatId Unique identifier for the message recipient — User or GroupChat id.
	 * @param photo Photo to send.
	 * @param caption Optional. Photo caption.
	 * @param replyToMessageId Optional. If the message is a reply, ID of the original message.
	 * @param replyMarkup Optional. Additional interface options. An object for a custom reply keyboard, instructions to hide keyboard or to force a reply from the user.
	 * @return On success, the sent message is returned.
	 */
	Message::Ptr sendPhoto(int32_t chatId, const InputFile::Ptr& photo, const std::string& caption = "", int32_t replyToMessageId = 0, const GenericReply::Ptr& replyMarkup = GenericReply::Ptr()) const;

	/**
	 * Use this method to send photos.
	 * @param chatId Unique identifier for the message recipient — User or GroupChat id.
	 * @param photo Photo to send. Id of the photo that is already on the Telegram servers.
	 * @param caption Optional. Photo caption.
	 * @param replyToMessageId Optional. If the message is a reply, ID of the original message.
	 * @param replyMarkup Optional. Additional interface options. An object for a custom reply keyboard, instructions to hide keyboard or to force a reply from the user.
	 * @return On success, the sent message is returned.
	 */
	Message::Ptr sendPhoto(int32_t chatId, const std::string& photo, const std::string& caption = "", int32_t replyToMessageId = 0, const GenericReply::Ptr& replyMarkup = GenericReply::Ptr()) const;

	/**
	 * Use this method to send audio files, if you want Telegram clients to display the file as a playable voice message. For this to work, your audio must be in an .ogg file encoded with OPUS (other formats may be sent as Document).
	 * @param chatId Unique identifier for the message recipient — User or GroupChat id.
	 * @param audio Audio to send.
	 * @param duration Duration of sent audio in seconds.
	 * @param replyToMessageId Optional. If the message is a reply, ID of the original message.
	 * @param replyMarkup Optional. Additional interface options. An object for a custom reply keyboard, instructions to hide keyboard or to force a reply from the user.
	 * @return On success, the sent message is returned.
	 */
	Message::Ptr sendAudio(int32_t chatId, const InputFile::Ptr& audio, int32_t duration = 0, int32_t replyToMessageId = 0, const GenericReply::Ptr& replyMarkup = GenericReply::Ptr()) const;

	/**
	 * Use this method to send audio files, if you want Telegram clients to display the file as a playable voice message. For this to work, your audio must be in an .ogg file encoded with OPUS (other formats may be sent as Document).
	 * @param chatId Unique identifier for the message recipient — User or GroupChat id.
	 * @param audio Id of the audio that is already on the Telegram servers.
	 * @param duration Duration of sent audio in seconds.
	 * @param replyToMessageId Optional. If the message is a reply, ID of the original message.
	 * @param replyMarkup Optional. Additional interface options. An object for a custom reply keyboard, instructions to hide keyboard or to force a reply from the user.
	 * @return On success, the sent message is returned.
	 */
	Message::Ptr sendAudio(int32_t chatId, const std::string& audio, int32_t duration = 0, int32_t replyToMessageId = 0, const GenericReply::Ptr& replyMarkup = GenericReply::Ptr()) const;

	/**
	 * Use this method to send general files.
	 * @param chatId Unique identifier for the message recipient — User or GroupChat id.
	 * @param document Document to send.
	 * @param replyToMessageId Optional. If the message is a reply, ID of the original message.
	 * @param replyMarkup Optional. Additional interface options. An object for a custom reply keyboard, instructions to hide keyboard or to force a reply from the user.
	 * @return On success, the sent message is returned.
	 */
	Message::Ptr sendDocument(int32_t chatId, const InputFile::Ptr& document, int32_t replyToMessageId = 0, const GenericReply::Ptr& replyMarkup = GenericReply::Ptr()) const;

	/**
	 * Use this method to send general files.
	 * @param chatId Unique identifier for the message recipient — User or GroupChat id.
	 * @param document Id of the document that is already on the Telegram servers.
	 * @param replyToMessageId Optional. If the message is a reply, ID of the original message.
	 * @param replyMarkup Optional. Additional interface options. An object for a custom reply keyboard, instructions to hide keyboard or to force a reply from the user.
	 * @return On success, the sent message is returned.
	 */
	Message::Ptr sendDocument(int32_t chatId, const std::string& document, int32_t replyToMessageId = 0, const GenericReply::Ptr& replyMarkup = GenericReply::Ptr()) const;

	/**
	 * Use this method to send .webp stickers.
	 * @param chatId Unique identifier for the message recipient — User or GroupChat id.
	 * @param sticker Sticker to send.
	 * @param replyToMessageId Optional. If the message is a reply, ID of the original message.
	 * @param replyMarkup Optional. Additional interface options. An object for a custom reply keyboard, instructions to hide keyboard or to force a reply from the user.
	 * @return On success, the sent message is returned.
	 */
	Message::Ptr sendSticker(int32_t chatId, const InputFile::Ptr& sticker, int32_t replyToMessageId = 0, const GenericReply::Ptr& replyMarkup = GenericReply::Ptr()) const;

	/**
	 * Use this method to send .webp stickers.
	 * @param chatId Unique identifier for the message recipient — User or GroupChat id.
	 * @param sticker Id of the sticker that is already on the Telegram servers.
	 * @param replyToMessageId Optional. If the message is a reply, ID of the original message.
	 * @param replyMarkup Optional. Additional interface options. A object for a custom reply keyboard, instructions to hide keyboard or to force a reply from the user.
	 * @return On success, the sent message is returned.
	 */
	Message::Ptr sendSticker(int32_t chatId, const std::string& sticker, int32_t replyToMessageId = 0, const GenericReply::Ptr& replyMarkup = GenericReply::Ptr()) const;

	/**
	 * Use this method to send video files, Telegram clients support mp4 videos (other formats may be sent as Document).
	 * @param chatId Unique identifier for the message recipient — User or GroupChat id.
	 * @param video Video to send.
	 * @param replyToMessageId Optional. If the message is a reply, ID of the original message.
	 * @param replyMarkup Optional. Additional interface options. An object for a custom reply keyboard, instructions to hide keyboard or to force a reply from the user.
	 * @return On success, the sent message is returned.
	 */
	Message::Ptr sendVideo(int32_t chatId, const InputFile::Ptr& video, int32_t replyToMessageId = 0, const GenericReply::Ptr& replyMarkup = GenericReply::Ptr()) const;

	/**
	 * Use this method to send video files, Telegram clients support mp4 videos (other formats may be sent as Document).
	 * @param chatId Unique identifier for the message recipient — User or GroupChat id.
	 * @param video Id of the video that is already on the Telegram servers.
	 * @param replyToMessageId Optional. If the message is a reply, ID of the original message.
	 * @param replyMarkup Optional. Additional interface options. A object for a custom reply keyboard, instructions to hide keyboard or to force a reply from the user.
	 * @return On success, the sent message is returned.
	 */
	Message::Ptr sendVideo(int32_t chatId, const std::string& video, int32_t replyToMessageId = 0, const GenericReply::Ptr& replyMarkup = GenericReply::Ptr()) const;

	/**
	 * Use this method to send point on the map.
	 * @param chatId Unique identifier for the message recipient — User or GroupChat id.
	 * @param latitude Latitude of location.
	 * @param longitude Longitude of location.
	 * @param replyToMessageId Optional. If the message is a reply, ID of the original message.
	 * @param replyMarkup Optional. Additional interface options. A object for a custom reply keyboard, instructions to hide keyboard or to force a reply from the user.
	 * @return On success, the sent message is returned.
	 */
	Message::Ptr sendLocation(int32_t chatId, float latitude, float longitude, int32_t replyToMessageId = 0, const GenericReply::Ptr& replyMarkup = GenericReply::Ptr()) const;

	/**
	 * Use this method when you need to tell the user that something is happening on the bot's side. The status is set for 5 seconds or less (when a message arrives from your bot, Telegram clients clear its typing status).
	 * Example: The ImageBot needs some time to process a request and upload the image. Instead of sending a text message along the lines of “Retrieving image, please wait…”, the bot may use sendChatAction with action = upload_photo. The user will see a “sending photo” status for the bot.
	 * We only recommend using this method when a response from the bot will take a noticeable amount of time to arrive.
	 * @param chatId Unique identifier for the message recipient — User or GroupChat id.
	 * @param action Type of action to broadcast. Choose one, depending on what the user is about to receive: typing for text messages, upload_photo for photos, record_video or upload_video for videos, record_audio or upload_audio for audio files, upload_document for general files, find_location for location data.
	 */
	void sendChatAction(int32_t chatId, const std::string& action) const;

	/**
	 * Use this method to get a list of profile pictures for a user.
	 * @param userId Unique identifier of the target user.
	 * @param offset Optional. Sequential number of the first photo to be returned. By default, all photos are returned.
	 * @param limit Optional. Limits the number of photos to be retrieved. Values between 1—100 are accepted. Defaults to 100.
	 * @return A UserProfilePhotos object.
	 */
	UserProfilePhotos::Ptr getUserProfilePhotos(int32_t userId, int32_t offset = 0, int32_t limit = 100) const;

	/**
	 * Use this method to receive incoming updates using long polling.
	 * This method will not work if an outgoing webhook is set up.
	 * In order to avoid getting duplicate updates, recalculate offset after each server response.
	 * @param offset Optional. Identifier of the first update to be returned. Must be greater by one than the highest among the identifiers of previously received updates. By default, updates starting with the earliest unconfirmed update are returned. An update is considered confirmed as soon as getUpdates is called with an offset higher than its update_id.
	 * @param limit Optional. Limits the number of updates to be retrieved. Values between 1—100 are accepted. Defaults to 100.
	 * @param timeout Optional. Timeout in seconds for long polling. Defaults to 0, i.e. usual short polling.
	 * @return An Array of Update objects
	 */
	std::vector<Update::Ptr> getUpdates(int32_t offset = 0, int32_t limit = 100, int32_t timeout = 0) const;

	/**
	 * Use this method to specify a url and receive incoming updates via an outgoing webhook. Whenever there is an update for the bot, we will send an HTTPS POST request to the specified url, containing a JSON-serialized Update. In case of an unsuccessful request, we will give up after a reasonable amount of attempts.
	 * If you'd like to make sure that the Webhook request comes from Telegram, we recommend using a secret path in the URL, e.g. www.example.com/<token>. Since nobody else knows your bot‘s token, you can be pretty sure it’s us.
	 * You will not be able to receive updates using getUpdates for as long as an outgoing webhook is set up.
	 * We currently do not support self-signed certificates.
	 * Ports currently supported for Webhooks: 443, 80, 88, 8443.
	 * @param url Optional. HTTPS url to send updates to. Use an empty string to remove webhook integration.
	 */
	void setWebhook(const std::string& url = "") const;

private:
	boost::property_tree::ptree sendRequest(const std::string& method, const std::vector<HttpReqArg>& args = std::vector<HttpReqArg>()) const;

	const std::string _token;
};

}

#endif //TGBOT_CPP_API_H
