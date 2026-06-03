#ifndef MAXBOT_EVENTBROADCASTER_H
#define MAXBOT_EVENTBROADCASTER_H

#include "maxbot/export.h"
#include "maxbot/types/Message.h"
#include "maxbot/types/UpdateBotAddedToChat.h"
#include "maxbot/types/UpdateBotStarted.h"
#include "maxbot/types/UpdateBotStopped.h"
#include "maxbot/types/UpdateBotRemovedFromChat.h"
#include "maxbot/types/UpdateChatTitleChanged.h"
#include "maxbot/types/UpdateDialogCleared.h"
#include "maxbot/types/UpdateDialogMuted.h"
#include "maxbot/types/UpdateDialogUnmuted.h"
#include "maxbot/types/UpdateDialogRemoved.h"
#include "maxbot/types/UpdateMessageCallback.h"
#include "maxbot/types/UpdateMessageRemoved.h"
#include "maxbot/types/UpdateUserAddedToChat.h"
#include "maxbot/types/UpdateUserRemovedFromChat.h"

#include <functional>
#include <initializer_list>
#include <string>
#include <unordered_map>
#include <vector>

namespace MaxBot {

class EventHandler;

/**
 * @brief This class holds all event listeners.
 *
 * @ingroup general
 */
class MAXBOT_API EventBroadcaster {

friend EventHandler;

public:
    typedef std::function<void (const Message::Ptr)> MessageListener;
    typedef std::function<void (const UpdateBotAddedToChat::Ptr)> UpdateBotAddedToChatListener;
    typedef std::function<void (const UpdateBotStarted::Ptr)> UpdateBotStartedListener;
    typedef std::function<void (const UpdateBotStopped::Ptr)> UpdateBotStoppedListener;
    typedef std::function<void (const UpdateBotRemovedFromChat::Ptr)> UpdateBotRemovedFromChatListener;
    typedef std::function<void (const UpdateChatTitleChanged::Ptr)> UpdateChatTitleChangedListener;
    typedef std::function<void (const UpdateDialogCleared::Ptr)> UpdateDialogClearedListener;
    typedef std::function<void (const UpdateDialogMuted::Ptr)> UpdateDialogMutedListener;
    typedef std::function<void (const UpdateDialogUnmuted::Ptr)> UpdateDialogUnmutedListener;
    typedef std::function<void (const UpdateDialogRemoved::Ptr)> UpdateDialogRemovedListener;
    typedef std::function<void (const UpdateMessageCallback::Ptr)> MessageCallbackListener;
    typedef std::function<void (const UpdateMessageRemoved::Ptr)> UpdateMessageRemovedListener;
    typedef std::function<void (const UpdateUserAddedToChat::Ptr)> UpdateUserAddedToChatListener;
    typedef std::function<void (const UpdateUserRemovedFromChat::Ptr)> UpdateUserRemovedFromChatListener;

    /**
     * @brief Registers listener which receives new incoming message of any kind - text, photo, sticker, etc.
     * @param listener Listener.
     */
    inline void onAnyMessage(const MessageListener& listener) {
        _onAnyMessageListeners.push_back(listener);
    }

    /**
     * @brief Registers listener which receives all messages with commands (messages with leading '/' char).
     * @param commandName Command name which listener can handle.
     * @param listener Listener. Pass nullptr to remove listener of command
     */
    inline void onCommand(const std::string& commandName, const MessageListener& listener) {
        if (listener) {
            _onCommandListeners[commandName] = listener;
        } else {
            _onCommandListeners.erase(commandName);
        }
    }

    /**
    * @brief Registers listener which receives all messages with commands (messages with leading '/' char).
    * @param commandsList Commands names which listener can handle.
    * @param listener Listener. Pass nullptr to remove listener of commands
    */
    inline void onCommand(const std::initializer_list<std::string>& commandsList, const MessageListener& listener) {
        if (listener) {
            for (const auto& command : commandsList) {
                _onCommandListeners[command] = listener;
            }
        } else {
            for (const auto& command : commandsList) {
                _onCommandListeners.erase(command);
            }
        }
    }

    /**
     * @brief Registers listener which receives all messages with commands (messages with leading '/' char) which haven't been handled by other listeners.
     * @param listener Listener.
     */
    inline void onUnknownCommand(const MessageListener& listener) {
        _onUnknownCommandListeners.push_back(listener);
    }

    /**
     * @brief Registers listener which receives all messages without commands (messages with no leading '/' char)
     * @param listener Listener.
     */
    inline void onNonCommandMessage(const MessageListener& listener) {
        _onNonCommandMessageListeners.push_back(listener);
    }

