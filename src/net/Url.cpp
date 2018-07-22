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

#include "tgbot/net/Url.h"

#include "tgbot/tools/StringTools.h"

using namespace std;

namespace TgBot {

Url::Url(const string& url) {
    bool isProtocolParsed = false;
    bool isHostParsed = false;
    bool isPathParsed = false;
    bool isQueryParsed = false;

    for (size_t i = 0, count = url.length(); i < count; ++i) {
        char c = url[i];

        if (!isProtocolParsed) {
            if (c == ':') {
                isProtocolParsed = true;
                i += 2;
            } else {
                protocol += c;
            }
        } else if (!isHostParsed) {
            if (c == '/') {
                isHostParsed = true;
                path += '/';
            } else if (c == '?') {
                isHostParsed = isPathParsed = true;
                path += '/';
            } else if (c == '#') {
                isHostParsed = isPathParsed = isQueryParsed = true;
                path += '/';
            } else {
                host += c;
            }
        } else if (!isPathParsed) {
            if (c == '?') {
                isPathParsed = true;
            } else if (c == '#') {
                isPathParsed = isQueryParsed = true;
            } else {
                path += c;
            }
        } else if (!isQueryParsed) {
            if (c == '#') {
                isQueryParsed = true;
            } else {
                query += c;
            }
        } else {
            fragment += c;
        }
    }
}

}
