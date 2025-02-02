#include "tgbot/EventHandler.h"

namespace TgBot {

void EventHandler::handleUpdate(const Update::Ptr& update) const {
    if (update->message != nullptr) {
        handleMessage(update->message);
    }
    if (update->editedMessage != nullptr) {
        _broadcaster.broadcastEditedMessage(update->editedMessage);
    }
    if (update->channelPost != nullptr) {
        handleMessage(update->channelPost);
    }
    if (update->editedChannelPost != nullptr) {
        _broadcaster.broadcastEditedMessage(update->editedChannelPost);
    }
    if (update->inlineQuery != nullptr) {
        _broadcaster.broadcastInlineQuery(update->inlineQuery);
    }
    if (update->chosenInlineResult != nullptr) {
        _broadcaster.broadcastChosenInlineResult(update->chosenInlineResult);
    }
    if (update->callbackQuery != nullptr) {
        _broadcaster.broadcastCallbackQuery(update->callbackQuery);
    }
    if (update->shippingQuery != nullptr) {
        _broadcaster.broadcastShippingQuery(update->shippingQuery);
    }
    if (update->preCheckoutQuery != nullptr) {
        _broadcaster.broadcastPreCheckoutQuery(update->preCheckoutQuery);
    }
    if (update->poll != nullptr) {
        _broadcaster.broadcastPoll(update->poll);
    }
    if (update->pollAnswer != nullptr) {
        _broadcaster.broadcastPollAnswer(update->pollAnswer);
    }
    if (update->myChatMember != nullptr) {
        _broadcaster.broadcastMyChatMember(update->myChatMember);
    }
    if (update->chatMember != nullptr) {
        _broadcaster.broadcastChatMember(update->chatMember);
    }
    if (update->chatJoinRequest != nullptr) {
        _broadcaster.broadcastChatJoinRequest(update->chatJoinRequest);
    }
}

void EventHandler::handleMessage(const Message::Ptr& message) const {
    _broadcaster.broadcastAnyMessage(message);

    if (StringTools::startsWith(message->text, "/")) {
        std::size_t splitPosition;
        std::size_t spacePosition = message->text.find(' ');
        std::size_t atSymbolPosition = message->text.find('@');
        if (spacePosition == std::string::npos) {
            if (atSymbolPosition == std::string::npos) {
                splitPosition = message->text.size();
            } else {
                splitPosition = atSymbolPosition;
            }
        } else if (atSymbolPosition == std::string::npos) {
            splitPosition = spacePosition;
        } else {
            splitPosition = std::min(spacePosition, atSymbolPosition);
        }
        std::string command = message->text.substr(1, splitPosition - 1);
        if (!_broadcaster.broadcastCommand(command, message)) {
            _broadcaster.broadcastUnknownCommand(message);
        }
    } else {
        _broadcaster.broadcastNonCommandMessage(message);
    }
    
    if (message->successfulPayment != nullptr) {
        _broadcaster.broadcastSuccessfulPayment(message);
    }

}

}
