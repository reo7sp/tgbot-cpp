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
#include <tgbot/tgbot.h>

int main() {
    TgBot::Bot bot("PLACE YOUR TOKEN HERE");
    bot.getEvents().onCommand("start", [&bot](TgBot::Message::Ptr message) {
        bot.getApi().sendMessage(message->chat->id, "Hi!");
    });
    bot.getEvents().onAnyMessage([&bot](TgBot::Message::Ptr message) {
        const std::string text = message->text.value_or("");
        std::cout << "User wrote " << text << std::endl;
        if (text.starts_with("/start")) {
            return;
        }
        bot.getApi().sendMessage(message->chat->id, "Your message is: " + text);
    });
    try {
        std::cout << "Bot username: " << bot.getApi().getMe()->username.value_or("") << std::endl;
        TgBot::TgLongPoll longPoll(bot);
        while (true) {
            std::cout << "Long poll started" << std::endl;
            longPoll.start();
        }
    } catch (TgBot::TgException& e) {
        std::cout << "error: " << e.what() << std::endl;
    }
    return 0;
}
```

Other examples are available in [`examples`](examples): webhook server, custom
curl client, proxy carousel, inline and reply keyboards, file upload/download,
and command configuration.

Build and run an example against a locally installed copy of the library:

```sh
make install INSTALL_PREFIX="$PWD/build/install"
make example EXAMPLE=echobot INSTALL_PREFIX="$PWD/build/install"
TOKEN=... ./build/Release/examples/echobot/echobot
```

Alternatively, build and run the example in Docker:

```sh
TOKEN=... make docker-run-example EXAMPLE=echobot
```

To run every example, copy `env.example` to `env`, fill in the values, then run:

```sh
make docker-compose-run-examples
```

Only `echobot-webhook-server` exposes an HTTP port. The other examples use
Telegram long polling and do not listen on local ports.

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


## Building the library

The Makefile wraps the Conan and CMake workflow on every supported platform:

```sh
git clone https://github.com/reo7sp/tgbot-cpp
cd tgbot-cpp
make
make install INSTALL_PREFIX=build/install
```

Development checks are also exposed through the Makefile:

```sh
make test
make format
make lint
```

Alternatively, build and test the Docker images through the same Makefile:

```sh
make docker-image
make docker-test
```


## Updating Telegram Bot API types

[Help page](./HOW_TO_UPDATE_TELEGRAM_API.md).


## Licence

[The MIT License](./LICENSE).
