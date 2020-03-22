#ifndef TGBOT_HTTPCLIENT_H
#define TGBOT_HTTPCLIENT_H

#include "tgbot/net/Url.h"
#include "tgbot/net/HttpReqArg.h"

#include <string>
#include <vector>

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
};

}


#endif //TGBOT_HTTPCLIENT_H
