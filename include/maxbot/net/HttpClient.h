#ifndef MAXBOT_HTTPCLIENT_H
#define MAXBOT_HTTPCLIENT_H

#include "maxbot/net/Url.h"
#include "maxbot/net/HttpReqArg.h"

#include <string>
#include <vector>
#include <cstdint>

namespace MaxBot {

/**
 * @brief This class makes http requests.
 *
 * @ingroup net
 */
class MAXBOT_API HttpClient {

public:
    virtual ~HttpClient() = default;

    /**
     * @brief Sends a request to the url.
     *
     * If there's no args specified, a GET request will be sent, otherwise a POST request will be sent.
     * If at least 1 arg is marked as file, the content type of a request will be multipart/form-data, otherwise it will be application/x-www-form-urlencoded.
     */
    virtual std::pair<long, std::string> makeRequest(const Url& url, const std::vector<HttpReqArg>& args, const std::string& customMethod = {}) const = 0;

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

private:
    int requestMaxRetries = 3;
    int requestBackoff = 1;
};

}


#endif //MAXBOT_HTTPCLIENT_H
