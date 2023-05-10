#ifndef TGBOT_TGWEBHOOKLOCALSERVER_H
#define TGBOT_TGWEBHOOKLOCALSERVER_H

#ifdef BOOST_ASIO_HAS_LOCAL_SOCKETS

#include "tgbot/net/TgWebhookServer.h"

#include <string>

namespace TgBot {

/**
 * @brief This class setups HTTP server for receiving Telegram Update objects from unix socket.
 *
 * @ingroup net
 */
class TgWebhookLocalServer : public TgWebhookServer<boost::asio::local::stream_protocol> {

public:
    TgWebhookLocalServer(
        const std::string& unixSocketPath, 
        const std::string& path, 
        const EventHandler& eventHandler,
        const bool request_must_contain_a_secret_token = false
    )
        : TgWebhookServer<boost::asio::local::stream_protocol>(
            boost::asio::local::stream_protocol::endpoint(unixSocketPath),
            eventHandler,
            request_must_contain_a_secret_token
            )
    {
    }

    TgWebhookLocalServer(
        const std::string& unixSocketPath, 
        const Bot& bot,
        const bool request_must_contain_a_secret_token = false
    )
        : TgWebhookServer<boost::asio::local::stream_protocol>(
            boost::asio::local::stream_protocol::endpoint(unixSocketPath),
            bot,
            request_must_contain_a_secret_token
            )
    {
    }
};

}

#endif //BOOST_ASIO_HAS_LOCAL_SOCKETS

#endif //TGBOT_TGWEBHOOKLOCALSERVER_H
