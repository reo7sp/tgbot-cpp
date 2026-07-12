#ifndef TGBOT_HTTPCLIENT_H
#define TGBOT_HTTPCLIENT_H

#include "tgbot/net/Url.h"
#include "tgbot/net/HttpReqArg.h"

#include <string>
#include <vector>
#include <cstdint>
#include <atomic>

namespace TgBot {

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
     * If there's no args specified, a GET request will be sent, otherwise a POST request will be sent.
     * If at least 1 arg is marked as file, the content type of a request will be multipart/form-data, otherwise it will be application/x-www-form-urlencoded.
     */
    virtual std::string makeRequest(const Url& url, const std::vector<HttpReqArg>& args) const = 0;

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
    virtual int getRequestBackoff() const {
        return requestBackoff;
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
        }
        else {
            _cancelEpoch.fetch_add(1);
        }
    }

    /**
     *  @brief Checks if the HTTP client is permanently disabled.
     */
    virtual bool isEternalCancelled() const {
        return _isEternalCancel.load();
    }

    /**
     *  @brief Get the exception message that occurs when the request is aborted.
     */
    virtual const std::string& getCancelExceptionText() const {
        return cancelExceptionText;
    }

protected:

    /**
     *  @brief Flag indicating whether the HTTP client is permanently disabled.
     */
    mutable std::atomic<bool> _isEternalCancel{ false };

    /**
     *  @brief Counter used to invalidate current requests.
     */
    mutable std::atomic<uint64_t> _cancelEpoch{ 0 };

private:
    int requestMaxRetries = 3;
    int requestBackoff = 1;
    const std::string cancelExceptionText = "request cancelled";
};

}


#endif //TGBOT_HTTPCLIENT_H
