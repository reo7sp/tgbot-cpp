/*
 * Copyright (c) 2015 Oleg Morozenkov
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef TGBOT_CPP_HTTP_H
#define TGBOT_CPP_HTTP_H

#include <string>

#include <boost/asio.hpp>
#include <boost/lexical_cast.hpp>

#include "tgbot/Url.h"

namespace TgBot {

class Http {

public:
    typedef std::function<void (const std::string&)> ServerHandler;

    class Argument {

    public:
        template<typename T>
        Argument(const std::string& name, const T& value, bool isFile = false, const std::string& mimeType = "") :
                name(name), value(boost::lexical_cast<std::string>(value)), isFile(isFile), mimeType(mimeType)
        {
        }

        std::string name;
        std::string value;
        bool isFile = false;
        std::string mimeType;
    };

    std::string makeRequest(const Url& url, const std::vector<Argument>& args);
    void startServer(unsigned short port, const ServerHandler& handler);
    void startServer(const std::string& unixSocketPath, const ServerHandler& handler);
    void stopServer();

private:
    template<typename Protocol>
    class Connection {

    public:
        Connection(Http* http, boost::asio::basic_stream_socket<Protocol>* socket) : http(http), socket(socket) {
        }

        ~Connection() {
            delete socket;
        }

        void start() {
            data.reserve(10240);
            socket->async_receive(data, [this]() {
                size_t headerEnd = data.find("\r\n\r\n");
                if (headerEnd == data.npos) {
                    headerEnd = data.find("\n\n");
                }
                if (headerEnd == data.npos) {
                    headerEnd = 0;
                }
                data.erase(0, headerEnd);
                http->_serverHandler(data);
            });
        }

        Http* http;
        boost::asio::basic_stream_socket<Protocol>* socket;
        std::string data;
    };

    template<typename Protocol>
    class Server {

    public:
        Server(Http* http, boost::asio::basic_socket_acceptor<Protocol>* acceptor) : http(http), acceptor(acceptor) {
        }

        ~Server() {
            delete acceptor;
        }

        void start() {
            boost::asio::basic_stream_socket<Protocol>* socket = new boost::asio::basic_stream_socket<Protocol>(acceptor->get_io_service());
            std::shared_ptr<Http::Connection<Protocol>> connection(new Connection<Protocol>(http, socket));
            acceptor->async_accept(*connection->socket, [this, connection]() {
                connection->start();
                start();
            });
        }

        Http* http;
        boost::asio::basic_socket_acceptor<Protocol>* acceptor;
    };


    boost::asio::io_service _ioService;
    Server<boost::asio::ip::tcp>* _tcpServer = nullptr;
    Server<boost::asio::local::stream_protocol>* _unixSocketServer = nullptr;
    ServerHandler _serverHandler;
};

}

#endif //TGBOT_CPP_HTTP_H