    /**
     * @brief Registers listener which receives new versions of a message that is known to the bot and was edited
     * @param listener Listener.
     */
    inline void onEditedMessage(const MessageListener& listener) {
        _onEditedMessageListeners.push_back(listener);
    }

    /**
     * @brief Registers listener which receives event when bot is added to a chat or channel.
     * @param listener Listener.
     */
    inline void onBotAddedToChat(const UpdateBotAddedToChatListener& listener) {
        _onBotAddedToChatListeners.push_back(listener);
    }

    /**
     * @brief Registers listener which receives event when user presses the Start button.
     * @param listener Listener.
     */
    inline void onBotStarted(const UpdateBotStartedListener& listener) {
        _onBotStartedListeners.push_back(listener);
    }

    /**
     * @brief Registers listener which receives event when user stops the bot.
     * @param listener Listener.
     */
    inline void onBotStopped(const UpdateBotStoppedListener& listener) {
        _onBotStoppedListeners.push_back(listener);
    }

    /**
     * @brief Registers listener which receives event when bot is removed from a chat or channel.
     * @param listener Listener.
     */
    inline void onBotRemovedFromChat(const UpdateBotRemovedFromChatListener& listener) {
        _onBotRemovedFromChatListeners.push_back(listener);
    }

    /**
     * @brief Registers listener which receives event when chat title is changed.
     * @param listener Listener.
     */
    inline void onChatTitleChanged(const UpdateChatTitleChangedListener& listener) {
        _onChatTitleChangedListeners.push_back(listener);
    }

    /**
     * @brief Registers listener which receives event when dialog history is cleared.
     * @param listener Listener.
     */
    inline void onDialogCleared(const UpdateDialogClearedListener& listener) {
        _onDialogClearedListeners.push_back(listener);
    }

    /**
     * @brief Registers listener which receives event when dialog is muted.
     * @param listener Listener.
     */
    inline void onDialogMuted(const UpdateDialogMutedListener& listener) {
        _onDialogMutedListeners.push_back(listener);
    }

    /**
     * @brief Registers listener which receives event when dialog is unmuted.
     * @param listener Listener.
     */
    inline void onDialogUnmuted(const UpdateDialogUnmutedListener& listener) {
        _onDialogUnmutedListeners.push_back(listener);
    }

    /**
     * @brief Registers listener which receives event when dialog is removed.
     * @param listener Listener.
     */
    inline void onDialogRemoved(const UpdateDialogRemovedListener& listener) {
        _onDialogRemovedListeners.push_back(listener);
    }

    /**
     * @brief Registers listener which receives new incoming callback queries.
     * @param listener Listener.
     */
    inline void onMessageCallback(const MessageCallbackListener& listener) {
        _onMessageCallbackListeners.push_back(listener);
    }

    /**
     * @brief Registers listener which receives event when message is removed.
     * @param listener Listener.
     */
    inline void onMessageRemoved(const UpdateMessageRemovedListener& listener) {
        _onMessageRemovedListeners.push_back(listener);
    }

    /**
     * @brief Registers listener which receives event when user is added to chat.
     * @param listener Listener.
     */
    inline void onUserAddedToChat(const UpdateUserAddedToChatListener& listener) {
        _onUserAddedToChatListeners.push_back(listener);
    }

    /**
     * @brief Registers listener which receives event when user is removed from chat.
     * @param listener Listener.
     */
    inline void onUserRemovedFromChat(const UpdateUserRemovedFromChatListener& listener) {
        _onUserRemovedFromChatListeners.push_back(listener);
    }


private:
    template<typename ListenerType, typename ObjectType>
    inline void broadcast(const std::vector<ListenerType>& listeners, const ObjectType object) const {
        if (!object)
            return;

        for (const ListenerType& item : listeners) {
            item(object);
        }
    }

    inline void broadcastAnyMessage(const Message::Ptr& message) const {
        broadcast<MessageListener, Message::Ptr>(_onAnyMessageListeners, message);
    }

    inline bool broadcastCommand(const std::string& command, const Message::Ptr& message) const {
        auto iter = _onCommandListeners.find(command);
        if (iter == _onCommandListeners.end()) {
            return false;
        }
        iter->second(message);
        return true;
    }

    inline void broadcastUnknownCommand(const Message::Ptr& message) const {
        broadcast<MessageListener, Message::Ptr>(_onUnknownCommandListeners, message);
    }

    inline void broadcastNonCommandMessage(const Message::Ptr& message) const {
        broadcast<MessageListener, Message::Ptr>(_onNonCommandMessageListeners, message);
    }

    inline void broadcastEditedMessage(const Message::Ptr& message) const {
        broadcast<MessageListener, Message::Ptr>(_onEditedMessageListeners, message);
    }

