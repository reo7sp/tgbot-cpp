# tgbot-cpp

[![Travis build Status](https://travis-ci.org/reo7sp/tgbot-cpp.svg?branch=master)](https://travis-ci.org/reo7sp/tgbot-cpp)
[![Appveyor build status](https://ci.appveyor.com/api/projects/status/tncys4p1flm8817m?svg=true)](https://ci.appveyor.com/project/reo7sp/tgbot-cpp)
[![Docker Hub pulls](https://img.shields.io/docker/pulls/reo7sp/tgbot-cpp.svg)](https://hub.docker.com/r/reo7sp/tgbot-cpp/)
[![Open documentation](https://img.shields.io/badge/open-documentation-orange.svg)](http://reo7sp.github.io/tgbot-cpp)
[![Donate using PayPal](https://img.shields.io/badge/donate-PayPal-orange.svg)](https://paypal.me/reo7sp)

---

[![GitHub contributors](https://img.shields.io/github/contributors/reo7sp/tgbot-cpp.svg)](https://github.com/reo7sp/tgbot-cpp/graphs/contributors) &nbsp; 🚀🚀🚀 thanks for the contributing!

---

C++ library for Telegram bot API.

Documentation is located [here](http://reo7sp.github.io/tgbot-cpp).


## State

- [x] Bot API 3.0 ~ 3.6
- [x] Bot API 4.0 (Implemented all APIs except 'Telegram Passport')


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

Or you can treat this repository as a submodule of your project, for example, see [echobot-submodule](samples/echobot-submodule/CMakeLists.txt)

## Specific library installation notes

### Docker
You can use Docker to build and run your bot. Set the base image of your's Dockerfile to [reo7sp/tgbot-cpp](https://hub.docker.com/r/reo7sp/tgbot-cpp/).

### Conan
You can use Conan C/C++ Package Manager. Follow [Conan instructions](https://docs.conan.io/en/latest/getting_started.html) and use [the template](https://github.com/reo7sp/tgbot-cpp/tree/master/samples/echobot-conan).

### Arch Linux
A PKGBUILD compiles shared library with header files is hosted on [Arch Linux User Repository](https://aur.archlinux.org/packages/libtgbot-cpp-git/).


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


## Feedback
Feel free to [create new issues on GitHub](https://github.com/reo7sp/tgbot-cpp/issues) or [contact me on Telegram](https://t.me/reo7sp).


## Licence
[The MIT License](http://opensource.org/licenses/MIT).
