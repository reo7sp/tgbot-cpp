#ifndef TGBOT_CURLHTTPCLIENT_H
#define TGBOT_CURLHTTPCLIENT_H

#ifdef HAVE_CURL

#include "tgbot/net/HttpClient.h"
#include "tgbot/net/Url.h"
#include "tgbot/net/HttpReqArg.h"
#include "tgbot/net/HttpParser.h"

#include <curl/curl.h>

#include <mutex>
#include <string>
#include <vector>
#include <thread>
#include <unordered_map>

namespace TgBot {

/**
 * @brief This class makes http requests via libcurl.
 *
 * @ingroup net
 */
class TGBOT_API CurlHttpClient : public HttpClient {

public:
    CurlHttpClient();
    ~CurlHttpClient() override;

    /**
     * @brief Sends a request to the url.
     *
     * If there's no args specified, a GET request will be sent, otherwise a POST request will be sent.
     * If at least 1 arg is marked as file, the content type of a request will be multipart/form-data, otherwise it will be application/x-www-form-urlencoded.
     */
    std::string makeRequest(const Url& url, const std::vector<HttpReqArg>& args) const override;

    /**
     * @brief Raw curl handles, each thread has its own handle.
     */
    std::unordered_map<std::thread::id, CURL*> curlHandles;

    /**
     * @brief Lock for curlHandles access.
     */
    std::mutex curlHandlesMutex;

private:
    const HttpParser _httpParser;
};

}

#endif

#endif //TGBOT_CURLHTTPCLIENT_H
