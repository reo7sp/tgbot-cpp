# tgbot-cpp

[![GitHub contributors](https://img.shields.io/github/contributors/reo7sp/tgbot-cpp.svg)](https://github.com/reo7sp/tgbot-cpp/graphs/contributors)

C++ library for Telegram bot API.

Documentation is located [here](http://reo7sp.github.io/tgbot-cpp).


## State

- [x] Telegram Bot API 7.2
- [ ] [MaybeInaccessibleMessage](https://core.telegram.org/bots/api#maybeinaccessiblemessage)
- [ ] [Message->pinnedMessage](https://core.telegram.org/bots/api#message)
- [ ] [CallbackQuery->message](https://core.telegram.org/bots/api#callbackquery)
- [ ] [Deep Linking](https://core.telegram.org/bots/features#deep-linking)


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

Dependencies:
- CMake
- Boost
- OpenSSL
- ZLib
- Libcurl (optional unless you want to use curl-based http client `CurlHttpClient`).


## Library installation on Linux

You can install dependencies on Debian-based distibutives with these commands:

```sh
sudo apt install g++ make binutils cmake libboost-system-dev libssl-dev zlib1g-dev libcurl4-openssl-dev
```

Optionally, install the dependencies for testing and documenting
```sh
sudo apt install libboost-test-dev doxygen
```

You can compile and install the library with these commands:

```sh
git clone https://github.com/reo7sp/tgbot-cpp
cd tgbot-cpp
cmake .
make -j4
sudo make install
```

Alternatively, you can use Docker to build and run your bot. Set the base image of your's Dockerfile to [reo7sp/tgbot-cpp](https://hub.docker.com/r/reo7sp/tgbot-cpp/).


## Library installation on MacOS

You can install dependencies with these commands:

```sh
brew install gcc cmake boost openssl zlib curl
```

You can compile and install the library like Linux instructions.


## Library installation on Windows

### Download vcpkg and tgbot-cpp

Taken from [Vcpkg - Quick Start: Windows](https://github.com/Microsoft/vcpkg/#quick-start-windows).

Prerequisites:
- Windows 7 or newer
- [Git][https://git-scm.com/downloads]
- [Visual Studio][https://visualstudio.microsoft.com] 2015 Update 3 or greater with the English language pack

First, download and bootstrap vcpkg itself; it can be installed anywhere, but generally we recommend using vcpkg as a submodule for CMake projects, and installing it globally for Visual Studio projects. We recommend somewhere like `C:\src\vcpkg` or `C:\dev\vcpkg`, since otherwise you may run into path issues for some port build systems.

```cmd
> git clone https://github.com/microsoft/vcpkg
> .\vcpkg\bootstrap-vcpkg.bat
```

In order to use vcpkg with Visual Studio, run the following command (may require administrator elevation):

```cmd
> .\vcpkg\vcpkg integrate install
```

To install the libraries for Windows x64, run:

```cmd
> .\vcpkg\vcpkg install tgbot-cpp:x64-windows
```

To install for Windows x86, run:

```cmd
> .\vcpkg\vcpkg install tgbot-cpp
```

The library will now be installed and Visual Studio should be able to find the vcpkg installation.

### Setup project with CMakeLists

Use the [example CMakeLists.txt](samples/echobot/CMakeLists.txt) with changes:

1. Remove `/usr/local/include`
2. Change `/usr/local/lib/libTgBot.a` to `C:/src/vcpkg/installed/x64-windows/lib/TgBot.lib` or something simmilar according to your own installation path.


## Bot compilation

### With CMake

[Example CMakeLists.txt](samples/echobot/CMakeLists.txt)

Also, you can treat this repository as a submodule of your project, for example, see [echobot-submodule](samples/echobot-submodule/CMakeLists.txt).

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
