#include <gtest/gtest.h>

#include "tgbot/Api.h"
#include "tgbot/HttpClient.h"
#include "tgbot/TgException.h"
#include "tgbot/Types.h"

#include <nlohmann/json.hpp>

#include <span>
#include <stdexcept>
#include <string>
#include <utility>
#include <variant>
#include <vector>

namespace {

class HttpClientMock final : public TgBot::HttpClient {
public:
    std::string makeRequest(const std::string& url, std::span<const TgBot::HttpFormField> fields) const override {
        requestUrl = url;
        requestFields.assign(fields.begin(), fields.end());
        return response;
    }

    mutable std::string requestUrl;
    mutable std::vector<TgBot::HttpFormField> requestFields;
    std::string response;
};

bool requestThrows(TgBot::TgException::ErrorCode expectedCode, const std::string& response) {
    HttpClientMock httpClient;
    httpClient.response = response;
    TgBot::Api api("token", httpClient, "url");

    try {
        api.getMe();
    } catch (const TgBot::TgException& exception) {
        return exception.errorCode == expectedCode;
    }

    return false;
}

} // namespace

TEST(Api, GeneratedMethodMapsTelegramErrors) {
    using ErrorCode = TgBot::TgException::ErrorCode;

    EXPECT_TRUE(requestThrows(ErrorCode::HtmlResponse, "<html>"));
    EXPECT_TRUE(requestThrows(ErrorCode::Undefined, R"({"ok":false})"));
    EXPECT_TRUE(requestThrows(ErrorCode::Undefined, R"({"ok":false,"error_code":0})"));
    EXPECT_TRUE(requestThrows(ErrorCode::BadRequest, R"({"ok":false,"error_code":400})"));
    EXPECT_TRUE(requestThrows(ErrorCode::Unauthorized, R"({"ok":false,"error_code":401})"));
    EXPECT_TRUE(requestThrows(ErrorCode::Forbidden, R"({"ok":false,"error_code":403})"));
    EXPECT_TRUE(requestThrows(ErrorCode::NotFound, R"({"ok":false,"error_code":404})"));
    EXPECT_TRUE(requestThrows(ErrorCode::Flood, R"({"ok":false,"error_code":429})"));
    EXPECT_TRUE(requestThrows(ErrorCode::Internal, R"({"ok":false,"error_code":500})"));
    EXPECT_TRUE(requestThrows(ErrorCode::InvalidJson, "error_code:101"));
}

TEST(Api, PassesCompleteUrlToHttpClient) {
    HttpClientMock httpClient;
    httpClient.response = R"({"ok":true,"result":{"id":1,"is_bot":true,"first_name":"bot"}})";
    TgBot::Api api("token", httpClient, "https://api.telegram.org");

    api.getMe();

    EXPECT_EQ(httpClient.requestUrl, "https://api.telegram.org/bottoken/getMe");
}

TEST(Api, DownloadFilePassesCompleteUrlAndFieldsToHttpClient) {
    HttpClientMock httpClient;
    httpClient.response = "file-data";
    TgBot::Api api("token", httpClient, "https://api.telegram.org");
    const std::vector<TgBot::HttpFormField> fields { { "range", "bytes=0-3" } };

    const auto contents = api.downloadFile("documents/file.bin", fields);

    EXPECT_EQ(contents, "file-data");
    EXPECT_EQ(httpClient.requestUrl, "https://api.telegram.org/file/bottoken/documents/file.bin");
    ASSERT_EQ(httpClient.requestFields.size(), 1);
    EXPECT_EQ(httpClient.requestFields[0].name, "range");
    EXPECT_EQ(std::get<std::string>(httpClient.requestFields[0].value), "bytes=0-3");
}

