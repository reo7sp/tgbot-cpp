#include <cstdlib>
#include <exception>
#include <iostream>
#include <memory>
#include <string>

#include <tgbot/tgbot.h>

int main() {
    const auto token = std::string(std::getenv("TOKEN"));

    const auto photoFilePath = std::string("example.jpg");
    const auto photoMimeType = std::string("image/jpeg");

    TgBot::Bot bot(token);
    bot.getEvents().onCommand("start", [&bot](std::shared_ptr<TgBot::Message> message) {
        bot.getApi().sendMessage(message->chat->id, "Hi!");
    });
    bot.getEvents().onCommand("photo", [&bot, &photoFilePath, &photoMimeType](std::shared_ptr<TgBot::Message> message) {
        bot.getApi().sendPhoto(message->chat->id, TgBot::InputFile::fromFile(photoFilePath, photoMimeType));
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
