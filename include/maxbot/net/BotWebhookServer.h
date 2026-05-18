#ifndef TGBOT_TGHTTPSERVER_H
#define TGBOT_TGHTTPSERVER_H

#include "maxbot/Bot.h"
#include "maxbot/EventHandler.h"
#include "maxbot/BotTypeParser.h"
#include "maxbot/net/HttpServer.h"

#include <string>
#include <unordered_map>
#include <utility>

namespace MaxBot {

template<typename Protocol>
class BotWebhookServer : public HttpServer<Protocol> {

public:
    BotWebhookServer(const typename boost::asio::basic_socket_acceptor<Protocol>::endpoint_type& endpoint, const typename HttpServer<Protocol>::ServerHandler& handler) = delete;

    BotWebhookServer(const typename boost::asio::basic_socket_acceptor<Protocol>::endpoint_type& endpoint, std::string path, const EventHandler& eventHandler)
            : HttpServer<Protocol>(endpoint,
                                   [this](const std::string& _1, const std::unordered_map<std::string, std::string>& _2) { return _handle(_1, _2); }),
              _path(std::move(path)), _eventHandler(eventHandler), _botTypeParser()
    {
    }

    BotWebhookServer(const typename boost::asio::basic_socket_acceptor<Protocol>::endpoint_type& endpoint, const Bot& bot)
            : BotWebhookServer(endpoint, "/" + bot.getToken(), bot.getEventHandler())
    {
    }

private:
    std::string _handle(const std::string& data, const std::unordered_map<std::string, std::string>& headers) {
        if (headers.at("_method") == "POST" && headers.at("_path") == _path) {
            _eventHandler.handleUpdate(_botTypeParser.parseJsonAndGetUpdate(_botTypeParser.parseJson(data)));
        }
        return HttpServer<Protocol>::_httpParser.generateResponse("", "text/plain", 200, "OK", false);
    }

    const std::string _path;
    const EventHandler& _eventHandler;
    const BotTypeParser _botTypeParser;
};

}

#endif //TGBOT_TGHTTPSERVER_H
