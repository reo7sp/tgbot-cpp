#include "tgbot/Api.h"
#include <json/json.h>
#include "tgbot/TgException.h"
#include "tgbot/TgTypeParser.h"
#include "tgbot/types/Message.h"
#include "tgbot/types/MessageId.h"

#include <chrono>
#include <iomanip>
#include <iostream>
#include <thread>

namespace {
std::vector<std::string>
escapeJSONStringVec(const std::vector<std::string> &vec) {
  std::vector<std::string> newVec = vec;
  for (auto i = newVec.begin(); i != newVec.end(); ++i) {
    std::stringstream ss;
    ss << std::quoted(StringTools::escapeJsonString(*i));
    *i = ss.str();
  }
  return newVec;
}
} // namespace
namespace TgBot {

Api::Api(std::string token, const HttpClient &httpClient,
         const std::string &url)
    : _httpClient(httpClient), _token(std::move(token)), _url(url) {}

std::vector<Update::Ptr>
Api::getUpdates(std::int32_t offset, std::int32_t limit, std::int32_t timeout,
                const StringArrayPtr &allowedUpdates) const {
  std::vector<HttpReqArg> args;
  args.reserve(4);

  if (offset != 0) {
    args.emplace_back("offset", offset);
  }
  if (limit != 100) {
    args.emplace_back("limit", std::max(1, std::min(100, limit)));
  }
  if (timeout != 0) {
    args.emplace_back("timeout", timeout);
  }
  if (allowedUpdates != nullptr) {
    std::string allowedUpdatesJson = putJSON(*allowedUpdates);
    args.emplace_back("allowed_updates", allowedUpdatesJson);
  }

  return parseArray<Update>(sendRequest("getUpdates", args));
}

bool Api::setWebhook(const std::string &url, InputFile::Ptr certificate,
                     std::int32_t maxConnections,
                     const StringArrayPtr &allowedUpdates,
                     const std::string &ipAddress, bool dropPendingUpdates,
                     const std::string &secretToken) const {
  std::vector<HttpReqArg> args;
  args.reserve(7);

  args.emplace_back("url", url);
  if (certificate != nullptr) {
    args.emplace_back("certificate", certificate->data, true,
                      certificate->mimeType, certificate->fileName);
  }
  if (!ipAddress.empty()) {
    args.emplace_back("ip_address", ipAddress);
  }
  if (maxConnections != 40) {
    args.emplace_back("max_connections",
                      std::max(1, std::min(100, maxConnections)));
  }
  if (allowedUpdates != nullptr) {
    auto allowedUpdatesJson = putJSON(*allowedUpdates);
    args.emplace_back("allowed_updates", allowedUpdatesJson);
  }
  if (dropPendingUpdates) {
    args.emplace_back("drop_pending_updates", dropPendingUpdates);
  }
  if (!secretToken.empty()) {
    args.emplace_back("secret_token", secretToken);
  }

  return sendRequest("setWebhook", args).asBool();
}

bool Api::deleteWebhook(bool dropPendingUpdates) const {
  std::vector<HttpReqArg> args;
  args.reserve(1);

  if (dropPendingUpdates) {
    args.emplace_back("drop_pending_updates", dropPendingUpdates);
  }

  return sendRequest("deleteWebhook", args).asBool();
}

WebhookInfo::Ptr Api::getWebhookInfo() const {
  const auto& p = sendRequest("getWebhookInfo");

  if (!p.isMember("url")) {
    return nullptr;
  }

  if (!p["url"].asString().empty()) {
    return parse<WebhookInfo>(p["url"]);
  } else {
    return nullptr;
  }
}

User::Ptr Api::getMe() const { return parse<User>(sendRequest("getMe")); }

bool Api::logOut() const { return sendRequest("logOut").asBool(); }

bool Api::close() const { return sendRequest("close").asBool(); }

Message::Ptr Api::sendMessage(boost::variant<std::int64_t, std::string> chatId,
                              const std::string &text,
                              LinkPreviewOptions::Ptr linkPreviewOptions,
                              ReplyParameters::Ptr replyParameters,
                              GenericReply::Ptr replyMarkup,
                              const std::string &parseMode,
                              bool disableNotification,
                              const std::vector<MessageEntity::Ptr> &entities,
                              std::int32_t messageThreadId, bool protectContent,
                              const std::string &businessConnectionId) const {
  std::vector<HttpReqArg> args;
  args.reserve(11);

  if (!businessConnectionId.empty()) {
    args.emplace_back("business_connection_id", businessConnectionId);
  }
  args.emplace_back("chat_id", chatId);
  if (messageThreadId != 0) {
    args.emplace_back("message_thread_id", messageThreadId);
  }
  args.emplace_back("text", text);
  if (!parseMode.empty()) {
    args.emplace_back("parse_mode", parseMode);
  }
  if (!entities.empty()) {
    args.emplace_back("entities", putJSON(entities));
  }
  if (linkPreviewOptions != nullptr) {
    args.emplace_back("link_preview_options", putJSON(linkPreviewOptions));
  }
  if (disableNotification) {
    args.emplace_back("disable_notification", disableNotification);
  }
  if (protectContent) {
    args.emplace_back("protect_content", protectContent);
  }
  if (replyParameters != nullptr) {
    args.emplace_back("reply_parameters", putJSON(replyParameters));
  }
  if (replyMarkup) {
    args.emplace_back("reply_markup", putJSON(replyMarkup));
  }

  return parse<Message>(sendRequest("sendMessage", args));
}

Message::Ptr
Api::forwardMessage(boost::variant<std::int64_t, std::string> chatId,
                    boost::variant<std::int64_t, std::string> fromChatId,
                    std::int32_t messageId, bool disableNotification,
                    bool protectContent, std::int32_t messageThreadId) const {
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

  return parse<Message>(sendRequest("forwardMessage", args));
}

std::vector<MessageId::Ptr>
Api::forwardMessages(boost::variant<std::int64_t, std::string> chatId,
                     boost::variant<std::int64_t, std::string> fromChatId,
                     const std::vector<std::int32_t> &messageIds,
                     std::int32_t messageThreadId, bool disableNotification,
                     bool protectContent) const {
  std::vector<HttpReqArg> args;
  args.reserve(6);

  args.emplace_back("chat_id", chatId);
  args.emplace_back("from_chat_id", fromChatId);
  if (!messageIds.empty()) {
    args.emplace_back("message_ids", putJSON(messageIds));
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

  return parseArray<MessageId>(sendRequest("forwardMessages", args));
}

MessageId::Ptr
Api::copyMessage(boost::variant<std::int64_t, std::string> chatId,
                 boost::variant<std::int64_t, std::string> fromChatId,
                 std::int32_t messageId, const std::string &caption,
                 const std::string &parseMode,
                 const std::vector<MessageEntity::Ptr> &captionEntities,
                 bool disableNotification, ReplyParameters::Ptr replyParameters,
                 GenericReply::Ptr replyMarkup, bool protectContent,
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
    args.emplace_back("caption_entities", putJSON(captionEntities));
  }
  if (disableNotification) {
    args.emplace_back("disable_notification", disableNotification);
  }
  if (protectContent) {
    args.emplace_back("protect_content", protectContent);
  }
  if (replyParameters != nullptr) {
    args.emplace_back("reply_parameters", putJSON(replyParameters));
  }
  if (replyMarkup) {
    args.emplace_back("reply_markup", putJSON(replyMarkup));
  }

  return parse<MessageId>(sendRequest("copyMessage", args));
}

std::vector<MessageId::Ptr>
Api::copyMessages(boost::variant<std::int64_t, std::string> chatId,
                  boost::variant<std::int64_t, std::string> fromChatId,
                  const std::vector<std::int32_t> &messageIds,
                  std::int32_t messageThreadId, bool disableNotification,
                  bool protectContent, bool removeCaption) const {
  std::vector<HttpReqArg> args;
  args.reserve(7);

  args.emplace_back("chat_id", chatId);
  args.emplace_back("from_chat_id", fromChatId);

  if (!messageIds.empty()) {
    args.emplace_back("message_ids", putJSON(messageIds));
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

  return parseArray<MessageId>(sendRequest("copyMessages", args));
}

Message::Ptr
Api::sendPhoto(boost::variant<std::int64_t, std::string> chatId,
               boost::variant<InputFile::Ptr, std::string> photo,
               const std::string &caption, ReplyParameters::Ptr replyParameters,
               GenericReply::Ptr replyMarkup, const std::string &parseMode,
               bool disableNotification,
               const std::vector<MessageEntity::Ptr> &captionEntities,
               std::int32_t messageThreadId, bool protectContent,
               bool hasSpoiler, const std::string &businessConnectionId) const {
  std::vector<HttpReqArg> args;
  args.reserve(12);

  if (!businessConnectionId.empty()) {
    args.emplace_back("business_connection_id", businessConnectionId);
  }
  args.emplace_back("chat_id", chatId);
  if (messageThreadId != 0) {
    args.emplace_back("message_thread_id", messageThreadId);
  }
  if (photo.which() == 0) { // InputFile::Ptr
    auto file = boost::get<InputFile::Ptr>(photo);
    args.emplace_back("photo", file->data, true, file->mimeType,
                      file->fileName);
  } else { // std::string
    args.emplace_back("photo", boost::get<std::string>(photo));
  }
  if (!caption.empty()) {
    args.emplace_back("caption", caption);
  }
  if (!parseMode.empty()) {
    args.emplace_back("parse_mode", parseMode);
  }
  if (!captionEntities.empty()) {
    args.emplace_back("caption_entities", putJSON(captionEntities));
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
    args.emplace_back("reply_parameters", putJSON(replyParameters));
  }
  if (replyMarkup != nullptr) {
    args.emplace_back("reply_markup", putJSON(replyMarkup));
  }

  return parse<Message>(sendRequest("sendPhoto", args));
}

Message::Ptr
Api::sendAudio(boost::variant<std::int64_t, std::string> chatId,
               boost::variant<InputFile::Ptr, std::string> audio,
               const std::string &caption, std::int32_t duration,
               const std::string &performer, const std::string &title,
               boost::variant<InputFile::Ptr, std::string> thumbnail,
               ReplyParameters::Ptr replyParameters,
               GenericReply::Ptr replyMarkup, const std::string &parseMode,
               bool disableNotification,
               const std::vector<MessageEntity::Ptr> &captionEntities,
               std::int32_t messageThreadId, bool protectContent,
               const std::string &businessConnectionId) const {
  std::vector<HttpReqArg> args;
  args.reserve(15);

  if (!businessConnectionId.empty()) {
    args.emplace_back("business_connection_id", businessConnectionId);
  }
  args.emplace_back("chat_id", chatId);
  if (messageThreadId != 0) {
    args.emplace_back("message_thread_id", messageThreadId);
  }
  if (audio.which() == 0) { // InputFile::Ptr
    auto file = boost::get<InputFile::Ptr>(audio);
    args.emplace_back("audio", file->data, true, file->mimeType,
                      file->fileName);
  } else { // std::string
    args.emplace_back("audio", boost::get<std::string>(audio));
  }
  if (!caption.empty()) {
    args.emplace_back("caption", caption);
  }
  if (!parseMode.empty()) {
    args.emplace_back("parse_mode", parseMode);
  }
  if (!captionEntities.empty()) {
    args.emplace_back("caption_entities", putJSON(captionEntities));
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
  if (thumbnail.which() == 0) { // InputFile::Ptr
    auto file = boost::get<InputFile::Ptr>(thumbnail);
    args.emplace_back("thumbnail", file->data, true, file->mimeType,
                      file->fileName);
  } else { // std::string
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
    args.emplace_back("reply_parameters", putJSON(replyParameters));
  }
  if (replyMarkup) {
    args.emplace_back("reply_markup", putJSON(replyMarkup));
  }

  return parse<Message>(sendRequest("sendAudio", args));
}

Message::Ptr Api::sendDocument(
    boost::variant<std::int64_t, std::string> chatId,
    boost::variant<InputFile::Ptr, std::string> document,
    boost::variant<InputFile::Ptr, std::string> thumbnail,
    const std::string &caption, ReplyParameters::Ptr replyParameters,
    GenericReply::Ptr replyMarkup, const std::string &parseMode,
    bool disableNotification,
    const std::vector<MessageEntity::Ptr> &captionEntities,
    bool disableContentTypeDetection, std::int32_t messageThreadId,
    bool protectContent, const std::string &businessConnectionId) const {
  std::vector<HttpReqArg> args;
  args.reserve(13);

  if (!businessConnectionId.empty()) {
    args.emplace_back("business_connection_id", businessConnectionId);
  }
  args.emplace_back("chat_id", chatId);
  if (messageThreadId != 0) {
    args.emplace_back("message_thread_id", messageThreadId);
  }
  if (document.which() == 0) { // InputFile::Ptr
    auto file = boost::get<InputFile::Ptr>(document);
    args.emplace_back("document", file->data, true, file->mimeType,
                      file->fileName);
  } else { // std::string
    args.emplace_back("document", boost::get<std::string>(document));
  }
  if (thumbnail.which() == 0) { // InputFile::Ptr
    auto file = boost::get<InputFile::Ptr>(thumbnail);
    args.emplace_back("thumbnail", file->data, true, file->mimeType,
                      file->fileName);
  } else { // std::string
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
    args.emplace_back("caption_entities", putJSON(captionEntities));
  }
  if (disableContentTypeDetection) {
    args.emplace_back("disable_content_type_detection",
                      disableContentTypeDetection);
  }
  if (disableNotification) {
    args.emplace_back("disable_notification", disableNotification);
  }
  if (protectContent) {
    args.emplace_back("protect_content", protectContent);
  }
  if (replyParameters != nullptr) {
    args.emplace_back("reply_parameters", putJSON(replyParameters));
  }
  if (replyMarkup) {
    args.emplace_back("reply_markup", putJSON(replyMarkup));
  }

  return parse<Message>(sendRequest("sendDocument", args));
}

Message::Ptr
Api::sendVideo(boost::variant<std::int64_t, std::string> chatId,
               boost::variant<InputFile::Ptr, std::string> video,
               bool supportsStreaming, std::int32_t duration,
               std::int32_t width, std::int32_t height,
               boost::variant<InputFile::Ptr, std::string> thumbnail,
               const std::string &caption, ReplyParameters::Ptr replyParameters,
               GenericReply::Ptr replyMarkup, const std::string &parseMode,
               bool disableNotification,
               const std::vector<MessageEntity::Ptr> &captionEntities,
               std::int32_t messageThreadId, bool protectContent,
               bool hasSpoiler, const std::string &businessConnectionId) const {
  std::vector<HttpReqArg> args;
  args.reserve(17);

  if (!businessConnectionId.empty()) {
    args.emplace_back("business_connection_id", businessConnectionId);
  }
  args.emplace_back("chat_id", chatId);
  if (messageThreadId != 0) {
    args.emplace_back("message_thread_id", messageThreadId);
  }
  if (video.which() == 0) { // InputFile::Ptr
    auto file = boost::get<InputFile::Ptr>(video);
    args.emplace_back("video", file->data, true, file->mimeType,
                      file->fileName);
  } else { // std::string
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
  if (thumbnail.which() == 0) { // InputFile::Ptr
    auto file = boost::get<InputFile::Ptr>(thumbnail);
    args.emplace_back("thumbnail", file->data, true, file->mimeType,
                      file->fileName);
  } else { // std::string
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
    args.emplace_back("caption_entities", putJSON(captionEntities));
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
    args.emplace_back("reply_parameters", putJSON(replyParameters));
  }
  if (replyMarkup != nullptr) {
    args.emplace_back("reply_markup", putJSON(replyMarkup));
  }

  return parse<Message>(sendRequest("sendVideo", args));
}

Message::Ptr Api::sendAnimation(
    boost::variant<std::int64_t, std::string> chatId,
    boost::variant<InputFile::Ptr, std::string> animation,
    std::int32_t duration, std::int32_t width, std::int32_t height,
    boost::variant<InputFile::Ptr, std::string> thumbnail,
    const std::string &caption, ReplyParameters::Ptr replyParameters,
    GenericReply::Ptr replyMarkup, const std::string &parseMode,
    bool disableNotification,
    const std::vector<MessageEntity::Ptr> &captionEntities,
    std::int32_t messageThreadId, bool protectContent, bool hasSpoiler,
    const std::string &businessConnectionId) const {
  std::vector<HttpReqArg> args;
  args.reserve(16);

  if (!businessConnectionId.empty()) {
    args.emplace_back("business_connection_id", businessConnectionId);
  }
  args.emplace_back("chat_id", chatId);
  if (messageThreadId != 0) {
    args.emplace_back("message_thread_id", messageThreadId);
  }
  if (animation.which() == 0) { // InputFile::Ptr
    auto file = boost::get<InputFile::Ptr>(animation);
    args.emplace_back("animation", file->data, true, file->mimeType,
                      file->fileName);
  } else { // std::string
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
  if (thumbnail.which() == 0) { // InputFile::Ptr
    auto file = boost::get<InputFile::Ptr>(thumbnail);
    args.emplace_back("thumbnail", file->data, true, file->mimeType,
                      file->fileName);
  } else { // std::string
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
    args.emplace_back("caption_entities", putJSON(captionEntities));
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
    args.emplace_back("reply_parameters", putJSON(replyParameters));
  }
  if (replyMarkup != nullptr) {
    args.emplace_back("reply_markup", putJSON(replyMarkup));
  }

  return parse<Message>(sendRequest("sendAnimation", args));
}

Message::Ptr
Api::sendVoice(boost::variant<std::int64_t, std::string> chatId,
               boost::variant<InputFile::Ptr, std::string> voice,
               const std::string &caption, std::int32_t duration,
               ReplyParameters::Ptr replyParameters,
               GenericReply::Ptr replyMarkup, const std::string &parseMode,
               bool disableNotification,
               const std::vector<MessageEntity::Ptr> &captionEntities,
               std::int32_t messageThreadId, bool protectContent,
               const std::string &businessConnectionId) const {
  std::vector<HttpReqArg> args;
  args.reserve(12);

  if (!businessConnectionId.empty()) {
    args.emplace_back("business_connection_id", businessConnectionId);
  }
  args.emplace_back("chat_id", chatId);
  if (messageThreadId != 0) {
    args.emplace_back("message_thread_id", messageThreadId);
  }
  if (voice.which() == 0) { // InputFile::Ptr
    auto file = boost::get<InputFile::Ptr>(voice);
    args.emplace_back("voice", file->data, true, file->mimeType,
                      file->fileName);
  } else { // std::string
    args.emplace_back("voice", boost::get<std::string>(voice));
  }
  if (!caption.empty()) {
    args.emplace_back("caption", caption);
  }
  if (!parseMode.empty()) {
    args.emplace_back("parse_mode", parseMode);
  }
  if (!captionEntities.empty()) {
    args.emplace_back("caption_entities", putJSON(captionEntities));
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
    args.emplace_back("reply_parameters", putJSON(replyParameters));
  }
  if (replyMarkup) {
    args.emplace_back("reply_markup", putJSON(replyMarkup));
  }

  return parse<Message>(sendRequest("sendVoice", args));
}

Message::Ptr Api::sendVideoNote(
    boost::variant<std::int64_t, std::string> chatId,
    boost::variant<InputFile::Ptr, std::string> videoNote,
    ReplyParameters::Ptr replyParameters, bool disableNotification,
    std::int32_t duration, std::int32_t length,
    boost::variant<InputFile::Ptr, std::string> thumbnail,
    GenericReply::Ptr replyMarkup, std::int32_t messageThreadId,
    bool protectContent, const std::string &businessConnectionId) const {
  std::vector<HttpReqArg> args;
  args.reserve(11);

  if (!businessConnectionId.empty()) {
    args.emplace_back("business_connection_id", businessConnectionId);
  }
  args.emplace_back("chat_id", chatId);
  if (messageThreadId != 0) {
    args.emplace_back("message_thread_id", messageThreadId);
  }
  if (videoNote.which() == 0) { // InputFile::Ptr
    auto file = boost::get<InputFile::Ptr>(videoNote);
    args.emplace_back("video_note", file->data, true, file->mimeType,
                      file->fileName);
  } else { // std::string
    args.emplace_back("video_note", boost::get<std::string>(videoNote));
  }
  if (duration) {
    args.emplace_back("duration", duration);
  }
  if (length) {
    args.emplace_back("length", length);
  }
  if (thumbnail.which() == 0) { // InputFile::Ptr
    auto file = boost::get<InputFile::Ptr>(thumbnail);
    args.emplace_back("thumbnail", file->data, true, file->mimeType,
                      file->fileName);
  } else { // std::string
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
    args.emplace_back("reply_parameters", putJSON(replyParameters));
  }
  if (replyMarkup) {
    args.emplace_back("reply_markup", putJSON(replyMarkup));
  }

  return parse<Message>(sendRequest("sendVideoNote", args));
}

std::vector<Message::Ptr> Api::sendMediaGroup(
    boost::variant<std::int64_t, std::string> chatId,
    const std::vector<InputMedia::Ptr> &media, bool disableNotification,
    ReplyParameters::Ptr replyParameters, std::int32_t messageThreadId,
    bool protectContent, const std::string &businessConnectionId) const {
  std::vector<HttpReqArg> args;
  args.reserve(7);

  if (!businessConnectionId.empty()) {
    args.emplace_back("business_connection_id", businessConnectionId);
  }
  args.emplace_back("chat_id", chatId);
  if (messageThreadId != 0) {
    args.emplace_back("message_thread_id", messageThreadId);
  }
  args.emplace_back("media", putJSON(media));
  if (disableNotification) {
    args.emplace_back("disable_notification", disableNotification);
  }
  if (protectContent) {
    args.emplace_back("protect_content", protectContent);
  }
  if (replyParameters != nullptr) {
    args.emplace_back("reply_parameters", putJSON(replyParameters));
  }

  return parseArray<Message>(sendRequest("sendMediaGroup", args));
}

Message::Ptr Api::sendLocation(
    boost::variant<std::int64_t, std::string> chatId, float latitude,
    float longitude, std::int32_t livePeriod,
    ReplyParameters::Ptr replyParameters, GenericReply::Ptr replyMarkup,
    bool disableNotification, float horizontalAccuracy, std::int32_t heading,
    std::int32_t proximityAlertRadius, std::int32_t messageThreadId,
    bool protectContent, const std::string &businessConnectionId) const {
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
    args.emplace_back("proximity_alert_radius",
                      std::max(1, std::min(100000, proximityAlertRadius)));
  }
  if (disableNotification) {
    args.emplace_back("disable_notification", disableNotification);
  }
  if (protectContent) {
    args.emplace_back("protect_content", protectContent);
  }
  if (replyParameters != nullptr) {
    args.emplace_back("reply_parameters", putJSON(replyParameters));
  }
  if (replyMarkup) {
    args.emplace_back("reply_markup", putJSON(replyMarkup));
  }

  return parse<Message>(sendRequest("sendLocation", args));
}

Message::Ptr Api::editMessageLiveLocation(
    float latitude, float longitude,
    boost::variant<std::int64_t, std::string> chatId, std::int32_t messageId,
    const std::string &inlineMessageId, InlineKeyboardMarkup::Ptr replyMarkup,
    float horizontalAccuracy, std::int32_t heading,
    std::int32_t proximityAlertRadius) const {
  std::vector<HttpReqArg> args;
  args.reserve(9);

  if (chatId.which() == 0) { // std::int64_t
    if (boost::get<std::int64_t>(chatId) != 0) {
      args.emplace_back("chat_id", chatId);
    }
  } else { // std::string
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
    args.emplace_back("reply_markup", putJSON(replyMarkup));
  }

  return parse<Message>(sendRequest("editMessageLiveLocation", args));
}

Message::Ptr
Api::stopMessageLiveLocation(boost::variant<std::int64_t, std::string> chatId,
                             std::int32_t messageId,
                             const std::string &inlineMessageId,
                             InlineKeyboardMarkup::Ptr replyMarkup) const {
  std::vector<HttpReqArg> args;
  args.reserve(4);

  if (chatId.which() == 0) { // std::int64_t
    if (boost::get<std::int64_t>(chatId) != 0) {
      args.emplace_back("chat_id", chatId);
    }
  } else { // std::string
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
    args.emplace_back("reply_markup", putJSON(replyMarkup));
  }

  return parse<Message>(sendRequest("stopMessageLiveLocation", args));
}

Message::Ptr Api::sendVenue(
    boost::variant<std::int64_t, std::string> chatId, float latitude,
    float longitude, const std::string &title, const std::string &address,
    const std::string &foursquareId, const std::string &foursquareType,
    bool disableNotification, ReplyParameters::Ptr replyParameters,
    GenericReply::Ptr replyMarkup, const std::string &googlePlaceId,
    const std::string &googlePlaceType, std::int32_t messageThreadId,
    bool protectContent, const std::string &businessConnectionId) const {
  std::vector<HttpReqArg> args;
  args.reserve(15);

  if (!businessConnectionId.empty()) {
    args.emplace_back("business_connection_id", businessConnectionId);
  }
  args.emplace_back("chat_id", chatId);
  if (messageThreadId != 0) {
    args.emplace_back("message_thread_id", messageThreadId);
  }
  args.emplace_back("latitude", latitude);
  args.emplace_back("longitude", longitude);
  args.emplace_back("title", title);
  args.emplace_back("address", address);
  if (!foursquareId.empty()) {
    args.emplace_back("foursquare_id", foursquareId);
  }
  if (!foursquareType.empty()) {
    args.emplace_back("foursquare_type", foursquareType);
  }
  if (!googlePlaceId.empty()) {
    args.emplace_back("google_place_id", googlePlaceId);
  }
  if (!googlePlaceType.empty()) {
    args.emplace_back("google_place_type", googlePlaceType);
  }
  if (disableNotification) {
    args.emplace_back("disable_notification", disableNotification);
  }
  if (protectContent) {
    args.emplace_back("protect_content", protectContent);
  }
  if (replyParameters != nullptr) {
    args.emplace_back("reply_parameters", putJSON(replyParameters));
  }
  if (replyMarkup) {
    args.emplace_back("reply_markup", putJSON(replyMarkup));
  }

  return parse<Message>(sendRequest("sendVenue", args));
}

Message::Ptr
Api::sendContact(boost::variant<std::int64_t, std::string> chatId,
                 const std::string &phoneNumber, const std::string &firstName,
                 const std::string &lastName, const std::string &vcard,
                 bool disableNotification, ReplyParameters::Ptr replyParameters,
                 GenericReply::Ptr replyMarkup, std::int32_t messageThreadId,
                 bool protectContent,
                 const std::string &businessConnectionId) const {
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
    args.emplace_back("reply_parameters", putJSON(replyParameters));
  }
  if (replyMarkup) {
    args.emplace_back("reply_markup", putJSON(replyMarkup));
  }

  return parse<Message>(sendRequest("sendContact", args));
}

Message::Ptr Api::sendPoll(
    boost::variant<std::int64_t, std::string> chatId,
    const std::string &question, const std::vector<std::string> &options,
    bool disableNotification, ReplyParameters::Ptr replyParameters,
    GenericReply::Ptr replyMarkup, bool isAnonymous, const std::string &type,
    bool allowsMultipleAnswers, std::int32_t correctOptionId,
    const std::string &explanation, const std::string &explanationParseMode,
    const std::vector<MessageEntity::Ptr> &explanationEntities,
    std::int32_t openPeriod, std::int32_t closeDate, bool isClosed,
    std::int32_t messageThreadId, bool protectContent,
    const std::string &businessConnectionId) const {
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
  args.emplace_back("options", putJSON(escapeJSONStringVec(options)));
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
    args.emplace_back("explanation_entities", putJSON(explanationEntities));
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
    args.emplace_back("reply_parameters", putJSON(replyParameters));
  }
  if (replyMarkup) {
    args.emplace_back("reply_markup", putJSON(replyMarkup));
  }

  return parse<Message>(sendRequest("sendPoll", args));
}

Message::Ptr Api::sendDice(boost::variant<std::int64_t, std::string> chatId,
                           bool disableNotification,
                           ReplyParameters::Ptr replyParameters,
                           GenericReply::Ptr replyMarkup,
                           const std::string &emoji,
                           std::int32_t messageThreadId, bool protectContent,
                           const std::string &businessConnectionId) const {
  std::vector<HttpReqArg> args;
  args.reserve(8);

  if (!businessConnectionId.empty()) {
    args.emplace_back("business_connection_id", businessConnectionId);
  }
  args.emplace_back("chat_id", chatId);
  if (messageThreadId != 0) {
    args.emplace_back("message_thread_id", messageThreadId);
  }
  if (!emoji.empty()) {
    args.emplace_back("emoji", emoji);
  }
  if (disableNotification) {
    args.emplace_back("disable_notification", disableNotification);
  }
  if (protectContent) {
    args.emplace_back("protect_content", protectContent);
  }
  if (replyParameters != nullptr) {
    args.emplace_back("reply_parameters", putJSON(replyParameters));
  }
  if (replyMarkup) {
    args.emplace_back("reply_markup", putJSON(replyMarkup));
  }

  return parse<Message>(sendRequest("sendDice", args));
}

bool Api::setMessageReaction(boost::variant<std::int64_t, std::string> chatId,
                             std::int32_t messageId,
                             const std::vector<ReactionType::Ptr> &reaction,
                             bool isBig) const {
  std::vector<HttpReqArg> args;
  args.reserve(4);

  args.emplace_back("chat_id", chatId);
  args.emplace_back("message_id", messageId);
  if (!reaction.empty()) {
    args.emplace_back("reaction", putJSON(reaction));
  }
  if (isBig) {
    args.emplace_back("is_big", isBig);
  }

  return sendRequest("setMessageReaction", args).asBool();
}

bool Api::sendChatAction(std::int64_t chatId, const std::string &action,
                         std::int32_t messageThreadId,
                         const std::string &businessConnectionId) const {
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

  return sendRequest("sendChatAction", args).asBool();
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

  return parse<UserProfilePhotos>(sendRequest("getUserProfilePhotos", args));
}

File::Ptr Api::getFile(const std::string &fileId) const {
  std::vector<HttpReqArg> args;
  args.reserve(1);

  args.emplace_back("file_id", fileId);

  return parse<File>(sendRequest("getFile", args));
}

bool Api::banChatMember(boost::variant<std::int64_t, std::string> chatId,
                        std::int64_t userId, std::int32_t untilDate,
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

  return sendRequest("banChatMember", args).asBool();
}

bool Api::unbanChatMember(boost::variant<std::int64_t, std::string> chatId,
                          std::int64_t userId, bool onlyIfBanned) const {
  std::vector<HttpReqArg> args;
  args.reserve(3);

  args.emplace_back("chat_id", chatId);
  args.emplace_back("user_id", userId);
  if (onlyIfBanned) {
    args.emplace_back("only_if_banned", onlyIfBanned);
  }

  return sendRequest("unbanChatMember", args).asBool();
}

bool Api::restrictChatMember(boost::variant<std::int64_t, std::string> chatId,
                             std::int64_t userId,
                             TgBot::ChatPermissions::Ptr permissions,
                             std::uint32_t untilDate,
                             bool useIndependentChatPermissions) const {
  std::vector<HttpReqArg> args;
  args.reserve(5);

  args.emplace_back("chat_id", chatId);
  args.emplace_back("user_id", userId);
  args.emplace_back("permissions", putJSON(permissions));
  if (useIndependentChatPermissions != false) {
    args.emplace_back("use_independent_chat_permissions",
                      useIndependentChatPermissions);
  }
  if (untilDate != 0) {
    args.emplace_back("until_date", untilDate);
  }

  return sendRequest("restrictChatMember", args).asBool();
}

bool Api::promoteChatMember(boost::variant<std::int64_t, std::string> chatId,
                            std::int64_t userId, bool canChangeInfo,
                            bool canPostMessages, bool canEditMessages,
                            bool canDeleteMessages, bool canInviteUsers,
                            bool canPinMessages, bool canPromoteMembers,
                            bool isAnonymous, bool canManageChat,
                            bool canManageVideoChats, bool canRestrictMembers,
                            bool canManageTopics, bool canPostStories,
                            bool canEditStories, bool canDeleteStories) const {
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

  return sendRequest("promoteChatMember", args).asBool();
}

bool Api::setChatAdministratorCustomTitle(
    boost::variant<std::int64_t, std::string> chatId, std::int64_t userId,
    const std::string &customTitle) const {
  std::vector<HttpReqArg> args;
  args.reserve(3);

  args.emplace_back("chat_id", chatId);
  args.emplace_back("user_id", userId);
  args.emplace_back("custom_title", customTitle);

  return sendRequest("setChatAdministratorCustomTitle", args)
      .asBool();
}

bool Api::banChatSenderChat(boost::variant<std::int64_t, std::string> chatId,
                            std::int64_t senderChatId) const {
  std::vector<HttpReqArg> args;
  args.reserve(2);

  args.emplace_back("chat_id", chatId);
  args.emplace_back("sender_chat_id", senderChatId);

  return sendRequest("banChatSenderChat", args).asBool();
}

bool Api::unbanChatSenderChat(boost::variant<std::int64_t, std::string> chatId,
                              std::int64_t senderChatId) const {
  std::vector<HttpReqArg> args;
  args.reserve(2);

  args.emplace_back("chat_id", chatId);
  args.emplace_back("sender_chat_id", senderChatId);

  return sendRequest("unbanChatSenderChat", args).asBool();
}

bool Api::setChatPermissions(boost::variant<std::int64_t, std::string> chatId,
                             ChatPermissions::Ptr permissions,
                             bool useIndependentChatPermissions) const {
  std::vector<HttpReqArg> args;
  args.reserve(3);

  args.emplace_back("chat_id", chatId);
  args.emplace_back("permissions", putJSON(permissions));
  if (useIndependentChatPermissions) {
    args.emplace_back("use_independent_chat_permissions",
                      useIndependentChatPermissions);
  }

  return sendRequest("setChatPermissions", args).asBool();
}

std::string Api::exportChatInviteLink(
    boost::variant<std::int64_t, std::string> chatId) const {
  std::vector<HttpReqArg> args;
  args.reserve(1);

  args.emplace_back("chat_id", chatId);

  return sendRequest("exportChatInviteLink", args).asString();
}

ChatInviteLink::Ptr
Api::createChatInviteLink(boost::variant<std::int64_t, std::string> chatId,
                          std::int32_t expireDate, std::int32_t memberLimit,
                          const std::string &name,
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

  return parse<ChatInviteLink>(sendRequest("createChatInviteLink", args));
}

ChatInviteLink::Ptr
Api::editChatInviteLink(boost::variant<std::int64_t, std::string> chatId,
                        const std::string &inviteLink, std::int32_t expireDate,
                        std::int32_t memberLimit, const std::string &name,
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

  return parse<ChatInviteLink>(sendRequest("editChatInviteLink", args));
}

ChatInviteLink::Ptr
Api::revokeChatInviteLink(boost::variant<std::int64_t, std::string> chatId,
                          const std::string &inviteLink) const {
  std::vector<HttpReqArg> args;
  args.reserve(2);

  args.emplace_back("chat_id", chatId);
  args.emplace_back("invite_link", inviteLink);

  return parse<ChatInviteLink>(sendRequest("revokeChatInviteLink", args));
}

bool Api::approveChatJoinRequest(
    boost::variant<std::int64_t, std::string> chatId,
    std::int64_t userId) const {
  std::vector<HttpReqArg> args;
  args.reserve(2);

  args.emplace_back("chat_id", chatId);
  args.emplace_back("user_id", userId);

  return sendRequest("approveChatJoinRequest", args).asBool();
}

bool Api::declineChatJoinRequest(
    boost::variant<std::int64_t, std::string> chatId,
    std::int64_t userId) const {
  std::vector<HttpReqArg> args;
  args.reserve(2);

  args.emplace_back("chat_id", chatId);
  args.emplace_back("user_id", userId);

  return sendRequest("declineChatJoinRequest", args).asBool();
}

bool Api::setChatPhoto(boost::variant<std::int64_t, std::string> chatId,
                       const InputFile::Ptr photo) const {
  std::vector<HttpReqArg> args;
  args.reserve(2);

  args.emplace_back("chat_id", chatId);
  args.emplace_back("photo", photo->data, true, photo->mimeType,
                    photo->fileName);

  return sendRequest("setChatPhoto", args).asBool();
}

bool Api::deleteChatPhoto(
    boost::variant<std::int64_t, std::string> chatId) const {
  std::vector<HttpReqArg> args;
  args.reserve(1);

  args.emplace_back("chat_id", chatId);

  return sendRequest("deleteChatPhoto", args).asBool();
}

bool Api::setChatTitle(boost::variant<std::int64_t, std::string> chatId,
                       const std::string &title) const {
  std::vector<HttpReqArg> args;
  args.reserve(2);

  args.emplace_back("chat_id", chatId);
  args.emplace_back("title", title);

  return sendRequest("setChatTitle", args).asBool();
}

bool Api::setChatDescription(boost::variant<std::int64_t, std::string> chatId,
                             const std::string &description) const {
  std::vector<HttpReqArg> args;
  args.reserve(2);

  args.emplace_back("chat_id", chatId);
  if (!description.empty()) {
    args.emplace_back("description", description);
  }

  return sendRequest("setChatDescription", args).asBool();
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

  return sendRequest("pinChatMessage", args).asBool();
}

bool Api::unpinChatMessage(boost::variant<std::int64_t, std::string> chatId,
                           std::int32_t messageId) const {
  std::vector<HttpReqArg> args;
  args.reserve(2);

  args.emplace_back("chat_id", chatId);
  if (messageId != 0) {
    args.emplace_back("message_id", messageId);
  }

  return sendRequest("unpinChatMessage", args).asBool();
}

bool Api::unpinAllChatMessages(
    boost::variant<std::int64_t, std::string> chatId) const {
  std::vector<HttpReqArg> args;
  args.reserve(1);

  args.emplace_back("chat_id", chatId);

  return sendRequest("unpinAllChatMessages", args).asBool();
}

bool Api::leaveChat(boost::variant<std::int64_t, std::string> chatId) const {
  std::vector<HttpReqArg> args;
  args.reserve(1);

  args.emplace_back("chat_id", chatId);

  return sendRequest("leaveChat", args).asBool();
}

Chat::Ptr Api::getChat(boost::variant<std::int64_t, std::string> chatId) const {
  std::vector<HttpReqArg> args;
  args.reserve(1);

  args.emplace_back("chat_id", chatId);

  return parse<Chat>(sendRequest("getChat", args));
}

std::vector<ChatMember::Ptr> Api::getChatAdministrators(
    boost::variant<std::int64_t, std::string> chatId) const {
  std::vector<HttpReqArg> args;
  args.reserve(1);

  args.emplace_back("chat_id", chatId);

  return parseArray<ChatMember>(sendRequest("getChatAdministrators", args));
}

int32_t Api::getChatMemberCount(
    boost::variant<std::int64_t, std::string> chatId) const {
  std::vector<HttpReqArg> args;
  args.reserve(1);

  args.emplace_back("chat_id", chatId);

  return sendRequest("getChatMemberCount", args).asInt();
}

ChatMember::Ptr
Api::getChatMember(boost::variant<std::int64_t, std::string> chatId,
                   std::int64_t userId) const {
  std::vector<HttpReqArg> args;
  args.reserve(2);

  args.emplace_back("chat_id", chatId);
  args.emplace_back("user_id", userId);

  return parse<ChatMember>(sendRequest("getChatMember", args));
}

bool Api::setChatStickerSet(boost::variant<std::int64_t, std::string> chatId,
                            const std::string &stickerSetName) const {
  std::vector<HttpReqArg> args;
  args.reserve(2);

  args.emplace_back("chat_id", chatId);
  args.emplace_back("sticker_set_name	", stickerSetName);

  return sendRequest("setChatStickerSet", args).asBool();
}

bool Api::deleteChatStickerSet(
    boost::variant<std::int64_t, std::string> chatId) const {
  std::vector<HttpReqArg> args;
  args.reserve(1);

  args.emplace_back("chat_id", chatId);

  return sendRequest("deleteChatStickerSet", args).asBool();
}

std::vector<Sticker::Ptr> Api::getForumTopicIconStickers() const {
  return parseArray<Sticker>(sendRequest("getForumTopicIconStickers"));
}

ForumTopic::Ptr
Api::createForumTopic(boost::variant<std::int64_t, std::string> chatId,
                      const std::string &name, std::int32_t iconColor,
                      const std::string &iconCustomEmojiId) const {
  std::vector<HttpReqArg> args;
  args.reserve(4);

  args.emplace_back("chat_id", chatId);
  args.emplace_back("name", name);
  if (iconColor != 0) {
    args.emplace_back("icon_color", iconColor);
  }
  if (!iconCustomEmojiId.empty()) {
    args.emplace_back("icon_custom_emoji_id", iconCustomEmojiId);
  }

  return parse<ForumTopic>(sendRequest("createForumTopic", args));
}

bool Api::editForumTopic(
    boost::variant<std::int64_t, std::string> chatId,
    std::int32_t messageThreadId, const std::string &name,
    boost::variant<std::int32_t, std::string> iconCustomEmojiId) const {
  std::vector<HttpReqArg> args;
  args.reserve(4);

  args.emplace_back("chat_id", chatId);
  args.emplace_back("message_thread_id", messageThreadId);
  if (!name.empty()) {
    args.emplace_back("name", name);
  }
  if (iconCustomEmojiId.which() == 0) { // std::int32_t
    if (boost::get<std::int32_t>(iconCustomEmojiId) != 0) {
      args.emplace_back("icon_custom_emoji_id", iconCustomEmojiId);
    }
  } else { // std::string
    if (boost::get<std::string>(iconCustomEmojiId) != "") {
      args.emplace_back("icon_custom_emoji_id", iconCustomEmojiId);
    }
  }

  return sendRequest("editForumTopic", args).asBool();
}

bool Api::closeForumTopic(boost::variant<std::int64_t, std::string> chatId,
                          std::int32_t messageThreadId) const {
  std::vector<HttpReqArg> args;
  args.reserve(2);

  args.emplace_back("chat_id", chatId);
  args.emplace_back("message_thread_id", messageThreadId);

  return sendRequest("closeForumTopic", args).asBool();
}

bool Api::reopenForumTopic(boost::variant<std::int64_t, std::string> chatId,
                           std::int32_t messageThreadId) const {
  std::vector<HttpReqArg> args;
  args.reserve(2);

  args.emplace_back("chat_id", chatId);
  args.emplace_back("message_thread_id", messageThreadId);

  return sendRequest("reopenForumTopic", args).asBool();
}

bool Api::deleteForumTopic(boost::variant<std::int64_t, std::string> chatId,
                           std::int32_t messageThreadId) const {
  std::vector<HttpReqArg> args;
  args.reserve(2);

  args.emplace_back("chat_id", chatId);
  args.emplace_back("message_thread_id", messageThreadId);

  return sendRequest("deleteForumTopic", args).asBool();
}

bool Api::unpinAllForumTopicMessages(
    boost::variant<std::int64_t, std::string> chatId,
    std::int32_t messageThreadId) const {
  std::vector<HttpReqArg> args;
  args.reserve(2);

  args.emplace_back("chat_id", chatId);
  args.emplace_back("message_thread_id", messageThreadId);

  return sendRequest("unpinAllForumTopicMessages", args).asBool();
}

bool Api::editGeneralForumTopic(
    boost::variant<std::int64_t, std::string> chatId, std::string name) const {
  std::vector<HttpReqArg> args;
  args.reserve(2);

  args.emplace_back("chat_id", chatId);
  args.emplace_back("name", name);

  return sendRequest("editGeneralForumTopic", args).asBool();
}

bool Api::closeGeneralForumTopic(
    boost::variant<std::int64_t, std::string> chatId) const {
  std::vector<HttpReqArg> args;
  args.reserve(1);

  args.emplace_back("chat_id", chatId);

  return sendRequest("closeGeneralForumTopic", args).asBool();
}

bool Api::reopenGeneralForumTopic(
    boost::variant<std::int64_t, std::string> chatId) const {
  std::vector<HttpReqArg> args;
  args.reserve(1);

  args.emplace_back("chat_id", chatId);

  return sendRequest("reopenGeneralForumTopic", args).asBool();
}

bool Api::hideGeneralForumTopic(
    boost::variant<std::int64_t, std::string> chatId) const {
  std::vector<HttpReqArg> args;
  args.reserve(1);

  args.emplace_back("chat_id", chatId);

  return sendRequest("hideGeneralForumTopic", args).asBool();
}

bool Api::unhideGeneralForumTopic(
    boost::variant<std::int64_t, std::string> chatId) const {
  std::vector<HttpReqArg> args;
  args.reserve(1);

  args.emplace_back("chat_id", chatId);

  return sendRequest("unhideGeneralForumTopic", args).asBool();
}

bool Api::unpinAllGeneralForumTopicMessages(
    boost::variant<std::int64_t, std::string> chatId) const {
  std::vector<HttpReqArg> args;
  args.reserve(1);

  args.emplace_back("chat_id", chatId);

  return sendRequest("unpinAllGeneralForumTopicMessages", args)
      .asBool();
}

bool Api::answerCallbackQuery(const std::string &callbackQueryId,
                              const std::string &text, bool showAlert,
                              const std::string &url,
                              std::int32_t cacheTime) const {
  std::vector<HttpReqArg> args;
  args.reserve(5);

  args.emplace_back("callback_query_id", callbackQueryId);
  if (!text.empty()) {
    args.emplace_back("text", text);
  }
  if (showAlert) {
    args.emplace_back("show_alert", showAlert);
  }
  if (!url.empty()) {
    args.emplace_back("url", url);
  }
  if (cacheTime) {
    args.emplace_back("cache_time", cacheTime);
  }

  return sendRequest("answerCallbackQuery", args).asBool();
}

UserChatBoosts::Ptr
Api::getUserChatBoosts(boost::variant<std::int64_t, std::string> chatId,
                       std::int32_t userId) const {
  std::vector<HttpReqArg> args;
  args.reserve(2);

  args.emplace_back("chat_id", chatId);
  args.emplace_back("user_id", userId);

  return parse<UserChatBoosts>(sendRequest("getUserChatBoosts", args));
}

BusinessConnection::Ptr
Api::getBusinessConnection(const std::string &businessConnectionId) const {
  std::vector<HttpReqArg> args;
  args.reserve(1);

  args.emplace_back("business_connection_id", businessConnectionId);

  return parse<BusinessConnection>(sendRequest("getBusinessConnection", args));
}

bool Api::setMyCommands(const std::vector<BotCommand::Ptr> &commands,
                        BotCommandScope::Ptr scope,
                        const std::string &languageCode) const {
  std::vector<HttpReqArg> args;
  args.reserve(3);

  args.emplace_back("commands", putJSON(commands));
  if (scope != nullptr) {
    args.emplace_back("scope", putJSON(scope));
  }
  if (!languageCode.empty()) {
    args.emplace_back("language_code", languageCode);
  }

  return sendRequest("setMyCommands", args).asBool();
}

bool Api::deleteMyCommands(BotCommandScope::Ptr scope,
                           const std::string &languageCode) const {
  std::vector<HttpReqArg> args;
  args.reserve(2);

  if (scope != nullptr) {
    args.emplace_back("scope", putJSON(scope));
  }
  if (!languageCode.empty()) {
    args.emplace_back("language_code", languageCode);
  }

  return sendRequest("deleteMyCommands", args).asBool();
}

std::vector<BotCommand::Ptr>
Api::getMyCommands(BotCommandScope::Ptr scope,
                   const std::string &languageCode) const {
  std::vector<HttpReqArg> args;
  args.reserve(2);

  if (scope != nullptr) {
    args.emplace_back("scope", putJSON(scope));
  }
  if (!languageCode.empty()) {
    args.emplace_back("language_code", languageCode);
  }

  return parseArray<BotCommand>(sendRequest("getMyCommands", args));
}

bool Api::setMyName(const std::string &name,
                    const std::string &languageCode) const {
  std::vector<HttpReqArg> args;
  args.reserve(2);

  if (!name.empty()) {
    args.emplace_back("name", name);
  }
  if (!languageCode.empty()) {
    args.emplace_back("language_code", languageCode);
  }

  return sendRequest("setMyName", args).asBool();
}

BotName::Ptr Api::getMyName(const std::string &languageCode) const {
  std::vector<HttpReqArg> args;
  args.reserve(1);

  if (!languageCode.empty()) {
    args.emplace_back("language_code", languageCode);
  }

  return parse<BotName>(sendRequest("getMyName", args));
}

bool Api::setMyDescription(const std::string &description,
                           const std::string &languageCode) const {
  std::vector<HttpReqArg> args;
  args.reserve(2);

  if (!description.empty()) {
    args.emplace_back("description", description);
  }
  if (!languageCode.empty()) {
    args.emplace_back("language_code", languageCode);
  }

  return sendRequest("setMyDescription", args).asBool();
}

BotDescription::Ptr
Api::getMyDescription(const std::string &languageCode) const {
  std::vector<HttpReqArg> args;
  args.reserve(1);

  if (!languageCode.empty()) {
    args.emplace_back("language_code", languageCode);
  }

  return parse<BotDescription>(sendRequest("getMyDescription", args));
}

bool Api::setMyShortDescription(const std::string &shortDescription,
                                const std::string &languageCode) const {
  std::vector<HttpReqArg> args;
  args.reserve(2);

  if (!shortDescription.empty()) {
    args.emplace_back("short_description", shortDescription);
  }
  if (!languageCode.empty()) {
    args.emplace_back("language_code", languageCode);
  }

  return sendRequest("setMyShortDescription", args).asBool();
}

BotShortDescription::Ptr
Api::getMyShortDescription(const std::string &languageCode) const {
  std::vector<HttpReqArg> args;
  args.reserve(1);

  if (!languageCode.empty()) {
    args.emplace_back("language_code", languageCode);
  }

  return parse<BotShortDescription>(sendRequest("getMyShortDescription", args));
}

bool Api::setChatMenuButton(std::int64_t chatId,
                            MenuButton::Ptr menuButton) const {
  std::vector<HttpReqArg> args;
  args.reserve(2);

  if (chatId != 0) {
    args.emplace_back("chat_id", chatId);
  }
  if (menuButton != nullptr) {
    args.emplace_back("menu_button", putJSON(menuButton));
  }

  return sendRequest("setChatMenuButton", args).asBool();
}

MenuButton::Ptr Api::getChatMenuButton(std::int64_t chatId) const {
  std::vector<HttpReqArg> args;
  args.reserve(1);

  if (chatId != 0) {
    args.emplace_back("chat_id", chatId);
  }

  return parse<MenuButton>(sendRequest("getChatMenuButton", args));
}

bool Api::setMyDefaultAdministratorRights(ChatAdministratorRights::Ptr rights,
                                          bool forChannels) const {
  std::vector<HttpReqArg> args;
  args.reserve(2);

  if (rights != nullptr) {
    args.emplace_back("rights", putJSON(rights));
  }
  if (forChannels) {
    args.emplace_back("for_channels", forChannels);
  }

  return sendRequest("setMyDefaultAdministratorRights", args)
      .asBool();
}

ChatAdministratorRights::Ptr
Api::getMyDefaultAdministratorRights(bool forChannels) const {
  std::vector<HttpReqArg> args;
  args.reserve(1);

  if (forChannels) {
    args.emplace_back("for_channels", forChannels);
  }

  return parse<ChatAdministratorRights>(
      sendRequest("getMyDefaultAdministratorRights", args));
}

Message::Ptr Api::editMessageText(
    const std::string &text, boost::variant<std::int64_t, std::string> chatId,
    std::int32_t messageId, const std::string &inlineMessageId,
    const std::string &parseMode, LinkPreviewOptions::Ptr linkPreviewOptions,
    InlineKeyboardMarkup::Ptr replyMarkup,
    const std::vector<MessageEntity::Ptr> &entities) const {
  std::vector<HttpReqArg> args;
  args.reserve(8);

  if (chatId.which() == 0) { // std::int64_t
    if (boost::get<std::int64_t>(chatId) != 0) {
      args.emplace_back("chat_id", chatId);
    }
  } else { // std::string
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
    args.emplace_back("entities", putJSON(entities));
  }
  if (linkPreviewOptions) {
    args.emplace_back("link_preview_options", putJSON(linkPreviewOptions));
  }
  if (replyMarkup) {
    args.emplace_back("reply_markup", putJSON(replyMarkup));
  }

  const auto p = sendRequest("editMessageText", args);
  if (p.isMember("message_id")) {
    return parse<Message>(p);
  } else {
    return nullptr;
  }
}

Message::Ptr Api::editMessageCaption(
    boost::variant<std::int64_t, std::string> chatId, std::int32_t messageId,
    const std::string &caption, const std::string &inlineMessageId,
    GenericReply::Ptr replyMarkup, const std::string &parseMode,
    const std::vector<MessageEntity::Ptr> &captionEntities) const {
  std::vector<HttpReqArg> args;
  args.reserve(7);

  if (chatId.which() == 0) { // std::int64_t
    if (boost::get<std::int64_t>(chatId) != 0) {
      args.emplace_back("chat_id", chatId);
    }
  } else { // std::string
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
    args.emplace_back("caption_entities", putJSON(captionEntities));
  }
  if (replyMarkup) {
    args.emplace_back("reply_markup", putJSON(replyMarkup));
  }

  const auto p = sendRequest("editMessageCaption", args);
  if (p.isMember("message_id")) {
    return parse<Message>(p);
  } else {
    return nullptr;
  }
}

Message::Ptr Api::editMessageMedia(
    InputMedia::Ptr media, boost::variant<std::int64_t, std::string> chatId,
    std::int32_t messageId, const std::string &inlineMessageId,
    GenericReply::Ptr replyMarkup) const {

  std::vector<HttpReqArg> args;
  args.reserve(5);

  if (chatId.which() == 0) { // std::int64_t
    if (boost::get<std::int64_t>(chatId) != 0) {
      args.emplace_back("chat_id", chatId);
    }
  } else { // std::string
    if (boost::get<std::string>(chatId) != "") {
      args.emplace_back("chat_id", chatId);
    }
  }
  args.emplace_back("media", putJSON(media));
  if (messageId) {
    args.emplace_back("message_id", messageId);
  }
  if (!inlineMessageId.empty()) {
    args.emplace_back("inline_message_id", inlineMessageId);
  }
  if (replyMarkup) {
    args.emplace_back("reply_markup", putJSON(replyMarkup));
  }

  const auto& p = sendRequest("editMessageMedia", args);
  if (p.isMember("message_id")) {
    return parse<Message>(p);
  } else {
    return nullptr;
  }
}

Message::Ptr
Api::editMessageReplyMarkup(boost::variant<std::int64_t, std::string> chatId,
                            std::int32_t messageId,
                            const std::string &inlineMessageId,
                            const GenericReply::Ptr replyMarkup) const {

  std::vector<HttpReqArg> args;
  args.reserve(4);

  if (chatId.which() == 0) { // std::int64_t
    if (boost::get<std::int64_t>(chatId) != 0) {
      args.emplace_back("chat_id", chatId);
    }
  } else { // std::string
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
    args.emplace_back("reply_markup", putJSON(replyMarkup));
  }

  const auto& p = sendRequest("editMessageReplyMarkup", args);
  if (p.isMember("message_id")) {
    return parse<Message>(p);
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
    args.emplace_back("reply_markup", putJSON(replyMarkup));
  }

  return parse<Poll>(sendRequest("stopPoll", args));
}

bool Api::deleteMessage(boost::variant<std::int64_t, std::string> chatId,
                        std::int32_t messageId) const {
  std::vector<HttpReqArg> args;
  args.reserve(2);

  args.emplace_back("chat_id", chatId);
  args.emplace_back("message_id", messageId);

  return sendRequest("deleteMessage", args).asBool();
}

bool Api::deleteMessages(boost::variant<std::int64_t, std::string> chatId,
                         const std::vector<std::int32_t> &messageIds) const {
  std::vector<HttpReqArg> args;
  args.reserve(2);

  args.emplace_back("chat_id", chatId);
  if (!messageIds.empty()) {
    args.emplace_back("message_ids", putJSON(messageIds));
  }

  return sendRequest("deleteMessages", args).asBool();
}

Message::Ptr Api::sendSticker(
    boost::variant<std::int64_t, std::string> chatId,
    boost::variant<InputFile::Ptr, std::string> sticker,
    ReplyParameters::Ptr replyParameters, GenericReply::Ptr replyMarkup,
    bool disableNotification, std::int32_t messageThreadId, bool protectContent,
    const std::string &emoji, const std::string &businessConnectionId) const {
  std::vector<HttpReqArg> args;
  args.reserve(9);

  if (!businessConnectionId.empty()) {
    args.emplace_back("business_connection_id", businessConnectionId);
  }
  args.emplace_back("chat_id", chatId);
  if (messageThreadId != 0) {
    args.emplace_back("message_thread_id", messageThreadId);
  }
  if (sticker.which() == 0) { // InputFile::Ptr
    auto file = boost::get<InputFile::Ptr>(sticker);
    args.emplace_back("sticker", file->data, true, file->mimeType,
                      file->fileName);
  } else { // std::string
    args.emplace_back("sticker", boost::get<std::string>(sticker));
  }
  if (!emoji.empty()) {
    args.emplace_back("emoji", emoji);
  }
  if (disableNotification) {
    args.emplace_back("disable_notification", disableNotification);
  }
  if (protectContent) {
    args.emplace_back("protect_content", protectContent);
  }
  if (replyParameters != nullptr) {
    args.emplace_back("reply_parameters", putJSON(replyParameters));
  }
  if (replyMarkup) {
    args.emplace_back("reply_markup", putJSON(replyMarkup));
  }

  return parse<Message>(sendRequest("sendSticker", args));
}

StickerSet::Ptr Api::getStickerSet(const std::string &name) const {
  std::vector<HttpReqArg> args;
  args.reserve(1);

  args.emplace_back("name", name);

  return parse<StickerSet>(sendRequest("getStickerSet", args));
}

std::vector<Sticker::Ptr> Api::getCustomEmojiStickers(
    const std::vector<std::string> &customEmojiIds) const {
  std::vector<HttpReqArg> args;
  args.reserve(1);

  args.emplace_back("custom_emoji_ids",
                    putJSON(escapeJSONStringVec(customEmojiIds)));

  return parseArray<Sticker>(sendRequest("getCustomEmojiStickers", args));
}

File::Ptr Api::uploadStickerFile(std::int64_t userId, InputFile::Ptr sticker,
                                 const std::string &stickerFormat) const {
  std::vector<HttpReqArg> args;
  args.reserve(3);

  args.emplace_back("user_id", userId);
  args.emplace_back("sticker", sticker->data, true, sticker->mimeType,
                    sticker->fileName);
  args.emplace_back("sticker_format", stickerFormat);

  return parse<File>(sendRequest("uploadStickerFile", args));
}

bool Api::createNewStickerSet(std::int64_t userId, const std::string &name,
                              const std::string &title,
                              const std::vector<InputSticker::Ptr> &stickers,
                              Sticker::Type stickerType,
                              bool needsRepainting) const {
  std::vector<HttpReqArg> args;
  args.reserve(6);

  args.emplace_back("user_id", userId);
  args.emplace_back("name", name);
  args.emplace_back("title", title);
  args.emplace_back("stickers", putJSON(stickers));
  if (stickerType == Sticker::Type::Regular) {
    args.emplace_back("sticker_type", "regular");
  } else if (stickerType == Sticker::Type::Mask) {
    args.emplace_back("sticker_type", "mask");
  } else if (stickerType == Sticker::Type::CustomEmoji) {
    args.emplace_back("sticker_type", "custom_emoji");
  }
  if (needsRepainting) {
    args.emplace_back("needs_repainting", needsRepainting);
  }

  return sendRequest("createNewStickerSet", args).asBool();
}

bool Api::addStickerToSet(std::int64_t userId, const std::string &name,
                          InputSticker::Ptr sticker) const {
  std::vector<HttpReqArg> args;
  args.reserve(3);

  args.emplace_back("user_id", userId);
  args.emplace_back("name", name);
  args.emplace_back("sticker", putJSON(sticker));

  return sendRequest("addStickerToSet", args).asBool();
}

bool Api::setStickerPositionInSet(const std::string &sticker,
                                  std::int32_t position) const {
  std::vector<HttpReqArg> args;
  args.reserve(2);

  args.emplace_back("sticker", sticker);
  args.emplace_back("position", position);

  return sendRequest("setStickerPositionInSet", args).asBool();
}

bool Api::deleteStickerFromSet(const std::string &sticker) const {
  std::vector<HttpReqArg> args;
  args.reserve(1);

  args.emplace_back("sticker", sticker);

  return sendRequest("deleteStickerFromSet", args).asBool();
}

bool Api::replaceStickerInSet(std::int64_t userId, const std::string &name,
                              const std::string &oldSticker,
                              InputSticker::Ptr sticker) const {
  std::vector<HttpReqArg> args;
  args.reserve(4);

  args.emplace_back("user_id", userId);
  args.emplace_back("name", name);
  args.emplace_back("old_sticker", oldSticker);
  args.emplace_back("sticker", putJSON(sticker));

  return sendRequest("replaceStickerInSet", args).asBool();
}

bool Api::setStickerEmojiList(const std::string &sticker,
                              const std::vector<std::string> &emojiList) const {
  std::vector<HttpReqArg> args;
  args.reserve(2);

  args.emplace_back("sticker", sticker);
  args.emplace_back("emoji_list", putJSON(escapeJSONStringVec(emojiList)));
  return sendRequest("setStickerEmojiList", args).asBool();
}

bool Api::setStickerKeywords(const std::string &sticker,
                             const std::vector<std::string> &keywords) const {
  std::vector<HttpReqArg> args;
  args.reserve(2);

  args.emplace_back("sticker", sticker);
  if (!keywords.empty()) {
    args.emplace_back("keywords", putJSON(escapeJSONStringVec(keywords)));
  }

  return sendRequest("setStickerKeywords", args).asBool();
}

bool Api::setStickerMaskPosition(const std::string &sticker,
                                 MaskPosition::Ptr maskPosition) const {
  std::vector<HttpReqArg> args;
  args.reserve(2);

  args.emplace_back("sticker", sticker);
  if (maskPosition != nullptr) {
    args.emplace_back("mask_position", putJSON(maskPosition));
  }

  return sendRequest("setStickerMaskPosition", args).asBool();
}

bool Api::setStickerSetTitle(const std::string &name,
                             const std::string &title) const {
  std::vector<HttpReqArg> args;
  args.reserve(2);

  args.emplace_back("name", name);
  args.emplace_back("title", title);

  return sendRequest("setStickerSetTitle", args).asBool();
}

bool Api::setStickerSetThumbnail(
    const std::string &name, std::int64_t userId, const std::string &format,
    boost::variant<InputFile::Ptr, std::string> thumbnail) const {
  std::vector<HttpReqArg> args;
  args.reserve(4);

  args.emplace_back("name", name);
  args.emplace_back("user_id", userId);
  args.emplace_back("format", format);
  if (thumbnail.which() == 0) { // InputFile::Ptr
    if (boost::get<InputFile::Ptr>(thumbnail) != nullptr) {
      auto file = boost::get<InputFile::Ptr>(thumbnail);
      args.emplace_back("thumbnail", file->data, true, file->mimeType,
                        file->fileName);
    }
  } else { // std::string
    if (boost::get<std::string>(thumbnail) != "") {
      args.emplace_back("thumbnail", boost::get<std::string>(thumbnail));
    }
  }

  return sendRequest("setStickerSetThumbnail", args).asBool();
}

bool Api::setCustomEmojiStickerSetThumbnail(
    const std::string &name, const std::string &customEmojiId) const {
  std::vector<HttpReqArg> args;
  args.reserve(2);

  args.emplace_back("name", name);
  if (!customEmojiId.empty()) {
    args.emplace_back("custom_emoji_id", customEmojiId);
  }

  return sendRequest("setCustomEmojiStickerSetThumbnail", args)
      .asBool();
}

bool Api::deleteStickerSet(const std::string &name) const {
  std::vector<HttpReqArg> args;
  args.reserve(1);

  args.emplace_back("name", name);

  return sendRequest("deleteStickerSet", args).asBool();
}

bool Api::answerInlineQuery(const std::string &inlineQueryId,
                            const std::vector<InlineQueryResult::Ptr> &results,
                            std::int32_t cacheTime, bool isPersonal,
                            const std::string &nextOffset,
                            InlineQueryResultsButton::Ptr button) const {
  std::vector<HttpReqArg> args;
  args.reserve(6);

  args.emplace_back("inline_query_id", inlineQueryId);
  args.emplace_back("results", putJSON(results));
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
    args.emplace_back("button", putJSON(button));
  }

  return sendRequest("answerInlineQuery", args).asBool();
}

SentWebAppMessage::Ptr
Api::answerWebAppQuery(const std::string &webAppQueryId,
                       InlineQueryResult::Ptr result) const {
  std::vector<HttpReqArg> args;
  args.reserve(2);

  args.emplace_back("web_app_query_id", webAppQueryId);
  args.emplace_back("result", putJSON(result));

  return parse<SentWebAppMessage>(sendRequest("answerWebAppQuery", args));
}

Message::Ptr
Api::sendInvoice(boost::variant<std::int64_t, std::string> chatId,
                 const std::string &title, const std::string &description,
                 const std::string &payload, const std::string &providerToken,
                 const std::string &currency,
                 const std::vector<LabeledPrice::Ptr> &prices,
                 const std::string &providerData, const std::string &photoUrl,
                 std::int32_t photoSize, std::int32_t photoWidth,
                 std::int32_t photoHeight, bool needName, bool needPhoneNumber,
                 bool needEmail, bool needShippingAddress,
                 bool sendPhoneNumberToProvider, bool sendEmailToProvider,
                 bool isFlexible, ReplyParameters::Ptr replyParameters,
                 GenericReply::Ptr replyMarkup, bool disableNotification,
                 std::int32_t messageThreadId, std::int32_t maxTipAmount,
                 const std::vector<std::int32_t> &suggestedTipAmounts,
                 const std::string &startParameter, bool protectContent) const {
  std::vector<HttpReqArg> args;
  args.reserve(27);

  args.emplace_back("chat_id", chatId);
  if (messageThreadId != 0) {
    args.emplace_back("message_thread_id", messageThreadId);
  }
  args.emplace_back("title", title);
  args.emplace_back("description", description);
  args.emplace_back("payload", payload);
  args.emplace_back("provider_token", providerToken);
  args.emplace_back("currency", currency);
  args.emplace_back("prices", putJSON(prices));
  args.emplace_back("max_tip_amount", maxTipAmount);
  if (!suggestedTipAmounts.empty()) {
    args.emplace_back("suggested_tip_amounts", putJSON(suggestedTipAmounts));
  }
  if (!startParameter.empty()) {
    args.emplace_back("start_parameter", startParameter);
  }
  if (!providerData.empty()) {
    args.emplace_back("provider_data", providerData);
  }
  if (!photoUrl.empty()) {
    args.emplace_back("photo_url", photoUrl);
  }
  if (photoSize) {
    args.emplace_back("photo_size", photoSize);
  }
  if (photoWidth) {
    args.emplace_back("photo_width", photoWidth);
  }
  if (photoHeight) {
    args.emplace_back("photo_height", photoHeight);
  }
  if (needName) {
    args.emplace_back("need_name", needName);
  }
  if (needPhoneNumber) {
    args.emplace_back("need_phone_number", needPhoneNumber);
  }
  if (needEmail) {
    args.emplace_back("need_email", needEmail);
  }
  if (needShippingAddress) {
    args.emplace_back("need_shipping_address", needShippingAddress);
  }
  if (sendPhoneNumberToProvider) {
    args.emplace_back("send_phone_number_to_provider",
                      sendPhoneNumberToProvider);
  }
  if (sendEmailToProvider) {
    args.emplace_back("send_email_to_provider", sendEmailToProvider);
  }
  if (isFlexible) {
    args.emplace_back("is_flexible", isFlexible);
  }
  if (disableNotification) {
    args.emplace_back("disable_notification", disableNotification);
  }
  if (protectContent) {
    args.emplace_back("protect_content", protectContent);
  }
  if (replyParameters != nullptr) {
    args.emplace_back("reply_parameters", putJSON(replyParameters));
  }
  if (replyMarkup) {
    args.emplace_back("reply_markup", putJSON(replyMarkup));
  }

  return parse<Message>(sendRequest("sendInvoice", args));
}

std::string Api::createInvoiceLink(
    const std::string &title, const std::string &description,
    const std::string &payload, const std::string &providerToken,
    const std::string &currency, const std::vector<LabeledPrice::Ptr> &prices,
    std::int32_t maxTipAmount,
    const std::vector<std::int32_t> &suggestedTipAmounts,
    const std::string &providerData, const std::string &photoUrl,
    std::int32_t photoSize, std::int32_t photoWidth, std::int32_t photoHeight,
    bool needName, bool needPhoneNumber, bool needEmail,
    bool needShippingAddress, bool sendPhoneNumberToProvider,
    bool sendEmailToProvider, bool isFlexible) const {
  std::vector<HttpReqArg> args;
  args.reserve(20);

  args.emplace_back("title", title);
  args.emplace_back("description", description);
  args.emplace_back("payload", payload);
  args.emplace_back("provider_token", providerToken);
  args.emplace_back("currency", currency);
  args.emplace_back("prices", putJSON(prices));
  args.emplace_back("max_tip_amount", maxTipAmount);
  if (!suggestedTipAmounts.empty()) {
    args.emplace_back("suggested_tip_amounts", putJSON(suggestedTipAmounts));
  }
  if (!providerData.empty()) {
    args.emplace_back("provider_data", providerData);
  }
  if (!photoUrl.empty()) {
    args.emplace_back("photo_url", photoUrl);
  }
  if (photoSize) {
    args.emplace_back("photo_size", photoSize);
  }
  if (photoWidth) {
    args.emplace_back("photo_width", photoWidth);
  }
  if (photoHeight) {
    args.emplace_back("photo_height", photoHeight);
  }
  if (needName) {
    args.emplace_back("need_name", needName);
  }
  if (needPhoneNumber) {
    args.emplace_back("need_phone_number", needPhoneNumber);
  }
  if (needEmail) {
    args.emplace_back("need_email", needEmail);
  }
  if (needShippingAddress) {
    args.emplace_back("need_shipping_address", needShippingAddress);
  }
  if (sendPhoneNumberToProvider) {
    args.emplace_back("send_phone_number_to_provider",
                      sendPhoneNumberToProvider);
  }
  if (sendEmailToProvider) {
    args.emplace_back("send_email_to_provider", sendEmailToProvider);
  }
  if (isFlexible) {
    args.emplace_back("is_flexible", isFlexible);
  }

  return sendRequest("createInvoiceLink", args).asString();
}

bool Api::answerShippingQuery(
    const std::string &shippingQueryId, bool ok,
    const std::vector<ShippingOption::Ptr> &shippingOptions,
    const std::string &errorMessage) const {
  std::vector<HttpReqArg> args;
  args.reserve(4);

  args.emplace_back("shipping_query_id", shippingQueryId);
  args.emplace_back("ok", ok);
  if (!shippingOptions.empty()) {
    args.emplace_back("shipping_options", putJSON(shippingOptions));
  }
  if (!errorMessage.empty()) {
    args.emplace_back("error_message", errorMessage);
  }

  return sendRequest("answerShippingQuery", args).asBool();
}

bool Api::answerPreCheckoutQuery(const std::string &preCheckoutQueryId, bool ok,
                                 const std::string &errorMessage) const {
  std::vector<HttpReqArg> args;
  args.reserve(3);

  args.emplace_back("pre_checkout_query_id", preCheckoutQueryId);
  args.emplace_back("ok", ok);
  if (!errorMessage.empty()) {
    args.emplace_back("error_message", errorMessage);
  }

  return sendRequest("answerPreCheckoutQuery", args).asBool();
}

bool Api::setPassportDataErrors(
    std::int64_t userId,
    const std::vector<PassportElementError::Ptr> &errors) const {
  std::vector<HttpReqArg> args;
  args.reserve(2);

  args.emplace_back("user_id", userId);
  args.emplace_back("errors", putJSON(errors));

  return sendRequest("setPassportDataErrors", args).asBool();
}

Message::Ptr Api::sendGame(std::int64_t chatId,
                           const std::string &gameShortName,
                           ReplyParameters::Ptr replyParameters,
                           InlineKeyboardMarkup::Ptr replyMarkup,
                           bool disableNotification,
                           std::int32_t messageThreadId, bool protectContent,
                           const std::string &businessConnectionId) const {
  std::vector<HttpReqArg> args;
  args.reserve(8);

  if (!businessConnectionId.empty()) {
    args.emplace_back("business_connection_id", businessConnectionId);
  }
  args.emplace_back("chat_id", chatId);
  if (messageThreadId != 0) {
    args.emplace_back("message_thread_id", messageThreadId);
  }
  args.emplace_back("game_short_name", gameShortName);
  if (disableNotification) {
    args.emplace_back("disable_notification", disableNotification);
  }
  if (protectContent) {
    args.emplace_back("protect_content", protectContent);
  }
  if (replyParameters != nullptr) {
    args.emplace_back("reply_parameters", putJSON(replyParameters));
  }
  if (replyMarkup) {
    args.emplace_back("reply_markup", putJSON(replyMarkup));
  }

  return parse<Message>(sendRequest("sendGame", args));
}

Message::Ptr Api::setGameScore(std::int64_t userId, std::int32_t score,
                               bool force, bool disableEditMessage,
                               std::int64_t chatId, std::int32_t messageId,
                               const std::string &inlineMessageId) const {
  std::vector<HttpReqArg> args;
  args.reserve(7);

  args.emplace_back("user_id", userId);
  args.emplace_back("score", score);
  if (force) {
    args.emplace_back("force", force);
  }
  if (disableEditMessage) {
    args.emplace_back("disable_edit_message", disableEditMessage);
  }
  if (chatId) {
    args.emplace_back("chat_id", chatId);
  }
  if (messageId) {
    args.emplace_back("message_id", messageId);
  }
  if (!inlineMessageId.empty()) {
    args.emplace_back("inline_message_id", inlineMessageId);
  }

  return parse<Message>(sendRequest("setGameScore", args));
}

std::vector<GameHighScore::Ptr>
Api::getGameHighScores(std::int64_t userId, std::int64_t chatId,
                       std::int32_t messageId,
                       const std::string &inlineMessageId) const {
  std::vector<HttpReqArg> args;
  args.reserve(4);

  args.emplace_back("user_id", userId);
  if (chatId) {
    args.emplace_back("chat_id", chatId);
  }
  if (messageId) {
    args.emplace_back("message_id", messageId);
  }
  if (!inlineMessageId.empty()) {
    args.emplace_back("inline_message_id", inlineMessageId);
  }

  return parseArray<GameHighScore>(sendRequest("getGameHighScores", args));
}

std::string Api::downloadFile(const std::string &filePath,
                              const std::vector<HttpReqArg> &args) const {
  std::string url(_url);
  url += "/file/bot";
  url += _token;
  url += "/";
  url += filePath;

  return _httpClient.makeRequest(url, args);
}

bool Api::blockedByUser(std::int64_t chatId) const {
  bool isBotBlocked = false;

  try {
    sendChatAction(chatId, "typing");

  } catch (std::exception &e) {
    std::string error = e.what();

    if (error.compare("Forbidden: bot was blocked by the user") == 0) {
      isBotBlocked = true;
    }
  }

  return isBotBlocked;
}

constexpr bool kSendRequestDebug = true;

Json::Value
Api::sendRequest(const std::string &method,
                 const std::vector<HttpReqArg> &args) const {
  std::string url(_url);
  url += "/bot";
  url += _token;
  url += "/";
  url += method;

  int requestRetryBackoff = _httpClient.getRequestBackoff();
  int retries = 0;
  if constexpr (kSendRequestDebug) {
    std::cout << "tgbot-cpp: Sending request: " << method << std::endl;
    for (const auto &arg : args) {
      std::cout << arg.name << " is " << arg.value << std::endl;
    }
  }
  while (1) {
    try {
      std::string serverResponse = _httpClient.makeRequest(url, args);

      if (!serverResponse.compare(0, 6, "<html>")) {
        std::string message =
            "tgbot-cpp library have got html page instead of json response. "
            "Maybe you entered wrong bot token.";
        throw TgException(message, TgException::ErrorCode::HtmlResponse);
      }

      Json::Value result;
      Json::Reader reader;
      if (!reader.parse(serverResponse, result, false)){
        std::string message = "tgbot-cpp library can't parse json response.";
        throw TgException(message, TgException::ErrorCode::InvalidJson);
      }

      if (result["ok"].asBool()) {
        return result["result"];
      } else {
        std::string message = result["description"].asString();
        size_t errorCode = result["error_code"].as<size_t>();

        throw TgException(message,
                          static_cast<TgException::ErrorCode>(errorCode));
      }
    } catch (const TgException& ex) {
      if constexpr (kSendRequestDebug) {
        std::cerr << "tgbot-cpp: Error: " << ex.what() << std::endl;
      }
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
} // namespace TgBot
