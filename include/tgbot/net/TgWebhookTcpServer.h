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

#ifndef TGBOT_TGWEBHOOKTCPSERVER_H
#define TGBOT_TGWEBHOOKTCPSERVER_H

#include "tgbot/net/TgWebhookServer.h"

namespace TgBot {

/**
 * This class setups HTTP server for receiving Telegram Update objects from tcp connections.
 * @ingroup net
 */
class TgWebhookTcpServer : public TgWebhookServer<boost::asio::ip::tcp> {

public:
	TgWebhookTcpServer(std::shared_ptr<boost::asio::basic_socket_acceptor<boost::asio::ip::tcp>> acceptor, const std::string& path, EventHandler* eventHandler) = delete;

	TgWebhookTcpServer(unsigned short port, const std::string& path, const EventHandler* eventHandler) :
		TgWebhookServer(std::shared_ptr<boost::asio::basic_socket_acceptor<boost::asio::ip::tcp>>(new boost::asio::ip::tcp::acceptor(_ioService, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port))), path, eventHandler)
	{
	}

	TgWebhookTcpServer(const std::string& path, const Bot& bot) : TgWebhookTcpServer(path, &bot.getEventHandler()) {
	}
};

}

#endif //TGBOT_TGWEBHOOKTCPSERVER_H
