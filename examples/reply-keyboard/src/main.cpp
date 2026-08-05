#include <csignal>
#include <cstdlib>
#include <exception>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include <tgbot/tgbot.h>

void createOneColumnKeyboard(const std::vector<std::string>& buttonStrings,
                             std::shared_ptr<TgBot::ReplyKeyboardMarkup>& kb) {
    for (std::size_t i = 0; i < buttonStrings.size(); ++i) {
        std::vector<std::shared_ptr<TgBot::KeyboardButton>> row;
        std::shared_ptr<TgBot::KeyboardButton> button = std::make_shared<TgBot::KeyboardButton>();
        button->text = buttonStrings[i];
        row.push_back(button);
        kb->keyboard.push_back(row);
    }
}

void createKeyboard(const std::vector<std::vector<std::string>>& buttonLayout,
                    std::shared_ptr<TgBot::ReplyKeyboardMarkup>& kb) {
    for (std::size_t i = 0; i < buttonLayout.size(); ++i) {
        std::vector<std::shared_ptr<TgBot::KeyboardButton>> row;
        for (std::size_t j = 0; j < buttonLayout[i].size(); ++j) {
            std::shared_ptr<TgBot::KeyboardButton> button = std::make_shared<TgBot::KeyboardButton>();
            button->text = buttonLayout[i][j];
            row.push_back(button);
        }
        kb->keyboard.push_back(row);
    }
}

int main() {
    std::string token(std::getenv("TOKEN"));
    std::cout << "Token: " << token << std::endl;

    TgBot::Bot bot(token);

    std::shared_ptr<TgBot::ReplyKeyboardMarkup> keyboardOneCol = std::make_shared<TgBot::ReplyKeyboardMarkup>();
    createOneColumnKeyboard({ "Option 1", "Option 2", "Option 3" }, keyboardOneCol);

    std::shared_ptr<TgBot::ReplyKeyboardMarkup> keyboardWithLayout = std::make_shared<TgBot::ReplyKeyboardMarkup>();
    createKeyboard({ { "Dog", "Cat", "Mouse" },
                     { "Green", "White", "Red" },
                     { "On", "Off" },
                     { "Back" },
                     { "Info", "About", "Map", "Etc" } },
                   keyboardWithLayout);

    bot.getEvents().onCommand("start", [&bot, &keyboardOneCol](std::shared_ptr<TgBot::Message> message) {
        bot.getApi().sendMessage(message->chat->id,
                                 "/start for one column keyboard\n/layout for a more complex keyboard", nullptr,
                                 nullptr, keyboardOneCol);
    });
    bot.getEvents().onCommand("layout", [&bot, &keyboardWithLayout](std::shared_ptr<TgBot::Message> message) {
        bot.getApi().sendMessage(message->chat->id,
                                 "/start for one column keyboard\n/layout for a more complex keyboard", nullptr,
                                 nullptr, keyboardWithLayout);
    });
    bot.getEvents().onAnyMessage([&bot](std::shared_ptr<TgBot::Message> message) {
        const std::string text = message->text.value_or("");
        std::cout << "User wrote " << text << std::endl;
        if (text.starts_with("/start") || text.starts_with("/layout")) {
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
