#include <csignal>
#include <cstdio>
#include <cstdlib>
#include <exception>

#include <tgbot/tgbot.h>

using namespace std;
using namespace TgBot;

bool sigintGot = false;

int main() {
    string token(getenv("TOKEN"));
    printf("Token: %s\n", token.c_str());

    CurlHttpClient curlHttpClient;

    Bot bot(token, curlHttpClient);
    bot.getEvents().onCommand("start", [&bot](Message::Ptr message) {
        bot.getApi().sendMessage(message->chat->id, "Hi!");
    });
    bot.getEvents().onAnyMessage([&bot](Message::Ptr message) {
        printf("User wrote %s\n", message->text.c_str());
        if (StringTools::startsWith(message->text, "/start")) {
            return;
        }
        bot.getApi().sendMessage(message->chat->id, "Your message is: " + message->text);
    });

    signal(SIGINT, [](int s) {
        printf("SIGINT got\n");
        sigintGot = true;
    });
    try {
        printf("Bot username: %s\n", bot.getApi().getMe()->username.c_str());

        TgLongPoll longPoll(bot);
        while (!sigintGot) {
            printf("Long poll started\n");
            longPoll.start();
        }
    } catch (exception& e) {
        printf("error: %s\n", e.what());
    }

    return 0;
}
