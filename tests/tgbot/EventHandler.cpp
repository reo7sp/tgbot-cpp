#include <gtest/gtest.h>

#include "tgbot/EventBroadcaster.h"
#include "tgbot/EventHandler.h"
#include "tgbot/types/Message.h"
#include "tgbot/types/Update.h"

#include <memory>
#include <string>

namespace {

TgBot::Update::Ptr messageUpdate(const std::string& text) {
    auto message = std::make_shared<TgBot::Message>();
    message->text = text;
    auto update = std::make_shared<TgBot::Update>();
    update->message = message;

    return update;
}

} // namespace

TEST(EventHandler, KnownCommandNotifiesAnyAndMatchingCommandListeners) {
    TgBot::EventBroadcaster broadcaster;
    TgBot::EventHandler handler(broadcaster);
    int anyMessages = 0;
    int commands = 0;
    int unknownCommands = 0;
    int nonCommands = 0;
    broadcaster.onAnyMessage([&](const auto&) { ++anyMessages; });
    broadcaster.onCommand("start", [&](const auto&) { ++commands; });
    broadcaster.onUnknownCommand([&](const auto&) { ++unknownCommands; });
    broadcaster.onNonCommandMessage([&](const auto&) { ++nonCommands; });

    handler.handleUpdate(messageUpdate("/start@my_bot argument"));

    EXPECT_EQ(anyMessages, 1);
    EXPECT_EQ(commands, 1);
    EXPECT_EQ(unknownCommands, 0);
    EXPECT_EQ(nonCommands, 0);
}

TEST(EventHandler, UnknownCommandNotifiesUnknownCommandListener) {
    TgBot::EventBroadcaster broadcaster;
    TgBot::EventHandler handler(broadcaster);
    int unknownCommands = 0;
    broadcaster.onUnknownCommand([&](const auto&) { ++unknownCommands; });

    handler.handleUpdate(messageUpdate("/missing argument"));

    EXPECT_EQ(unknownCommands, 1);
}

TEST(EventHandler, PlainTextNotifiesNonCommandListener) {
    TgBot::EventBroadcaster broadcaster;
    TgBot::EventHandler handler(broadcaster);
    int nonCommands = 0;
    broadcaster.onNonCommandMessage([&](const auto&) { ++nonCommands; });

    handler.handleUpdate(messageUpdate("hello"));

    EXPECT_EQ(nonCommands, 1);
}

TEST(EventHandler, RemovedCommandListenerIsNotCalled) {
    TgBot::EventBroadcaster broadcaster;
    TgBot::EventHandler handler(broadcaster);
    int commands = 0;
    int unknownCommands = 0;
    broadcaster.onCommand("start", [&](const auto&) { ++commands; });
    broadcaster.onCommand("start", nullptr);
    broadcaster.onUnknownCommand([&](const auto&) { ++unknownCommands; });

    handler.handleUpdate(messageUpdate("/start"));

    EXPECT_EQ(commands, 0);
    EXPECT_EQ(unknownCommands, 1);
}
