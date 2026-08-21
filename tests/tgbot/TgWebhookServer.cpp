#include <gtest/gtest.h>

#include "tgbot/Bot.h"
#include "tgbot/EventBroadcaster.h"
#include "tgbot/EventHandler.h"
#include "tgbot/HttpClient.h"
#include "tgbot/TgWebhookLocalServer.h"
#include "tgbot/TgWebhookTcpServer.h"

#include <boost/asio.hpp>
#include <boost/beast/core/flat_buffer.hpp>
#include <boost/beast/http.hpp>

#include <algorithm>
#include <atomic>
#include <cstdint>
#include <filesystem>
#include <future>
#include <memory>
#include <mutex>
#include <span>
#include <string>
#include <string_view>
#include <thread>
#include <vector>

namespace {

using Tcp = boost::asio::ip::tcp;

constexpr std::string_view defaultUpdateBody
    = R"({"update_id":1,"message":{"message_id":2,"date":0,"chat":{"id":3,"type":"private"},"text":"hello"}})";

class HttpClientStub final : public TgBot::HttpClient {
public:
    std::string makeRequest(const std::string&, std::span<const TgBot::HttpFormField>) const override {
        return { };
    }
};

std::uint16_t findAvailablePort() {
    boost::asio::io_context ioContext;
    Tcp::acceptor acceptor(ioContext, Tcp::endpoint(Tcp::v4(), 0));

    return acceptor.local_endpoint().port();
}

template<typename Protocol>
void sendUpdate(boost::asio::basic_stream_socket<Protocol>& socket, std::string_view path,
                std::string_view body = defaultUpdateBody) {
    namespace http = boost::beast::http;

    http::request<http::string_body> request(http::verb::post, path, 11);
    request.set(http::field::host, "localhost");
    request.body() = body;
    request.prepare_payload();
    http::write(socket, request);

    boost::beast::flat_buffer buffer;
    http::response<http::string_body> response;
    http::read(socket, buffer, response);
    EXPECT_EQ(response.result(), http::status::ok);
}

void sendTcpUpdate(std::uint16_t port, std::string_view path, std::string_view body = defaultUpdateBody) {
    boost::asio::io_context ioContext;
    Tcp::socket socket(ioContext);
    socket.connect(Tcp::endpoint(boost::asio::ip::address_v4::loopback(), port));
    sendUpdate(socket, path, body);
}

TEST(TgWebhookTcpServer, DispatchesOnlyUpdatesSentToConfiguredPath) {
    const std::uint16_t port = findAvailablePort();
    TgBot::EventBroadcaster broadcaster;
    TgBot::EventHandler handler(broadcaster);
    TgBot::TgWebhookTcpServer server(port, "/webhook", handler);
    int messages = 0;
    broadcaster.onAnyMessage([&](const auto&) {
        ++messages;
        server.stop();
    });
    std::thread serverThread([&] {
        server.start({ }, { });
    });

    sendTcpUpdate(port, "/wrong");
    EXPECT_EQ(messages, 0);
    sendTcpUpdate(port, "/webhook");
    serverThread.join();

    EXPECT_EQ(messages, 1);
}

TEST(TgWebhookTcpServer, UsesBotTokenAsDefaultPath) {
    const std::uint16_t port = findAvailablePort();
    HttpClientStub httpClient;
    TgBot::Bot bot("token", httpClient);
    TgBot::TgWebhookTcpServer server(port, bot);
    int messages = 0;
    bot.getEvents().onAnyMessage([&](const auto&) {
        ++messages;
        server.stop();
    });
    std::thread serverThread([&] {
        server.start({ }, { });
    });

    sendTcpUpdate(port, "/token");
    serverThread.join();

    EXPECT_EQ(messages, 1);
}

TEST(TgWebhookTcpServer, KeepsFirstMessageAliveWhileNextListenerRuns) {
    const std::uint16_t port = findAvailablePort();
    TgBot::EventBroadcaster broadcaster;
    TgBot::EventHandler handler(broadcaster);
    TgBot::TgWebhookTcpServer server(port, "/webhook", handler);
    std::promise<TgBot::Message::Ptr> firstMessagePromise;
    std::promise<TgBot::Message::Ptr> secondMessagePromise;
    auto firstMessageFuture = firstMessagePromise.get_future();
    auto secondMessageFuture = secondMessagePromise.get_future();
    std::atomic<bool> secondListenerStarted { false };
    std::atomic<bool> releaseSecondListener { false };
    broadcaster.onAnyMessage([&](const auto& message) {
        if (*message->text == "first") {
            firstMessagePromise.set_value(message);
            return;
        }

        secondMessagePromise.set_value(message);
        secondListenerStarted.store(true);
        secondListenerStarted.notify_one();
        releaseSecondListener.wait(false);
        server.stop();
    });
    std::thread serverThread([&] {
        server.start({ }, { });
    });

    sendTcpUpdate(
        port, "/webhook",
        R"({"update_id":1,"message":{"message_id":1,"date":0,"chat":{"id":3,"type":"private"},"text":"first"}})");
    auto firstMessage = firstMessageFuture.get();
    std::thread secondRequestThread([&] {
        sendTcpUpdate(
            port, "/webhook",
            R"({"update_id":2,"message":{"message_id":2,"date":0,"chat":{"id":3,"type":"private"},"text":"second"}})");
    });

    secondListenerStarted.wait(false);
    auto secondMessage = secondMessageFuture.get();
    EXPECT_EQ(*firstMessage->text, "first");
    EXPECT_EQ(firstMessage->messageId, 1);
    EXPECT_EQ(*secondMessage->text, "second");
    EXPECT_EQ(secondMessage->messageId, 2);

    releaseSecondListener.store(true);
    releaseSecondListener.notify_one();
    secondRequestThread.join();
    serverThread.join();
}

TEST(TgWebhookTcpServer, ReleasesMessageAfterRequestCompletes) {
    const std::uint16_t port = findAvailablePort();
    TgBot::EventBroadcaster broadcaster;
    TgBot::EventHandler handler(broadcaster);
    TgBot::TgWebhookTcpServer server(port, "/webhook", handler);
    std::weak_ptr<TgBot::Message> receivedMessage;
    broadcaster.onAnyMessage([&](const auto& message) {
        receivedMessage = message;
        server.stop();
    });
    std::thread serverThread([&] {
        server.start({ }, { });
    });

    sendTcpUpdate(port, "/webhook");
    serverThread.join();

    EXPECT_TRUE(receivedMessage.expired());
}

TEST(TgWebhookTcpServer, KeepsConcurrentUpdatesIndependent) {
    constexpr std::size_t updateCount = 8;

    const std::uint16_t port = findAvailablePort();
    TgBot::EventBroadcaster broadcaster;
    TgBot::EventHandler handler(broadcaster);
    TgBot::TgWebhookTcpServer server(port, "/webhook", handler);
    std::mutex messagesMutex;
    std::vector<TgBot::Message::Ptr> messages;
    broadcaster.onAnyMessage([&](const auto& message) {
        bool receivedAllUpdates;
        {
            const std::lock_guard lock(messagesMutex);
            messages.push_back(message);
            receivedAllUpdates = messages.size() == updateCount;
        }
        if (receivedAllUpdates) {
            server.stop();
        }
    });
    std::thread serverThread([&] {
        server.start({ }, { });
    });

    std::vector<std::thread> requestThreads;
    requestThreads.reserve(updateCount);
    for (std::size_t index = 0; index < updateCount; ++index) {
        requestThreads.emplace_back([&, index] {
            const std::string body = "{\"update_id\":" + std::to_string(index + 1) + ",\"message\":{\"message_id\":"
                + std::to_string(index + 1) + ",\"date\":0,\"chat\":{\"id\":3,\"type\":\"private\"},\"text\":\"message-"
                + std::to_string(index + 1) + "\"}}";
            sendTcpUpdate(port, "/webhook", body);
        });
    }

    for (auto& thread : requestThreads) {
        thread.join();
    }
    serverThread.join();

    std::ranges::sort(messages, { }, &TgBot::Message::messageId);
    ASSERT_EQ(messages.size(), updateCount);
    std::vector<std::weak_ptr<TgBot::Message>> weakMessages;
    weakMessages.reserve(updateCount);
    for (std::size_t index = 0; index < updateCount; ++index) {
        EXPECT_EQ(messages[index]->messageId, index + 1);
        EXPECT_EQ(*messages[index]->text, "message-" + std::to_string(index + 1));
        weakMessages.push_back(messages[index]);
    }

    messages.clear();

    for (const auto& message : weakMessages) {
        EXPECT_TRUE(message.expired());
    }
}

#if defined(BOOST_ASIO_HAS_LOCAL_SOCKETS) && !defined(_WIN32)

TEST(TgWebhookLocalServer, DispatchesUpdateFromUnixSocket) {
    TgBot::EventBroadcaster broadcaster;
    TgBot::EventHandler handler(broadcaster);
    const std::filesystem::path socketPath = std::filesystem::temp_directory_path()
        / ("tgbot-cpp-webhook-" + std::to_string(reinterpret_cast<std::uintptr_t>(&broadcaster)) + ".sock");
    TgBot::TgWebhookLocalServer server(socketPath.string(), "/webhook", handler);
    int messages = 0;
    broadcaster.onAnyMessage([&](const auto&) {
        ++messages;
        server.stop();
    });
    std::thread serverThread([&] {
        server.start({ }, { });
    });

    boost::asio::io_context ioContext;
    boost::asio::local::stream_protocol::socket socket(ioContext);
    socket.connect(boost::asio::local::stream_protocol::endpoint(socketPath.string()));
    sendUpdate(socket, "/webhook");
    serverThread.join();
    std::filesystem::remove(socketPath);

    EXPECT_EQ(messages, 1);
}

#endif

} // namespace