TEST(Api, GetChatAdministratorsPreservesAdministratorRights) {
    HttpClientMock httpClient;
    httpClient.response
        = R"({"ok":true,"result":[{"status":"administrator","user":{"id":1,"is_bot":false,"first_name":"Admin"},"can_be_edited":true,"is_anonymous":false,"can_manage_chat":true,"can_delete_messages":true,"can_manage_video_chats":false,"can_restrict_members":true,"can_promote_members":false,"can_change_info":true,"can_invite_users":true,"can_post_stories":false,"can_edit_stories":false,"can_delete_stories":false}]})";
    TgBot::Api api("token", httpClient, "https://api.telegram.org");

    const auto members = api.getChatAdministrators(std::int64_t { 42 });

    ASSERT_EQ(members.size(), 1);
    ASSERT_TRUE(members.front());
    ASSERT_TRUE(std::holds_alternative<std::shared_ptr<TgBot::ChatMemberAdministrator>>(members.front()->value));
    const auto& administrator = std::get<std::shared_ptr<TgBot::ChatMemberAdministrator>>(members.front()->value);
    ASSERT_TRUE(administrator);
    EXPECT_TRUE(administrator->canBeEdited);
    EXPECT_TRUE(administrator->canManageChat);
    EXPECT_TRUE(administrator->canDeleteMessages);
    EXPECT_TRUE(administrator->canRestrictMembers);
    EXPECT_TRUE(administrator->canChangeInfo);
    EXPECT_TRUE(administrator->canInviteUsers);
}

TEST(Api, SerializesRequiredVariantArgumentsAndOmitsEmptyOptionalArguments) {
    HttpClientMock httpClient;
    httpClient.response = R"({"ok":true,"result":true})";
    TgBot::Api api("token", httpClient, "https://api.telegram.org");

    EXPECT_TRUE(api.sendChatAction(std::int64_t { 42 }, "typing"));

    ASSERT_EQ(httpClient.requestFields.size(), 2);
    EXPECT_EQ(httpClient.requestFields[0].name, "chat_id");
    EXPECT_EQ(std::get<std::string>(httpClient.requestFields[0].value), "42");
    EXPECT_EQ(httpClient.requestFields[1].name, "action");
    EXPECT_EQ(std::get<std::string>(httpClient.requestFields[1].value), "typing");
}

TEST(Api, SerializesStringVariantAndPresentOptionalArguments) {
    HttpClientMock httpClient;
    httpClient.response = R"({"ok":true,"result":true})";
    TgBot::Api api("token", httpClient, "https://api.telegram.org");

    EXPECT_TRUE(api.sendChatAction("@channel", "upload_photo", 7, "business-id"));

    ASSERT_EQ(httpClient.requestFields.size(), 4);
    EXPECT_EQ(httpClient.requestFields[0].name, "chat_id");
    EXPECT_EQ(std::get<std::string>(httpClient.requestFields[0].value), "@channel");
    EXPECT_EQ(httpClient.requestFields[1].name, "action");
    EXPECT_EQ(std::get<std::string>(httpClient.requestFields[1].value), "upload_photo");
    EXPECT_EQ(httpClient.requestFields[2].name, "message_thread_id");
    EXPECT_EQ(std::get<std::string>(httpClient.requestFields[2].value), "7");
    EXPECT_EQ(httpClient.requestFields[3].name, "business_connection_id");
    EXPECT_EQ(std::get<std::string>(httpClient.requestFields[3].value), "business-id");
}

TEST(Api, SerializesOptionalFileIdStoredInsideVariant) {
    HttpClientMock httpClient;
    httpClient.response = R"({"ok":true,"result":{"message_id":1,"date":2,"chat":{"id":3,"type":"private"}}})";
    TgBot::Api api("token", httpClient, "https://api.telegram.org");
    const std::variant<std::shared_ptr<TgBot::InputFile>, std::string> animation { std::string("animation-id") };
    const std::variant<std::shared_ptr<TgBot::InputFile>, std::string> thumbnail { std::string("thumbnail-id") };

    const auto message = api.sendAnimation(std::int64_t { 42 }, animation, 0, 0, 0, thumbnail);

    ASSERT_TRUE(message);
    ASSERT_EQ(httpClient.requestFields.size(), 3);
    EXPECT_EQ(httpClient.requestFields[0].name, "chat_id");
    EXPECT_EQ(std::get<std::string>(httpClient.requestFields[0].value), "42");
    EXPECT_EQ(httpClient.requestFields[1].name, "animation");
    EXPECT_EQ(std::get<std::string>(httpClient.requestFields[1].value), "animation-id");
    EXPECT_EQ(httpClient.requestFields[2].name, "thumbnail");
    EXPECT_EQ(std::get<std::string>(httpClient.requestFields[2].value), "thumbnail-id");
}

