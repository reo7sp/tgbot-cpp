/*
 * Copyright (c) 2018 Egor Pugin
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef TGBOT_CURLHTTPCLIENT_H
#define TGBOT_CURLHTTPCLIENT_H

#ifdef HAVE_CURL

#include <string>

#include <curl/curl.h>

#include "tgbot/net/HttpClient.h"
#include "tgbot/net/Url.h"
#include "tgbot/net/HttpReqArg.h"
#include "tgbot/net/HttpParser.h"

namespace TgBot {

/**
 * @brief This class makes http requests via libcurl.
 *
 * @ingroup net
 */
class CurlHttpClient : public HttpClient {

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
     * @brief Raw curl settings storage for fine tuning.
     */
    CURL* curlSettings;

private:
    const HttpParser _httpParser;
};

}

#endif

#endif //TGBOT_CURLHTTPCLIENT_H
