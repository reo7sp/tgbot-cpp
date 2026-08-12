#include <gtest/gtest.h>

#include "tgbot/Bot.h"
#include "tgbot/HttpClient.h"
#include "tgbot/TgLongPoll.h"

#include <atomic>
#include <csignal>
#include <exception>
#include <span>
#include <stdexcept>
#include <string>
#include <thread>

namespace {

class BlockingHttpClient final : public TgBot::HttpClient {
public:
    std::string makeRequest(const std::string&, std::span<const TgBot::HttpFormField>) const override {
        const auto cancelEpoch = _cancelEpoch.load();
        requestStarted.store(true);
        requestStarted.notify_one();

        while (cancelEpoch == _cancelEpoch.load()) {
            std::this_thread::yield();
        }

        throw TgBot::RequestCancelled();
    }

    mutable std::atomic<bool> requestStarted { false };
};

class FailingHttpClient final : public TgBot::HttpClient {
public:
    std::string makeRequest(const std::string&, std::span<const TgBot::HttpFormField>) const override {
        throw std::runtime_error("network error");
    }
};

} // namespace

TEST(TgLongPoll, StopCancelsActiveRequest) {
    BlockingHttpClient httpClient;
    TgBot::Bot bot("token", httpClient, "url");
    TgBot::TgLongPoll longPoll(bot);
    std::exception_ptr exception;

    std::thread thread([&] {
        try {
            longPoll.startLoop({ }, { });
        } catch (...) {
            exception = std::current_exception();
        }
    });

    httpClient.requestStarted.wait(false);
    EXPECT_TRUE(longPoll.isRunning());

    longPoll.stop();
    thread.join();

    EXPECT_FALSE(longPoll.isRunning());
    EXPECT_EQ(exception, nullptr);
}

TEST(TgLongPoll, StopReportsCancellationToErrorHandler) {
    BlockingHttpClient httpClient;
    TgBot::Bot bot("token", httpClient, "url");
    TgBot::TgLongPoll longPoll(bot);
    std::string errorMessage;

    std::thread thread([&] {
        longPoll.startLoop(
            [&](const std::exception& error) {
                errorMessage = error.what();
            },
            { });
    });

    httpClient.requestStarted.wait(false);
    longPoll.stop();
    thread.join();

    EXPECT_EQ(errorMessage, "request cancelled");
}

TEST(TgLongPoll, SignalStopsLoop) {
    BlockingHttpClient httpClient;
    TgBot::Bot bot("token", httpClient, "url");
    TgBot::TgLongPoll longPoll(bot);
    std::exception_ptr exception;

    std::thread thread([&] {
        try {
            longPoll.startLoop({ }, { SIGINT });
        } catch (...) {
            exception = std::current_exception();
        }
    });

    httpClient.requestStarted.wait(false);
    std::raise(SIGINT);
    thread.join();

    EXPECT_FALSE(longPoll.isRunning());
    EXPECT_EQ(exception, nullptr);
}

TEST(TgLongPoll, StartLoopPropagatesRequestErrors) {
    FailingHttpClient httpClient;
    TgBot::Bot bot("token", httpClient, "url");
    TgBot::TgLongPoll longPoll(bot);

    EXPECT_THROW(longPoll.startLoop({ }, { }), std::runtime_error);
    EXPECT_FALSE(longPoll.isRunning());
}

TEST(TgLongPoll, StartLoopHandlesRequestErrors) {
    FailingHttpClient httpClient;
    TgBot::Bot bot("token", httpClient, "url");
    TgBot::TgLongPoll longPoll(bot);
    std::string errorMessage;

    longPoll.startLoop(
        [&](const std::exception& error) {
            errorMessage = error.what();
            longPoll.stop();
        },
        { });

    EXPECT_EQ(errorMessage, "network error");
    EXPECT_FALSE(longPoll.isRunning());
}