TEST(Api, SerializesArgumentObject) {
    HttpClientMock httpClient;
    httpClient.response = R"({"ok":true,"result":{"message_id":1,"date":2,"chat":{"id":3,"type":"private"}}})";
    TgBot::Api api("token", httpClient, "https://api.telegram.org");
    TgBot::SendMessageArgs args;
    args.chatId = std::int64_t { 42 };
    args.text = "text";
    args.businessConnectionId = "business-id";

    const auto message = api.sendMessage(args);

    ASSERT_TRUE(message);
    ASSERT_EQ(httpClient.requestFields.size(), 3);
    EXPECT_EQ(httpClient.requestFields[0].name, "chat_id");
    EXPECT_EQ(httpClient.requestFields[1].name, "text");
    EXPECT_EQ(httpClient.requestFields[2].name, "business_connection_id");
    EXPECT_EQ(std::get<std::string>(httpClient.requestFields[2].value), "business-id");
}

TEST(Api, ArgumentObjectPreservesAdjacentBooleanParameterOrder) {
    using Args = TgBot::PromoteChatMemberArgs;

    HttpClientMock httpClient;
    httpClient.response = R"({"ok":true,"result":true})";
    TgBot::Api api("token", httpClient, "https://api.telegram.org");
    const std::vector<std::pair<bool Args::*, std::string>> cases {
        { &Args::canChangeInfo, "can_change_info" },
        { &Args::canPostMessages, "can_post_messages" },
        { &Args::canEditMessages, "can_edit_messages" },
        { &Args::canDeleteMessages, "can_delete_messages" },
        { &Args::canInviteUsers, "can_invite_users" },
        { &Args::canPinMessages, "can_pin_messages" },
        { &Args::canPromoteMembers, "can_promote_members" },
        { &Args::isAnonymous, "is_anonymous" },
        { &Args::canManageChat, "can_manage_chat" },
        { &Args::canManageVideoChats, "can_manage_video_chats" },
        { &Args::canRestrictMembers, "can_restrict_members" },
        { &Args::canManageTopics, "can_manage_topics" },
        { &Args::canPostStories, "can_post_stories" },
        { &Args::canEditStories, "can_edit_stories" },
        { &Args::canDeleteStories, "can_delete_stories" },
        { &Args::canManageDirectMessages, "can_manage_direct_messages" },
        { &Args::canManageTags, "can_manage_tags" },
    };

    for (const auto& [member, wireName] : cases) {
        Args args;
        args.chatId = std::int64_t { 42 };
        args.userId = 7;
        args.*member = true;

        EXPECT_TRUE(api.promoteChatMember(args));

        ASSERT_EQ(httpClient.requestFields.size(), 3) << wireName;
        EXPECT_EQ(httpClient.requestFields[0].name, "chat_id") << wireName;
        EXPECT_EQ(httpClient.requestFields[1].name, "user_id") << wireName;
        EXPECT_EQ(httpClient.requestFields[2].name, wireName) << wireName;
        EXPECT_EQ(std::get<std::string>(httpClient.requestFields[2].value), "1") << wireName;
    }
}

