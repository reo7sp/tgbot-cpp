#ifndef TGBOT_EVENTBROADCASTER_H
#define TGBOT_EVENTBROADCASTER_H

#include "tgbot/export.h"
#include "tgbot/types/Message.h"
#include "tgbot/types/InlineQuery.h"
#include "tgbot/types/ChosenInlineResult.h"
#include "tgbot/types/CallbackQuery.h"
#include "tgbot/types/ShippingQuery.h"
#include "tgbot/types/PreCheckoutQuery.h"
#include "tgbot/types/Poll.h"
#include "tgbot/types/PollAnswer.h"
#include "tgbot/types/ChatMemberUpdated.h"
#include "tgbot/types/ChatJoinRequest.h"
#include "tgbot/types/SuccessfulPayment.h"

#include <functional>
#include <initializer_list>
#include <string>
#include <unordered_map>
#include <vector>

namespace TgBot {

class EventHandler;

/**
 * @brief This class holds all event listeners.
 *
 * @ingroup general
 */
class TGBOT_API EventBroadcaster {

friend EventHandler;

public:
    typedef std::function<void (const Message::Ptr)> MessageListener;
    typedef std::function<void (const InlineQuery::Ptr)> InlineQueryListener;
    typedef std::function<void (const ChosenInlineResult::Ptr)> ChosenInlineResultListener;
    typedef std::function<void (const CallbackQuery::Ptr)> CallbackQueryListener;
    typedef std::function<void (const ShippingQuery::Ptr)> ShippingQueryListener;
    typedef std::function<void (const PreCheckoutQuery::Ptr)> PreCheckoutQueryListener;
    typedef std::function<void (const Poll::Ptr)> PollListener;
    typedef std::function<void (const PollAnswer::Ptr)> PollAnswerListener;
    typedef std::function<void (const ChatMemberUpdated::Ptr)> ChatMemberUpdatedListener;
    typedef std::function<void (const ChatJoinRequest::Ptr)> ChatJoinRequestListener;
    typedef std::function<void (const Message::Ptr, const SuccessfulPayment::Ptr)> SuccessfulPaymentListener;

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
     * @brief Registers listener which receives new incoming inline queries
     * @param listener Listener.
     */
    inline void onInlineQuery(const InlineQueryListener& listener) {
        _onInlineQueryListeners.push_back(listener);
    }

    /**
     * @brief Registers listener which receives the results of an inline query that was chosen by a user and sent to their chat partner.
     * Please see https://core.telegram.org/bots/inline#collecting-feedback for details on how to enable these updates for your bot.
     * 
     * @param listener Listener.
     */
    inline void onChosenInlineResult(const ChosenInlineResultListener& listener){
        _onChosenInlineResultListeners.push_back(listener);
    }

    /**
     * @brief Registers listener which receives new incoming callback queries
     * @param listener Listener.
     */
    inline void onCallbackQuery(const CallbackQueryListener& listener){
        _onCallbackQueryListeners.push_back(listener);
    }

    /**
     * @brief Registers listener which receives new incoming shipping queries.
     * Only for invoices with flexible price
     * 
     * @param listener Listener.
     */
    inline void onShippingQuery(const ShippingQueryListener& listener){
        _onShippingQueryListeners.push_back(listener);
    }

    /**
     * @brief Registers listener which receives new incoming pre-checkout queries.
     * Contains full information about checkout
     * 
     * @param listener Listener.
     */
    inline void onPreCheckoutQuery(const PreCheckoutQueryListener& listener){
        _onPreCheckoutQueryListeners.push_back(listener);
    }

    /**
     * @brief Registers listener which receives new poll states.
     * Bots receive only updates about stopped polls and polls, which are sent by the bot
     * 
     * @param listener Listener.
     */
    inline void onPoll(const PollListener& listener){
        _onPollListeners.push_back(listener);
    }

    /**
     * @brief Registers listener which receives an answer if a user changed their answer in a non-anonymous poll.
     * Bots receive new votes only in polls that were sent by the bot itself.
     * 
     * @param listener Listener.
     */
    inline void onPollAnswer(const PollAnswerListener& listener){
        _onPollAnswerListeners.push_back(listener);
    }

    /**
     * @brief Registers listener which receives the bot's chat member status if it was updated in a chat.
     * For private chats, this update is received only when the bot is blocked or unblocked by the user.
     * 
     * @param listener Listener.
     */
    inline void onMyChatMember(const ChatMemberUpdatedListener& listener){
        _onMyChatMemberListeners.push_back(listener);
    }

