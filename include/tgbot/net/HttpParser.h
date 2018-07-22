/*
 * Copyright (c) 2015 Oleg Morozenkov
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

#ifndef TGBOT_HTTPPARSER_H
#define TGBOT_HTTPPARSER_H

#include <string>
#include <unordered_map>
#include <vector>

#include "tgbot/net/Url.h"
#include "tgbot/net/HttpReqArg.h"

namespace TgBot {

class HttpParser {

public:
    std::string generateRequest(const Url& url, const std::vector<HttpReqArg>& args, bool isKeepAlive = false) const;
    std::string generateMultipartFormData(const std::vector<HttpReqArg>& args, const std::string& bondary) const;
    std::string generateMultipartBoundary(const std::vector<HttpReqArg>& args) const;
    std::string generateWwwFormUrlencoded(const std::vector<HttpReqArg>& args) const;
    std::string generateResponse(const std::string& data, const std::string& mimeType, unsigned short statusCode, const std::string& statusStr, bool isKeepAlive) const;
    std::unordered_map<std::string, std::string> parseHeader(const std::string& data, bool isRequest) const;
    std::string extractBody(const std::string& data) const;
};

}

#endif //TGBOT_HTTPPARSER_H
