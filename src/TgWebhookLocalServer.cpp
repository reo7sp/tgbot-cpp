#include "tgbot/TgWebhookLocalServer.h"

#ifdef BOOST_ASIO_HAS_LOCAL_SOCKETS

namespace TgBot {

TgWebhookLocalServer::TgWebhookLocalServer(const std::string& unixSocketPath, const std::string& path,
                                           const EventHandler& eventHandler)
    : TgWebhookServer(boost::asio::local::stream_protocol::endpoint(unixSocketPath), path, eventHandler) {
}

TgWebhookLocalServer::TgWebhookLocalServer(const std::string& unixSocketPath, const Bot& bot)
    : TgWebhookServer(boost::asio::local::stream_protocol::endpoint(unixSocketPath), bot) {
}

} // namespace TgBot

#endif // BOOST_ASIO_HAS_LOCAL_SOCKETS
