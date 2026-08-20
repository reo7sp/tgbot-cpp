#include <gtest/gtest.h>

#include "tgbot/CurlHttpClient.h"
#include "tgbot/HttpFormField.h"

#include <boost/asio.hpp>
#include <boost/beast/core/flat_buffer.hpp>
#include <boost/beast/http.hpp>

#include <atomic>
#include <chrono>
#include <cstddef>
#include <exception>
#include <filesystem>
#include <fstream>
#include <future>
#include <span>
#include <stdexcept>
#include <string>
#include <string_view>
#include <system_error>
#include <thread>
#include <vector>

namespace {

using Tcp = boost::asio::ip::tcp;
namespace http = boost::beast::http;

class TemporaryFile {
public:
    explicit TemporaryFile(std::string_view contents)
        : path(std::filesystem::temp_directory_path()
               / ("tgbot-cpp-upload-" + std::to_string(std::chrono::steady_clock::now().time_since_epoch().count())
                  + ".bin")) {
        std::ofstream output(path, std::ios::binary);
        output.exceptions(std::ofstream::failbit | std::ofstream::badbit);
        output.write(contents.data(), static_cast<std::streamsize>(contents.size()));
    }

    ~TemporaryFile() {
        std::error_code error;
        std::filesystem::remove(path, error);
    }

