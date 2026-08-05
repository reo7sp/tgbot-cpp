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

    // Thanks Pietro Falessi for code
    std::shared_ptr<TgBot::InlineKeyboardMarkup> keyboard = std::make_shared<TgBot::InlineKeyboardMarkup>();
    std::vector<std::shared_ptr<TgBot::InlineKeyboardButton>> row0;
    std::shared_ptr<TgBot::InlineKeyboardButton> checkButton = std::make_shared<TgBot::InlineKeyboardButton>();
    checkButton->text = "check";
    checkButton->callbackData = "check";
    row0.push_back(checkButton);
    keyboard->inlineKeyboard.push_back(row0);

    bot.getEvents().onCommand("start", [&bot, &keyboard](std::shared_ptr<TgBot::Message> message) {
        bot.getApi().sendMessage(message->chat->id, "Hi!", nullptr, nullptr, keyboard);
    });
    bot.getEvents().onCommand("check", [&bot, &keyboard](std::shared_ptr<TgBot::Message> message) {
        bot.getApi().sendMessage(message->chat->id, "ok", nullptr, nullptr, keyboard, "Markdown");
    });
    bot.getEvents().onCallbackQuery([&bot, &keyboard](std::shared_ptr<TgBot::CallbackQuery> query) {
        if (query->data.value_or("").starts_with("check") && query->message) {
            std::visit(
                [&bot, &keyboard](const auto& message) {
                    bot.getApi().sendMessage(message->chat->id, "ok", nullptr, nullptr, keyboard, "Markdown");
                },
                query->message->value);
        }
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
