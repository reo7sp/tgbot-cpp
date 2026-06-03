#ifndef MAXBOT_BOOSTHTTPCLIENT_H
#define MAXBOT_BOOSTHTTPCLIENT_H

#include "maxbot/net/HttpClient.h"
#include "maxbot/net/Url.h"
#include "maxbot/net/HttpReqArg.h"
#include "maxbot/net/HttpParser.h"

#include <boost/asio.hpp>

#include <string>
#include <vector>

namespace MaxBot {

/**
 * @brief This class makes http requests via boost::asio.
 *
 * @ingroup net
 */
class MAXBOT_API BoostHttpOnlySslClient : public HttpClient {

public:
    BoostHttpOnlySslClient(const std::string& token);
    ~BoostHttpOnlySslClient() override;

    /**
     * @brief Sends a request to the url.
     *
     * If there's no args specified, a GET request will be sent, otherwise a POST request will be sent.
     * If at least 1 arg is marked as file, the content type of a request will be multipart/form-data, otherwise it will be application/x-www-form-urlencoded.
     */
    std::pair<long, std::string> makeRequest(const Url& url, const std::vector<HttpReqArg>& args, const std::string& customMethod = {}) const override;

private:
#if BOOST_VERSION >= 108700
    mutable boost::asio::io_context _ioService;
#else
    mutable boost::asio::io_service _ioService;
#endif
    const HttpParser _httpParser;
	std::unordered_map<std::string, std::string> _headers;
};

}

#endif //MAXBOT_BOOSTHTTPCLIENT_H
