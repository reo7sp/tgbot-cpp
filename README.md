# tgbot-cpp

[![GitHub contributors](https://img.shields.io/github/contributors/reo7sp/tgbot-cpp.svg)](https://github.com/reo7sp/tgbot-cpp/graphs/contributors)

C++ library for Telegram bot API.

Documentation is located [here](http://reo7sp.github.io/tgbot-cpp).


## State

- [x] Telegram Bot API 10.2.


## Example

Simple echo bot which sends everything it receives:

```cpp
#include <iostream>
#include <memory>

#include <tgbot/tgbot.h>

int main() {
    TgBot::Bot bot("PLACE YOUR TOKEN HERE");
    bot.getEvents().onCommand("start", [&bot](std::shared_ptr<TgBot::Message> message) {
        bot.getApi().sendMessage(message->chat->id, "Hi!");
    });
    bot.getEvents().onAnyMessage([&bot](std::shared_ptr<TgBot::Message> message) {
        const auto text = message->text.value_or("");
        std::cout << "User wrote " << text << std::endl;
        if (text.starts_with("/start")) {
            return;
        }
        bot.getApi().sendMessage(message->chat->id, "Your message is: " + text);
    });
    try {
        std::cout << "Bot username: " << bot.getApi().getMe()->username.value_or("") << std::endl;
        TgBot::TgLongPoll longPoll(bot);
        longPoll.startLoop();
    } catch (const TgBot::TgException& e) {
        std::cout << "error: " << e.what() << std::endl;
    }
    return 0;
}
```

Other examples are available in [`examples`](examples): webhook server, custom
curl client, proxy usage, inline and reply keyboards, file upload/download,
and command configuration.

Build and run an example against a locally installed copy of the library:

```sh
make install INSTALL_PREFIX=build/install
make example EXAMPLE=echobot INSTALL_PREFIX=build/install
TOKEN=... ./build/Release/examples/echobot/echobot
```

Alternatively, build and run the example in Docker:

```sh
TOKEN=... make docker-run-example EXAMPLE=echobot
```

Also you can build and run all examples at once using Docker Compose. For this
copy `env.example` to `env`, fill in the values, then run:

```sh
make docker-compose-run-examples
make docker-compose-stop-examples
```

For your own bot image, use [reo7sp/tgbot-cpp](https://hub.docker.com/r/reo7sp/tgbot-cpp/) as the base image.


## Usage in CMake

For an installed tgbot-cpp package, add it to your `CMakeLists.txt`:

```cmake
find_package(TgBot CONFIG REQUIRED)
target_link_libraries(your_bot PRIVATE TgBot::TgBot)
```

See the complete [echobot CMakeLists.txt](examples/echobot/CMakeLists.txt).

The repository can also be added directly with `add_subdirectory`, for example
when it is included as a Git submodule. See the
[submodule example](examples/echobot-submodule/CMakeLists.txt).


## Dependencies

Required to build the library:

- C++20 compiler;
- CMake 3.16 or newer;
- Conan 2;
- Make.

Additionally required for code generation:

- Python;
- Poetry.

Conan installs the library dependencies:

- Boost;
- nlohmann/json;
- libcurl;
- GoogleTest when tests are enabled.

These libraries do not need to be installed separately.


## Installing dependencies

### Linux

On Debian or Ubuntu, install the build tools and the official Conan 2 package:

```sh
sudo apt-get update
sudo apt-get install -y build-essential cmake curl git
CONAN_VERSION=2.31.2
curl -fLO "https://github.com/conan-io/conan/releases/download/${CONAN_VERSION}/conan-${CONAN_VERSION}-$(dpkg --print-architecture).deb"
sudo apt-get install -y "./conan-${CONAN_VERSION}-$(dpkg --print-architecture).deb"
```

For development, also install Python, Poetry and clang-format:

```sh
sudo apt-get install -y clang-format pipx python3
pipx install poetry
```

### macOS

```sh
xcode-select --install
brew install cmake conan
```

For development:

```sh
brew install clang-format pipx python
pipx install poetry
```

### Windows

Install Git, Make, CMake, Visual Studio 2022 with the Desktop development with
C++ workload, and Conan 2 using its official Windows installer.

For development, also install Python, Poetry and clang-format.


## Developing tgbot-cpp

Development checks are exposed through the Makefile:

```sh
make format
make lint
make test
```

Alternatively, via Docker:

```sh
make docker-test
```


## Updating Telegram Bot API types

[Help page](./HOW_TO_UPDATE_TELEGRAM_API.md).


## Licence

[The MIT License](./LICENSE).
