#pragma once

#include "tgbot/HttpFormField.h"
#include "tgbot/export.h"

#include <atomic>
#include <cstdint>
#include <span>
#include <stdexcept>
#include <string>
#include <string_view>

namespace TgBot {

/**
 * @brief Exception thrown when an HTTP request is cancelled.
 *
 * @ingroup net
 */
class TGBOT_API RequestCancelled : public std::runtime_error {
public:
    RequestCancelled();
    explicit RequestCancelled(std::string_view request);
};

/**
 * @brief This class makes http requests.
 *
 * @ingroup net
 */
class TGBOT_API HttpClient {
public:
    virtual ~HttpClient() = default;

    /**
     * @brief Sends a request to the url.
     *
     * If there are no fields, a GET request is sent. Otherwise, a multipart/form-data POST request is sent.
     */
    virtual std::string makeRequest(const std::string& url, std::span<const HttpFormField> fields) const = 0;

    std::int32_t _timeout = 25;

    /**
     * @brief Get the maximum number of makeRequest() retries before giving up and throwing an exception.
     */
    virtual int getRequestMaxRetries() const {
        return requestMaxRetries;
    }

    /**
     * @brief Get the makeRequest() backoff duration between retries, in seconds.
     */
    virtual int getRequestBackoffSeconds() const {
        return requestBackoffSeconds;
    }

    /**
     * @brief Cancels the requests.
     *                          
     * @param eternal Optional. If true, permanently disables the HTTP client, canceling all current and future requests. 
     *                          If false, cancel the currently running requests.
     */
    virtual void cancel(const bool eternal = false) const {
        if (eternal) {
            _isEternalCancel.store(true);
        } else {
            _cancelEpoch.fetch_add(1);
        }
    }

    /**
     *  @brief Checks if the HTTP client is permanently disabled.
     */
    virtual bool isEternalCancelled() const {
        return _isEternalCancel.load();
    }

protected:
    /**
     *  @brief Flag indicating whether the HTTP client is permanently disabled.
     */
    mutable std::atomic<bool> _isEternalCancel { false };

    /**
     *  @brief Counter used to invalidate current requests.
     */
    mutable std::atomic<uint64_t> _cancelEpoch { 0 };

private:
    int requestMaxRetries = 3;
    int requestBackoffSeconds = 1;
};

} // namespace TgBot
