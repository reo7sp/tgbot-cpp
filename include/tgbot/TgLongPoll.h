#pragma once

#include "tgbot/Types.h"
#include "tgbot/export.h"

#include <atomic>
#include <csignal>
#include <cstdint>
#include <exception>
#include <functional>
#include <initializer_list>
#include <memory>
#include <string>
#include <vector>

namespace TgBot {

class Api;
class Bot;
class EventHandler;

/**
 * @brief This class handles long polling and updates parsing.
 *
 * @ingroup net
 */
class TGBOT_API TgLongPoll {
public:
    using ErrorHandler = std::function<void(const std::exception&)>;

    TgLongPoll(const Api* api, const EventHandler* eventHandler, std::int32_t limit, std::int32_t timeout,
               std::shared_ptr<std::vector<std::string>> allowUpdates);
    TgLongPoll(const Bot& bot, std::int32_t limit = 100, std::int32_t timeout = 10,
               const std::shared_ptr<std::vector<std::string>>& allowUpdates = nullptr);

    /**
     * @brief Performs one long-polling iteration and dispatches received updates. Parses received updates and
     * passes them to EventHandler, which invokes the registered listeners.
     */
    void start();

    /**
     * @brief Polls for updates until stop() is called, one of the configured signals is received, or an unhandled
     * error occurs.
     * @param errorHandler Called when a polling iteration fails. The loop continues after the handler returns. If no
     * handler is provided, the exception is propagated.
     * @param signals Process signals that stop the loop. Pass an empty list to disable signal handling.
     */
    void startLoop(const ErrorHandler& errorHandler = { }, std::initializer_list<int> signals = { SIGINT, SIGTERM });

    /**
     * @brief Requests cancellation of the active HTTP request and stops startLoop().
     */
    void stop();

    /**
     * @brief Returns true while startLoop() is active.
     */
    bool isRunning() const {
        return _isRunning.load();
    }

private:
    const Api* _api;
    const EventHandler* _eventHandler;
    std::int32_t _lastUpdateId = 0;
    std::int32_t _limit;
    std::int32_t _timeout;
    std::shared_ptr<std::vector<std::string>> _allowUpdates;
    std::atomic<bool> _isRunning { false };

    std::vector<std::shared_ptr<Update>> _updates;
};

} // namespace TgBot
