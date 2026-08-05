#pragma once

#include "tgbot/HttpClient.h"
#include "tgbot/export.h"

#include <curl/curl.h>

#include <mutex>
#include <span>
#include <string>
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
     * If there are no fields, a GET request is sent. Otherwise, a multipart/form-data POST request is sent.
     */
    std::string makeRequest(const std::string& url, std::span<const HttpFormField> fields) const override;

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
    const char* _proxyUrl = NULL;
    long _connectTimeout = 20L;
};

} // namespace TgBot
