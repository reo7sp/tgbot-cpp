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

#include "tgbot/net/HttpParser.h"

#include <boost/algorithm/string.hpp>

#include "tgbot/tools/StringTools.h"

using namespace std;
using namespace boost;

namespace TgBot {

HttpParser& HttpParser::getInstance() {
	static HttpParser result;
	return result;
}

string HttpParser::generateRequest(const Url& url, const vector<HttpReqArg>& args, bool isKeepAlive) {
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
		result += lexical_cast<string>(requestData.length());
		result += "\r\n\r\n";
		result += requestData;
	}
	return result;
}

string HttpParser::generateMultipartFormData(const vector<HttpReqArg>& args, const string& bondary) {
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

string HttpParser::generateMultipartBoundary(const vector<HttpReqArg>& args) {
	string result;
	srand((unsigned int) time(nullptr));
	for (const HttpReqArg& item : args) {
		if (item.isFile) {
			while (result.empty() || item.value.find(result) != item.value.npos) {
				result += StringTools::generateRandomString(4);
			}
		}
	}
	return result;
}

string HttpParser::generateWwwFormUrlencoded(const vector<HttpReqArg>& args) {
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

string HttpParser::generateResponse(const string& data, const string& mimeType, unsigned short statusCode, const string& statusStr, bool isKeepAlive) {
	string result;
	result += "HTTP/1.1 ";
	result += lexical_cast<string>(statusCode);
	result += ' ';
	result += statusStr;
	result += "\r\nContent-Type: ";
	result += mimeType;
	result += "\r\nContent-Length: ";
	result += lexical_cast<string>(data.length());
	result += "\r\n\r\n";
	result += data;
	return result;
}

string HttpParser::parseHttp(bool isRequest, const string& data, unordered_map<string, string>& headers) {
	bool onlyNewLineChar = false;
	size_t headerEnd = data.find("\r\n\r\n");
	if (headerEnd == data.npos) {
		headerEnd = data.find("\n\n");
		if (headerEnd != data.npos) {
			onlyNewLineChar = true;
			headerEnd += 2;
		}
	} else {
		headerEnd += 4;
	}

	size_t lineStart = 0;
	size_t lineEnd = 0;
	size_t lineSepPos = 0;
	size_t lastLineEnd = data.npos;
	while (lastLineEnd != lineEnd) {
		lastLineEnd = lineEnd;
		if (lineEnd == 0) {
			if (isRequest) {
				lineSepPos = data.find(' ');
				lineEnd = data.find(onlyNewLineChar ? "\n" : "\r\n");
				headers["method"] = data.substr(0, lineSepPos);
				headers["path"] = data.substr(lineSepPos + 1, data.find(' ', lineSepPos + 1) - lineSepPos - 1);
			} else {
				lineSepPos = data.find(' ');
				lineEnd = data.find(onlyNewLineChar ? "\n" : "\r\n");
				headers["status"] = data.substr(lineSepPos + 1, data.find(' ', lineSepPos + 1) - lineSepPos - 1);
			}
		} else {
			lineStart = lineEnd;
			lineStart += onlyNewLineChar ? 1 : 2;
			lineEnd = data.find(onlyNewLineChar ? "\n" : "\r\n", lineStart);
			lineSepPos = data.find(':', lineStart);
			if (lineEnd >= headerEnd || lastLineEnd == lineEnd || lineSepPos >= headerEnd) {
				break;
			}
			headers[to_lower_copy(data.substr(lineStart, lineSepPos - lineStart))] = trim_copy(data.substr(lineSepPos + 1, lineEnd - lineSepPos - 1));
		}
	}

	return headerEnd == data.npos ? "" : data.substr(headerEnd);
}

string HttpParser::parseHttp(bool isRequest, const string& data) {
	size_t headerEnd = data.find("\r\n\r\n");
	if (headerEnd != data.npos) {
		headerEnd += 4;
	} else {
		headerEnd = data.find("\n\n");
		if (headerEnd != data.npos) {
			headerEnd += 2;
		} else {
			headerEnd = 0;
		}
	}
	return data.substr(headerEnd);
}

}
