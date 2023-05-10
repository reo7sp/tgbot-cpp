#ifndef TGBOT_TGWEBHOOKTCPSERVER_H
#define TGBOT_TGWEBHOOKTCPSERVER_H

#include "tgbot/net/TgWebhookServer.h"

#include <string>

namespace TgBot {

/**
 * This class setups HTTP server for receiving Telegram Update objects from tcp connections.
 * @ingroup net
 */
class TgWebhookTcpServer : public TgWebhookServer<boost::asio::ip::tcp> {

public:
    TgWebhookTcpServer(
        unsigned short port, 
        const EventHandler& eventHandler,
        const bool request_must_contain_a_secret_token = false
    )
            : TgWebhookServer<boost::asio::ip::tcp>(
                boost::asio::ip::tcp::endpoint(
                    boost::asio::ip::tcp::v4(), 
                    port
                )
                , eventHandler
                , request_must_contain_a_secret_token
            )
    {
    }

    TgWebhookTcpServer(
        unsigned short port, 
        const Bot& bot,
        const bool request_must_contain_a_secret_token = false
    )
            : TgWebhookServer<boost::asio::ip::tcp>(
                boost::asio::ip::tcp::endpoint(
                    boost::asio::ip::tcp::v4(),
                    port
                )
                , bot
                , request_must_contain_a_secret_token
            )
    {
    }
};

}

#endif //TGBOT_TGWEBHOOKTCPSERVER_H
