#pragma once

#include <boost/asio.hpp>
#include <boost/beast/core/flat_buffer.hpp>
#include <boost/beast/http.hpp>

#include <exception>
#include <functional>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <utility>

namespace TgBot {

/**
 * @brief This class handles HTTP requests from the Internet.
 *
 * @ingroup net
 */
template<typename Protocol>
class HttpServer {

public:
    using ServerHandler
        = std::function<std::string(const std::string&, const std::unordered_map<std::string, std::string>&)>;

    HttpServer(const typename boost::asio::basic_socket_acceptor<Protocol>::endpoint_type& endpoint,
               ServerHandler handler)
        : _acceptor(_ioContext, endpoint)
        , _handler(std::move(handler)) {
    }

    /**
     * @brief Starts receiving new connections.
     */
    void start() {
        _ioContext.restart();
        accept();
        _ioContext.run();
    }

    /**
     * @brief Stops receiving new connections. Connections already accepted are completed.
     */
    void stop() {
        boost::asio::post(_ioContext, [this] {
            boost::system::error_code error;
            _acceptor.close(error);
        });
    }

private:
    class Connection : public std::enable_shared_from_this<Connection> {
    public:
        Connection(boost::asio::basic_stream_socket<Protocol> socket, ServerHandler handler)
            : _socket(std::move(socket))
            , _handler(std::move(handler)) {
        }

        void start() {
            auto self = this->shared_from_this();
            boost::beast::http::async_read(
                _socket, _buffer, _request,
                [self](const boost::system::error_code& error, std::size_t) { self->handleRequest(error); });
        }

    private:
        void handleRequest(const boost::system::error_code& error) {
            namespace http = boost::beast::http;

            if (error == http::error::end_of_stream) {
                close();
                return;
            }
            if (error) {
                std::cerr << "[TgBot] error reading HTTP request: " << error.message() << '\n';
                close();
                return;
            }

            std::unordered_map<std::string, std::string> headers;
            headers.emplace("_method", std::string(_request.method_string()));
            headers.emplace("_path", std::string(_request.target()));
            for (const auto& field : _request) {
                headers.emplace(std::string(field.name_string()), std::string(field.value()));
            }

            _response = { http::status::ok, _request.version() };
            _response.set(http::field::content_type, "text/plain");
            _response.keep_alive(false);
            try {
                _response.body() = _handler(_request.body(), headers);
            } catch (const std::exception& exception) {
                std::cerr << "[TgBot] error handling HTTP request: " << exception.what() << '\n';
                _response.result(http::status::internal_server_error);
                _response.body() = "Internal server error";
            }
            _response.prepare_payload();

            auto self = this->shared_from_this();
            http::async_write(_socket, _response, [self](const boost::system::error_code& writeError, std::size_t) {
                if (writeError) {
                    std::cerr << "[TgBot] error writing HTTP response: " << writeError.message() << '\n';
                }
                self->close();
            });
        }

        void close() {
            boost::system::error_code error;
            _socket.shutdown(boost::asio::socket_base::shutdown_both, error);
            _socket.close(error);
        }

        boost::asio::basic_stream_socket<Protocol> _socket;
        const ServerHandler _handler;
        boost::beast::flat_buffer _buffer;
        boost::beast::http::request<boost::beast::http::string_body> _request;
        boost::beast::http::response<boost::beast::http::string_body> _response;
    };

    void accept() {
        _acceptor.async_accept(
            [this](const boost::system::error_code& error, boost::asio::basic_stream_socket<Protocol> socket) {
                if (error == boost::asio::error::operation_aborted) {
                    return;
                }
                if (error) {
                    std::cerr << "[TgBot] error accepting HTTP connection: " << error.message() << '\n';
                    if (_acceptor.is_open()) {
                        accept();
                    }
                } else {
                    accept();
                    std::make_shared<Connection>(std::move(socket), _handler)->start();
                }
            });
    }

    boost::asio::io_context _ioContext;
    boost::asio::basic_socket_acceptor<Protocol> _acceptor;
    const ServerHandler _handler;
};

} // namespace TgBot
