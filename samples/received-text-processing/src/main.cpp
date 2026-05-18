#include <csignal>
#include <cstdio>
#include <cstdlib>
#include <exception>
#include <string>

#include <maxbot/maxbot.h>

using namespace std;
using namespace MaxBot;

vector<string> bot_commands = {"start", "test"};

int main() {
    string token(getenv("TOKEN"));
    printf("Token: %s\n", token.c_str());

    bool test_text_state = false;

    Bot bot(token);
    BotLongPoll long_poll(bot);

    bot.getEvents().onCommand("start", [&bot](Message::Ptr message) {
        bot.getApi().sendMessage(message->chat->id, "Hi!");
    });

    bot.getEvents().onCommand("test", [&](Message::Ptr message) {
        bot.getApi().sendMessage(message->chat->id, "Enter text");
        test_text_state = true;
    });

    bot.getEvents().onAnyMessage([&](MaxBot::Message::Ptr message) {
        if (test_text_state) {
            bot.getApi().sendMessage(message->chat->id, message->text);
            test_text_state = false;
            return;
        }

        for (const auto& command : bot_commands) {
            if ("/" + command == message->text) {
                return;
            }
        }

        bot.getApi().sendMessage(message->chat->id, "unknown command");
    });

    try {
        printf("Bot username: %s\n", bot.getApi().getMe()->username.c_str());
        bot.getApi().deleteWebhook();

        while (true) {
            printf("Long poll started\n");
            long_poll.start();
        }
    } catch (exception& e) {
        printf("error: %s\n", e.what());
    }

    return 0;
}
