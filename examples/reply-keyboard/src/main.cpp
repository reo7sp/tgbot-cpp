#include <cstdlib>
#include <exception>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include <tgbot/tgbot.h>

void createOneColumnKeyboard(const std::vector<std::string>& buttonStrings,
                             const std::shared_ptr<TgBot::ReplyKeyboardMarkup>& keyboard) {
    for (const auto& buttonString : buttonStrings) {
        std::vector<std::shared_ptr<TgBot::KeyboardButton>> row;
        auto button = std::make_shared<TgBot::KeyboardButton>();
        button->text = buttonString;
        row.push_back(button);
        keyboard->keyboard.push_back(row);
    }
}

void createKeyboard(const std::vector<std::vector<std::string>>& buttonLayout,
                    const std::shared_ptr<TgBot::ReplyKeyboardMarkup>& keyboard) {
    for (const auto& buttonStrings : buttonLayout) {
        std::vector<std::shared_ptr<TgBot::KeyboardButton>> row;
        for (const auto& buttonString : buttonStrings) {
            auto button = std::make_shared<TgBot::KeyboardButton>();
            button->text = buttonString;
            row.push_back(button);
        }
        keyboard->keyboard.push_back(row);
    }
}

int main() {
    const auto token = std::string(std::getenv("TOKEN"));
    std::cout << "Token: " << token << std::endl;

    TgBot::Bot bot(token);

    auto keyboardOneCol = std::make_shared<TgBot::ReplyKeyboardMarkup>();
    createOneColumnKeyboard({ "Option 1", "Option 2", "Option 3" }, keyboardOneCol);

    auto keyboardWithLayout = std::make_shared<TgBot::ReplyKeyboardMarkup>();
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
        const auto text = message->text.value_or("");
        std::cout << "User wrote " << text << std::endl;
        if (text.starts_with("/start") || text.starts_with("/layout")) {
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
