#pragma once

#include "tgbot/TgWebhookServer.h"
#include "tgbot/export.h"

#include <string>

#ifdef BOOST_ASIO_HAS_LOCAL_SOCKETS

namespace TgBot {

/**
 * @brief This class setups HTTP server for receiving Telegram Update objects from unix socket.
 *
 * @ingroup net
 */
class TGBOT_API TgWebhookLocalServer : public TgWebhookServer<boost::asio::local::stream_protocol> {
public:
    TgWebhookLocalServer(const std::string& unixSocketPath, std::string path, const EventHandler& eventHandler);

    TgWebhookLocalServer(const std::string& unixSocketPath, const Bot& bot);
};

} // namespace TgBot

#endif // BOOST_ASIO_HAS_LOCAL_SOCKETS
