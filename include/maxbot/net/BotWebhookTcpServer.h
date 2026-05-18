#ifndef TGBOT_TGWEBHOOKTCPSERVER_H
#define TGBOT_TGWEBHOOKTCPSERVER_H

#include "maxbot/net/BotWebhookServer.h"

#include <string>

namespace MaxBot {

/**
 * This class setups HTTP server for receiving Telegram Update objects from tcp connections.
 * @ingroup net
 */
class BotWebhookTcpServer : public BotWebhookServer<boost::asio::ip::tcp> {

public:
    BotWebhookTcpServer(unsigned short port, const std::string& path, const EventHandler& eventHandler)
            : BotWebhookServer<boost::asio::ip::tcp>(boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port),
                                                    path, eventHandler)
    {
    }

    BotWebhookTcpServer(unsigned short port, const Bot& bot)
            : BotWebhookServer<boost::asio::ip::tcp>(boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port),
                                                    bot)
    {
    }
};

}

#endif //TGBOT_TGWEBHOOKTCPSERVER_H