    /**
     * @brief Registers listener which receives a status if a chat member's status was updated in a chat.
     * The bot must be an administrator in the chat and must explicitly specify “chat_member” in the list of allowedUpdates to receive these updates.
     * 
     * @param listener Listener.
     */
    inline void onChatMember(const ChatMemberUpdatedListener& listener){
        _onChatMemberListeners.push_back(listener);
    }

    /**
     * @brief Registers listener which receives requests to join the chat.
     * The bot must have the canInviteUsers administrator right in the chat to receive these updates.
     * 
     * @param listener Listener.
     */
    inline void onChatJoinRequest(const ChatJoinRequestListener& listener){
        _onChatJoinRequestListeners.push_back(listener);
    }

    /**
    * @brief Registers listener which receives information about successful payments.
    * This listener is triggered when a successful payment is received by the bot.
    * 
    * @param listener Listener.
    */
    inline void onSuccessfulPayment(const SuccessfulPaymentListener& listener) {
        _onSuccessfulPaymentListeners.push_back(listener);
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

    inline void broadcastInlineQuery(const InlineQuery::Ptr& query) const {
        broadcast<InlineQueryListener, InlineQuery::Ptr>(_onInlineQueryListeners, query);
    }

    inline void broadcastChosenInlineResult(const ChosenInlineResult::Ptr& result) const {
        broadcast<ChosenInlineResultListener, ChosenInlineResult::Ptr>(_onChosenInlineResultListeners, result);
    }

    inline void broadcastCallbackQuery(const CallbackQuery::Ptr& result) const {
        broadcast<CallbackQueryListener, CallbackQuery::Ptr>(_onCallbackQueryListeners, result);
    }

    inline void broadcastShippingQuery(const ShippingQuery::Ptr& result) const {
        broadcast<ShippingQueryListener, ShippingQuery::Ptr>(_onShippingQueryListeners, result);
    }

    inline void broadcastPreCheckoutQuery(const PreCheckoutQuery::Ptr& result) const {
        broadcast<PreCheckoutQueryListener, PreCheckoutQuery::Ptr>(_onPreCheckoutQueryListeners, result);
    }

    inline void broadcastPoll(const Poll::Ptr& result) const {
        broadcast<PollListener, Poll::Ptr>(_onPollListeners, result);
    }

    inline void broadcastPollAnswer(const PollAnswer::Ptr& result) const {
        broadcast<PollAnswerListener, PollAnswer::Ptr>(_onPollAnswerListeners, result);
    }

    inline void broadcastMyChatMember(const ChatMemberUpdated::Ptr& result) const {
        broadcast<ChatMemberUpdatedListener, ChatMemberUpdated::Ptr>(_onMyChatMemberListeners, result);
    }

    inline void broadcastChatMember(const ChatMemberUpdated::Ptr& result) const {
        broadcast<ChatMemberUpdatedListener, ChatMemberUpdated::Ptr>(_onChatMemberListeners, result);
    }

    inline void broadcastChatJoinRequest(const ChatJoinRequest::Ptr& result) const {
        broadcast<ChatJoinRequestListener, ChatJoinRequest::Ptr>(_onChatJoinRequestListeners, result);
    }

    inline void broadcastSuccessfulPayment(const Message::Ptr& message) const {
        if (!message || !message->successfulPayment) {
            return;
        }
        for (const auto& listener : _onSuccessfulPaymentListeners) {
            listener(message, message->successfulPayment);
        }
    }


    std::vector<MessageListener> _onAnyMessageListeners;
    std::unordered_map<std::string, MessageListener> _onCommandListeners;
    std::vector<MessageListener> _onUnknownCommandListeners;
    std::vector<MessageListener> _onNonCommandMessageListeners;
    std::vector<MessageListener> _onEditedMessageListeners;
    std::vector<InlineQueryListener> _onInlineQueryListeners;
    std::vector<ChosenInlineResultListener> _onChosenInlineResultListeners;
    std::vector<CallbackQueryListener> _onCallbackQueryListeners;
    std::vector<ShippingQueryListener> _onShippingQueryListeners;
    std::vector<PreCheckoutQueryListener> _onPreCheckoutQueryListeners;
    std::vector<PollListener> _onPollListeners;
    std::vector<PollAnswerListener> _onPollAnswerListeners;
    std::vector<ChatMemberUpdatedListener> _onMyChatMemberListeners;
    std::vector<ChatMemberUpdatedListener> _onChatMemberListeners;
    std::vector<ChatJoinRequestListener> _onChatJoinRequestListeners;
    std::vector<SuccessfulPaymentListener> _onSuccessfulPaymentListeners;

};

}

#endif //TGBOT_EVENTBROADCASTER_H
