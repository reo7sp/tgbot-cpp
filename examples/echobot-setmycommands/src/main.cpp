#include <cstdlib>
#include <exception>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include <tgbot/tgbot.h>

int main() {
    const auto token = std::string(std::getenv("TOKEN"));

    TgBot::Bot bot(token);

    std::vector<std::shared_ptr<TgBot::BotCommand>> commands;
    auto command = std::make_shared<TgBot::BotCommand>();
    command->command = "ccuno";
    command->description = "es el comando uno";
    commands.push_back(command);

    command = std::make_shared<TgBot::BotCommand>();
    command->command = "dossendo";
    command->description = "es el comando dos";
    commands.push_back(command);

    command = std::make_shared<TgBot::BotCommand>();
    command->command = "tressss";
    command->description = "es el comando tres";
    commands.push_back(command);

    bot.getApi().setMyCommands(commands);

    const auto configuredCommands = bot.getApi().getMyCommands();
    for (const auto& configuredCommand : configuredCommands) {
        std::cout << "cmd: " << configuredCommand->command << " -> " << configuredCommand->description << std::endl;
    }

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
        bot.getApi().deleteWebhook();

        TgBot::TgLongPoll longPoll(bot);
        longPoll.startLoop(handleError);
    } catch (const std::exception& error) {
        handleError(error);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
