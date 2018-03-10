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

#ifndef TGBOT_TGHTTPSERVER_H
#define TGBOT_TGHTTPSERVER_H

#include "tgbot/Bot.h"
#include "tgbot/EventHandler.h"
#include "tgbot/TgTypeParser.h"
#include "tgbot/net/HttpServer.h"

namespace TgBot {

template<typename Protocol>
class TgWebhookServer : public HttpServer<Protocol> {

public:
	TgWebhookServer(std::shared_ptr<boost::asio::basic_socket_acceptor<Protocol>> acceptor, const typename HttpServer<Protocol>::ServerHandler& handler) = delete;

	TgWebhookServer(std::shared_ptr<boost::asio::basic_socket_acceptor<Protocol>> acceptor, const std::string& path, const EventHandler* eventHandler) :
		HttpServer<Protocol>(acceptor, [eventHandler, &path](const std::string& data, const std::map<std::string, std::string>& headers) -> std::string {
			if (headers.at("method") == "POST" && headers.at("path") == path) {
				eventHandler->handleUpdate(TgTypeParser::getInstance().parseJsonAndGetUpdate(TgTypeParser::getInstance().parseJson(data)));
			}
			return HttpParser::getInstance().generateResponse("");
		})
	{
	}

	TgWebhookServer(std::shared_ptr<boost::asio::basic_socket_acceptor<Protocol>> acceptor, const std::string& path, const Bot& bot) :
		TgWebhookServer(acceptor, path, &bot.getEventHandler())
	{
	}
};

}

#endif //TGBOT_TGHTTPSERVER_H
