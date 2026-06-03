#include "maxbot/Api.h"
#include "maxbot/tools/StringTools.h"

#include <chrono>
#include <stdexcept>
#include <thread>

namespace MaxBot {

Api::Api(const HttpClient& httpClient, const std::string& url)
	: _httpClient(httpClient)
	, _botTypeParser()
	, _url([&] {
		if (url.empty())
			throw std::runtime_error("url is empty");
		if (url.back() != '/')
			return url + '/';
		return url;
	}())
{ }

Updates::Ptr Api::getUpdates(
	std::int64_t marker,
    std::int32_t limit,
    std::int32_t timeout,
    const StringArrayPtr& allowedUpdates) const {
    std::vector<HttpReqArg> args;
    args.reserve(4);

    if (marker != 0) {
        args.emplace_back("marker", marker);
    }
    if (limit != 100) {
        args.emplace_back("limit", std::max(1, std::min(100, limit)));
    }
    if (timeout != 0) {
        args.emplace_back("timeout", timeout);
    }
    if (allowedUpdates != nullptr) {
        auto allowedUpdatesJson = _botTypeParser.parseArray<std::string>(
            [] (const std::string& s)->std::string {
            return s;
        }, *allowedUpdates);
        args.emplace_back("update_types", allowedUpdatesJson);
    }

    return _botTypeParser.parseJsonAndGetUpdates(sendRequest("updates", args));
}

bool Api::setWebhook(const std::string& url,
                     const StringArrayPtr& allowedUpdates,
                     const std::string& secretToken) const {
    std::vector<HttpReqArg> args;
    args.reserve(7);

    args.emplace_back("url", url);
    if (allowedUpdates != nullptr) {
        auto allowedUpdatesJson = _botTypeParser.parseArray<std::string>(
            [] (const std::string& s)->std::string {
            return s;
        }, *allowedUpdates);
        args.emplace_back("update_types", allowedUpdatesJson);
    }
    if (!secretToken.empty()) {
        args.emplace_back("secret", secretToken);
    }

    return sendRequest("subscriptions", args).get<bool>("success", false);
}

bool Api::deleteWebhook(const std::string& url) const {
    return sendRequest("subscriptions?url="+StringTools::urlEncode(url), std::vector<HttpReqArg>{}, "DELETE").get<bool>("success", false);
}

WebhookInfo::Ptr Api::getWebhookInfo() const {
    boost::property_tree::ptree p = sendRequest("subscriptions");

    if (!p.get_child_optional("url")) {
        return nullptr;
    }

    if (p.get<std::string>("url", "") != std::string("")) {
        return _botTypeParser.parseJsonAndGetWebhookInfo(p);
    } else {
        return nullptr;
    }
}

User::Ptr Api::getMe() const {
    return _botTypeParser.parseJsonAndGetUser(sendRequest("me"));
}

bool Api::logOut() const {
    return sendRequest("logOut").get<bool>("", false);
}

bool Api::close() const {
    return sendRequest("close").get<bool>("", false);
}

Message::Ptr Api::sendMessage(std::int64_t chatId,
                             NewMessageBody::Ptr msg,
                             bool disableLinkPreview) const
{
	if (!msg)
		return {};

	auto url = "messages?chat_id=" + std::to_string(chatId) + "&disable_link_preview=" + (disableLinkPreview ? '1' : '0');
    auto json = _botTypeParser.parseNewMessageBody(msg);
    return _botTypeParser.parseJsonAndGetMessage(sendRequest(url, json).get_child("message"));
}

bool Api::editMessage(const std::string& msgId, NewMessageBody::Ptr msg) const
{
	if (!msg)
		return {};

	auto url = "messages?message_id=" + msgId;
    auto json = _botTypeParser.parseNewMessageBody(msg);
    return sendRequest(url, json, "PUT").get<bool>("success", false);
}

Message::Ptr Api::forwardMessage(boost::variant<std::int64_t, std::string> chatId,
                                 boost::variant<std::int64_t, std::string> fromChatId,
                                 std::int32_t messageId,
                                 bool disableNotification,
                                 bool protectContent,
                                 std::int32_t messageThreadId) const {
    std::vector<HttpReqArg> args;
    args.reserve(6);

    args.emplace_back("chat_id", chatId);
    if (messageThreadId != 0) {
        args.emplace_back("message_thread_id", messageThreadId);
    }
    args.emplace_back("from_chat_id", fromChatId);
    if (disableNotification) {
        args.emplace_back("disable_notification", disableNotification);
    }
    if (protectContent) {
        args.emplace_back("protect_content", protectContent);
    }
    args.emplace_back("message_id", messageId);

    return _botTypeParser.parseJsonAndGetMessage(sendRequest("forwardMessage", args));
}

std::vector<MessageId::Ptr> Api::forwardMessages(boost::variant<std::int64_t, std::string> chatId,
                                                 boost::variant<std::int64_t, std::string> fromChatId,
                                                 const std::vector<std::int32_t>& messageIds,
                                                 std::int32_t messageThreadId,
                                                 bool disableNotification,
                                                 bool protectContent) const {
    std::vector<HttpReqArg> args;
    args.reserve(6);

    args.emplace_back("chat_id", chatId);
    args.emplace_back("from_chat_id", fromChatId);
    if (!messageIds.empty()) {
        args.emplace_back("message_ids", _botTypeParser.parseArray<std::int32_t>(
            [] (const std::int32_t& i)->std::int32_t {
            return i;
        }, messageIds));
    }
    if (messageThreadId != 0) {
        args.emplace_back("message_thread_id", messageThreadId);
    }
    if (disableNotification) {
        args.emplace_back("disable_notification", disableNotification);
    }
    if (protectContent) {
        args.emplace_back("protect_content", protectContent);
    }

    return _botTypeParser.parseJsonAndGetArray<MessageId>(&BotTypeParser::parseJsonAndGetMessageId, sendRequest("forwardMessages", args));
}

MessageId::Ptr Api::copyMessage(boost::variant<std::int64_t, std::string> chatId,
                                boost::variant<std::int64_t, std::string> fromChatId,
                                std::int32_t messageId,
                                const std::string& caption,
                                const std::string& parseMode,
                                const std::vector<MessageEntity::Ptr>& captionEntities,
                                bool disableNotification,
                                ReplyParameters::Ptr replyParameters,
                                GenericReply::Ptr replyMarkup,
                                bool protectContent,
                                std::int32_t messageThreadId) const {
    std::vector<HttpReqArg> args;
    args.reserve(11);

    args.emplace_back("chat_id", chatId);
    if (messageThreadId != 0) {
        args.emplace_back("message_thread_id", messageThreadId);
    }
    args.emplace_back("from_chat_id", fromChatId);
    args.emplace_back("message_id", messageId);
    if (!caption.empty()) {
        args.emplace_back("caption", caption);
    }
    if (!parseMode.empty()) {
        args.emplace_back("parse_mode", parseMode);
    }
    if (!captionEntities.empty()) {
        args.emplace_back("caption_entities", _botTypeParser.parseArray<MessageEntity>(&BotTypeParser::parseMessageEntity, captionEntities));
    }
    if (disableNotification) {
        args.emplace_back("disable_notification", disableNotification);
    }
    if (protectContent) {
        args.emplace_back("protect_content", protectContent);
    }
    if (replyParameters != nullptr) {
        args.emplace_back("reply_parameters", _botTypeParser.parseReplyParameters(replyParameters));
    }
    if (replyMarkup) {
        args.emplace_back("reply_markup", _botTypeParser.parseGenericReply(replyMarkup));
    }

    return _botTypeParser.parseJsonAndGetMessageId(sendRequest("copyMessage", args));
}

std::vector<MessageId::Ptr> Api::copyMessages(boost::variant<std::int64_t, std::string> chatId,
                                              boost::variant<std::int64_t, std::string> fromChatId,
                                              const std::vector<std::int32_t>& messageIds,
                                              std::int32_t messageThreadId,
                                              bool disableNotification,
                                              bool protectContent,
                                              bool removeCaption) const {
    std::vector<HttpReqArg> args;
    args.reserve(7);

    args.emplace_back("chat_id", chatId);
    args.emplace_back("from_chat_id", fromChatId);

    if (!messageIds.empty()) {
        args.emplace_back("message_ids", _botTypeParser.parseArray<std::int32_t>(
            [] (const std::int32_t& i)->std::int32_t {
            return i;
        }, messageIds));
    }
    if (messageThreadId != 0) {
        args.emplace_back("message_thread_id", messageThreadId);
    }
    if (disableNotification) {
        args.emplace_back("disable_notification", disableNotification);
    }
    if (protectContent) {
        args.emplace_back("protect_content", protectContent);
    }
    if (removeCaption) {
        args.emplace_back("remove_caption", removeCaption);
    }

    return _botTypeParser.parseJsonAndGetArray<MessageId>(&BotTypeParser::parseJsonAndGetMessageId, sendRequest("copyMessages", args));
}

Message::Ptr Api::sendPhoto(boost::variant<std::int64_t, std::string> chatId,
                            boost::variant<InputFile::Ptr, std::string> photo,
                            const std::string& caption,
                            ReplyParameters::Ptr replyParameters,
                            GenericReply::Ptr replyMarkup,
                            const std::string& parseMode,
                            bool disableNotification,
                            const std::vector<MessageEntity::Ptr>& captionEntities,
                            std::int32_t messageThreadId,
                            bool protectContent,
                            bool hasSpoiler,
                            const std::string& businessConnectionId) const {
    std::vector<HttpReqArg> args;
    args.reserve(12);

    if (!businessConnectionId.empty()) {
        args.emplace_back("business_connection_id", businessConnectionId);
    }
    args.emplace_back("chat_id", chatId);
    if (messageThreadId != 0) {
        args.emplace_back("message_thread_id", messageThreadId);
    }
    if (photo.which() == 0) {  // InputFile::Ptr
        auto file = boost::get<InputFile::Ptr>(photo);
        args.emplace_back("photo", file->data, true, file->mimeType, file->fileName);
    } else {  // std::string
        args.emplace_back("photo", boost::get<std::string>(photo));
    }
    if (!caption.empty()) {
        args.emplace_back("caption", caption);
    }
    if (!parseMode.empty()) {
        args.emplace_back("parse_mode", parseMode);
    }
    if (!captionEntities.empty()) {
        args.emplace_back("caption_entities", _botTypeParser.parseArray<MessageEntity>(&BotTypeParser::parseMessageEntity, captionEntities));
    }
    if (hasSpoiler) {
        args.emplace_back("has_spoiler", hasSpoiler);
    }
    if (disableNotification) {
        args.emplace_back("disable_notification", disableNotification);
    }
    if (protectContent) {
        args.emplace_back("protect_content", protectContent);
    }
    if (replyParameters != nullptr) {
        args.emplace_back("reply_parameters", _botTypeParser.parseReplyParameters(replyParameters));
    }
    if (replyMarkup != nullptr) {
        args.emplace_back("reply_markup", _botTypeParser.parseGenericReply(replyMarkup));
    }
    
    return _botTypeParser.parseJsonAndGetMessage(sendRequest("sendPhoto", args));
}

Message::Ptr Api::sendAudio(boost::variant<std::int64_t, std::string> chatId,
                            boost::variant<InputFile::Ptr, std::string> audio,
                            const std::string& caption,
                            std::int32_t duration,
                            const std::string& performer,
                            const std::string& title,
                            boost::variant<InputFile::Ptr, std::string> thumbnail,
                            ReplyParameters::Ptr replyParameters,
                            GenericReply::Ptr replyMarkup,
                            const std::string& parseMode,
                            bool disableNotification,
                            const std::vector<MessageEntity::Ptr>& captionEntities,
                            std::int32_t messageThreadId,
                            bool protectContent,
                            const std::string& businessConnectionId) const {
    std::vector<HttpReqArg> args;
    args.reserve(15);

    if (!businessConnectionId.empty()) {
        args.emplace_back("business_connection_id", businessConnectionId);
    }
    args.emplace_back("chat_id", chatId);
    if (messageThreadId != 0) {
        args.emplace_back("message_thread_id", messageThreadId);
    }
    if (audio.which() == 0) {   // InputFile::Ptr
        auto file = boost::get<InputFile::Ptr>(audio);
        args.emplace_back("audio", file->data, true, file->mimeType, file->fileName);
    } else {    // std::string
        args.emplace_back("audio", boost::get<std::string>(audio));
    }
    if (!caption.empty()) {
        args.emplace_back("caption", caption);
    }
    if (!parseMode.empty()) {
        args.emplace_back("parse_mode", parseMode);
    }
    if (!captionEntities.empty()) {
        args.emplace_back("caption_entities", _botTypeParser.parseArray<MessageEntity>(&BotTypeParser::parseMessageEntity, captionEntities));
    }
    if (duration) {
        args.emplace_back("duration", duration);
    }
    if (!performer.empty()) {
        args.emplace_back("performer", performer);
    }
    if (!title.empty()) {
        args.emplace_back("title", title);
    }
    if (thumbnail.which() == 0) {   // InputFile::Ptr
        auto file = boost::get<InputFile::Ptr>(thumbnail);
        args.emplace_back("thumbnail", file->data, true, file->mimeType, file->fileName);
    } else {    // std::string
        auto thumbnailStr = boost::get<std::string>(thumbnail);
        if (!thumbnailStr.empty()) {
            args.emplace_back("thumbnail", thumbnailStr);
        }
    }
    if (disableNotification) {
        args.emplace_back("disable_notification", disableNotification);
    }
    if (protectContent) {
        args.emplace_back("protect_content", protectContent);
    }
    if (replyParameters != nullptr) {
        args.emplace_back("reply_parameters", _botTypeParser.parseReplyParameters(replyParameters));
    }
    if (replyMarkup) {
        args.emplace_back("reply_markup", _botTypeParser.parseGenericReply(replyMarkup));
    }
    
    return _botTypeParser.parseJsonAndGetMessage(sendRequest("sendAudio", args));
}

Message::Ptr Api::sendDocument(boost::variant<std::int64_t, std::string> chatId,
                               boost::variant<InputFile::Ptr, std::string> document,
                               boost::variant<InputFile::Ptr, std::string> thumbnail,
                               const std::string& caption,
                               ReplyParameters::Ptr replyParameters,
                               GenericReply::Ptr replyMarkup,
                               const std::string& parseMode,
                               bool disableNotification,
                               const std::vector<MessageEntity::Ptr>& captionEntities,
                               bool disableContentTypeDetection,
                               std::int32_t messageThreadId,
                               bool protectContent,
                               const std::string& businessConnectionId) const {
    std::vector<HttpReqArg> args;
    args.reserve(13);

    if (!businessConnectionId.empty()) {
        args.emplace_back("business_connection_id", businessConnectionId);
    }
    args.emplace_back("chat_id", chatId);
    if (messageThreadId != 0) {
        args.emplace_back("message_thread_id", messageThreadId);
    }
    if (document.which() == 0) {    // InputFile::Ptr
        auto file = boost::get<InputFile::Ptr>(document);
        args.emplace_back("document", file->data, true, file->mimeType, file->fileName);
    } else {    // std::string
        args.emplace_back("document", boost::get<std::string>(document));
    }
    if (thumbnail.which() == 0) {   // InputFile::Ptr
        auto file = boost::get<InputFile::Ptr>(thumbnail);
        args.emplace_back("thumbnail", file->data, true, file->mimeType, file->fileName);
    } else {    // std::string
        auto thumbnailStr = boost::get<std::string>(thumbnail);
        if (!thumbnailStr.empty()) {
            args.emplace_back("thumbnail", thumbnailStr);
        }
    }
    if (!caption.empty()) {
        args.emplace_back("caption", caption);
    }
    if (!parseMode.empty()) {
        args.emplace_back("parse_mode", parseMode);
    }
    if (!captionEntities.empty()) {
        args.emplace_back("caption_entities", _botTypeParser.parseArray<MessageEntity>(&BotTypeParser::parseMessageEntity, captionEntities));
    }
    if (disableContentTypeDetection) {
        args.emplace_back("disable_content_type_detection", disableContentTypeDetection);
    }
    if (disableNotification) {
        args.emplace_back("disable_notification", disableNotification);
    }
    if (protectContent) {
        args.emplace_back("protect_content", protectContent);
    }
    if (replyParameters != nullptr) {
        args.emplace_back("reply_parameters", _botTypeParser.parseReplyParameters(replyParameters));
    }
    if (replyMarkup) {
        args.emplace_back("reply_markup", _botTypeParser.parseGenericReply(replyMarkup));
    }
    
    return _botTypeParser.parseJsonAndGetMessage(sendRequest("sendDocument", args));
}

Message::Ptr Api::sendVideo(boost::variant<std::int64_t, std::string> chatId,
                            boost::variant<InputFile::Ptr, std::string> video,
                            bool supportsStreaming,
                            std::int32_t duration,
                            std::int32_t width,
                            std::int32_t height,
                            boost::variant<InputFile::Ptr, std::string> thumbnail,
                            const std::string& caption ,
                            ReplyParameters::Ptr replyParameters,
                            GenericReply::Ptr replyMarkup,
                            const std::string& parseMode,
                            bool disableNotification,
                            const std::vector<MessageEntity::Ptr>& captionEntities,
                            std::int32_t messageThreadId,
                            bool protectContent,
                            bool hasSpoiler,
                            const std::string& businessConnectionId) const {
    std::vector<HttpReqArg> args;
    args.reserve(17);

    if (!businessConnectionId.empty()) {
        args.emplace_back("business_connection_id", businessConnectionId);
    }
    args.emplace_back("chat_id", chatId);
    if (messageThreadId != 0) {
        args.emplace_back("message_thread_id", messageThreadId);
    }
    if (video.which() == 0) {   // InputFile::Ptr
        auto file = boost::get<InputFile::Ptr>(video);
        args.emplace_back("video", file->data, true, file->mimeType, file->fileName);
    } else {    // std::string
        args.emplace_back("video", boost::get<std::string>(video));
    }
    if (duration != 0) {
        args.emplace_back("duration", duration);
    }
    if (width != 0) {
        args.emplace_back("width", width);
    }
    if (height != 0) {
        args.emplace_back("height", height);
    }
    if (thumbnail.which() == 0) {   // InputFile::Ptr
        auto file = boost::get<InputFile::Ptr>(thumbnail);
        args.emplace_back("thumbnail", file->data, true, file->mimeType, file->fileName);
    } else {    // std::string
        auto thumbnailStr = boost::get<std::string>(thumbnail);
        if (!thumbnailStr.empty()) {
            args.emplace_back("thumbnail", thumbnailStr);
        }
    }
    if (!caption.empty()) {
        args.emplace_back("caption", caption);
    }
    if (!parseMode.empty()) {
        args.emplace_back("parse_mode", parseMode);
    }
    if (!captionEntities.empty()) {
        args.emplace_back("caption_entities", _botTypeParser.parseArray<MessageEntity>(&BotTypeParser::parseMessageEntity, captionEntities));
    }
    if (hasSpoiler) {
        args.emplace_back("has_spoiler", hasSpoiler);
    }
    if (supportsStreaming) {
        args.emplace_back("supports_streaming", supportsStreaming);
    }
    if (disableNotification) {
        args.emplace_back("disable_notification", disableNotification);
    }
    if (protectContent) {
        args.emplace_back("protect_content", protectContent);
    }
    if (replyParameters != nullptr) {
        args.emplace_back("reply_parameters", _botTypeParser.parseReplyParameters(replyParameters));
    }
    if (replyMarkup != nullptr) {
        args.emplace_back("reply_markup", _botTypeParser.parseGenericReply(replyMarkup));
    }
    
    return _botTypeParser.parseJsonAndGetMessage(sendRequest("sendVideo", args));
}

Message::Ptr Api::sendAnimation(boost::variant<std::int64_t, std::string> chatId,
                                boost::variant<InputFile::Ptr, std::string> animation,
                                std::int32_t duration,
                                std::int32_t width,
                                std::int32_t height,
                                boost::variant<InputFile::Ptr, std::string> thumbnail,
                                const std::string& caption,
                                ReplyParameters::Ptr replyParameters,
                                GenericReply::Ptr replyMarkup,
                                const std::string& parseMode,
                                bool disableNotification,
                                const std::vector<MessageEntity::Ptr>& captionEntities,
                                std::int32_t messageThreadId,
                                bool protectContent,
                                bool hasSpoiler,
                                const std::string& businessConnectionId) const {
    std::vector<HttpReqArg> args;
    args.reserve(16);

    if (!businessConnectionId.empty()) {
        args.emplace_back("business_connection_id", businessConnectionId);
    }
    args.emplace_back("chat_id", chatId);
    if (messageThreadId != 0) {
        args.emplace_back("message_thread_id", messageThreadId);
    }
    if (animation.which() == 0) {   // InputFile::Ptr
        auto file = boost::get<InputFile::Ptr>(animation);
        args.emplace_back("animation", file->data, true, file->mimeType, file->fileName);
    } else {    // std::string
        args.emplace_back("animation", boost::get<std::string>(animation));
    }
    if (duration != 0) {
        args.emplace_back("duration", duration);
    }
    if (width != 0) {
        args.emplace_back("width", width);
    }
    if (height != 0) {
        args.emplace_back("height", height);
    }
    if (thumbnail.which() == 0) {      // InputFile::Ptr
        auto file = boost::get<InputFile::Ptr>(thumbnail);
        args.emplace_back("thumbnail", file->data, true, file->mimeType, file->fileName);
    } else {    // std::string
        auto thumbnailStr = boost::get<std::string>(thumbnail);
        if (!thumbnailStr.empty()) {
            args.emplace_back("thumbnail", thumbnailStr);
        }
    }
    if (!caption.empty()) {
        args.emplace_back("caption", caption);
    }
    if (!parseMode.empty()) {
        args.emplace_back("parse_mode", parseMode);
    }
    if (!captionEntities.empty()) {
        args.emplace_back("caption_entities", _botTypeParser.parseArray<MessageEntity>(&BotTypeParser::parseMessageEntity, captionEntities));
    }
    if (hasSpoiler) {
        args.emplace_back("has_spoiler", hasSpoiler);
    }
    if (disableNotification) {
        args.emplace_back("disable_notification", disableNotification);
    }
    if (protectContent) {
        args.emplace_back("protect_content", protectContent);
    }
    if (replyParameters != nullptr) {
        args.emplace_back("reply_parameters", _botTypeParser.parseReplyParameters(replyParameters));
    }
    if (replyMarkup != nullptr) {
        args.emplace_back("reply_markup", _botTypeParser.parseGenericReply(replyMarkup));
    }
    
    return _botTypeParser.parseJsonAndGetMessage(sendRequest("sendAnimation", args));
}

Message::Ptr Api::sendVoice(boost::variant<std::int64_t, std::string> chatId,
                            boost::variant<InputFile::Ptr, std::string> voice,
                            const std::string& caption,
                            std::int32_t duration,
                            ReplyParameters::Ptr replyParameters,
                            GenericReply::Ptr replyMarkup,
                            const std::string& parseMode,
                            bool disableNotification,
                            const std::vector<MessageEntity::Ptr>& captionEntities,
                            std::int32_t messageThreadId,
                            bool protectContent,
                            const std::string& businessConnectionId) const {
    std::vector<HttpReqArg> args;
    args.reserve(12);

    if (!businessConnectionId.empty()) {
        args.emplace_back("business_connection_id", businessConnectionId);
    }
    args.emplace_back("chat_id", chatId);
    if (messageThreadId != 0) {
        args.emplace_back("message_thread_id", messageThreadId);
    }
    if (voice.which() == 0) {   // InputFile::Ptr
        auto file = boost::get<InputFile::Ptr>(voice);
        args.emplace_back("voice", file->data, true, file->mimeType, file->fileName);
    } else {    // std::string
        args.emplace_back("voice", boost::get<std::string>(voice));
    }
    if (!caption.empty()) {
        args.emplace_back("caption", caption);
    }
    if (!parseMode.empty()) {
        args.emplace_back("parse_mode", parseMode);
    }
    if (!captionEntities.empty()) {
        args.emplace_back("caption_entities", _botTypeParser.parseArray<MessageEntity>(&BotTypeParser::parseMessageEntity, captionEntities));
    }
    if (duration) {
        args.emplace_back("duration", duration);
    }
    if (disableNotification) {
        args.emplace_back("disable_notification", disableNotification);
    }
    if (protectContent) {
        args.emplace_back("protect_content", protectContent);
    }
    if (replyParameters != nullptr) {
        args.emplace_back("reply_parameters", _botTypeParser.parseReplyParameters(replyParameters));
    }
    if (replyMarkup) {
        args.emplace_back("reply_markup", _botTypeParser.parseGenericReply(replyMarkup));
    }
    
    return _botTypeParser.parseJsonAndGetMessage(sendRequest("sendVoice", args));
}

Message::Ptr Api::sendVideoNote(boost::variant<std::int64_t, std::string> chatId,
                                boost::variant<InputFile::Ptr, std::string> videoNote,
                                ReplyParameters::Ptr replyParameters,
                                bool disableNotification,
                                std::int32_t duration,
                                std::int32_t length,
                                boost::variant<InputFile::Ptr, std::string> thumbnail,
                                GenericReply::Ptr replyMarkup,
                                std::int32_t messageThreadId,
                                bool protectContent,
                                const std::string& businessConnectionId) const {
    std::vector<HttpReqArg> args;
    args.reserve(11);

    if (!businessConnectionId.empty()) {
        args.emplace_back("business_connection_id", businessConnectionId);
    }
    args.emplace_back("chat_id", chatId);
    if (messageThreadId != 0) {
        args.emplace_back("message_thread_id", messageThreadId);
    }
    if (videoNote.which() == 0) {   // InputFile::Ptr
        auto file = boost::get<InputFile::Ptr>(videoNote);
        args.emplace_back("video_note", file->data, true, file->mimeType, file->fileName);
    } else {    // std::string
        args.emplace_back("video_note", boost::get<std::string>(videoNote));
    }
    if (duration) {
        args.emplace_back("duration", duration);
    }
    if (length) {
        args.emplace_back("length", length);
    }
    if (thumbnail.which() == 0) {   // InputFile::Ptr
        auto file = boost::get<InputFile::Ptr>(thumbnail);
        args.emplace_back("thumbnail", file->data, true, file->mimeType, file->fileName);
    } else {    // std::string
        auto thumbnailStr = boost::get<std::string>(thumbnail);
        if (!thumbnailStr.empty()) {
            args.emplace_back("thumbnail", thumbnailStr);
        }
    }
    if (disableNotification) {
        args.emplace_back("disable_notification", disableNotification);
    }
    if (protectContent) {
        args.emplace_back("protect_content", protectContent);
    }
    if (replyParameters != nullptr) {
        args.emplace_back("reply_parameters", _botTypeParser.parseReplyParameters(replyParameters));
    }
    if (replyMarkup) {
        args.emplace_back("reply_markup", _botTypeParser.parseGenericReply(replyMarkup));
    }
    
    return _botTypeParser.parseJsonAndGetMessage(sendRequest("sendVideoNote", args));
}

std::vector<Message::Ptr> Api::sendMediaGroup(boost::variant<std::int64_t, std::string> chatId,
                                              const std::vector<InputMedia::Ptr>& media,
                                              bool disableNotification,
                                              ReplyParameters::Ptr replyParameters,
                                              std::int32_t messageThreadId,
                                              bool protectContent,
                                              const std::string& businessConnectionId) const {
    std::vector<HttpReqArg> args;
    args.reserve(7);

    if (!businessConnectionId.empty()) {
        args.emplace_back("business_connection_id", businessConnectionId);
    }
    args.emplace_back("chat_id", chatId);
    if (messageThreadId != 0) {
        args.emplace_back("message_thread_id", messageThreadId);
    }
    args.emplace_back("media", _botTypeParser.parseArray<InputMedia>(&BotTypeParser::parseInputMedia, media));
    if (disableNotification) {
        args.emplace_back("disable_notification", disableNotification);
    }
    if (protectContent) {
        args.emplace_back("protect_content", protectContent);
    }
    if (replyParameters != nullptr) {
        args.emplace_back("reply_parameters", _botTypeParser.parseReplyParameters(replyParameters));
    }

    return _botTypeParser.parseJsonAndGetArray<Message>(&BotTypeParser::parseJsonAndGetMessage, sendRequest("sendMediaGroup", args));
}

Message::Ptr Api::sendLocation(boost::variant<std::int64_t, std::string> chatId,
                               float latitude,
                               float longitude,
                               std::int32_t livePeriod,
                               ReplyParameters::Ptr replyParameters,
                               GenericReply::Ptr replyMarkup,
                               bool disableNotification,
                               float horizontalAccuracy,
                               std::int32_t heading,
                               std::int32_t proximityAlertRadius,
                               std::int32_t messageThreadId,
                               bool protectContent,
                               const std::string& businessConnectionId) const {
    std::vector<HttpReqArg> args;
    args.reserve(13);

    if (!businessConnectionId.empty()) {
        args.emplace_back("business_connection_id", businessConnectionId);
    }
    args.emplace_back("chat_id", chatId);
    if (messageThreadId != 0) {
        args.emplace_back("message_thread_id", messageThreadId);
    }
    args.emplace_back("latitude", latitude);
    args.emplace_back("longitude", longitude);
    if (horizontalAccuracy) {
        args.emplace_back("horizontal_accuracy", horizontalAccuracy);
    }
    if (livePeriod) {
        args.emplace_back("live_period", std::max(60, std::min(86400, livePeriod)));
    }
    if (heading) {
        args.emplace_back("heading", std::max(1, std::min(360, heading)));
    }
    if (proximityAlertRadius) {
        args.emplace_back("proximity_alert_radius", std::max(1, std::min(100000, proximityAlertRadius)));
    }
    if (disableNotification) {
        args.emplace_back("disable_notification", disableNotification);
    }
    if (protectContent) {
        args.emplace_back("protect_content", protectContent);
    }
    if (replyParameters != nullptr) {
        args.emplace_back("reply_parameters", _botTypeParser.parseReplyParameters(replyParameters));
    }
    if (replyMarkup) {
        args.emplace_back("reply_markup", _botTypeParser.parseGenericReply(replyMarkup));
    }
    
    return _botTypeParser.parseJsonAndGetMessage(sendRequest("sendLocation", args));
}

Message::Ptr Api::editMessageLiveLocation(float latitude,
                                          float longitude,
                                          boost::variant<std::int64_t, std::string> chatId,
                                          std::int32_t messageId,
                                          const std::string& inlineMessageId,
                                          InlineKeyboardMarkup::Ptr replyMarkup,
                                          float horizontalAccuracy,
                                          std::int32_t heading,
                                          std::int32_t proximityAlertRadius) const {
    std::vector<HttpReqArg> args;
    args.reserve(9);

    if (chatId.which() == 0) {   // std::int64_t
        if (boost::get<std::int64_t>(chatId) != 0) {
            args.emplace_back("chat_id", chatId);
        }
    } else {    // std::string
        if (boost::get<std::string>(chatId) != "") {
            args.emplace_back("chat_id", chatId);
        }
    }
    if (messageId) {
        args.emplace_back("message_id", messageId);
    }
    if (!inlineMessageId.empty()) {
        args.emplace_back("inline_message_id", inlineMessageId);
    }
    args.emplace_back("latitude", latitude);
    args.emplace_back("longitude", longitude);
    if (horizontalAccuracy) {
        args.emplace_back("horizontal_accuracy", horizontalAccuracy);
    }
    if (heading) {
        args.emplace_back("heading", heading);
    }
    if (proximityAlertRadius) {
        args.emplace_back("proximity_alert_radius", proximityAlertRadius);
    }
    if (replyMarkup) {
        args.emplace_back("reply_markup", _botTypeParser.parseInlineKeyboardMarkup(replyMarkup));
    }

    return _botTypeParser.parseJsonAndGetMessage(sendRequest("editMessageLiveLocation", args));
}

Message::Ptr Api::stopMessageLiveLocation(boost::variant<std::int64_t, std::string> chatId,
                                          std::int32_t messageId,
                                          const std::string& inlineMessageId,
                                          InlineKeyboardMarkup::Ptr replyMarkup) const {
    std::vector<HttpReqArg> args;
    args.reserve(4);

    if (chatId.which() == 0) {   // std::int64_t
        if (boost::get<std::int64_t>(chatId) != 0) {
            args.emplace_back("chat_id", chatId);
        }
    } else {    // std::string
        if (boost::get<std::string>(chatId) != "") {
            args.emplace_back("chat_id", chatId);
        }
    }
    if (messageId) {
        args.emplace_back("message_id", messageId);
    }
    if (!inlineMessageId.empty()) {
        args.emplace_back("inline_message_id", inlineMessageId);
    }
    if (replyMarkup) {
        args.emplace_back("reply_markup", _botTypeParser.parseInlineKeyboardMarkup(replyMarkup));
    }

    return _botTypeParser.parseJsonAndGetMessage(sendRequest("stopMessageLiveLocation", args));
}

Message::Ptr Api::sendContact(boost::variant<std::int64_t, std::string> chatId,
                              const std::string& phoneNumber,
                              const std::string& firstName,
                              const std::string& lastName ,
                              const std::string& vcard,
                              bool disableNotification,
                              ReplyParameters::Ptr replyParameters,
                              GenericReply::Ptr replyMarkup,
                              std::int32_t messageThreadId,
                              bool protectContent,
                              const std::string& businessConnectionId) const {
    std::vector<HttpReqArg> args;
    args.reserve(11);

    if (!businessConnectionId.empty()) {
        args.emplace_back("business_connection_id", businessConnectionId);
    }
    args.emplace_back("chat_id", chatId);
    if (messageThreadId != 0) {
        args.emplace_back("message_thread_id", messageThreadId);
    }
    args.emplace_back("phone_number", phoneNumber);
    args.emplace_back("first_name", firstName);
    if (!lastName.empty()) {
        args.emplace_back("last_name", lastName);
    }
    if (!vcard.empty()) {
        args.emplace_back("vcard", vcard);
    }
    if (disableNotification) {
        args.emplace_back("disable_notification", disableNotification);
    }
    if (protectContent) {
        args.emplace_back("protect_content", protectContent);
    }
    if (replyParameters != nullptr) {
        args.emplace_back("reply_parameters", _botTypeParser.parseReplyParameters(replyParameters));
    }
    if (replyMarkup) {
        args.emplace_back("reply_markup", _botTypeParser.parseGenericReply(replyMarkup));
    }
    
    return _botTypeParser.parseJsonAndGetMessage(sendRequest("sendContact", args));
}

Message::Ptr Api::sendPoll(boost::variant<std::int64_t, std::string> chatId,
                           const std::string& question,
                           const std::vector<std::string>& options,
                           bool disableNotification,
                           ReplyParameters::Ptr replyParameters,
                           GenericReply::Ptr replyMarkup,
                           bool isAnonymous,
                           const std::string& type,
                           bool allowsMultipleAnswers,
                           std::int32_t correctOptionId,
                           const std::string& explanation,
                           const std::string& explanationParseMode,
                           const std::vector<MessageEntity::Ptr>& explanationEntities,
                           std::int32_t openPeriod,
                           std::int32_t closeDate,
                           bool isClosed,
                           std::int32_t messageThreadId,
                           bool protectContent,
                           const std::string& businessConnectionId) const {
    std::vector<HttpReqArg> args;
    args.reserve(19);

    if (!businessConnectionId.empty()) {
        args.emplace_back("business_connection_id", businessConnectionId);
    }
    args.emplace_back("chat_id", chatId);
    if (messageThreadId != 0) {
        args.emplace_back("message_thread_id", messageThreadId);
    }
    args.emplace_back("question", question);
    args.emplace_back("options", _botTypeParser.parseArray<std::string>(
        [](const std::string& option)->std::string {
        return "\"" + StringTools::escapeJsonString(option) + "\"";
    }, options));
    if (!isAnonymous) {
        args.emplace_back("is_anonymous", isAnonymous);
    }
    if (!type.empty()) {
        args.emplace_back("type", type);
    }
    if (allowsMultipleAnswers) {
        args.emplace_back("allows_multiple_answers", allowsMultipleAnswers);
    }
    if (correctOptionId != -1) {
        args.emplace_back("correct_option_id", correctOptionId);
    }
    if (!explanation.empty()) {
        args.emplace_back("explanation", explanation);
    }
    if (!explanationParseMode.empty()) {
        args.emplace_back("explanation_parse_mode", explanationParseMode);
    }
    if (!explanationEntities.empty()) {
        args.emplace_back("explanation_entities", _botTypeParser.parseArray<MessageEntity>(&BotTypeParser::parseMessageEntity, explanationEntities));
    }
    if (openPeriod != 0) {
        args.emplace_back("open_period", openPeriod);
    }
    if (closeDate != 0) {
        args.emplace_back("close_date", closeDate);
    }
    if (isClosed) {
        args.emplace_back("is_closed", isClosed);
    }
    if (disableNotification) {
        args.emplace_back("disable_notification", disableNotification);
    }
    if (protectContent) {
        args.emplace_back("protect_content", protectContent);
    }
    if (replyParameters != nullptr) {
        args.emplace_back("reply_parameters", _botTypeParser.parseReplyParameters(replyParameters));
    }
    if (replyMarkup) {
        args.emplace_back("reply_markup", _botTypeParser.parseGenericReply(replyMarkup));
    }

    return _botTypeParser.parseJsonAndGetMessage(sendRequest("sendPoll", args));
}

bool Api::setMessageReaction(boost::variant<std::int64_t, std::string> chatId,
                             std::int32_t messageId,
                             const std::vector<ReactionType::Ptr>& reaction,
                             bool isBig) const {
    std::vector<HttpReqArg> args;
    args.reserve(4);

    args.emplace_back("chat_id", chatId);
    args.emplace_back("message_id", messageId);
    if (!reaction.empty()) {
        args.emplace_back("reaction", _botTypeParser.parseArray<ReactionType>(&BotTypeParser::parseReactionType, reaction));
    }
    if (isBig) {
        args.emplace_back("is_big", isBig);
    }

    return sendRequest("setMessageReaction", args).get<bool>("", false);
}

bool Api::sendChatAction(std::int64_t chatId,
                         const std::string& action,
                         std::int32_t messageThreadId,
                         const std::string& businessConnectionId) const {
    std::vector<HttpReqArg> args;
    args.reserve(4);

    if (!businessConnectionId.empty()) {
        args.emplace_back("business_connection_id", businessConnectionId);
    }
    args.emplace_back("chat_id", chatId);
    args.emplace_back("action", action);
    if (messageThreadId != 0) {
        args.emplace_back("message_thread_id", messageThreadId);
    }

    return sendRequest("sendChatAction", args).get<bool>("", false);
}

UserProfilePhotos::Ptr Api::getUserProfilePhotos(std::int64_t userId,
                                                 std::int32_t offset,
                                                 std::int32_t limit) const {
    std::vector<HttpReqArg> args;
    args.reserve(3);

    args.emplace_back("user_id", userId);
    if (offset) {
        args.emplace_back("offset", offset);
    }
    if (limit != 100) {
        args.emplace_back("limit", std::max(1, std::min(100, limit)));
    }

    return _botTypeParser.parseJsonAndGetUserProfilePhotos(sendRequest("getUserProfilePhotos", args));
}

File::Ptr Api::getFile(const std::string& fileId) const {
    std::vector<HttpReqArg> args;
    args.reserve(1);

    args.emplace_back("file_id", fileId);

    return _botTypeParser.parseJsonAndGetFile(sendRequest("getFile", args));
}

bool Api::banChatMember(boost::variant<std::int64_t, std::string> chatId,
                        std::int64_t userId,
                        std::int32_t untilDate,
                        bool revokeMessages) const {
    std::vector<HttpReqArg> args;
    args.reserve(4);

    args.emplace_back("chat_id", chatId);
    args.emplace_back("user_id", userId);
    if (untilDate != 0) {
        args.emplace_back("until_date", untilDate);
    }
    if (revokeMessages) {
        args.emplace_back("revoke_messages", revokeMessages);
    }

    return sendRequest("banChatMember", args).get<bool>("", false);
}

bool Api::unbanChatMember(boost::variant<std::int64_t, std::string> chatId,
                          std::int64_t userId,
                          bool onlyIfBanned) const {
    std::vector<HttpReqArg> args;
    args.reserve(3);

    args.emplace_back("chat_id", chatId);
    args.emplace_back("user_id", userId);
    if (onlyIfBanned) {
        args.emplace_back("only_if_banned", onlyIfBanned);
    }

    return sendRequest("unbanChatMember", args).get<bool>("", false);
}

bool Api::restrictChatMember(boost::variant<std::int64_t, std::string> chatId,
                             std::int64_t userId,
                             MaxBot::ChatPermissions::Ptr permissions,
                             std::uint32_t untilDate,
                             bool useIndependentChatPermissions) const {
    std::vector<HttpReqArg> args;
    args.reserve(5);

    args.emplace_back("chat_id", chatId);
    args.emplace_back("user_id", userId);
    args.emplace_back("permissions", _botTypeParser.parseChatPermissions(permissions));
    if (useIndependentChatPermissions != false) {
        args.emplace_back("use_independent_chat_permissions", useIndependentChatPermissions);
    }
    if (untilDate != 0) {
        args.emplace_back("until_date", untilDate);
    }

    return sendRequest("restrictChatMember", args).get<bool>("", false);
}

bool Api::promoteChatMember(boost::variant<std::int64_t, std::string> chatId,
                            std::int64_t userId,
                            bool canChangeInfo,
                            bool canPostMessages,
                            bool canEditMessages,
                            bool canDeleteMessages,
                            bool canInviteUsers,
                            bool canPinMessages,
                            bool canPromoteMembers,
                            bool isAnonymous,
                            bool canManageChat,
                            bool canManageVideoChats,
                            bool canRestrictMembers,
                            bool canManageTopics,
                            bool canPostStories,
                            bool canEditStories,
                            bool canDeleteStories) const {
    std::vector<HttpReqArg> args;
    args.reserve(17);

    args.emplace_back("chat_id", chatId);
    args.emplace_back("user_id", userId);
    if (isAnonymous != false) {
        args.emplace_back("is_anonymous", isAnonymous);
    }
    if (canManageChat != false) {
        args.emplace_back("can_manage_chat", canManageChat);
    }
    if (canPostMessages != false) {
        args.emplace_back("can_post_messages", canPostMessages);
    }
    if (canEditMessages != false) {
        args.emplace_back("can_edit_messages", canEditMessages);
    }
    if (canDeleteMessages != false) {
        args.emplace_back("can_delete_messages", canDeleteMessages);
    }
    if (canPostStories != false) {
        args.emplace_back("can_post_stories", canPostStories);
    }
    if (canEditStories != false) {
        args.emplace_back("can_edit_stories", canEditStories);
    }
    if (canDeleteStories != false) {
        args.emplace_back("can_delete_stories", canDeleteStories);
    }
    if (canManageVideoChats != false) {
        args.emplace_back("can_manage_video_chats", canManageVideoChats);
    }
    if (canRestrictMembers != false) {
        args.emplace_back("can_restrict_members", canRestrictMembers);
    }
    if (canPromoteMembers != false) {
        args.emplace_back("can_promote_members", canPromoteMembers);
    }
    if (canChangeInfo != false) {
        args.emplace_back("can_change_info", canChangeInfo);
    }
    if (canInviteUsers != false) {
        args.emplace_back("can_invite_users", canInviteUsers);
    }
    if (canPinMessages != false) {
        args.emplace_back("can_pin_messages", canPinMessages);
    }
    if (canManageTopics != false) {
        args.emplace_back("can_manage_topics", canManageTopics);
    }

    return sendRequest("promoteChatMember", args).get<bool>("", false);
}

bool Api::setChatAdministratorCustomTitle(boost::variant<std::int64_t, std::string> chatId,
                                          std::int64_t userId,
                                          const std::string& customTitle) const {
    std::vector<HttpReqArg> args;
    args.reserve(3);

    args.emplace_back("chat_id", chatId);
    args.emplace_back("user_id", userId);
    args.emplace_back("custom_title", customTitle);

    return sendRequest("setChatAdministratorCustomTitle", args).get<bool>("", false);
}

bool Api::banChatSenderChat(boost::variant<std::int64_t, std::string> chatId,
                            std::int64_t senderChatId) const {
    std::vector<HttpReqArg> args;
    args.reserve(2);

    args.emplace_back("chat_id", chatId);
    args.emplace_back("sender_chat_id", senderChatId);

    return sendRequest("banChatSenderChat", args).get<bool>("", false);
}

bool Api::unbanChatSenderChat(boost::variant<std::int64_t, std::string> chatId,
                              std::int64_t senderChatId) const {
    std::vector<HttpReqArg> args;
    args.reserve(2);

    args.emplace_back("chat_id", chatId);
    args.emplace_back("sender_chat_id", senderChatId);

    return sendRequest("unbanChatSenderChat", args).get<bool>("", false);
}

bool Api::setChatPermissions(boost::variant<std::int64_t, std::string> chatId,
                             ChatPermissions::Ptr permissions,
                             bool useIndependentChatPermissions) const {
    std::vector<HttpReqArg> args;
    args.reserve(3);

    args.emplace_back("chat_id", chatId);
    args.emplace_back("permissions", _botTypeParser.parseChatPermissions(permissions));
    if (useIndependentChatPermissions) {
        args.emplace_back("use_independent_chat_permissions", useIndependentChatPermissions);
    }

    return sendRequest("setChatPermissions", args).get<bool>("", false);
}

std::string Api::exportChatInviteLink(boost::variant<std::int64_t, std::string> chatId) const {
    std::vector<HttpReqArg> args;
    args.reserve(1);

    args.emplace_back("chat_id", chatId);

    return sendRequest("exportChatInviteLink", args).get("", "");
}

ChatInviteLink::Ptr Api::createChatInviteLink(boost::variant<std::int64_t, std::string> chatId,
                                              std::int32_t expireDate,
                                              std::int32_t memberLimit,
                                              const std::string& name,
                                              bool createsJoinRequest) const {
    std::vector<HttpReqArg> args;
    args.reserve(5);

    args.emplace_back("chat_id", chatId);
    if (!name.empty()) {
        args.emplace_back("name", name);
    }
    if (expireDate != 0) {
        args.emplace_back("expire_date", expireDate);
    }
    if (memberLimit != 0) {
        args.emplace_back("member_limit", memberLimit);
    }
    if (createsJoinRequest) {
        args.emplace_back("createsJoinRequest", createsJoinRequest);
    }

    return _botTypeParser.parseJsonAndGetChatInviteLink(sendRequest("createChatInviteLink", args));
}

ChatInviteLink::Ptr Api::editChatInviteLink(boost::variant<std::int64_t, std::string> chatId,
                                            const std::string& inviteLink,
                                            std::int32_t expireDate,
                                            std::int32_t memberLimit,
                                            const std::string& name,
                                            bool createsJoinRequest) const {
    std::vector<HttpReqArg> args;
    args.reserve(6);

    args.emplace_back("chat_id", chatId);
    args.emplace_back("invite_link", inviteLink);
    if (!name.empty()) {
        args.emplace_back("name", name);
    }
    if (expireDate != 0) {
        args.emplace_back("expire_date", expireDate);
    }
    if (memberLimit != 0) {
        args.emplace_back("member_limit", memberLimit);
    }
    if (createsJoinRequest) {
        args.emplace_back("createsJoinRequest", createsJoinRequest);
    }

    return _botTypeParser.parseJsonAndGetChatInviteLink(sendRequest("editChatInviteLink", args));
}

ChatInviteLink::Ptr Api::revokeChatInviteLink(boost::variant<std::int64_t, std::string> chatId,
                                              const std::string& inviteLink) const {
    std::vector<HttpReqArg> args;
    args.reserve(2);

    args.emplace_back("chat_id", chatId);
    args.emplace_back("invite_link", inviteLink);

    return _botTypeParser.parseJsonAndGetChatInviteLink(sendRequest("revokeChatInviteLink", args));
}

bool Api::approveChatJoinRequest(boost::variant<std::int64_t, std::string> chatId,
                                 std::int64_t userId) const {
    std::vector<HttpReqArg> args;
    args.reserve(2);

    args.emplace_back("chat_id", chatId);
    args.emplace_back("user_id", userId);

    return sendRequest("approveChatJoinRequest", args).get<bool>("", false);
}

bool Api::declineChatJoinRequest(boost::variant<std::int64_t, std::string> chatId,
                                 std::int64_t userId) const {
    std::vector<HttpReqArg> args;
    args.reserve(2);

    args.emplace_back("chat_id", chatId);
    args.emplace_back("user_id", userId);

    return sendRequest("declineChatJoinRequest", args).get<bool>("", false);
}

bool Api::setChatPhoto(boost::variant<std::int64_t, std::string> chatId,
                       const InputFile::Ptr photo) const {
    std::vector<HttpReqArg> args;
    args.reserve(2);

    args.emplace_back("chat_id", chatId);
    args.emplace_back("photo", photo->data, true, photo->mimeType, photo->fileName);

    return sendRequest("setChatPhoto", args).get<bool>("", false);
}

bool Api::deleteChatPhoto(boost::variant<std::int64_t, std::string> chatId) const {
    std::vector<HttpReqArg> args;
    args.reserve(1);

    args.emplace_back("chat_id", chatId);

    return sendRequest("deleteChatPhoto", args).get<bool>("", false);
}

bool Api::setChatTitle(boost::variant<std::int64_t, std::string> chatId,
                       const std::string& title) const {
    std::vector<HttpReqArg> args;
    args.reserve(2);

    args.emplace_back("chat_id", chatId);
    args.emplace_back("title", title);

    return sendRequest("setChatTitle", args).get<bool>("", false);
}

bool Api::setChatDescription(boost::variant<std::int64_t, std::string> chatId,
                             const std::string& description) const {
    std::vector<HttpReqArg> args;
    args.reserve(2);

    args.emplace_back("chat_id", chatId);
    if (!description.empty()) {
        args.emplace_back("description", description);
    }

    return sendRequest("setChatDescription", args).get<bool>("", false);
}

bool Api::pinChatMessage(boost::variant<std::int64_t, std::string> chatId,
                         std::int32_t messageId,
                         bool disableNotification) const {
    std::vector<HttpReqArg> args;
    args.reserve(3);

    args.emplace_back("chat_id", chatId);
    args.emplace_back("message_id", messageId);
    if (disableNotification) {
        args.emplace_back("disable_notification", disableNotification);
    }

    return sendRequest("pinChatMessage", args).get<bool>("", false);
}

bool Api::unpinChatMessage(boost::variant<std::int64_t, std::string> chatId,
                           std::int32_t messageId) const {
    std::vector<HttpReqArg> args;
    args.reserve(2);

    args.emplace_back("chat_id", chatId);
    if (messageId != 0) {
        args.emplace_back("message_id", messageId);
    }

    return sendRequest("unpinChatMessage", args).get<bool>("", false);
}

bool Api::unpinAllChatMessages(boost::variant<std::int64_t, std::string> chatId) const {
    std::vector<HttpReqArg> args;
    args.reserve(1);

    args.emplace_back("chat_id", chatId);

    return sendRequest("unpinAllChatMessages", args).get<bool>("", false);
}

bool Api::leaveChat(boost::variant<std::int64_t, std::string> chatId) const {
    std::vector<HttpReqArg> args;
    args.reserve(1);

    args.emplace_back("chat_id", chatId);

    return sendRequest("leaveChat", args).get<bool>("", false);
}

Chat::Ptr Api::getChat(boost::variant<std::int64_t, std::string> chatId) const {
    std::vector<HttpReqArg> args;
    args.reserve(1);

    args.emplace_back("chat_id", chatId);

    return _botTypeParser.parseJsonAndGetChat(sendRequest("getChat", args));
}

std::vector<ChatMember::Ptr> Api::getChatAdministrators(boost::variant<std::int64_t, std::string> chatId) const {
    std::vector<HttpReqArg> args;
    args.reserve(1);

    args.emplace_back("chat_id", chatId);

    return _botTypeParser.parseJsonAndGetArray<ChatMember>(&BotTypeParser::parseJsonAndGetChatMember, sendRequest("getChatAdministrators", args));
}

int32_t Api::getChatMemberCount(boost::variant<std::int64_t, std::string> chatId) const {
    std::vector<HttpReqArg> args;
    args.reserve(1);

    args.emplace_back("chat_id", chatId);

    return sendRequest("getChatMemberCount", args).get<int32_t>("", 0);
}

ChatMember::Ptr Api::getChatMember(boost::variant<std::int64_t, std::string> chatId,
                                   std::int64_t userId) const {
    std::vector<HttpReqArg> args;
    args.reserve(2);

    args.emplace_back("chat_id", chatId);
    args.emplace_back("user_id", userId);

    return _botTypeParser.parseJsonAndGetChatMember(sendRequest("getChatMember", args));
}

bool Api::answerCallbackQuery(const std::string& callbackId, CallbackAnswer::Ptr answer) const {
	auto url = "answers?callback_id=" + callbackId;
    auto json = _botTypeParser.parseCallbackAnswer(answer);
    return sendRequest(url, json).get<bool>("success", false);
}

UserChatBoosts::Ptr Api::getUserChatBoosts(boost::variant<std::int64_t, std::string> chatId,
                                           std::int32_t userId) const {
    std::vector<HttpReqArg> args;
    args.reserve(2);

    args.emplace_back("chat_id", chatId);
    args.emplace_back("user_id", userId);

    return _botTypeParser.parseJsonAndGetUserChatBoosts(sendRequest("getUserChatBoosts", args));
}

bool Api::setMyCommands(const std::vector<BotCommand::Ptr>& commands,
                        BotCommandScope::Ptr scope,
                        const std::string& languageCode) const {
    std::vector<HttpReqArg> args;
    args.reserve(3);

    args.emplace_back("commands", _botTypeParser.parseArray<BotCommand>(&BotTypeParser::parseBotCommand, commands));
    if (scope != nullptr) {
        args.emplace_back("scope", _botTypeParser.parseBotCommandScope(scope));
    }
    if (!languageCode.empty()) {
        args.emplace_back("language_code", languageCode);
    }

    return sendRequest("setMyCommands", args).get<bool>("", false);
}

bool Api::deleteMyCommands(BotCommandScope::Ptr scope,
                           const std::string& languageCode) const {
    std::vector<HttpReqArg> args;
    args.reserve(2);

    if (scope != nullptr) {
        args.emplace_back("scope", _botTypeParser.parseBotCommandScope(scope));
    }
    if (!languageCode.empty()) {
        args.emplace_back("language_code", languageCode);
    }

    return sendRequest("deleteMyCommands", args).get<bool>("", false);
}

std::vector<BotCommand::Ptr> Api::getMyCommands(BotCommandScope::Ptr scope,
                                                const std::string& languageCode) const {
    std::vector<HttpReqArg> args;
    args.reserve(2);

    if (scope != nullptr) {
        args.emplace_back("scope", _botTypeParser.parseBotCommandScope(scope));
    }
    if (!languageCode.empty()) {
        args.emplace_back("language_code", languageCode);
    }

    return _botTypeParser.parseJsonAndGetArray<BotCommand>(&BotTypeParser::parseJsonAndGetBotCommand, sendRequest("getMyCommands", args));
}

bool Api::setMyName(const std::string& name,
                    const std::string& languageCode) const {
    std::vector<HttpReqArg> args;
    args.reserve(2);

    if (!name.empty()) {
        args.emplace_back("name", name);
    }
    if (!languageCode.empty()) {
        args.emplace_back("language_code", languageCode);
    }

    return sendRequest("setMyName", args).get<bool>("", false);
}

BotName::Ptr Api::getMyName(const std::string& languageCode) const {
    std::vector<HttpReqArg> args;
    args.reserve(1);

    if (!languageCode.empty()) {
        args.emplace_back("language_code", languageCode);
    }

    return _botTypeParser.parseJsonAndGetBotName(sendRequest("getMyName", args));
}

bool Api::setMyDescription(const std::string& description,
                           const std::string& languageCode) const {
    std::vector<HttpReqArg> args;
    args.reserve(2);

    if (!description.empty()) {
        args.emplace_back("description", description);
    }
    if (!languageCode.empty()) {
        args.emplace_back("language_code", languageCode);
    }

    return sendRequest("setMyDescription", args).get<bool>("", false);
}

BotDescription::Ptr Api::getMyDescription(const std::string& languageCode) const {
    std::vector<HttpReqArg> args;
    args.reserve(1);

    if (!languageCode.empty()) {
        args.emplace_back("language_code", languageCode);
    }

    return _botTypeParser.parseJsonAndGetBotDescription(sendRequest("getMyDescription", args));
}

bool Api::setMyShortDescription(const std::string& shortDescription,
                                const std::string& languageCode) const {
    std::vector<HttpReqArg> args;
    args.reserve(2);

    if (!shortDescription.empty()) {
        args.emplace_back("short_description", shortDescription);
    }
    if (!languageCode.empty()) {
        args.emplace_back("language_code", languageCode);
    }

    return sendRequest("setMyShortDescription", args).get<bool>("", false);
}

BotShortDescription::Ptr Api::getMyShortDescription(const std::string& languageCode) const {
    std::vector<HttpReqArg> args;
    args.reserve(1);

    if (!languageCode.empty()) {
        args.emplace_back("language_code", languageCode);
    }

    return _botTypeParser.parseJsonAndGetBotShortDescription(sendRequest("getMyShortDescription", args));
}

bool Api::setChatMenuButton(std::int64_t chatId,
                            MenuButton::Ptr menuButton) const {
    std::vector<HttpReqArg> args;
    args.reserve(2);

    if (chatId != 0) {
        args.emplace_back("chat_id", chatId);
    }
    if (menuButton != nullptr) {
        args.emplace_back("menu_button", _botTypeParser.parseMenuButton(menuButton));
    }

    return sendRequest("setChatMenuButton", args).get<bool>("", false);
}

MenuButton::Ptr Api::getChatMenuButton(std::int64_t chatId) const {
    std::vector<HttpReqArg> args;
    args.reserve(1);

    if (chatId != 0) {
        args.emplace_back("chat_id", chatId);
    }

    return _botTypeParser.parseJsonAndGetMenuButton(sendRequest("getChatMenuButton", args));
}

bool Api::setMyDefaultAdministratorRights(ChatAdministratorRights::Ptr rights,
                                          bool forChannels) const {
    std::vector<HttpReqArg> args;
    args.reserve(2);

    if (rights != nullptr) {
        args.emplace_back("rights", _botTypeParser.parseChatAdministratorRights(rights));
    }
    if (forChannels) {
        args.emplace_back("for_channels", forChannels);
    }

    return sendRequest("setMyDefaultAdministratorRights", args).get<bool>("", false);
}

ChatAdministratorRights::Ptr Api::getMyDefaultAdministratorRights(bool forChannels) const {
    std::vector<HttpReqArg> args;
    args.reserve(1);

    if (forChannels) {
        args.emplace_back("for_channels", forChannels);
    }

    return _botTypeParser.parseJsonAndGetChatAdministratorRights(sendRequest("getMyDefaultAdministratorRights", args));
}

Message::Ptr Api::editMessageText(const std::string& text,
                                  boost::variant<std::int64_t, std::string> chatId,
                                  std::int32_t messageId,
                                  const std::string& inlineMessageId,
                                  const std::string& parseMode,
                                  LinkPreviewOptions::Ptr linkPreviewOptions,
                                  InlineKeyboardMarkup::Ptr replyMarkup,
                                  const std::vector<MessageEntity::Ptr>& entities) const {
    std::vector<HttpReqArg> args;
    args.reserve(8);

    if (chatId.which() == 0) {   // std::int64_t
        if (boost::get<std::int64_t>(chatId) != 0) {
            args.emplace_back("chat_id", chatId);
        }
    } else {    // std::string
        if (boost::get<std::string>(chatId) != "") {
            args.emplace_back("chat_id", chatId);
        }
    }
    if (messageId) {
        args.emplace_back("message_id", messageId);
    }
    if (!inlineMessageId.empty()) {
        args.emplace_back("inline_message_id", inlineMessageId);
    }
    args.emplace_back("text", text);
    if (!parseMode.empty()) {
        args.emplace_back("parse_mode", parseMode);
    }
    if (!entities.empty()) {
        args.emplace_back("entities", _botTypeParser.parseArray<MessageEntity>(&BotTypeParser::parseMessageEntity, entities));
    }
    if (linkPreviewOptions) {
        args.emplace_back("link_preview_options", _botTypeParser.parseLinkPreviewOptions(linkPreviewOptions));
    }
    if (replyMarkup) {
        args.emplace_back("reply_markup", _botTypeParser.parseInlineKeyboardMarkup(replyMarkup));
    }

    boost::property_tree::ptree p = sendRequest("editMessageText", args);
    if (p.get_child_optional("message_id")) {
        return _botTypeParser.parseJsonAndGetMessage(p);
    } else {
        return nullptr;
    }
}

Message::Ptr Api::editMessageCaption(boost::variant<std::int64_t, std::string> chatId,
                                     std::int32_t messageId,
                                     const std::string& caption,
                                     const std::string& inlineMessageId,
                                     GenericReply::Ptr replyMarkup,
                                     const std::string& parseMode,
                                     const std::vector<MessageEntity::Ptr>& captionEntities) const {
    std::vector<HttpReqArg> args;
    args.reserve(7);

    if (chatId.which() == 0) {   // std::int64_t
        if (boost::get<std::int64_t>(chatId) != 0) {
            args.emplace_back("chat_id", chatId);
        }
    } else {    // std::string
        if (boost::get<std::string>(chatId) != "") {
            args.emplace_back("chat_id", chatId);
        }
    }
    if (messageId) {
        args.emplace_back("message_id", messageId);
    }
    if (!inlineMessageId.empty()) {
        args.emplace_back("inline_message_id", inlineMessageId);
    }
    if (!caption.empty()) {
        args.emplace_back("caption", caption);
    }
    if (!parseMode.empty()) {
        args.emplace_back("parse_mode", parseMode);
    }
    if (!captionEntities.empty()) {
        args.emplace_back("caption_entities", _botTypeParser.parseArray<MessageEntity>(&BotTypeParser::parseMessageEntity, captionEntities));
    }
    if (replyMarkup) {
        args.emplace_back("reply_markup", _botTypeParser.parseGenericReply(replyMarkup));
    }

    boost::property_tree::ptree p = sendRequest("editMessageCaption", args);
    if (p.get_child_optional("message_id")) {
        return _botTypeParser.parseJsonAndGetMessage(p);
    } else {
        return nullptr;
    }
}

Message::Ptr Api::editMessageMedia(InputMedia::Ptr media,
                                   boost::variant<std::int64_t, std::string> chatId,
                                   std::int32_t messageId,
                                   const std::string& inlineMessageId,
                                   GenericReply::Ptr replyMarkup) const {

    std::vector<HttpReqArg> args;
    args.reserve(5);

    if (chatId.which() == 0) {   // std::int64_t
        if (boost::get<std::int64_t>(chatId) != 0) {
            args.emplace_back("chat_id", chatId);
        }
    } else {    // std::string
        if (boost::get<std::string>(chatId) != "") {
            args.emplace_back("chat_id", chatId);
        }
    }
    args.emplace_back("media", _botTypeParser.parseInputMedia(media));
    if (messageId) {
        args.emplace_back("message_id", messageId);
    }
    if (!inlineMessageId.empty()) {
        args.emplace_back("inline_message_id", inlineMessageId);
    }
    if (replyMarkup) {
        args.emplace_back("reply_markup", _botTypeParser.parseGenericReply(replyMarkup));
    }

    boost::property_tree::ptree p = sendRequest("editMessageMedia", args);
    if (p.get_child_optional("message_id")) {
        return _botTypeParser.parseJsonAndGetMessage(p);
    } else {
        return nullptr;
    }
}

Message::Ptr Api::editMessageReplyMarkup(boost::variant<std::int64_t, std::string> chatId,
                                         std::int32_t messageId,
                                         const std::string& inlineMessageId,
                                         const GenericReply::Ptr replyMarkup) const {

    std::vector<HttpReqArg> args;
    args.reserve(4);

    if (chatId.which() == 0) {   // std::int64_t
        if (boost::get<std::int64_t>(chatId) != 0) {
            args.emplace_back("chat_id", chatId);
        }
    } else {    // std::string
        if (boost::get<std::string>(chatId) != "") {
            args.emplace_back("chat_id", chatId);
        }
    }
    if (messageId) {
        args.emplace_back("message_id", messageId);
    }
    if (!inlineMessageId.empty()) {
        args.emplace_back("inline_message_id", inlineMessageId);
    }
    if (replyMarkup) {
        args.emplace_back("reply_markup", _botTypeParser.parseGenericReply(replyMarkup));
    }

    boost::property_tree::ptree p = sendRequest("editMessageReplyMarkup", args);
    if (p.get_child_optional("message_id")) {
        return _botTypeParser.parseJsonAndGetMessage(p);
    } else {
        return nullptr;
    }
}

Poll::Ptr Api::stopPoll(boost::variant<std::int64_t, std::string> chatId,
                        std::int64_t messageId,
                        const InlineKeyboardMarkup::Ptr replyMarkup) const {
    std::vector<HttpReqArg> args;
    args.reserve(3);

    args.emplace_back("chat_id", chatId);
    args.emplace_back("message_id", messageId);
    if (replyMarkup) {
        args.emplace_back("reply_markup", _botTypeParser.parseGenericReply(replyMarkup));
    }

    return _botTypeParser.parseJsonAndGetPoll(sendRequest("stopPoll", args));
}

bool Api::deleteMessage(boost::variant<std::int64_t, std::string> chatId,
                        std::int32_t messageId) const {
    std::vector<HttpReqArg> args;
    args.reserve(2);

    args.emplace_back("chat_id", chatId);
    args.emplace_back("message_id", messageId);

    return sendRequest("deleteMessage", args).get<bool>("", false);
}

bool Api::deleteMessages(boost::variant<std::int64_t, std::string> chatId,
                         const std::vector<std::int32_t>& messageIds) const {
    std::vector<HttpReqArg> args;
    args.reserve(2);

    args.emplace_back("chat_id", chatId);
    if (!messageIds.empty()) {
        args.emplace_back("message_ids", _botTypeParser.parseArray<std::int32_t>(
            [] (const std::int32_t& i)->std::int32_t {
            return i;
        }, messageIds));
    }

    return sendRequest("deleteMessages", args).get<bool>("", false);
}

bool Api::answerInlineQuery(const std::string& inlineQueryId,
                            const std::vector<InlineQueryResult::Ptr>& results,
                            std::int32_t cacheTime,
                            bool isPersonal,
                            const std::string& nextOffset,
                            InlineQueryResultsButton::Ptr button) const {
    std::vector<HttpReqArg> args;
    args.reserve(6);

    args.emplace_back("inline_query_id", inlineQueryId);
    args.emplace_back("results", _botTypeParser.parseArray<InlineQueryResult>(&BotTypeParser::parseInlineQueryResult, results));
    if (cacheTime != 300) {
        args.emplace_back("cache_time", cacheTime);
    }
    if (isPersonal != false) {
        args.emplace_back("is_personal", isPersonal);
    }
    if (!nextOffset.empty()) {
        args.emplace_back("next_offset", nextOffset);
    }
    if (button != nullptr) {
        args.emplace_back("button", _botTypeParser.parseInlineQueryResultsButton(button));
    }

    return sendRequest("answerInlineQuery", args).get<bool>("", false);
}

SentWebAppMessage::Ptr Api::answerWebAppQuery(const std::string& webAppQueryId,
                                              InlineQueryResult::Ptr result) const {
    std::vector<HttpReqArg> args;
    args.reserve(2);

    args.emplace_back("web_app_query_id", webAppQueryId);
    args.emplace_back("result", _botTypeParser.parseInlineQueryResult(result));

    return _botTypeParser.parseJsonAndGetSentWebAppMessage(sendRequest("answerWebAppQuery", args));
}

std::pair<long, std::string> Api::downloadFile(const std::string& url,
                              const std::vector<HttpReqArg>& args) const {
    return _httpClient.makeRequest(url, args);
}

bool Api::blockedByUser(std::int64_t chatId) const {
    bool isBotBlocked = false;

    try {
        sendChatAction(chatId, "typing");

    } catch (std::exception& e) {
        std::string error = e.what();

        if (error.compare("Forbidden: bot was blocked by the user") == 0) {
            isBotBlocked = true;
        }
    }

    return isBotBlocked;
}

boost::property_tree::ptree Api::sendRequest(const std::string& urlPath, const std::string& json, const std::string& customMethod) const
{
    std::vector<HttpReqArg> args;
	args.emplace_back("", json, /*isFile=*/false, "application/json");
	return sendRequest(urlPath, args, customMethod);
}

boost::property_tree::ptree Api::sendRequest(const std::string& urlPath, const std::vector<HttpReqArg>& args, const std::string& customMethod) const {
    std::string url(_url);
    url += urlPath;

    int requestRetryBackoff = _httpClient.getRequestBackoff();
    int retries = 0;
    while (1)
    {
        try {
            auto [httpCode, serverResponse] = _httpClient.makeRequest(url, args, customMethod);
            if (!serverResponse.compare(0, 6, "<html>")) {
                std::string message = "maxbot-cpp library have got html page instead of json response. Maybe you entered wrong bot token.";
                throw BotException(message, BotException::ErrorCode::HtmlResponse);
            }

            boost::property_tree::ptree result;
            try {
                result = _botTypeParser.parseJson(serverResponse);
            } catch (boost::property_tree::ptree_error& e) {
                std::string message = "maxbot-cpp library can't parse json response. " + std::string(e.what());

                throw BotException(message, BotException::ErrorCode::InvalidJson);
            }

			if (httpCode < 200 || httpCode > 299)
			{
				std::string message = result.get("message", "");
				throw BotException(message, static_cast<BotException::ErrorCode>(httpCode));
			}

			return result;
        } catch (...) {
            int max_retries = _httpClient.getRequestMaxRetries();
            if ((max_retries >= 0) && (retries == max_retries)) {
                throw;
            } else {
                std::this_thread::sleep_for(std::chrono::seconds(requestRetryBackoff));
                retries++;
                continue;
            }
        }
    }
}
}
