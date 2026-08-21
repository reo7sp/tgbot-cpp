#include "tgbot/EventBroadcaster.h"

namespace TgBot {

template<typename ListenerType, typename ObjectType>
void EventBroadcaster::broadcast(const std::vector<ListenerType>& listeners, ObjectType object) const {
    if (!object) {
        return;
    }
    for (const ListenerType& listener : listeners) {
        listener(object);
    }
}

void EventBroadcaster::onAnyMessage(const MessageListener& listener) {
    _onAnyMessageListeners.push_back(listener);
}

void EventBroadcaster::onCommand(std::string_view commandName, const MessageListener& listener) {
    if (listener) {
        _onCommandListeners.insert_or_assign(std::string(commandName), listener);
    } else {
        const auto command = _onCommandListeners.find(commandName);
        if (command != _onCommandListeners.end()) {
            _onCommandListeners.erase(command);
        }
    }
}

void EventBroadcaster::onCommand(std::initializer_list<std::string_view> commandsList,
                                 const MessageListener& listener) {
    if (listener) {
        for (const std::string_view command : commandsList) {
            _onCommandListeners.insert_or_assign(std::string(command), listener);
        }
    } else {
        for (const std::string_view command : commandsList) {
            const auto item = _onCommandListeners.find(command);
            if (item != _onCommandListeners.end()) {
                _onCommandListeners.erase(item);
            }
        }
    }
}

void EventBroadcaster::onUnknownCommand(const MessageListener& listener) {
    _onUnknownCommandListeners.push_back(listener);
}

void EventBroadcaster::onNonCommandMessage(const MessageListener& listener) {
    _onNonCommandMessageListeners.push_back(listener);
}

void EventBroadcaster::onEditedMessage(const MessageListener& listener) {
    _onEditedMessageListeners.push_back(listener);
}

void EventBroadcaster::onInlineQuery(const InlineQueryListener& listener) {
    _onInlineQueryListeners.push_back(listener);
}

void EventBroadcaster::onChosenInlineResult(const ChosenInlineResultListener& listener) {
    _onChosenInlineResultListeners.push_back(listener);
}

void EventBroadcaster::onCallbackQuery(const CallbackQueryListener& listener) {
    _onCallbackQueryListeners.push_back(listener);
}

void EventBroadcaster::onShippingQuery(const ShippingQueryListener& listener) {
    _onShippingQueryListeners.push_back(listener);
}

void EventBroadcaster::onPreCheckoutQuery(const PreCheckoutQueryListener& listener) {
    _onPreCheckoutQueryListeners.push_back(listener);
}

void EventBroadcaster::onPoll(const PollListener& listener) {
    _onPollListeners.push_back(listener);
}

void EventBroadcaster::onPollAnswer(const PollAnswerListener& listener) {
    _onPollAnswerListeners.push_back(listener);
}

void EventBroadcaster::onMyChatMember(const ChatMemberUpdatedListener& listener) {
    _onMyChatMemberListeners.push_back(listener);
}

void EventBroadcaster::onChatMember(const ChatMemberUpdatedListener& listener) {
    _onChatMemberListeners.push_back(listener);
}

void EventBroadcaster::onChatJoinRequest(const ChatJoinRequestListener& listener) {
    _onChatJoinRequestListeners.push_back(listener);
}

void EventBroadcaster::onMessageReaction(const MessageReactionUpdatedListener& listener) {
    _onMessageReactionUpdatedListener.push_back(listener);
}

void EventBroadcaster::onMessageReactionCount(const MessageReactionCountUpdatedListener& listener) {
    _onMessageReactionCountUpdatedListener.push_back(listener);
}

void EventBroadcaster::onSuccessfulPayment(const SuccessfulPaymentListener& listener) {
    _onSuccessfulPaymentListeners.push_back(listener);
}

void EventBroadcaster::broadcastAnyMessage(const std::shared_ptr<Message>& message) const {
    broadcast<MessageListener, std::shared_ptr<Message>>(_onAnyMessageListeners, message);
}

bool EventBroadcaster::broadcastCommand(std::string_view command, const std::shared_ptr<Message>& message) const {
    const auto iter = _onCommandListeners.find(command);
    if (iter == _onCommandListeners.end()) {
        return false;
    }
    iter->second(message);
    return true;
}

void EventBroadcaster::broadcastUnknownCommand(const std::shared_ptr<Message>& message) const {
    broadcast<MessageListener, std::shared_ptr<Message>>(_onUnknownCommandListeners, message);
}

void EventBroadcaster::broadcastNonCommandMessage(const std::shared_ptr<Message>& message) const {
    broadcast<MessageListener, std::shared_ptr<Message>>(_onNonCommandMessageListeners, message);
}

void EventBroadcaster::broadcastEditedMessage(const std::shared_ptr<Message>& message) const {
    broadcast<MessageListener, std::shared_ptr<Message>>(_onEditedMessageListeners, message);
}

void EventBroadcaster::broadcastInlineQuery(const std::shared_ptr<InlineQuery>& query) const {
    broadcast<InlineQueryListener, std::shared_ptr<InlineQuery>>(_onInlineQueryListeners, query);
}

void EventBroadcaster::broadcastChosenInlineResult(const std::shared_ptr<ChosenInlineResult>& result) const {
    broadcast<ChosenInlineResultListener, std::shared_ptr<ChosenInlineResult>>(_onChosenInlineResultListeners, result);
}

void EventBroadcaster::broadcastCallbackQuery(const std::shared_ptr<CallbackQuery>& result) const {
    broadcast<CallbackQueryListener, std::shared_ptr<CallbackQuery>>(_onCallbackQueryListeners, result);
}

void EventBroadcaster::broadcastShippingQuery(const std::shared_ptr<ShippingQuery>& result) const {
    broadcast<ShippingQueryListener, std::shared_ptr<ShippingQuery>>(_onShippingQueryListeners, result);
}

void EventBroadcaster::broadcastPreCheckoutQuery(const std::shared_ptr<PreCheckoutQuery>& result) const {
    broadcast<PreCheckoutQueryListener, std::shared_ptr<PreCheckoutQuery>>(_onPreCheckoutQueryListeners, result);
}

void EventBroadcaster::broadcastPoll(const std::shared_ptr<Poll>& result) const {
    broadcast<PollListener, std::shared_ptr<Poll>>(_onPollListeners, result);
}

void EventBroadcaster::broadcastPollAnswer(const std::shared_ptr<PollAnswer>& result) const {
    broadcast<PollAnswerListener, std::shared_ptr<PollAnswer>>(_onPollAnswerListeners, result);
}

void EventBroadcaster::broadcastMyChatMember(const std::shared_ptr<ChatMemberUpdated>& result) const {
    broadcast<ChatMemberUpdatedListener, std::shared_ptr<ChatMemberUpdated>>(_onMyChatMemberListeners, result);
}

void EventBroadcaster::broadcastChatMember(const std::shared_ptr<ChatMemberUpdated>& result) const {
    broadcast<ChatMemberUpdatedListener, std::shared_ptr<ChatMemberUpdated>>(_onChatMemberListeners, result);
}

void EventBroadcaster::broadcastChatJoinRequest(const std::shared_ptr<ChatJoinRequest>& result) const {
    broadcast<ChatJoinRequestListener, std::shared_ptr<ChatJoinRequest>>(_onChatJoinRequestListeners, result);
}

void EventBroadcaster::broadcastMessageReactionUpdated(
    const std::shared_ptr<MessageReactionUpdated>& messageReaction) const {
    broadcast<MessageReactionUpdatedListener, std::shared_ptr<MessageReactionUpdated>>(
        _onMessageReactionUpdatedListener, messageReaction);
}

void EventBroadcaster::broadcastMessageReactionCountUpdated(
    const std::shared_ptr<MessageReactionCountUpdated>& messageReactionCount) const {
    broadcast<MessageReactionCountUpdatedListener, std::shared_ptr<MessageReactionCountUpdated>>(
        _onMessageReactionCountUpdatedListener, messageReactionCount);
}

void EventBroadcaster::broadcastSuccessfulPayment(const std::shared_ptr<Message>& message) const {
    if (!message || !message->successfulPayment) {
        return;
    }
    for (const auto& listener : _onSuccessfulPaymentListeners) {
        listener(message, message->successfulPayment);
    }
}

} // namespace TgBot
