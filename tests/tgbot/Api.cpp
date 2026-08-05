#include <gtest/gtest.h>

#include "tgbot/Api.h"
#include "tgbot/HttpClient.h"
#include "tgbot/TgException.h"
#include "tgbot/Types.h"

#include <span>
#include <string>
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
