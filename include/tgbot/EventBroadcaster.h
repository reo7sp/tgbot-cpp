#pragma once

#include "tgbot/Types.h"
#include "tgbot/export.h"

#include <functional>
#include <initializer_list>
#include <string>
#include <string_view>
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
    using MessageListener = std::function<void(std::shared_ptr<Message>)>;
    using InlineQueryListener = std::function<void(std::shared_ptr<InlineQuery>)>;
    using ChosenInlineResultListener = std::function<void(std::shared_ptr<ChosenInlineResult>)>;
    using CallbackQueryListener = std::function<void(std::shared_ptr<CallbackQuery>)>;
    using ShippingQueryListener = std::function<void(std::shared_ptr<ShippingQuery>)>;
    using PreCheckoutQueryListener = std::function<void(std::shared_ptr<PreCheckoutQuery>)>;
    using PollListener = std::function<void(std::shared_ptr<Poll>)>;
    using PollAnswerListener = std::function<void(std::shared_ptr<PollAnswer>)>;
    using ChatMemberUpdatedListener = std::function<void(std::shared_ptr<ChatMemberUpdated>)>;
    using ChatJoinRequestListener = std::function<void(std::shared_ptr<ChatJoinRequest>)>;
    using MessageReactionUpdatedListener = std::function<void(std::shared_ptr<MessageReactionUpdated>)>;
    using MessageReactionCountUpdatedListener = std::function<void(std::shared_ptr<MessageReactionCountUpdated>)>;
    using SuccessfulPaymentListener = std::function<void(std::shared_ptr<Message>, std::shared_ptr<SuccessfulPayment>)>;

    /**
     * @brief Registers listener which receives new incoming message of any kind - text, photo, sticker, etc.
     * @param listener Listener.
     */
    void onAnyMessage(const MessageListener& listener);

    /**
     * @brief Registers listener which receives all messages with commands (messages with leading '/' char).
     * @param commandName Command name which listener can handle.
     * @param listener Listener. Pass nullptr to remove listener of command
     */
    void onCommand(std::string_view commandName, const MessageListener& listener);

    /**
    * @brief Registers listener which receives all messages with commands (messages with leading '/' char).
    * @param commandsList Commands names which listener can handle.
    * @param listener Listener. Pass nullptr to remove listener of commands
    */
    void onCommand(std::initializer_list<std::string_view> commandsList, const MessageListener& listener);

    /**
     * @brief Registers listener which receives all messages with commands (messages with leading '/' char) which haven't been handled by other listeners.
     * @param listener Listener.
     */
    void onUnknownCommand(const MessageListener& listener);

    /**
     * @brief Registers listener which receives all messages without commands (messages with no leading '/' char)
     * @param listener Listener.
     */
    void onNonCommandMessage(const MessageListener& listener);

    /**
     * @brief Registers listener which receives new versions of a message that is known to the bot and was edited
     * @param listener Listener.
     */
    void onEditedMessage(const MessageListener& listener);

    /**
     * @brief Registers listener which receives new incoming inline queries
     * @param listener Listener.
     */
    void onInlineQuery(const InlineQueryListener& listener);

    /**
     * @brief Registers listener which receives the results of an inline query that was chosen by a user and sent to their chat partner.
     * Please see https://core.telegram.org/bots/inline#collecting-feedback for details on how to enable these updates for your bot.
     * 
     * @param listener Listener.
     */
    void onChosenInlineResult(const ChosenInlineResultListener& listener);

    /**
     * @brief Registers listener which receives new incoming callback queries
     * @param listener Listener.
     */
    void onCallbackQuery(const CallbackQueryListener& listener);

    /**
     * @brief Registers listener which receives new incoming shipping queries.
     * Only for invoices with flexible price
     * 
     * @param listener Listener.
     */
    void onShippingQuery(const ShippingQueryListener& listener);

    /**
     * @brief Registers listener which receives new incoming pre-checkout queries.
     * Contains full information about checkout
     * 
     * @param listener Listener.
     */
    void onPreCheckoutQuery(const PreCheckoutQueryListener& listener);

    /**
     * @brief Registers listener which receives new poll states.
     * Bots receive only updates about stopped polls and polls, which are sent by the bot
     * 
     * @param listener Listener.
     */
    void onPoll(const PollListener& listener);

    /**
     * @brief Registers listener which receives an answer if a user changed their answer in a non-anonymous poll.
     * Bots receive new votes only in polls that were sent by the bot itself.
     * 
     * @param listener Listener.
     */
    void onPollAnswer(const PollAnswerListener& listener);

    /**
     * @brief Registers listener which receives the bot's chat member status if it was updated in a chat.
     * For private chats, this update is received only when the bot is blocked or unblocked by the user.
     * 
     * @param listener Listener.
     */
    void onMyChatMember(const ChatMemberUpdatedListener& listener);

    /**
     * @brief Registers listener which receives a status if a chat member's status was updated in a chat.
     * The bot must be an administrator in the chat and must explicitly specify “chat_member” in the list of allowedUpdates to receive these updates.
     * 
     * @param listener Listener.
     */
    void onChatMember(const ChatMemberUpdatedListener& listener);

    /**
     * @brief Registers listener which receives requests to join the chat.
     * The bot must have the canInviteUsers administrator right in the chat to receive these updates.
     * 
     * @param listener Listener.
     */
    void onChatJoinRequest(const ChatJoinRequestListener& listener);

    /**
     * @brief Registers listener which receives new incoming message reaction update event.
     * @param listener Listener.
     */
    void onMessageReaction(const MessageReactionUpdatedListener& listener);

    /**
     * @brief Registers listener which receives new incoming message reaction count update event.
     * @param listener Listener.
     */
    void onMessageReactionCount(const MessageReactionCountUpdatedListener& listener);

    /**
    * @brief Registers listener which receives information about successful payments.
    * This listener is triggered when a successful payment is received by the bot.
    * 
    * @param listener Listener.
    */
    void onSuccessfulPayment(const SuccessfulPaymentListener& listener);

