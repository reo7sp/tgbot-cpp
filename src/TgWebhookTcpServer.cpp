#include "tgbot/TgWebhookTcpServer.h"

namespace TgBot {

TgWebhookTcpServer::TgWebhookTcpServer(unsigned short port, const std::string& path, const EventHandler& eventHandler)
    : TgWebhookServer(boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port), path, eventHandler) {
}

TgWebhookTcpServer::TgWebhookTcpServer(unsigned short port, const Bot& bot)
    : TgWebhookServer(boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port), bot) {
}

} // namespace TgBot
