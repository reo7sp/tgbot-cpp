# tgbot-cpp

[![Build Status](https://travis-ci.org/reo7sp/tgbot-cpp.svg?branch=master)](https://travis-ci.org/reo7sp/tgbot-cpp)
[![Docker Hub pulls](https://img.shields.io/docker/pulls/reo7sp/tgbot-cpp.svg)](https://hub.docker.com/r/reo7sp/tgbot-cpp/)

[![Contact @reo7sp](https://img.shields.io/badge/telegram-contact-green.svg)](https://t.me/reo7sp)
[![Donate using PayPal](https://img.shields.io/badge/donate-PayPal-brightgreen.svg)](https://paypal.me/reo7sp)
[![Donate using Rocketbank](https://img.shields.io/badge/donate-Rocketbank-brightgreen.svg)](https://rocketbank.ru/reo7sp)

---

[![GitHub contributors](https://img.shields.io/github/contributors/reo7sp/tgbot-cpp.svg)](https://github.com/reo7sp/tgbot-cpp/graphs/contributors) &nbsp; 🚀🚀🚀 thanks for the contributing!

---

C++ library for Telegram bot API.

Documentation is located [here](http://reo7sp.github.io/tgbot-cpp).

## State

- [x] Bot API 3.0 
- [x] Bot API 3.1
- [x] Bot API 3.2
- [x] Bot API 3.3
- [x] Bot API 3.4
- [x] Bot API 3.5
- [x] Bot API 3.6

## Library compilation

Firstly you need to install some dependencies such as Boost and build tools such as CMake. On Debian-based distibutives you can do it with these commands:
```sh
sudo apt-get install g++ make binutils cmake libssl-dev libboost-system-dev
```

To compile the library execute this commands:
```sh
cd /path/where/you/have/cloned/the/library/repository
cmake .
make -j4
sudo make install
```

## Bot compilation

### With CMake
[Example CMakeLists.txt](samples/echobot/CMakeLists.txt)

### Without CMake
```sh
g++ telegram_bot.cpp -o telegram_bot --std=c++11 -I/usr/local/include -lTgBot -lboost_system -lssl -lcrypto -lpthread
```

### Options available when compiling bot

#### With CMake
```
add_definitions(-DTGBOT_DISABLE_NAGLES_ALGORITHM) # Disable 'Nagle's algorithm'
add_definitions(-DTGBOT_CHANGE_SOCKET_BUFFER_SIZE) # Socket Buffer Size Expansion
add_definitions(-DTGBOT_CHANGE_READ_BUFFER_SIZE) # Read Buffer Size Expansion
```

#### Without CMake
```
-DTGBOT_DISABLE_NAGLES_ALGORITHM
-DTGBOT_CHANGE_SOCKET_BUFFER_SIZE
-DTGBOT_CHANGE_READ_BUFFER_SIZE
```

### Also
You can use Docker to build and run your bot. Set the base image of your's Dockerfile to [reo7sp/tgbot-cpp](https://hub.docker.com/r/reo7sp/tgbot-cpp/).

## Samples

Simple echo bot which sends everything it receives:
```cpp
#include <stdio.h>
#include <tgbot/tgbot.h>

int main() {
    TgBot::Bot bot("PLACE YOUR TOKEN HERE");
    bot.getEvents().onCommand("start", [&bot](TgBot::Message::Ptr message) {
        bot.getApi().sendMessage(message->chat->id, "Hi!");
    });
    bot.getEvents().onAnyMessage([&bot](TgBot::Message::Ptr message) {
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

All samples are located [here](samples).

## Feedback
Feel free to [create new issues on GitHub](https://github.com/reo7sp/tgbot-cpp/issues) or [contact me on Telegram](https://t.me/reo7sp).

## Licence
[The MIT License](http://opensource.org/licenses/MIT).
