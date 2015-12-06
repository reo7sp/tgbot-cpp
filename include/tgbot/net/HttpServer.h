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

#ifndef TGBOT_HTTPSERVER_H
#define TGBOT_HTTPSERVER_H

#include <string>

#include <boost/asio.hpp>

#include "tgbot/net/HttpParser.h"

namespace TgBot {

/**
 * This class handles HTTP requests from the Internet.
 * @ingroup net
 */
template<typename Protocol>
class HttpServer {

protected:
	class Connection;

public:
	typedef std::function<std::string (const std::string&, const std::map<std::string, std::string>)> ServerHandler;

	HttpServer(std::shared_ptr<boost::asio::basic_socket_acceptor<Protocol>> acceptor, const ServerHandler& handler) : _acceptor(acceptor), _handler(handler) {
	}

	/**
	 * Starts receiving new connections.
	 */
	void start() {
		std::shared_ptr<boost::asio::basic_stream_socket<Protocol>> socket(new boost::asio::basic_stream_socket<Protocol>(_acceptor->get_io_service()));
		std::shared_ptr<Connection> connection(new Connection(socket, _handler));
		_acceptor->async_accept(*connection->socket, [this, connection]() {
			connection->start();
			start();
		});
		_ioService.run();
	}

	/**
	 * Stops receiving new connections.
	 */
	void stop() {
		_ioService.stop();
	}

protected:
	class Connection {

	public:
		Connection(std::shared_ptr<boost::asio::basic_stream_socket<Protocol>>& socket, const ServerHandler& handler) : socket(socket), _handler(handler) {
			boost::asio::socket_base::keep_alive option(true);
			socket.set_option(option);
		}

		void start() {
			data.reserve(10240);
			socket->async_receive(data, [this]() {
				std::map<std::string, std::string> headers;
				std::string body = HttpParser::getInstance().parseResponse(data, headers);
				socket->async_send(_handler(body, headers));
			});
		}

		std::shared_ptr<boost::asio::basic_stream_socket<Protocol>> socket;
		std::string data;

	protected:
		const ServerHandler _handler;
	};

	boost::asio::io_service _ioService;
	std::shared_ptr<boost::asio::basic_socket_acceptor<Protocol>> _acceptor;
	const ServerHandler _handler;
};

}

#endif //TGBOT_HTTPSERVER_H
