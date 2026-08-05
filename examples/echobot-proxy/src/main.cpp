// Example of using array of proxies wth tgbot-cpp library.
// Based on original code (c) Oleg Morozenkov [reo7sp] https://github.com/reo7sp
// https://github.com/reo7sp/tgbot-cpp/blob/master/examples/echobot/src/main.cpp

#include <csignal>
#include <cstdlib>
#include <exception>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include <tgbot/CurlHttpClient.h>
#include <tgbot/tgbot.h>

#define CONNECT_TIMEOUT 10L

int main() {
    // Filling array of proxies.
    std::vector<const char*> proxies;
    // NULL = no proxy, direct connection to API.
    proxies.push_back(nullptr); // [0]
    // All proxy-URLs below are fake. Use yuor own.
    proxies.push_back("socks5://user:password@10.20.30.40:1080"); // [1]
    proxies.push_back("http://user:password@192.168.50.70:3128"); // [2]
    proxies.push_back("http://user:password@192.168.80.90:3128"); // [3]
    // Choose "staring" index of proxy. In this example [0] - NULL=no proxy.
    std::size_t proxy_now = 0;

    std::string token(std::getenv("TOKEN"));
    std::cout << "Token: " << token << std::endl;

    TgBot::CurlHttpClient curlHttpClient;
    TgBot::Bot bot(token, curlHttpClient);

    bot.getEvents().onCommand("start", [&bot](std::shared_ptr<TgBot::Message> message) {
        bot.getApi().sendMessage(message->chat->id, "Hi!");
    });
    bot.getEvents().onAnyMessage([&bot](std::shared_ptr<TgBot::Message> message) {
        const std::string text = message->text.value_or("");
        std::cout << "User wrote " << text << std::endl;
        if (text.starts_with("/start"))
            return;
        bot.getApi().sendMessage(message->chat->id, "Your message is: " + text);
    });

    std::signal(SIGINT, [](int s) {
        std::cout << "SIGINT got: " << s << std::endl;
        std::exit(0);
    });

    while (true) {
        try {
            std::cout << "Bot username: " << bot.getApi().getMe()->username.value_or("") << std::endl;
            bot.getApi().deleteWebhook();

            TgBot::TgLongPoll longPoll(bot);
            while (true) {
                std::cout << "Long poll started" << std::endl;
                longPoll.start();
            }
        } catch (std::exception& e) {
            std::cout << "Proxy[" << proxy_now
                      << "]: " << (proxies[proxy_now] != nullptr ? proxies[proxy_now] : "direct") << " error"
                      << std::endl;
            std::cout << e.what() << std::endl;
            // Assumption:
            // the reason of exception was - disconnect,
            // connection timeout or other network problem.
            // Trying to switch (cycle) to next proxy in array.
            proxy_now++;
            if (proxy_now >= proxies.size())
                proxy_now = 0;
            curlHttpClient.setProxy(proxies[proxy_now], CONNECT_TIMEOUT);
            std::cout << "Switch proxy[" << proxy_now
                      << "]: " << (proxies[proxy_now] != nullptr ? proxies[proxy_now] : "direct") << std::endl;
        }
    }
    return 0;
}

// eof
