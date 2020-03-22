#include "tgbot/net/HttpParser.h"

#include "tgbot/tools/StringTools.h"

#include <boost/algorithm/string.hpp>

#include <cstddef>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;
using namespace boost;

namespace TgBot {

string HttpParser::generateRequest(const Url& url, const vector<HttpReqArg>& args, bool isKeepAlive) const {
    string result;
    if (args.empty()) {
        result += "GET ";
    } else {
        result += "POST ";
    }
    result += url.path;
    result += url.query.empty() ? "" : "?" + url.query;
    result += " HTTP/1.1\r\n";
    result += "Host: ";
    result += url.host;
    result += "\r\nConnection: ";
    if (isKeepAlive) {
        result += "keep-alive";
    } else {
        result += "close";
    }
    result += "\r\n";
    if (args.empty()) {
        result += "\r\n";
    } else {
        string requestData;

        string bondary = generateMultipartBoundary(args);
        if (bondary.empty()) {
            result += "Content-Type: application/x-www-form-urlencoded\r\n";
            requestData = generateWwwFormUrlencoded(args);
        } else {
            result += "Content-Type: multipart/form-data; boundary=";
            result += bondary;
            result += "\r\n";
            requestData = generateMultipartFormData(args, bondary);
        }

        result += "Content-Length: ";
        result += std::to_string(requestData.length());
        result += "\r\n\r\n";
        result += requestData;
    }
    return result;
}

string HttpParser::generateMultipartFormData(const vector<HttpReqArg>& args, const string& bondary) const {
    string result;
    for (const HttpReqArg& item : args) {
        result += "--";
        result += bondary;
        result += "\r\nContent-Disposition: form-data; name=\"";
        result += item.name;
        if (item.isFile) {
            result += "\"; filename=\"" + item.fileName;
        }
        result += "\"\r\n";
        if (item.isFile) {
            result += "Content-Type: ";
            result += item.mimeType;
            result += "\r\n";
        }
        result += "\r\n";
        result += item.value;
        result += "\r\n";
    }
    result += "--" + bondary + "--\r\n";
    return result;
}

string HttpParser::generateMultipartBoundary(const vector<HttpReqArg>& args) const {
    string result;
    for (const HttpReqArg& item : args) {
        if (item.isFile) {
            while (result.empty() || item.value.find(result) != string::npos) {
                result += StringTools::generateRandomString(4);
            }
        }
    }
    return result;
}

string HttpParser::generateWwwFormUrlencoded(const vector<HttpReqArg>& args) const {
    string result;

    bool firstRun = true;
    for (const HttpReqArg& item : args) {
        if (firstRun) {
            firstRun = false;
        } else {
            result += '&';
        }
        result += StringTools::urlEncode(item.name);
        result += '=';
        result += StringTools::urlEncode(item.value);
    }

    return result;
}

string HttpParser::generateResponse(const string& data, const string& mimeType, unsigned short statusCode, const string& statusStr, bool isKeepAlive) const {
    string result;
    result += "HTTP/1.1 ";
    result += std::to_string(statusCode);
    result += ' ';
    result += statusStr;
    result += "\r\nContent-Type: ";
    result += mimeType;
    result += "\r\nContent-Length: ";
    result += std::to_string(data.length());
    result += "\r\nConnection: ";
    if (isKeepAlive) {
        result += "keep-alive";
    } else {
        result += "close";
    }
    result += "\r\n\r\n";
    result += data;
    return result;
}

unordered_map<string, string> HttpParser::parseHeader(const string& data, bool isRequest) const {
    unordered_map<string, string> headers;

    std::size_t lineStart = 0;
    std::size_t lineEnd = 0;
    std::size_t lineSepPos = 0;
    std::size_t lastLineEnd = string::npos;
    while (lastLineEnd != lineEnd) {
        lastLineEnd = lineEnd;
        bool isFirstLine = lineEnd == 0;
        if (isFirstLine) {
            if (isRequest) {
                lineSepPos = data.find(' ');
                lineEnd = data.find("\r\n");
                headers["_method"] = data.substr(0, lineSepPos);
                headers["_path"] = data.substr(lineSepPos + 1, data.find(' ', lineSepPos + 1) - lineSepPos - 1);
            } else {
                lineSepPos = data.find(' ');
                lineEnd = data.find("\r\n");
                headers["_status"] = data.substr(lineSepPos + 1, data.find(' ', lineSepPos + 1) - lineSepPos - 1);
            }
        } else {
            lineStart = lineEnd;
            lineStart += 2;
            lineEnd = data.find("\r\n", lineStart);
            lineSepPos = data.find(':', lineStart);
            if (lastLineEnd == lineEnd || lineEnd == string::npos) {
                break;
            }
            headers[data.substr(lineStart, lineSepPos - lineStart)] = trim_copy(data.substr(lineSepPos + 1, lineEnd - lineSepPos - 1));
        }
    }

    return headers;
}

string HttpParser::extractBody(const string& data) const {
    std::size_t headerEnd = data.find("\r\n\r\n");
    if (headerEnd == string::npos) {
        return data;
    }
    headerEnd += 4;
    return data.substr(headerEnd);
}

}
