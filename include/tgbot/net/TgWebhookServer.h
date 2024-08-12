#ifndef TGBOT_TGHTTPSERVER_H
#define TGBOT_TGHTTPSERVER_H

#include "tgbot/Bot.h"
#include "tgbot/EventHandler.h"
#include "tgbot/TgTypeParser.h"
#include "tgbot/net/HttpServer.h"

#include <boost/property_tree/json_parser.hpp>
#include <string>
#include <unordered_map>
#include <utility>

namespace TgBot {

template <typename Protocol>
class TgWebhookServer : public HttpServer<Protocol> {

public:
  TgWebhookServer(
      const typename boost::asio::basic_socket_acceptor<Protocol>::endpoint_type
          &endpoint,
      const typename HttpServer<Protocol>::ServerHandler &handler) = delete;

  TgWebhookServer(
      const typename boost::asio::basic_socket_acceptor<Protocol>::endpoint_type
          &endpoint,
      std::string path, const EventHandler &eventHandler)
      : HttpServer<Protocol>(
            endpoint,
            [this](const std::string &_1,
                   const std::unordered_map<std::string, std::string> &_2) {
              return _handle(_1, _2);
            }),
        _path(std::move(path)), _eventHandler(eventHandler) {}

  TgWebhookServer(
      const typename boost::asio::basic_socket_acceptor<Protocol>::endpoint_type
          &endpoint,
      const Bot &bot)
      : TgWebhookServer(endpoint, "/" + bot.getToken(), bot.getEventHandler()) {
  }

private:
  std::string
  _handle(const std::string &data,
          const std::unordered_map<std::string, std::string> &headers) {
    if (headers.at("_method") == "POST" && headers.at("_path") == _path) {
      std::istringstream iss(data);
      boost::property_tree::ptree pt;
      boost::property_tree::read_json(iss, pt);
      _eventHandler.handleUpdate(parse<Update>(pt));
    }
    return HttpServer<Protocol>::_httpParser.generateResponse("", "text/plain",
                                                              200, "OK", false);
  }

  const std::string _path;
  const EventHandler &_eventHandler;
};

} // namespace TgBot

#endif // TGBOT_TGHTTPSERVER_H
