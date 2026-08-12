#include <cstdlib>
#include <exception>
#include <iostream>
#include <memory>
#include <string>

#include <tgbot/tgbot.h>

int main() {
    const auto token = std::string(std::getenv("TOKEN"));
    const auto webhookUrl = std::string(std::getenv("WEBHOOK_URL"));
    std::cout << "Webhook URL: " << webhookUrl << std::endl;

    TgBot::Bot bot(token);
    bot.getEvents().onCommand("start", [&bot](std::shared_ptr<TgBot::Message> message) {
        bot.getApi().sendMessage(message->chat->id, "Hi!");
    });
    bot.getEvents().onAnyMessage([&bot](std::shared_ptr<TgBot::Message> message) {
        const auto text = message->text.value_or("");
        std::cout << "User wrote " << text << std::endl;
        if (text.starts_with("/start")) {
            return;
        }
        bot.getApi().sendMessage(message->chat->id, "Your message is: " + text);
    });

    const auto handleError = [](const std::exception& error) {
        std::cout << "error: " << error.what() << std::endl;
    };

    try {
        std::cout << "Bot username: " << bot.getApi().getMe()->username.value_or("") << std::endl;

        TgBot::TgWebhookTcpServer webhookServer(8080, bot);
        bot.getApi().setWebhook(webhookUrl);
        webhookServer.start(handleError);
    } catch (const std::exception& error) {
        handleError(error);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
