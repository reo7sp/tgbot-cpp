#ifndef TGBOT_TGHTTPSERVER_H
#define TGBOT_TGHTTPSERVER_H

#include "tgbot/Bot.h"
#include "tgbot/EventHandler.h"
#include "tgbot/TgTypeParser.h"
#include "tgbot/net/HttpServer.h"

#include <string>
#include <unordered_map>
#include <utility>

namespace TgBot {

    template<typename Protocol>
    class TgWebhookServer : public HttpServer<Protocol> {

    public:
        TgWebhookServer(
            const typename boost::asio::basic_socket_acceptor<Protocol>::endpoint_type& endpoint, 
            const typename HttpServer<Protocol>::ServerHandler& handler
        ) = delete;

        TgWebhookServer(
            const typename boost::asio::basic_socket_acceptor<Protocol>::endpoint_type& endpoint,
            const EventHandler& eventHandler,
            const bool request_must_contain_a_secret_token = false
        )
            : HttpServer<Protocol>(
                endpoint,
                [this](const std::string& _1, const std::unordered_map<std::string, std::string>& _2) { return _handle(_1, _2); }
                )
            , _eventHandler(eventHandler)
            , _tgTypeParser()
            , _request_must_contain_a_secret_token(request_must_contain_a_secret_token)
        {
        }

        TgWebhookServer(
            const typename boost::asio::basic_socket_acceptor<Protocol>::endpoint_type& endpoint,
            const Bot& bot,
            const bool request_must_contain_a_secret_token = false)
            : TgWebhookServer(endpoint, bot.getEventHandler(), request_must_contain_a_secret_token)
        {
        }


    private:
        std::string _handle(const std::string& data, const std::unordered_map<std::string, std::string>& headers) {
            //Content-Type: application/json
            //headers.count("X-Telegram-Bot-Api-Secret-Token")

            if (headers.at(HEADER_METHOD) == METHOD_POST && headers.at(HEADER_CONTENT_TYPE) == CONTENT_TYPE_JSON)
            {
                std::string token = "";
                if (_request_must_contain_a_secret_token)
                {
                    auto it = headers.find(HEADER_SECRET_TOKEN);
                    if (it == headers.end())
                    {
                        return HttpServer<Protocol>::_httpParser.generateResponse("Bad request", "text/plain", 400, "Bad request", false);
                    }

                    token = it->second;
                }

                _eventHandler.handleUpdate(_tgTypeParser.parseJsonAndGetUpdate(_tgTypeParser.parseJson(data)), std::move(token));
            }
            return HttpServer<Protocol>::_httpParser.generateResponse("", "text/plain", 200, "OK", false);
            

            //if (headers.at("_method") == "POST" && headers.at("_path") == _path) {
            //    _eventHandler.handleUpdate(_tgTypeParser.parseJsonAndGetUpdate(_tgTypeParser.parseJson(data)));
            //}
            //return HttpServer<Protocol>::_httpParser.generateResponse("", "text/plain", 200, "OK", false);
        }

        const EventHandler& _eventHandler;
        const TgTypeParser _tgTypeParser;
        const bool _request_must_contain_a_secret_token;

        inline static const char HEADER_SECRET_TOKEN[] = "X-Telegram-Bot-Api-Secret-Token";
        inline static const char HEADER_METHOD[] = "_method";
        inline static const char HEADER_CONTENT_TYPE[] = "Content-Type";

        inline static const char METHOD_POST[] = "POST";
        inline static const char CONTENT_TYPE_JSON[] = "application/json";
    };

}

#endif //TGBOT_TGHTTPSERVER_H