    const std::filesystem::path path;
};

void expectCancelledRequest(const bool includePath, const std::string& expectedMessage) {
    boost::asio::io_context ioContext;
    Tcp::acceptor acceptor(ioContext, Tcp::endpoint(Tcp::v4(), 0));
    Tcp::socket socket(ioContext);
    std::promise<boost::system::error_code> acceptedPromise;
    auto accepted = acceptedPromise.get_future();

    acceptor.async_accept(socket, [&](const boost::system::error_code& error) {
        acceptedPromise.set_value(error);
    });
    std::thread serverThread([&] {
        ioContext.run();
    });

    TgBot::CurlHttpClient httpClient;
    httpClient._timeout = 2;
    const auto port = acceptor.local_endpoint().port();
    const std::string address = "127.0.0.1:" + std::to_string(port);
    const std::string url = includePath ? "http://" + address + "/getUpdates" : address;
    std::exception_ptr exception;
    std::thread requestThread([&] {
        try {
            httpClient.makeRequest(url, std::span<const TgBot::HttpFormField> { });
        } catch (...) {
            exception = std::current_exception();
        }
    });

    const auto acceptStatus = accepted.wait_for(std::chrono::seconds(2));
    if (acceptStatus != std::future_status::ready) {
        boost::system::error_code error;
        acceptor.close(error);
        socket.close(error);
        ioContext.stop();
        httpClient.cancel(true);
        requestThread.join();
        serverThread.join();
        FAIL() << "CurlHttpClient did not connect to the local server";
        return;
    }

    const auto acceptError = accepted.get();
    if (acceptError) {
        httpClient.cancel(true);
        requestThread.join();
        serverThread.join();
        FAIL() << "Local server failed to accept the request: " << acceptError.message();
        return;
    }

    httpClient.cancel();
    requestThread.join();

    boost::system::error_code error;
    socket.close(error);
    serverThread.join();

    ASSERT_NE(exception, nullptr);
    try {
        std::rethrow_exception(exception);
    } catch (const TgBot::RequestCancelled& cancelled) {
        EXPECT_EQ(cancelled.what(), expectedMessage);
    } catch (...) {
        FAIL() << "Expected TgBot::RequestCancelled";
    }
}

http::request<http::string_body> captureMultipartRequest(std::span<const TgBot::HttpFormField> fields) {
    boost::asio::io_context ioContext;
    Tcp::acceptor acceptor(ioContext, Tcp::endpoint(Tcp::v4(), 0));
    std::promise<http::request<http::string_body>> requestPromise;
    auto capturedRequest = requestPromise.get_future();
    std::thread serverThread([&] {
        try {
            Tcp::socket socket(ioContext);
            acceptor.accept(socket);
            boost::beast::flat_buffer buffer;
            http::request<http::string_body> request;
            http::read(socket, buffer, request);

            http::response<http::string_body> response(http::status::ok, 11);
            response.body() = "ok";
            response.prepare_payload();
            http::write(socket, response);
            requestPromise.set_value(std::move(request));
        } catch (...) {
            requestPromise.set_exception(std::current_exception());
        }
    });

    TgBot::CurlHttpClient httpClient;
    const auto port = acceptor.local_endpoint().port();
    try {
        if (httpClient.makeRequest("http://127.0.0.1:" + std::to_string(port), fields) != "ok") {
            throw std::runtime_error("Local HTTP server returned an unexpected response");
        }
    } catch (...) {
        acceptor.close();
        serverThread.join();
        throw;
    }
    serverThread.join();

    return capturedRequest.get();
}

TEST(CurlHttpClient, CancelWithoutMethodThrowsRequestCancelled) {
    expectCancelledRequest(false, "request cancelled");
}

TEST(CurlHttpClient, CancelWithMethodThrowsRequestCancelledWithMethodName) {
    expectCancelledRequest(true, "request cancelled: getUpdates");
}

TEST(CurlHttpClient, EternalCancellationIsObservable) {
    TgBot::CurlHttpClient httpClient;

    EXPECT_FALSE(httpClient.isEternalCancelled());
    EXPECT_EQ(httpClient.getRequestMaxRetries(), 3);
    EXPECT_EQ(httpClient.getRequestBackoffSeconds(), 1);

    httpClient.cancel(true);

    EXPECT_TRUE(httpClient.isEternalCancelled());
}

TEST(CurlHttpClient, SendsBinaryMultipartFileWithMetadata) {
    const std::string binaryData("a\0b", 3);
    const std::vector<TgBot::HttpFormField> fields {
        { "chat_id", "42" },
        { "photo", TgBot::HttpFile { binaryData, "application/octet-stream", "photo.bin" } },
    };

    const auto request = captureMultipartRequest(fields);
    EXPECT_EQ(request.method(), http::verb::post);
    EXPECT_NE(std::string(request[http::field::content_type]).find("multipart/form-data; boundary="),
              std::string::npos);
    EXPECT_NE(request.body().find("name=\"chat_id\""), std::string::npos);
    EXPECT_NE(request.body().find("name=\"photo\"; filename=\"photo.bin\""), std::string::npos);
    EXPECT_NE(request.body().find("Content-Type: application/octet-stream"), std::string::npos);
    EXPECT_NE(request.body().find(binaryData), std::string::npos);
}

TEST(CurlHttpClient, StreamsMultipartFileFromDisk) {
    const std::string binaryData("streamed\0data", 13);
    const TemporaryFile temporaryFile(binaryData);
    const std::vector<TgBot::HttpFormField> fields {
        { "document", TgBot::HttpFile { "", "application/octet-stream", "document.bin", temporaryFile.path.string() } },
    };

    const auto request = captureMultipartRequest(fields);

    EXPECT_EQ(request.method(), http::verb::post);
    EXPECT_NE(request.body().find("name=\"document\"; filename=\"document.bin\""), std::string::npos);
    EXPECT_NE(request.body().find("Content-Type: application/octet-stream"), std::string::npos);
    EXPECT_NE(request.body().find(binaryData), std::string::npos);
}

TEST(CurlHttpClient, SupportsConcurrentMultipartRequests) {
    constexpr std::size_t requestCount = 8;

    boost::asio::io_context ioContext;
    Tcp::acceptor acceptor(ioContext, Tcp::endpoint(Tcp::v4(), 0));
    std::exception_ptr serverException;
    std::thread serverThread([&] {
        try {
            for (std::size_t index = 0; index < requestCount; ++index) {
                Tcp::socket socket(ioContext);
                acceptor.accept(socket);

                boost::beast::flat_buffer buffer;
                http::request<http::string_body> request;
                http::read(socket, buffer, request);

                http::response<http::string_body> response(http::status::ok, request.version());
                response.body() = request.body();
                response.prepare_payload();
                http::write(socket, response);
            }
        } catch (...) {
            serverException = std::current_exception();
        }
    });

    TgBot::CurlHttpClient httpClient;
    const std::string url = "http://127.0.0.1:" + std::to_string(acceptor.local_endpoint().port());
    std::vector<std::string> responses(requestCount);
    std::vector<std::exception_ptr> exceptions(requestCount);
    std::vector<std::thread> requestThreads;
    std::atomic<std::size_t> readyCount { 0 };
    std::atomic<bool> start { false };

    requestThreads.reserve(requestCount);
    for (std::size_t index = 0; index < requestCount; ++index) {
        requestThreads.emplace_back([&, index] {
            readyCount.fetch_add(1);
            readyCount.notify_one();
            start.wait(false);

            try {
                const std::string payload = "payload-" + std::to_string(index);
                const std::vector<TgBot::HttpFormField> fields {
                    { "document",
                      TgBot::HttpFile { payload, "application/octet-stream",
                                        "document-" + std::to_string(index) + ".bin" } },
                };
                responses[index] = httpClient.makeRequest(url + "/request/" + std::to_string(index), fields);
            } catch (...) {
                exceptions[index] = std::current_exception();
            }
        });
    }

    auto ready = readyCount.load();
    while (ready != requestCount) {
        readyCount.wait(ready);
        ready = readyCount.load();
    }
    start.store(true);
    start.notify_all();

    for (auto& thread : requestThreads) {
        thread.join();
    }
    serverThread.join();

    ASSERT_EQ(serverException, nullptr);
    for (std::size_t index = 0; index < requestCount; ++index) {
        EXPECT_EQ(exceptions[index], nullptr);
        EXPECT_NE(responses[index].find("filename=\"document-" + std::to_string(index) + ".bin\""), std::string::npos);
        EXPECT_NE(responses[index].find("payload-" + std::to_string(index)), std::string::npos);
    }
}

} // namespace
