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

To build all examples:
```sh
make install INSTALL_PREFIX=build/install
make examples INSTALL_PREFIX=build/install
```

Alternatively, build and run the example in Docker:

```sh
TOKEN=... make docker-run-example EXAMPLE=echobot
```

To build and run all examples at once use Docker Compose. You need to copy
`env.example` to `env`, fill in the values and then run:

```sh
make docker-compose-run-examples
make docker-compose-stop-examples
```


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

For Docker, you can use [reo7sp/tgbot-cpp](https://hub.docker.com/r/reo7sp/tgbot-cpp/) as the base image.


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

On Debian or Ubuntu, install the build tools and the official Conan package:

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

Install the build tools with Homebrew:

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

Run PowerShell and install the build tools:

```powershell
winget install --exact --id Git.Git
winget install --exact --id GnuWin32.Make
winget install --exact --id Kitware.CMake
winget install --exact --id Ninja-build.Ninja
winget install --exact --id Microsoft.VisualStudio.2022.Community --override "--wait --passive --add Microsoft.VisualStudio.Workload.NativeDesktop --includeRecommended"

$ConanVersion = "2.31.2"
$ConanInstaller = "conan-$ConanVersion-windows-x86_64-installer.exe"
Invoke-WebRequest "https://github.com/conan-io/conan/releases/download/$ConanVersion/$ConanInstaller" -OutFile $ConanInstaller
Start-Process -Wait ".\$ConanInstaller"
Remove-Item $ConanInstaller
```

Run Makefile targets from Git Bash.

For development, also install Python, Poetry and clang-format:

```powershell
winget install --exact --id Python.Python.3.12
python -m pip install --user pipx
python -m pipx ensurepath
python -m pipx install poetry
python -m pipx install "clang-format>=22.1.8"
```


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
