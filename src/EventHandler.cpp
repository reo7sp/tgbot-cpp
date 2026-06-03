#include "maxbot/EventHandler.h"
#include <iostream>
#include <variant>

namespace MaxBot {

void EventHandler::handleUpdate(const Update::Ptr& update) const {
	std::visit([&, this](auto arg) {
		using T = decltype(arg);
		if constexpr (!std::is_same_v<T, std::monostate>)
			if (!arg)
			{
				std::cerr << "error in EventHandler::handleUpdate: type: " << typeid(T).name() << " has nullptr object. Type:" << update->update_type << std::endl;
				return;
			}

		if constexpr (std::is_same_v<T, UpdateBotAddedToChat::Ptr>)
			_broadcaster.broadcastBotAddedToChat(arg);
		else if constexpr (std::is_same_v<T, UpdateBotStarted::Ptr>)
			_broadcaster.broadcastBotStarted(arg);
		else if constexpr (std::is_same_v<T, UpdateBotStopped::Ptr>)
			_broadcaster.broadcastBotStopped(arg);
		else if constexpr (std::is_same_v<T, UpdateBotRemovedFromChat::Ptr>)
			_broadcaster.broadcastBotRemovedFromChat(arg);
		else if constexpr (std::is_same_v<T, UpdateChatTitleChanged::Ptr>)
			_broadcaster.broadcastChatTitleChanged(arg);
		else if constexpr (std::is_same_v<T, UpdateDialogCleared::Ptr>)
			_broadcaster.broadcastDialogCleared(arg);
		else if constexpr (std::is_same_v<T, UpdateDialogMuted::Ptr>)
			_broadcaster.broadcastDialogMuted(arg);
		else if constexpr (std::is_same_v<T, UpdateDialogUnmuted::Ptr>)
			_broadcaster.broadcastDialogUnmuted(arg);
		else if constexpr (std::is_same_v<T, UpdateDialogRemoved::Ptr>)
			_broadcaster.broadcastDialogRemoved(arg);
		else if constexpr (std::is_same_v<T, UpdateMessageCallback::Ptr>)
			_broadcaster.broadcastCallbackQuery(arg);
		else if constexpr (std::is_same_v<T, UpdateMessageCreated::Ptr>)
			handleMessage(arg->message);
		else if constexpr (std::is_same_v<T, UpdateMessageEdited::Ptr>)
			_broadcaster.broadcastEditedMessage(arg->message);
		else if constexpr (std::is_same_v<T, UpdateMessageRemoved::Ptr>)
			_broadcaster.broadcastMessageRemoved(arg);
		else if constexpr (std::is_same_v<T, UpdateUserAddedToChat::Ptr>)
			_broadcaster.broadcastUserAddedToChat(arg);
		else if constexpr (std::is_same_v<T, UpdateUserRemovedFromChat::Ptr>)
			_broadcaster.broadcastUserRemovedFromChat(arg);
		else
			std::cerr << "error in EventHandler::handleUpdate: Unknown type: " << typeid(T).name() << " type: " << update->update_type << std::endl;
	}, update->_data);
}

void EventHandler::handleMessage(const Message::Ptr& msg) const {
    _broadcaster.broadcastAnyMessage(msg);

    if (msg->body && StringTools::startsWith(msg->body->text, "/")) {
        std::size_t splitPosition;
        std::size_t spacePosition = msg->body->text.find(' ');
        std::size_t atSymbolPosition = msg->body->text.find('@');
        if (spacePosition == std::string::npos) {
            if (atSymbolPosition == std::string::npos) {
                splitPosition = msg->body->text.size();
            } else {
                splitPosition = atSymbolPosition;
            }
        } else if (atSymbolPosition == std::string::npos) {
            splitPosition = spacePosition;
        } else {
            splitPosition = std::min(spacePosition, atSymbolPosition);
        }
        std::string command = msg->body->text.substr(1, splitPosition - 1);
        if (!_broadcaster.broadcastCommand(command, msg)) {
            _broadcaster.broadcastUnknownCommand(msg);
        }
    } else {
        _broadcaster.broadcastNonCommandMessage(msg);
    }
}

}
