#include <csignal>
#include <cstdlib>
#include <exception>
#include <iostream>
#include <string>
#include <vector>

#include <tgbot/tgbot.h>

std::vector<std::string> bot_commands = { "start", "test" };

int main() {
    std::string token(std::getenv("TOKEN"));
    std::cout << "Token: " << token << std::endl;

    bool test_text_state = false;

    TgBot::Bot bot(token);
    TgBot::TgLongPoll long_poll(bot);

    bot.getEvents().onCommand(
        "start", [&bot](TgBot::Message::Ptr message) { bot.getApi().sendMessage(message->chat->id, "Hi!"); });

    bot.getEvents().onCommand("test", [&](TgBot::Message::Ptr message) {
        bot.getApi().sendMessage(message->chat->id, "Enter text");
        test_text_state = true;
    });

    bot.getEvents().onAnyMessage([&](TgBot::Message::Ptr message) {
        if (test_text_state) {
            bot.getApi().sendMessage(message->chat->id, message->text.value_or(""));
            test_text_state = false;
            return;
        }

        for (const auto& command : bot_commands) {
            if ("/" + command == message->text.value_or("")) {
                return;
            }
        }

        bot.getApi().sendMessage(message->chat->id, "unknown command");
    });

    try {
        std::cout << "Bot username: " << bot.getApi().getMe()->username.value_or("") << std::endl;
        bot.getApi().deleteWebhook();

        while (true) {
            std::cout << "Long poll started" << std::endl;
            long_poll.start();
        }
    } catch (std::exception& e) {
        std::cout << "error: " << e.what() << std::endl;
    }

    return 0;
}
