#pragma once

#include "tgbot/Bot.h"
#include "tgbot/EventHandler.h"
#include "tgbot/HttpServer.h"

#include <nlohmann/json.hpp>

#include <memory>
#include <string>
#include <unordered_map>
#include <utility>

namespace TgBot {

/**
 * @ingroup net
 */
template<typename Protocol>
class TgWebhookServer : public HttpServer<Protocol> {
public:
    TgWebhookServer(const typename boost::asio::basic_socket_acceptor<Protocol>::endpoint_type& endpoint,
                    const typename HttpServer<Protocol>::ServerHandler& handler) = delete;

    TgWebhookServer(const typename boost::asio::basic_socket_acceptor<Protocol>::endpoint_type& endpoint,
                    std::string path, const EventHandler& eventHandler)
        : HttpServer<Protocol>(endpoint,
                               [this](const std::string& _1, const std::unordered_map<std::string, std::string>& _2) {
                                   return _handle(_1, _2);
                               })
        , _path(std::move(path))
        , _eventHandler(eventHandler) {
    }

    TgWebhookServer(const typename boost::asio::basic_socket_acceptor<Protocol>::endpoint_type& endpoint,
                    const Bot& bot)
        : TgWebhookServer(endpoint, "/" + bot.getToken(), bot.getEventHandler()) {
    }

private:
    std::string _handle(const std::string& data, const std::unordered_map<std::string, std::string>& headers) {
        if (headers.at("_method") == "POST" && headers.at("_path") == _path) {
            auto update = std::make_shared<Update>();
            nlohmann::json::parse(data).get_to(*update);
            _eventHandler.handleUpdate(update);
        }
        return { };
    }

    const std::string _path;
    const EventHandler& _eventHandler;
};

} // namespace TgBot
