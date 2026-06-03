#ifndef MAXBOT_CURLHTTPCLIENT_H
#define MAXBOT_CURLHTTPCLIENT_H

#ifdef HAVE_CURL

#include "maxbot/net/HttpClient.h"
#include "maxbot/net/Url.h"
#include "maxbot/net/HttpReqArg.h"
#include "maxbot/net/HttpParser.h"

#include <curl/curl.h>

#include <mutex>
#include <string>
#include <vector>
#include <thread>
#include <unordered_map>

namespace MaxBot {

/**
 * @brief This class makes http requests via libcurl.
 *
 * @ingroup net
 */
class MAXBOT_API CurlHttpClient : public HttpClient {

public:
    CurlHttpClient(const std::string& token);
    ~CurlHttpClient() override;

    /**
     * @brief Sends a request to the url.
     *
     * If there's no args specified, a GET request will be sent, otherwise a POST request will be sent.
     * If at least 1 arg is marked as file, the content type of a request will be multipart/form-data, otherwise it will be application/x-www-form-urlencoded.
     */
    std::pair<long, std::string> makeRequest(const Url& url, const std::vector<HttpReqArg>& args, const std::string& customMethod = {}) const override;

    /**
     * @brief Raw curl handles, each thread has its own handle.
     */
    std::unordered_map<std::thread::id, CURL*> curlHandles;

    /**
     * @brief Lock for curlHandles access.
     */
    std::mutex curlHandlesMutex;

    /**
     * @brief Proxy URL (NULL = no proxy).
     */
    void setProxy(const char* url = NULL, long timeout = 20L) {
	_proxyUrl = url;
	_connectTimeout = timeout;
    }

private:
    const HttpParser _httpParser;
    const char* _proxyUrl = NULL;
    long _connectTimeout = 20L;
	const std::string _authHeader;

};

}

#endif

#endif //MAXBOT_CURLHTTPCLIENT_H
