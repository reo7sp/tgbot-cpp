#pragma once

#include <boost/asio.hpp>
#include <boost/asio/signal_set.hpp>
#include <boost/beast/core/flat_buffer.hpp>
#include <boost/beast/http.hpp>

#include <csignal>
#include <exception>
#include <functional>
#include <initializer_list>
#include <memory>
#include <optional>
#include <stdexcept>
#include <string>
#include <string_view>
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
    using ErrorHandler = std::function<void(const std::exception&)>;

    HttpServer(const typename boost::asio::basic_socket_acceptor<Protocol>::endpoint_type& endpoint,
               ServerHandler handler)
        : _acceptor(_ioContext, endpoint)
        , _handler(std::move(handler)) {
    }

    /**
     * @brief Starts receiving connections until stop() is called or one of the configured signals is received.
     * @param errorHandler Called when receiving or handling a request fails.
     * @param signals Process signals that stop the server. Pass an empty list to disable signal handling.
     */
    void start(const ErrorHandler& errorHandler = { }, std::initializer_list<int> signals = { SIGINT, SIGTERM }) {
        _errorHandler = errorHandler;
        try {
            _ioContext.restart();
            if (signals.size() != 0) {
                _signals.emplace(_ioContext);
                for (const int signal : signals) {
                    _signals->add(signal);
                }
                _signals->async_wait([this](const boost::system::error_code& error, int) {
                    if (!error) {
                        stop();
                    }
                });
            }
            accept();
            _ioContext.run();
        } catch (...) {
            _signals.reset();
            _errorHandler = { };
            throw;
        }
        _signals.reset();
        _errorHandler = { };
    }

    /**
     * @brief Stops receiving new connections. Connections already accepted are completed.
     */
    void stop() {
        boost::asio::post(_ioContext, [this] {
            boost::system::error_code error;
            if (_signals) {
                _signals->cancel(error);
            }
            _acceptor.close(error);
        });
    }

private:
    class Connection : public std::enable_shared_from_this<Connection> {
    public:
        Connection(boost::asio::basic_stream_socket<Protocol> socket, ServerHandler handler, ErrorHandler errorHandler)
            : _socket(std::move(socket))
            , _handler(std::move(handler))
            , _errorHandler(std::move(errorHandler)) {
        }

        void start() {
            auto self = this->shared_from_this();
            boost::beast::http::async_read(_socket, _buffer, _request,
                                           [self](const boost::system::error_code& error, std::size_t) {
                                               self->handleRequest(error);
                                           });
        }

    private:
        void handleRequest(const boost::system::error_code& error) {
            namespace http = boost::beast::http;

            if (error == http::error::end_of_stream) {
                close();
                return;
            }
            if (error) {
                reportError(_errorHandler, "error reading HTTP request: " + error.message());
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
                reportError(_errorHandler, "error handling HTTP request: " + std::string(exception.what()));
                _response.result(http::status::internal_server_error);
                _response.body() = "Internal server error";
            }
            _response.prepare_payload();

            auto self = this->shared_from_this();
            http::async_write(_socket, _response, [self](const boost::system::error_code& writeError, std::size_t) {
                if (writeError) {
                    reportError(self->_errorHandler, "error writing HTTP response: " + writeError.message());
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
        const ErrorHandler _errorHandler;
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
                    reportError(_errorHandler, "error accepting HTTP connection: " + error.message());
                    if (_acceptor.is_open()) {
                        accept();
                    }
                } else {
                    accept();
                    std::make_shared<Connection>(std::move(socket), _handler, _errorHandler)->start();
                }
            });
    }

    static void reportError(const ErrorHandler& errorHandler, std::string_view message) {
        const std::runtime_error error { std::string(message) };
        if (errorHandler) {
            errorHandler(error);
        }
    }

    boost::asio::io_context _ioContext;
    std::optional<boost::asio::signal_set> _signals;
    boost::asio::basic_socket_acceptor<Protocol> _acceptor;
    const ServerHandler _handler;
    ErrorHandler _errorHandler;
};

} // namespace TgBot
