#pragma once

#include "tgbot/TgWebhookServer.h"
#include "tgbot/export.h"

#include <string>

namespace TgBot {

/**
 * This class setups HTTP server for receiving Telegram Update objects from tcp connections.
 * @ingroup net
 */
class TGBOT_API TgWebhookTcpServer : public TgWebhookServer<boost::asio::ip::tcp> {
public:
    TgWebhookTcpServer(unsigned short port, std::string path, const EventHandler& eventHandler);

    TgWebhookTcpServer(unsigned short port, const Bot& bot);
};

} // namespace TgBot
