#include <gtest/gtest.h>

#include "tgbot/EventBroadcaster.h"
#include "tgbot/EventHandler.h"
#include "tgbot/Types.h"

#include <memory>
#include <string>
#include <vector>

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
    broadcaster.onAnyMessage([&](const auto&) {
        ++anyMessages;
    });
    broadcaster.onCommand("start", [&](const auto&) {
        ++commands;
    });
    broadcaster.onUnknownCommand([&](const auto&) {
        ++unknownCommands;
    });
    broadcaster.onNonCommandMessage([&](const auto&) {
        ++nonCommands;
    });

    handler.handleUpdate(messageUpdate("/start@my_bot argument"));

    EXPECT_EQ(anyMessages, 1);
    EXPECT_EQ(commands, 1);
    EXPECT_EQ(unknownCommands, 0);
    EXPECT_EQ(nonCommands, 0);
}

TEST(EventHandler, CommandWithoutArgumentsIgnoresBotUsername) {
    TgBot::EventBroadcaster broadcaster;
    TgBot::EventHandler handler(broadcaster);
    int commands = 0;
    broadcaster.onCommand("start", [&](const auto&) {
        ++commands;
    });

    handler.handleUpdate(messageUpdate("/start@my_bot"));

    EXPECT_EQ(commands, 1);
}

TEST(EventHandler, UnknownCommandNotifiesUnknownCommandListener) {
    TgBot::EventBroadcaster broadcaster;
    TgBot::EventHandler handler(broadcaster);
    int unknownCommands = 0;
    broadcaster.onUnknownCommand([&](const auto&) {
        ++unknownCommands;
    });

    handler.handleUpdate(messageUpdate("/missing argument"));

    EXPECT_EQ(unknownCommands, 1);
}

TEST(EventHandler, PlainTextNotifiesNonCommandListener) {
    TgBot::EventBroadcaster broadcaster;
    TgBot::EventHandler handler(broadcaster);
    int nonCommands = 0;
    broadcaster.onNonCommandMessage([&](const auto&) {
        ++nonCommands;
    });

    handler.handleUpdate(messageUpdate("hello"));

    EXPECT_EQ(nonCommands, 1);
}

TEST(EventHandler, RemovedCommandListenerIsNotCalled) {
    TgBot::EventBroadcaster broadcaster;
    TgBot::EventHandler handler(broadcaster);
    int commands = 0;
    int unknownCommands = 0;
    broadcaster.onCommand("start", [&](const auto&) {
        ++commands;
    });
    broadcaster.onCommand("start", nullptr);
    broadcaster.onUnknownCommand([&](const auto&) {
        ++unknownCommands;
    });

    handler.handleUpdate(messageUpdate("/start"));

    EXPECT_EQ(commands, 0);
    EXPECT_EQ(unknownCommands, 1);
}

TEST(EventHandler, CommandListCanBeRegisteredAndRemoved) {
    TgBot::EventBroadcaster broadcaster;
    TgBot::EventHandler handler(broadcaster);
    std::vector<std::string> commands;
    broadcaster.onCommand({ "start", "help" }, [&](const auto& message) {
        commands.push_back(*message->text);
    });

    handler.handleUpdate(messageUpdate("/start"));
    handler.handleUpdate(messageUpdate("/help"));
    broadcaster.onCommand({ "start", "help", "missing" }, nullptr);
    handler.handleUpdate(messageUpdate("/start"));

    EXPECT_EQ(commands, (std::vector<std::string> { "/start", "/help" }));
}