private:
    struct TransparentStringHash {
        using is_transparent = void;

        std::size_t operator()(std::string_view value) const noexcept {
            return std::hash<std::string_view> { }(value);
        }
    };

    template<typename ListenerType, typename ObjectType>
    void broadcast(const std::vector<ListenerType>& listeners, ObjectType object) const;

    void broadcastAnyMessage(const std::shared_ptr<Message>& message) const;
    bool broadcastCommand(std::string_view command, const std::shared_ptr<Message>& message) const;
    void broadcastUnknownCommand(const std::shared_ptr<Message>& message) const;
    void broadcastNonCommandMessage(const std::shared_ptr<Message>& message) const;
    void broadcastEditedMessage(const std::shared_ptr<Message>& message) const;
    void broadcastInlineQuery(const std::shared_ptr<InlineQuery>& query) const;
    void broadcastChosenInlineResult(const std::shared_ptr<ChosenInlineResult>& result) const;
    void broadcastCallbackQuery(const std::shared_ptr<CallbackQuery>& result) const;
    void broadcastShippingQuery(const std::shared_ptr<ShippingQuery>& result) const;
    void broadcastPreCheckoutQuery(const std::shared_ptr<PreCheckoutQuery>& result) const;
    void broadcastPoll(const std::shared_ptr<Poll>& result) const;
    void broadcastPollAnswer(const std::shared_ptr<PollAnswer>& result) const;
    void broadcastMyChatMember(const std::shared_ptr<ChatMemberUpdated>& result) const;
    void broadcastChatMember(const std::shared_ptr<ChatMemberUpdated>& result) const;
    void broadcastChatJoinRequest(const std::shared_ptr<ChatJoinRequest>& result) const;
    void broadcastMessageReactionUpdated(const std::shared_ptr<MessageReactionUpdated>& messageReaction) const;
    void broadcastMessageReactionCountUpdated(
        const std::shared_ptr<MessageReactionCountUpdated>& messageReactionCount) const;
    void broadcastSuccessfulPayment(const std::shared_ptr<Message>& message) const;

    std::vector<MessageListener> _onAnyMessageListeners;
    std::unordered_map<std::string, MessageListener, TransparentStringHash, std::equal_to<>> _onCommandListeners;
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
    std::vector<MessageReactionUpdatedListener> _onMessageReactionUpdatedListener;
    std::vector<MessageReactionCountUpdatedListener> _onMessageReactionCountUpdatedListener;
    std::vector<SuccessfulPaymentListener> _onSuccessfulPaymentListeners;
};

} // namespace TgBot
