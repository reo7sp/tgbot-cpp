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

    auto keyboard = std::make_shared<TgBot::InlineKeyboardMarkup>();
    std::vector<std::shared_ptr<TgBot::InlineKeyboardButton>> row0;
    auto checkButton = std::make_shared<TgBot::InlineKeyboardButton>();
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