TEST(EventHandler, DispatchesEverySupportedUpdateType) {
    TgBot::EventBroadcaster broadcaster;
    TgBot::EventHandler handler(broadcaster);
    auto update = std::make_shared<TgBot::Update>();
    update->editedMessage = std::make_shared<TgBot::Message>();
    update->channelPost = std::make_shared<TgBot::Message>();
    update->editedChannelPost = std::make_shared<TgBot::Message>();
    update->inlineQuery = std::make_shared<TgBot::InlineQuery>();
    update->chosenInlineResult = std::make_shared<TgBot::ChosenInlineResult>();
    update->callbackQuery = std::make_shared<TgBot::CallbackQuery>();
    update->shippingQuery = std::make_shared<TgBot::ShippingQuery>();
    update->preCheckoutQuery = std::make_shared<TgBot::PreCheckoutQuery>();
    update->poll = std::make_shared<TgBot::Poll>();
    update->pollAnswer = std::make_shared<TgBot::PollAnswer>();
    update->myChatMember = std::make_shared<TgBot::ChatMemberUpdated>();
    update->chatMember = std::make_shared<TgBot::ChatMemberUpdated>();
    update->chatJoinRequest = std::make_shared<TgBot::ChatJoinRequest>();
    update->messageReaction = std::make_shared<TgBot::MessageReactionUpdated>();
    update->messageReactionCount = std::make_shared<TgBot::MessageReactionCountUpdated>();

    int anyMessages = 0;
    int editedMessages = 0;
    int inlineQueries = 0;
    int chosenInlineResults = 0;
    int callbackQueries = 0;
    int shippingQueries = 0;
    int preCheckoutQueries = 0;
    int polls = 0;
    int pollAnswers = 0;
    int myChatMembers = 0;
    int chatMembers = 0;
    int chatJoinRequests = 0;
    int messageReactions = 0;
    int messageReactionCounts = 0;
    broadcaster.onAnyMessage([&](const auto&) {
        ++anyMessages;
    });
    broadcaster.onEditedMessage([&](const auto&) {
        ++editedMessages;
    });
    broadcaster.onInlineQuery([&](const auto&) {
        ++inlineQueries;
    });
    broadcaster.onChosenInlineResult([&](const auto&) {
        ++chosenInlineResults;
    });
    broadcaster.onCallbackQuery([&](const auto&) {
        ++callbackQueries;
    });
    broadcaster.onShippingQuery([&](const auto&) {
        ++shippingQueries;
    });
    broadcaster.onPreCheckoutQuery([&](const auto&) {
        ++preCheckoutQueries;
    });
    broadcaster.onPoll([&](const auto&) {
        ++polls;
    });
    broadcaster.onPollAnswer([&](const auto&) {
        ++pollAnswers;
    });
    broadcaster.onMyChatMember([&](const auto&) {
        ++myChatMembers;
    });
    broadcaster.onChatMember([&](const auto&) {
        ++chatMembers;
    });
    broadcaster.onChatJoinRequest([&](const auto&) {
        ++chatJoinRequests;
    });
    broadcaster.onMessageReaction([&](const auto&) {
        ++messageReactions;
    });
    broadcaster.onMessageReactionCount([&](const auto&) {
        ++messageReactionCounts;
    });

    handler.handleUpdate(update);

    EXPECT_EQ(anyMessages, 1);
    EXPECT_EQ(editedMessages, 2);
    EXPECT_EQ(inlineQueries, 1);
    EXPECT_EQ(chosenInlineResults, 1);
    EXPECT_EQ(callbackQueries, 1);
    EXPECT_EQ(shippingQueries, 1);
    EXPECT_EQ(preCheckoutQueries, 1);
    EXPECT_EQ(polls, 1);
    EXPECT_EQ(pollAnswers, 1);
    EXPECT_EQ(myChatMembers, 1);
    EXPECT_EQ(chatMembers, 1);
    EXPECT_EQ(chatJoinRequests, 1);
    EXPECT_EQ(messageReactions, 1);
    EXPECT_EQ(messageReactionCounts, 1);
}

TEST(EventHandler, SuccessfulPaymentNotifiesListener) {
    TgBot::EventBroadcaster broadcaster;
    TgBot::EventHandler handler(broadcaster);
    auto update = messageUpdate("payment");
    update->message->successfulPayment = std::make_shared<TgBot::SuccessfulPayment>();
    std::shared_ptr<TgBot::Message> receivedMessage;
    std::shared_ptr<TgBot::SuccessfulPayment> receivedPayment;
    broadcaster.onSuccessfulPayment([&](const auto& message, const auto& payment) {
        receivedMessage = message;
        receivedPayment = payment;
    });

    handler.handleUpdate(update);

    EXPECT_EQ(receivedMessage, update->message);
    EXPECT_EQ(receivedPayment, update->message->successfulPayment);
}