TEST(Api, ArgumentObjectPreservesLegacyDefaults) {
    HttpClientMock httpClient;
    httpClient.response = R"({"ok":true,"result":true})";
    TgBot::Api api("token", httpClient, "https://api.telegram.org");
    TgBot::BanChatMemberArgs args;
    args.chatId = std::int64_t { 42 };
    args.userId = 7;

    EXPECT_TRUE(api.banChatMember(args));

    ASSERT_EQ(httpClient.requestFields.size(), 3);
    EXPECT_EQ(httpClient.requestFields[0].name, "chat_id");
    EXPECT_EQ(httpClient.requestFields[1].name, "user_id");
    EXPECT_EQ(httpClient.requestFields[2].name, "revoke_messages");
    EXPECT_EQ(std::get<std::string>(httpClient.requestFields[2].value), "1");
}

TEST(Api, SerializesWebhookFileAndStructuredArguments) {
    HttpClientMock httpClient;
    httpClient.response = R"({"ok":true,"result":true})";
    TgBot::Api api("token", httpClient, "https://api.telegram.org");
    auto certificate = std::make_shared<TgBot::InputFile>();
    certificate->data = "certificate-data";
    certificate->mimeType = "application/x-pem-file";
    certificate->fileName = "certificate.pem";

    EXPECT_TRUE(api.setWebhook("https://example.com/hook", certificate, 25, { "message", "callback_query" },
                               "192.0.2.1", true, "secret"));

    ASSERT_EQ(httpClient.requestFields.size(), 7);
    EXPECT_EQ(httpClient.requestFields[0].name, "url");
    EXPECT_EQ(std::get<std::string>(httpClient.requestFields[0].value), "https://example.com/hook");
    EXPECT_EQ(httpClient.requestFields[1].name, "certificate");
    const auto& file = std::get<TgBot::HttpFile>(httpClient.requestFields[1].value);
    EXPECT_EQ(file.data, "certificate-data");
    EXPECT_EQ(file.mimeType, "application/x-pem-file");
    EXPECT_EQ(file.fileName, "certificate.pem");
    EXPECT_EQ(httpClient.requestFields[2].name, "max_connections");
    EXPECT_EQ(std::get<std::string>(httpClient.requestFields[2].value), "25");
    EXPECT_EQ(httpClient.requestFields[3].name, "allowed_updates");
    EXPECT_EQ(std::get<std::string>(httpClient.requestFields[3].value), R"(["message","callback_query"])");
    EXPECT_EQ(httpClient.requestFields[4].name, "ip_address");
    EXPECT_EQ(std::get<std::string>(httpClient.requestFields[4].value), "192.0.2.1");
    EXPECT_EQ(httpClient.requestFields[5].name, "drop_pending_updates");
    EXPECT_EQ(std::get<std::string>(httpClient.requestFields[5].value), "1");
    EXPECT_EQ(httpClient.requestFields[6].name, "secret_token");
    EXPECT_EQ(std::get<std::string>(httpClient.requestFields[6].value), "secret");
}

TEST(Api, SendMediaGroupUploadsNamedAttachments) {
    HttpClientMock httpClient;
    httpClient.response = R"({"ok":true,"result":[]})";
    TgBot::Api api("token", httpClient, "https://api.telegram.org");
    auto media = std::make_shared<TgBot::InputMediaPhoto>();
    media->media = "attach://photo";
    auto file = std::make_shared<TgBot::InputFile>();
    file->data = "photo-data";
    file->mimeType = "image/jpeg";
    file->fileName = "photo.jpg";
    TgBot::SendMediaGroupArgs args;
    args.chatId = std::int64_t { 42 };
    args.media = { media };
    args.attachments = { { "photo", file } };

    EXPECT_TRUE(api.sendMediaGroup(args).empty());

    ASSERT_EQ(httpClient.requestFields.size(), 3);
    EXPECT_EQ(httpClient.requestFields[0].name, "chat_id");
    EXPECT_EQ(httpClient.requestFields[1].name, "media");
    const auto mediaJson = nlohmann::json::parse(std::get<std::string>(httpClient.requestFields[1].value));
    ASSERT_EQ(mediaJson.size(), 1);
    EXPECT_EQ(mediaJson[0].at("type"), "photo");
    EXPECT_EQ(mediaJson[0].at("media"), "attach://photo");
    EXPECT_EQ(httpClient.requestFields[2].name, "photo");
    const auto& uploaded = std::get<TgBot::HttpFile>(httpClient.requestFields[2].value);
    EXPECT_EQ(uploaded.data, "photo-data");
    EXPECT_EQ(uploaded.mimeType, "image/jpeg");
    EXPECT_EQ(uploaded.fileName, "photo.jpg");

    EXPECT_TRUE(api.sendMediaGroup(std::int64_t { 42 }, args.media).empty());
    ASSERT_EQ(httpClient.requestFields.size(), 2);
}

