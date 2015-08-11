# tgbot-cpp

[![Join the chat at https://gitter.im/reo7sp/tgbot-cpp](https://badges.gitter.im/Join%20Chat.svg)](https://gitter.im/reo7sp/tgbot-cpp?utm_source=badge&utm_medium=badge&utm_campaign=pr-badge&utm_content=badge)

C++ library for Telegram bot API.

**Warning:** It's not stable version yet. Something may not work.

Documentaion is located [here](http://reo7sp.ru/proj/tgbot-cpp/doc)

## Compilation

Firstly you need to install some dependencies. You have to have Boost library at the runtime and CMake at the compilation step to be able to use this library. On Debian-based distibutives you can do it with these commands:
```sh
sudo apt-get install g++ make binutils cmake libssl-dev libboost-system-dev libboost-iostreams-dev libboost-test-dev
```

To compile the library execute this commands:
```sh
cd /path/where/you/have/cloned/the/library/repository
cmake .
make -j4
sudo make install
```

That's all. All you have to do now is just link compiled library to your project.

## Samples

Simple echo bot which sends everything it recieves:
```cpp
int main() {
    TgBot::Bot bot("PLACE YOUR TOKEN HERE");
    bot.getEvents().onCommand("start", [&bot](Message::Ptr message) {
        bot.getApi().sendMessage(message->chat->id, "Hi!");
    });
    bot.getEvents().onAnyMessage([&bot](Message::Ptr message) {
        printf("User wrote %s\n", message->text.c_str());
        if (StringTools::startsWith(message->text, "/start")) {
            return;
        }
        bot.getApi().sendMessage(message->chat->id, "Your message is: " + message->text);
    });
    try {
        printf("Bot username: %s\n", bot.getApi().getMe()->username.c_str());
        TgBot::TgLongPoll longPoll(bot);
        while (true) {
            printf("Long poll started\n");
            longPoll.start();
        }
    } catch (TgBot::TgException& e) {
        printf("error: %s\n", e.what());
    }
    return 0;
}
```

All samples are located [here](samples)

## Feedback
Feel free to [create new issues on GitHub](https://github.com/reo7sp/tgbot-cpp/issues) or [contact me on Telegram](https://telegram.me/Reo_SP)

## Licence
[The MIT License](http://opensource.org/licenses/MIT)
