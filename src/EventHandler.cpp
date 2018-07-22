//
// Created by Oleg Morozenkov on 23.01.17.
//

#include "tgbot/EventHandler.h"
#include <algorithm>

using namespace std;

namespace TgBot {

void EventHandler::handleUpdate(Update::Ptr update) const {
    if (update->inlineQuery != nullptr) {
        _broadcaster.broadcastInlineQuery(update->inlineQuery);
    }
    if (update->chosenInlineResult != nullptr) {
        _broadcaster.broadcastChosenInlineResult(update->chosenInlineResult);
    }
    if (update->callbackQuery != nullptr) {
        _broadcaster.broadcastCallbackQuery(update->callbackQuery);
    }
    if (update->message != nullptr) {
        handleMessage(update->message);
    }
}

void EventHandler::handleMessage(Message::Ptr message) const {
    _broadcaster.broadcastAnyMessage(message);

    if (StringTools::startsWith(message->text, "/")) {
        size_t splitPosition;
        size_t spacePosition = message->text.find(' ');
        size_t atSymbolPosition = message->text.find('@');
        if (spacePosition == string::npos) {
            if (atSymbolPosition == string::npos) {
                splitPosition = message->text.size();
            } else {
                splitPosition = atSymbolPosition;
            }
        } else if (atSymbolPosition == string::npos) {
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
}

}