#include <cstdlib>
#include <exception>
#include <iostream>
#include <memory>
#include <string>

#include <tgbot/tgbot.h>

int main() {
    const auto token = std::string(std::getenv("TOKEN"));

    TgBot::Bot bot(token);
    bot.getEvents().onCommand("start", [&bot](std::shared_ptr<TgBot::Message> message) {
        bot.getApi().sendMessage(message->chat->id, "Hi!");
    });
    bot.getEvents().onAnyMessage([&bot](std::shared_ptr<TgBot::Message> message) {
        const auto text = message->text.value_or("");
        std::cout << "User wrote " << text << std::endl;

        if (text.starts_with("/start")) {
            return;
        }

        if (!message->document) {
            bot.getApi().sendMessage(message->chat->id, "Please send a file.");
            return;
        }

        const auto file = bot.getApi().getFile(message->document->fileId);
        const auto fileContent = bot.getApi().downloadFile(file->filePath.value_or(""));

        if (fileContent.size() > 4000) {
            bot.getApi().sendMessage(message->chat->id, "The file is too large to send as a message.");
            return;
        }

        bot.getApi().sendMessage(message->chat->id, "Your file content: " + fileContent);
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
