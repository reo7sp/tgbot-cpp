#include <cstdlib>
#include <exception>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include <tgbot/tgbot.h>

const std::vector<std::string> botCommands { "start", "test" };

int main() {
    const auto token = std::string(std::getenv("TOKEN"));

    bool isWaitingForText = false;

    TgBot::Bot bot(token);
    TgBot::TgLongPoll longPoll(bot);

    bot.getEvents().onCommand("start", [&bot](std::shared_ptr<TgBot::Message> message) {
        bot.getApi().sendMessage(message->chat->id, "Hi!");
    });

    bot.getEvents().onCommand("test", [&](std::shared_ptr<TgBot::Message> message) {
        bot.getApi().sendMessage(message->chat->id, "Enter text");
        isWaitingForText = true;
    });

    bot.getEvents().onAnyMessage([&](std::shared_ptr<TgBot::Message> message) {
        if (isWaitingForText) {
            bot.getApi().sendMessage(message->chat->id, message->text.value_or(""));
            isWaitingForText = false;
            return;
        }

        for (const auto& command : botCommands) {
            if ("/" + command == message->text.value_or("")) {
                return;
            }
        }

        bot.getApi().sendMessage(message->chat->id, "unknown command");
    });

    const auto handleError = [](const std::exception& error) {
        std::cout << "error: " << error.what() << std::endl;
    };

    try {
        std::cout << "Bot username: " << bot.getApi().getMe()->username.value_or("") << std::endl;
        bot.getApi().deleteWebhook();

        longPoll.startLoop(handleError);
    } catch (const std::exception& error) {
        handleError(error);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
