#include <gtest/gtest.h>

#include "tgbot/HttpServer.h"

#include <boost/asio.hpp>
#include <boost/beast/core/flat_buffer.hpp>
#include <boost/beast/http.hpp>

#include <cstdint>
#include <string>
#include <thread>

namespace {

using Tcp = boost::asio::ip::tcp;

std::uint16_t findAvailablePort() {
    boost::asio::io_context ioContext;
    Tcp::acceptor acceptor(ioContext, Tcp::endpoint(Tcp::v4(), 0));

    return acceptor.local_endpoint().port();
}

boost::beast::http::response<boost::beast::http::string_body> sendRequest(std::uint16_t port, const std::string& body) {
    namespace http = boost::beast::http;

    boost::asio::io_context ioContext;
    Tcp::socket socket(ioContext);
    socket.connect(Tcp::endpoint(boost::asio::ip::address_v4::loopback(), port));

    http::request<http::string_body> request(http::verb::post, "/", 11);
    request.set(http::field::host, "localhost");
    request.keep_alive(true);
    request.body() = body;
    request.prepare_payload();
    http::write(socket, request);

    boost::beast::flat_buffer buffer;
    http::response<http::string_body> response;
    http::read(socket, buffer, response);

    return response;
}

TEST(HttpServer, ClosesConnectionAndAcceptsNextClient) {
    const std::uint16_t port = findAvailablePort();
    std::size_t requestCount = 0;
    TgBot::HttpServer<Tcp>* serverPointer = nullptr;
    TgBot::HttpServer<Tcp> server(Tcp::endpoint(boost::asio::ip::address_v4::loopback(), port),
                                  [&](const std::string& body, const std::unordered_map<std::string, std::string>&) {
                                      if (++requestCount == 2) {
                                          serverPointer->stop();
                                      }

                                      return body;
                                  });
    serverPointer = &server;

    std::thread serverThread([&server] { server.start(); });

    try {
        const auto firstResponse = sendRequest(port, "first");
        EXPECT_EQ(firstResponse.body(), "first");
        EXPECT_EQ(firstResponse[boost::beast::http::field::connection], "close");
        EXPECT_FALSE(firstResponse.keep_alive());

        const auto secondResponse = sendRequest(port, "second");
        EXPECT_EQ(secondResponse.body(), "second");
        EXPECT_EQ(secondResponse[boost::beast::http::field::connection], "close");
        EXPECT_FALSE(secondResponse.keep_alive());
    } catch (...) {
        server.stop();
        serverThread.join();
        throw;
    }

    serverThread.join();
    EXPECT_EQ(requestCount, 2);
}

TEST(HttpServer, AcceptsAnotherClientWhileFirstRequestIsIncomplete) {
    const std::uint16_t port = findAvailablePort();
    TgBot::HttpServer<Tcp>* serverPointer = nullptr;
    TgBot::HttpServer<Tcp> server(Tcp::endpoint(boost::asio::ip::address_v4::loopback(), port),
                                  [&](const std::string& body, const auto&) {
                                      serverPointer->stop();

                                      return body;
                                  });
    serverPointer = &server;
    std::thread serverThread([&server] { server.start(); });

    boost::asio::io_context ioContext;
    Tcp::socket incompleteClient(ioContext);
    incompleteClient.connect(Tcp::endpoint(boost::asio::ip::address_v4::loopback(), port));
    boost::asio::write(incompleteClient, boost::asio::buffer("POST / HTTP/1.1\r\nContent-Length: 10\r\n"));

    const auto response = sendRequest(port, "complete");
    EXPECT_EQ(response.body(), "complete");

    boost::system::error_code error;
    incompleteClient.close(error);
    serverThread.join();
}

} // namespace
