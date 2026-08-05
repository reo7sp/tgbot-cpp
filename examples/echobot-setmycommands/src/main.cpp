#include <csignal>
#include <cstdlib>
#include <exception>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include <tgbot/tgbot.h>

int main() {
    std::string token(std::getenv("TOKEN"));
    std::cout << "Token: " << token << std::endl;

    TgBot::Bot bot(token);

    std::vector<std::shared_ptr<TgBot::BotCommand>> commands;
    std::shared_ptr<TgBot::BotCommand> cmdArray = std::make_shared<TgBot::BotCommand>();
    cmdArray->command = "ccuno";
    cmdArray->description = "es el comando uno";

    commands.push_back(cmdArray);

    cmdArray = std::make_shared<TgBot::BotCommand>();
    cmdArray->command = "dossendo";
    cmdArray->description = "es el comando dos";
    commands.push_back(cmdArray);

    cmdArray = std::make_shared<TgBot::BotCommand>();
    cmdArray->command = "tressss";
    cmdArray->description = "es el comando tres";
    commands.push_back(cmdArray);

    bot.getApi().setMyCommands(commands);

    std::vector<std::shared_ptr<TgBot::BotCommand>> vectCmd;
    vectCmd = bot.getApi().getMyCommands();

    for (std::vector<std::shared_ptr<TgBot::BotCommand>>::iterator it = vectCmd.begin(); it != vectCmd.end(); ++it) {
        std::cout << "cmd: " << (*it)->command << " -> " << (*it)->description << std::endl;
    }

    bot.getEvents().onCommand("start", [&bot](std::shared_ptr<TgBot::Message> message) {
        bot.getApi().sendMessage(message->chat->id, "Hi!");
    });
    bot.getEvents().onAnyMessage([&bot](std::shared_ptr<TgBot::Message> message) {
        const std::string text = message->text.value_or("");
        std::cout << "User wrote " << text << std::endl;
        if (text.starts_with("/start")) {
            return;
        }
        bot.getApi().sendMessage(message->chat->id, "Your message is: " + text);
    });

    std::signal(SIGINT, [](int s) {
        std::cout << "SIGINT got" << std::endl;
        std::exit(0);
    });

    try {
        std::cout << "Bot username: " << bot.getApi().getMe()->username.value_or("") << std::endl;
        bot.getApi().deleteWebhook();

        TgBot::TgLongPoll longPoll(bot);
        while (true) {
            std::cout << "Long poll started" << std::endl;
            longPoll.start();
        }
    } catch (std::exception& e) {
        std::cout << "error: " << e.what() << std::endl;
    }

    return 0;
}
