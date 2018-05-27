//
// Created by Oleg Morozenkov on 23.01.17.
//

#include "tgbot/EventHandler.h"
#include <algorithm>

namespace TgBot {

void EventHandler::handleUpdate(const Update::Ptr update) const {
    if (update->inlineQuery != nullptr) {
        _broadcaster->broadcastInlineQuery(update->inlineQuery);
    }
    if (update->chosenInlineResult != nullptr) {
        _broadcaster->broadcastChosenInlineResult(update->chosenInlineResult);
    }
    if (update->callbackQuery != nullptr) {
        _broadcaster->broadcastCallbackQuery(update->callbackQuery);
    }
    if (update->message != nullptr) {
        handleMessage(update->message);
    }
}

void EventHandler::handleMessage(const Message::Ptr message) const {
    _broadcaster->broadcastAnyMessage(message);

    if (StringTools::startsWith(message->text, "/")) {
        uint16_t splitPosition;
        uint16_t spacePosition = message->text.find(' ');
        uint16_t atSymbolPosition = message->text.find('@');
        if (spacePosition == message->text.npos) {
            if (atSymbolPosition == message->text.npos) {
                splitPosition = message->text.size();
            } else {
                splitPosition = atSymbolPosition;
            }
        } else if (atSymbolPosition == message->text.npos) {
            splitPosition = spacePosition;
        } else {
            splitPosition = std::min(spacePosition, atSymbolPosition);
        }
        std::string command = message->text.substr(1, splitPosition - 1);
        if (!_broadcaster->broadcastCommand(command, message)) {
            _broadcaster->broadcastUnknownCommand(message);
        }
    } else {
        _broadcaster->broadcastNonCommandMessage(message);
    }
}

}