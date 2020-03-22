#ifndef TGBOT_BOOSTHTTPCLIENT_H
#define TGBOT_BOOSTHTTPCLIENT_H

#include "tgbot/net/HttpClient.h"
#include "tgbot/net/Url.h"
#include "tgbot/net/HttpReqArg.h"
#include "tgbot/net/HttpParser.h"

#include <boost/asio.hpp>

#include <string>
#include <vector>

namespace TgBot {

/**
 * @brief This class makes http requests via boost::asio.
 *
 * @ingroup net
 */
class TGBOT_API BoostHttpOnlySslClient : public HttpClient {

public:
    BoostHttpOnlySslClient();
    ~BoostHttpOnlySslClient() override;

    /**
     * @brief Sends a request to the url.
     *
     * If there's no args specified, a GET request will be sent, otherwise a POST request will be sent.
     * If at least 1 arg is marked as file, the content type of a request will be multipart/form-data, otherwise it will be application/x-www-form-urlencoded.
     */
    std::string makeRequest(const Url& url, const std::vector<HttpReqArg>& args) const override;

private:
    mutable boost::asio::io_service _ioService;
    const HttpParser _httpParser;
};

}

#endif //TGBOT_BOOSTHTTPCLIENT_H
