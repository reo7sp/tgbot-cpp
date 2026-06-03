#ifndef MAXBOT_TGWEBHOOKLOCALSERVER_H
#define MAXBOT_TGWEBHOOKLOCALSERVER_H

#ifdef BOOST_ASIO_HAS_LOCAL_SOCKETS

#include "maxbot/net/BotWebhookServer.h"

#include <string>

namespace MaxBot {

/**
 * @brief This class setups HTTP server for receiving Telegram Update objects from unix socket.
 *
 * @ingroup net
 */
class BotWebhookLocalServer : public BotWebhookServer<boost::asio::local::stream_protocol> {

public:
    BotWebhookLocalServer(const std::string& unixSocketPath, const std::string& path, const EventHandler& eventHandler)
            : BotWebhookServer<boost::asio::local::stream_protocol>(boost::asio::local::stream_protocol::endpoint(unixSocketPath),
                                                                   path, eventHandler)
    {
    }

    BotWebhookLocalServer(const std::string& unixSocketPath, const Bot& bot)
            : BotWebhookServer<boost::asio::local::stream_protocol>(boost::asio::local::stream_protocol::endpoint(unixSocketPath),
                                                                   bot)
    {
    }
};

}

#endif //BOOST_ASIO_HAS_LOCAL_SOCKETS

#endif //MAXBOT_TGWEBHOOKLOCALSERVER_H
