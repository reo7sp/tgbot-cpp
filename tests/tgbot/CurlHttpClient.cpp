#include <gtest/gtest.h>

#include "tgbot/CurlHttpClient.h"

#include <boost/asio.hpp>

#include <chrono>
#include <exception>
#include <future>
#include <span>
#include <string>
#include <thread>

namespace {

using Tcp = boost::asio::ip::tcp;

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

TEST(CurlHttpClient, CancelWithoutMethodThrowsRequestCancelled) {
    expectCancelledRequest(false, "request cancelled");
}

TEST(CurlHttpClient, CancelWithMethodThrowsRequestCancelledWithMethodName) {
    expectCancelledRequest(true, "request cancelled: getUpdates");
}

} // namespace