TEST(Api, EditMessageMediaUploadsNamedAttachment) {
    HttpClientMock httpClient;
    httpClient.response = R"({"ok":true,"result":{"message_id":1,"date":2,"chat":{"id":3,"type":"private"}}})";
    TgBot::Api api("token", httpClient, "https://api.telegram.org");
    auto photo = std::make_shared<TgBot::InputMediaPhoto>();
    photo->media = "attach://photo";
    auto media = std::make_shared<TgBot::InputMedia>();
    media->value = photo;
    auto file = std::make_shared<TgBot::InputFile>();
    file->data = "photo-data";
    file->mimeType = "image/jpeg";
    file->fileName = "photo.jpg";

    TgBot::EditMessageMediaArgs args;
    args.media = media;
    args.chatId = std::int64_t { 42 };
    args.messageId = 7;
    args.attachments = { { "photo", file } };

    ASSERT_NE(api.editMessageMedia(args), nullptr);

    ASSERT_EQ(httpClient.requestFields.size(), 4);
    EXPECT_EQ(httpClient.requestFields[0].name, "media");
    EXPECT_EQ(httpClient.requestFields[1].name, "chat_id");
    EXPECT_EQ(httpClient.requestFields[2].name, "message_id");
    EXPECT_EQ(httpClient.requestFields[3].name, "photo");
}

TEST(Api, RejectsInvalidNamedAttachments) {
    HttpClientMock httpClient;
    httpClient.response = R"({"ok":true,"result":[]})";
    TgBot::Api api("token", httpClient, "https://api.telegram.org");
    auto media = std::make_shared<TgBot::InputMediaPhoto>();
    media->media = "attach://photo";
    auto file = std::make_shared<TgBot::InputFile>();
    TgBot::SendMediaGroupArgs args;
    args.chatId = std::int64_t { 42 };
    args.media = { media };

    args.attachments = { { "", file } };
    EXPECT_THROW(api.sendMediaGroup(args), std::invalid_argument);

    args.attachments = { { "photo", nullptr } };
    EXPECT_THROW(api.sendMediaGroup(args), std::invalid_argument);

    args.attachments = { { "photo", file }, { "photo", file } };
    EXPECT_THROW(api.sendMediaGroup(args), std::invalid_argument);

    args.attachments = { { "chat_id", file } };
    EXPECT_THROW(api.sendMediaGroup(args), std::invalid_argument);
}

TEST(Api, SerializesFileStoredInsideVariant) {
    HttpClientMock httpClient;
    httpClient.response = R"({"ok":true,"result":{"message_id":1,"date":2,"chat":{"id":3,"type":"private"}}})";
    TgBot::Api api("token", httpClient, "https://api.telegram.org");
    auto audio = std::make_shared<TgBot::InputFile>();
    audio->data = "audio-data";
    audio->mimeType = "audio/mpeg";
    audio->fileName = "audio.mp3";

    const auto message = api.sendAudio(std::int64_t { 42 }, audio);

    ASSERT_TRUE(message);
    EXPECT_EQ(message->messageId, 1);
    ASSERT_EQ(httpClient.requestFields.size(), 2);
    EXPECT_EQ(httpClient.requestFields[0].name, "chat_id");
    EXPECT_EQ(httpClient.requestFields[1].name, "audio");
    const auto& file = std::get<TgBot::HttpFile>(httpClient.requestFields[1].value);
    EXPECT_EQ(file.data, "audio-data");
    EXPECT_EQ(file.mimeType, "audio/mpeg");
    EXPECT_EQ(file.fileName, "audio.mp3");
    EXPECT_FALSE(file.filePath);
}

