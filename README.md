# tgbot-cpp

[![Travis build Status](https://travis-ci.org/reo7sp/tgbot-cpp.svg?branch=master)](https://travis-ci.org/reo7sp/tgbot-cpp)
![Build status](https://github.com/reo7sp/tgbot-cpp/workflows/sw/badge.svg)
<br>
[![GitHub contributors](https://img.shields.io/github/contributors/reo7sp/tgbot-cpp.svg)](https://github.com/reo7sp/tgbot-cpp/graphs/contributors)

C++14 library for Telegram bot API.

Documentation is located [here](http://reo7sp.github.io/tgbot-cpp).


## State

- [x] Bot API 3.0 ~ 3.6
- [x] Bot API 4.0 ~ 4.4 (Implemented all APIs except 'Telegram Passport')


## Sample

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

All other samples are located [here](samples).


## Dependencies

Firstly you need to install some dependencies such as Boost and build tools such as CMake. On Debian-based distibutives you can do it with these commands:
```sh
sudo apt-get install g++ make binutils cmake libssl-dev libboost-system-dev zlib1g-dev
```
If you want to use curl-based http client `CurlHttpClient`, you also need to install `libcurl4-openssl-dev` package.

## Library installation

If you want to install the library system-wide:
```sh
git clone https://github.com/reo7sp/tgbot-cpp
cd tgbot-cpp
cmake .
make -j4
sudo make install
```

You can treat this repository as a submodule of your project, for example, see [echobot-submodule](samples/echobot-submodule/CMakeLists.txt)

You can use Docker to build and run your bot. Set the base image of your's Dockerfile to [reo7sp/tgbot-cpp](https://hub.docker.com/r/reo7sp/tgbot-cpp/).


## Bot compilation

### With CMake
[Example CMakeLists.txt](samples/echobot/CMakeLists.txt)

### Without CMake
```sh
g++ telegram_bot.cpp -o telegram_bot --std=c++14 -I/usr/local/include -lTgBot -lboost_system -lssl -lcrypto -lpthread
```

### Build options
```
-DTGBOT_DISABLE_NAGLES_ALGORITHM   # Disable 'Nagle's algorithm'
-DTGBOT_CHANGE_SOCKET_BUFFER_SIZE  # Socket Buffer Size Expansion
-DTGBOT_CHANGE_READ_BUFFER_SIZE    # Read Buffer Size Expansion
```


## Licence
[The MIT License](https://github.com/reo7sp/tgbot-cpp/blob/master/LICENSE).
