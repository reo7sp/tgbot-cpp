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

#include "Http.h"

#include <iostream>

#include <boost/asio/ssl.hpp>

#include "tgbot/tools/StringTools.h"

using namespace std;
using namespace boost::asio;
using namespace boost::asio::ip;
using namespace boost::asio::local;
using boost::lexical_cast;

namespace TgBot {

string Http::makeRequest(const Url& url, const vector<Argument>& args) {
    string result;

    ssl::context context(ssl::context::sslv23);
    context.set_default_verify_paths();

    ssl::stream<tcp::socket> socket(_ioService, context);
    tcp::resolver resolver(_ioService);
    tcp::resolver::query query(url.host, url.protocol);
    connect(socket.lowest_layer(), resolver.resolve(query));

    socket.set_verify_mode(ssl::verify_none);
    socket.set_verify_callback(ssl::rfc2818_verification(url.host));
    socket.handshake(ssl::stream<tcp::socket>::client);

    string requestText;
    if (args.empty()) {
        requestText += "GET ";
    } else {
        requestText += "POST ";
    }
    requestText += url.path;
    requestText += url.query.empty() ? "" : "?" + url.query;
    requestText += " HTTP/1.1\r\n";
    requestText += "Host: ";
    requestText += url.host;
    requestText += "\r\nConnection: close\r\n";
    if (args.empty()) {
        requestText += "\r\n";
    } else {
        string requestData;

        bool isMultipart = false;
        string bondary;
        srand((unsigned int) time(nullptr));
        for (const Argument& item : args) {
            if (item.isFile) {
                isMultipart = true;
                while (bondary.empty() || item.value.find(bondary) != item.value.npos) {
                    bondary += StringTools::generateRandomString(4);
                }
            }
        }
        if (isMultipart) {
            requestText += "Content-Type: multipart/form-data; boundary=";
            requestText += bondary;
            requestText += "\r\n";
            for (const Argument& item : args) {
                requestData += "--";
                requestData += bondary;
                requestData += "\r\nContent-Disposition: form-data; name=\"";
                requestData += item.name;
                requestData += "\"\r\n";
                if (item.isFile) {
                    requestData += "Content-Type: ";
                    requestData += item.mimeType;
                    requestData += "\r\n";
                }
                requestData += "\r\n";
                requestData += item.value;
                requestData += "\r\n\r\n";
            }
        } else {
            requestText += "Content-Type: application/x-www-form-urlencoded\r\n";
            bool firstRun = true;
            for (const Argument& item : args) {
                if (firstRun) {
                    firstRun = false;
                } else {
                    requestData += '&';
                }
                requestData += StringTools::urlEncode(item.name);
                requestData += '=';
                requestData += StringTools::urlEncode(item.value);
            }
        }

        requestText += "Content-Length: ";
        requestText += lexical_cast<string>(requestData.length());
        requestText += "\r\n\r\n";
        requestText += requestData;
    }
    write(socket, buffer(requestText.c_str(), requestText.length()));

    char buff[1024];
    boost::system::error_code error;
    while (!error) {
        size_t bytes = read(socket, buffer(buff), error);
        result += string(buff, bytes);
    }

    cout << "REQUEST" << endl << requestText << endl << "RESPONSE" << endl << result << endl;

    size_t headerEnd = result.find("\r\n\r\n");
    if (headerEnd == result.npos) {
        headerEnd = result.find("\n\n");
    }
    if (headerEnd == result.npos) {
        headerEnd = 0;
    }
    result.erase(0, headerEnd);

    return result;
}

void Http::startServer(unsigned short port, const Http::ServerHandler& handler) {
    stopServer();
    _serverHandler = handler;
    tcp::acceptor* acceptor = new tcp::acceptor(_ioService, tcp::endpoint(tcp::v4(), port));
    _tcpServer = new Server<tcp>(this, acceptor);
    _ioService.run();
}

void Http::startServer(const std::string& unixSocketPath, const Http::ServerHandler& handler) {
    stopServer();
    _serverHandler = handler;
    stream_protocol::acceptor* acceptor = new stream_protocol::acceptor(_ioService, stream_protocol::endpoint(unixSocketPath));
    _unixSocketServer = new Server<stream_protocol>(this, acceptor);
    _ioService.run();
}

void Http::stopServer() {
    _ioService.stop();
    if (_tcpServer != nullptr) {
        delete _tcpServer;
        _tcpServer = nullptr;
    }
    if (_unixSocketServer != nullptr) {
        delete _unixSocketServer;
        _unixSocketServer = nullptr;
    }
}

}