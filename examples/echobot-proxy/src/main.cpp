#include <array>
#include <cstdlib>
#include <exception>
#include <iostream>
#include <memory>
#include <string>

#include <tgbot/CurlHttpClient.h>
#include <tgbot/tgbot.h>

int main() {
    // The proxy URLs below are examples. Replace them with your own.
    constexpr std::array<const char*, 4> proxies {
        nullptr,
        "socks5://user:password@10.20.30.40:1080",
        "http://user:password@192.168.50.70:3128",
        "http://user:password@192.168.80.90:3128",
    };
    constexpr auto connectTimeout = 10L;
    std::size_t proxyIndex = 0;

    const auto token = std::string(std::getenv("TOKEN"));

    TgBot::CurlHttpClient curlHttpClient;
    TgBot::Bot bot(token, curlHttpClient);

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

    const auto currentProxyName = [&] {
        return proxies[proxyIndex] != nullptr ? proxies[proxyIndex] : "direct";
    };
    const auto handleError = [&](const std::exception& error) {
        std::cout << "Proxy[" << proxyIndex << "] (" << currentProxyName() << ") error: " << error.what() << std::endl;

        proxyIndex = (proxyIndex + 1) % proxies.size();
        curlHttpClient.setProxy(proxies[proxyIndex], connectTimeout);

        std::cout << "Switched to proxy[" << proxyIndex << "] (" << currentProxyName() << ")" << std::endl;
    };

    try {
        std::cout << "Bot username: " << bot.getApi().getMe()->username.value_or("") << std::endl;
        bot.getApi().deleteWebhook();

        TgBot::TgLongPoll longPoll(bot);
        longPoll.startLoop(handleError);
    } catch (const std::exception& error) {
        handleError(error);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