TEST(Api, SerializesStreamingFilePathInsideVariant) {
    HttpClientMock httpClient;
    httpClient.response = R"({"ok":true,"result":{"message_id":1,"date":2,"chat":{"id":3,"type":"private"}}})";
    TgBot::Api api("token", httpClient, "https://api.telegram.org");
    const auto document = TgBot::InputFile::fromFile("files/document.pdf", "application/pdf");

    ASSERT_TRUE(api.sendDocument(std::int64_t { 42 }, document));

    ASSERT_EQ(httpClient.requestFields.size(), 2);
    const auto& file = std::get<TgBot::HttpFile>(httpClient.requestFields[1].value);
    EXPECT_TRUE(file.data.empty());
    EXPECT_EQ(file.mimeType, "application/pdf");
    EXPECT_EQ(file.fileName, "document.pdf");
    EXPECT_EQ(file.filePath, "files/document.pdf");
}

TEST(Api, LeavesDocumentedWebhookDefaultToTelegram) {
    HttpClientMock httpClient;
    httpClient.response = R"({"ok":true,"result":true})";
    TgBot::Api api("token", httpClient, "https://api.telegram.org");

    EXPECT_TRUE(api.setWebhook("https://example.com/hook"));

    ASSERT_EQ(httpClient.requestFields.size(), 1);
    EXPECT_EQ(httpClient.requestFields[0].name, "url");
}

TEST(Api, PreservesLegacyParameterOrder) {
    HttpClientMock httpClient;
    httpClient.response = R"({"ok":true,"result":true})";
    TgBot::Api api("token", httpClient, "https://api.telegram.org");

    EXPECT_TRUE(api.setStickerSetTitle("set-name", "Set title"));

    ASSERT_EQ(httpClient.requestFields.size(), 2);
    EXPECT_EQ(httpClient.requestFields[0].name, "name");
    EXPECT_EQ(std::get<std::string>(httpClient.requestFields[0].value), "set-name");
    EXPECT_EQ(httpClient.requestFields[1].name, "title");
    EXPECT_EQ(std::get<std::string>(httpClient.requestFields[1].value), "Set title");
}

TEST(Api, PreservesLegacyDefaults) {
    HttpClientMock httpClient;
    httpClient.response = R"({"ok":true,"result":[]})";
    TgBot::Api api("token", httpClient, "https://api.telegram.org");

    EXPECT_TRUE(api.getUpdates().empty());

    EXPECT_TRUE(httpClient.requestFields.empty());

    httpClient.response = R"({"ok":true,"result":true})";
    EXPECT_TRUE(api.banChatMember(std::int64_t { 42 }, 7));
    ASSERT_EQ(httpClient.requestFields.size(), 3);
    EXPECT_EQ(httpClient.requestFields[2].name, "revoke_messages");
    EXPECT_EQ(std::get<std::string>(httpClient.requestFields[2].value), "1");

    EXPECT_TRUE(api.banChatMember(std::int64_t { 42 }, 7, 0, false));
    ASSERT_EQ(httpClient.requestFields.size(), 3);
    EXPECT_EQ(httpClient.requestFields[2].name, "revoke_messages");
    EXPECT_EQ(std::get<std::string>(httpClient.requestFields[2].value), "0");

    EXPECT_TRUE(api.answerInlineQuery("query", { }, 0));
    ASSERT_EQ(httpClient.requestFields.size(), 3);
    EXPECT_EQ(httpClient.requestFields[2].name, "cache_time");
    EXPECT_EQ(std::get<std::string>(httpClient.requestFields[2].value), "0");
}

TEST(Api, MapsInlineTrueResultToNullLegacyMessage) {
    HttpClientMock httpClient;
    httpClient.response = R"({"ok":true,"result":true})";
    TgBot::Api api("token", httpClient, "https://api.telegram.org");

    EXPECT_EQ(api.editMessageReplyMarkup(), nullptr);
}
