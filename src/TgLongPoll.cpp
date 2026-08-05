#include "tgbot/TgLongPoll.h"

#include "tgbot/Api.h"
#include "tgbot/Bot.h"
#include "tgbot/EventHandler.h"
#include "tgbot/HttpClient.h"

#include <boost/asio/io_context.hpp>
#include <boost/asio/signal_set.hpp>

#include <stdexcept>
#include <stop_token>
#include <thread>
#include <utility>

namespace TgBot {

TgLongPoll::TgLongPoll(const Api* api, const EventHandler* eventHandler, std::int32_t limit, std::int32_t timeout,
                       std::shared_ptr<std::vector<std::string>> allowUpdates)
    : _api(api)
    , _eventHandler(eventHandler)
    , _limit(limit)
    , _timeout(timeout)
    , _allowUpdates(std::move(allowUpdates)) {

    const_cast<TgBot::HttpClient&>(_api->_httpClient)._timeout = _timeout + 5;
}

TgLongPoll::TgLongPoll(const Bot& bot, std::int32_t limit, std::int32_t timeout,
                       const std::shared_ptr<std::vector<std::string>>& allowUpdates)
    : TgLongPoll(&bot.getApi(), &bot.getEventHandler(), limit, timeout, allowUpdates) {
}

void TgLongPoll::start() {
    // handle updates
    for (std::shared_ptr<Update>& item : _updates) {
        if (item->updateId >= _lastUpdateId) {
            _lastUpdateId = item->updateId + 1;
        }
        _eventHandler->handleUpdate(item);
    }

    // confirm handled updates
    _updates = _api->getUpdates(_lastUpdateId, _limit, _timeout,
                                _allowUpdates ? *_allowUpdates : std::vector<std::string> { });
}

void TgLongPoll::startLoop(const ErrorHandler& errorHandler, std::initializer_list<int> signalNumbers) {
    if (_isRunning.exchange(true)) {
        throw std::logic_error("long poll is already running");
    }

    boost::asio::io_context signalContext;
    boost::asio::signal_set signals(signalContext);
    std::jthread signalThread;
    if (signalNumbers.size() != 0) {
        for (const int signalNumber : signalNumbers) {
            signals.add(signalNumber);
        }
        signals.async_wait([this](const boost::system::error_code& error, int) {
            if (!error) {
                stop();
            }
        });
        signalThread = std::jthread([&](std::stop_token stopToken) {
            std::stop_callback stopCallback(stopToken, [&] {
                signalContext.stop();
            });
            signalContext.run();
        });
    }

    try {
        while (_isRunning.load()) {
            try {
                start();
            } catch (const std::exception& error) {
                if (errorHandler) {
                    errorHandler(error);
                }
                if (!_isRunning.load()) {
                    break;
                }
                if (!errorHandler) {
                    throw;
                }
            }
        }
    } catch (...) {
        _isRunning.store(false);
        throw;
    }
}

void TgLongPoll::stop() {
    if (_isRunning.exchange(false)) {
        _api->_httpClient.cancel();
    }
}

} // namespace TgBot