    inline void broadcastBotAddedToChat(const UpdateBotAddedToChat::Ptr& update) const {
        broadcast<UpdateBotAddedToChatListener, UpdateBotAddedToChat::Ptr>(_onBotAddedToChatListeners, update);
    }

    inline void broadcastBotStarted(const UpdateBotStarted::Ptr& update) const {
        broadcast<UpdateBotStartedListener, UpdateBotStarted::Ptr>(_onBotStartedListeners, update);
    }

    inline void broadcastBotStopped(const UpdateBotStopped::Ptr& update) const {
        broadcast<UpdateBotStoppedListener, UpdateBotStopped::Ptr>(_onBotStoppedListeners, update);
    }

    inline void broadcastBotRemovedFromChat(const UpdateBotRemovedFromChat::Ptr& update) const {
        broadcast<UpdateBotRemovedFromChatListener, UpdateBotRemovedFromChat::Ptr>(_onBotRemovedFromChatListeners, update);
    }

    inline void broadcastChatTitleChanged(const UpdateChatTitleChanged::Ptr& update) const {
        broadcast<UpdateChatTitleChangedListener, UpdateChatTitleChanged::Ptr>(_onChatTitleChangedListeners, update);
    }

    inline void broadcastDialogCleared(const UpdateDialogCleared::Ptr& update) const {
        broadcast<UpdateDialogClearedListener, UpdateDialogCleared::Ptr>(_onDialogClearedListeners, update);
    }

    inline void broadcastDialogMuted(const UpdateDialogMuted::Ptr& update) const {
        broadcast<UpdateDialogMutedListener, UpdateDialogMuted::Ptr>(_onDialogMutedListeners, update);
    }

    inline void broadcastDialogUnmuted(const UpdateDialogUnmuted::Ptr& update) const {
        broadcast<UpdateDialogUnmutedListener, UpdateDialogUnmuted::Ptr>(_onDialogUnmutedListeners, update);
    }

    inline void broadcastDialogRemoved(const UpdateDialogRemoved::Ptr& update) const {
        broadcast<UpdateDialogRemovedListener, UpdateDialogRemoved::Ptr>(_onDialogRemovedListeners, update);
    }

    inline void broadcastCallbackQuery(const UpdateMessageCallback::Ptr& callback) const {
        broadcast<MessageCallbackListener, UpdateMessageCallback::Ptr>(_onMessageCallbackListeners, callback);
    }

    inline void broadcastMessageRemoved(const UpdateMessageRemoved::Ptr& update) const {
        broadcast<UpdateMessageRemovedListener, UpdateMessageRemoved::Ptr>(_onMessageRemovedListeners, update);
    }

    inline void broadcastUserAddedToChat(const UpdateUserAddedToChat::Ptr& update) const {
        broadcast<UpdateUserAddedToChatListener, UpdateUserAddedToChat::Ptr>(_onUserAddedToChatListeners, update);
    }

    inline void broadcastUserRemovedFromChat(const UpdateUserRemovedFromChat::Ptr& update) const {
        broadcast<UpdateUserRemovedFromChatListener, UpdateUserRemovedFromChat::Ptr>(_onUserRemovedFromChatListeners, update);
    }


    std::vector<MessageListener> _onAnyMessageListeners;
    std::unordered_map<std::string, MessageListener> _onCommandListeners;
    std::vector<MessageListener> _onUnknownCommandListeners;
    std::vector<MessageListener> _onNonCommandMessageListeners;
    std::vector<MessageListener> _onEditedMessageListeners;
    std::vector<UpdateBotAddedToChatListener> _onBotAddedToChatListeners;
    std::vector<UpdateBotStartedListener> _onBotStartedListeners;
    std::vector<UpdateBotStoppedListener> _onBotStoppedListeners;
    std::vector<UpdateBotRemovedFromChatListener> _onBotRemovedFromChatListeners;
    std::vector<UpdateChatTitleChangedListener> _onChatTitleChangedListeners;
    std::vector<UpdateDialogClearedListener> _onDialogClearedListeners;
    std::vector<UpdateDialogMutedListener> _onDialogMutedListeners;
    std::vector<UpdateDialogUnmutedListener> _onDialogUnmutedListeners;
    std::vector<UpdateDialogRemovedListener> _onDialogRemovedListeners;
    std::vector<MessageCallbackListener> _onMessageCallbackListeners;
    std::vector<UpdateMessageRemovedListener> _onMessageRemovedListeners;
    std::vector<UpdateUserAddedToChatListener> _onUserAddedToChatListeners;
    std::vector<UpdateUserRemovedFromChatListener> _onUserRemovedFromChatListeners;

};

}

#endif //MAXBOT_EVENTBROADCASTER_H
