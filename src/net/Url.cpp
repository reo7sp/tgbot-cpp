#include "tgbot/net/Url.h"

#include <cstddef>
#include <string>

using namespace std;

namespace TgBot {

Url::Url(const string& url) {
    bool isProtocolParsed = false;
    bool isHostParsed = false;
    bool isPathParsed = false;
    bool isQueryParsed = false;

    for (std::size_t i = 0, count = url.length(); i < count; ++i) {
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
