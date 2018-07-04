/*
 * Copyright (c) 2015 Oleg Morozenkov
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

#include "tgbot/net/HttpClient.h"

#include <boost/asio/ssl.hpp>

using namespace std;
using namespace boost::asio;
using namespace boost::asio::ip;

namespace TgBot {

BoostHttpClient& BoostHttpClient::getInstance() {
    static BoostHttpClient result;
	return result;
}

string BoostHttpClient::makeRequest(const Url& url, const vector<HttpReqArg>& args) const {
	ssl::context context(ssl::context::sslv23);
	context.set_default_verify_paths();

	ssl::stream<tcp::socket> socket(_ioService, context);
	tcp::resolver resolver(_ioService);
	tcp::resolver::query query(url.host, url.protocol);

	connect(socket.lowest_layer(), resolver.resolve(query));

	#ifdef TGBOT_DISABLE_NAGLES_ALGORITHM
	socket.lowest_layer().set_option(tcp::no_delay(true));
	#endif //TGBOT_DISABLE_NAGLES_ALGORITHM

	#ifdef TGBOT_CHANGE_SOCKET_BUFFER_SIZE
	#if _WIN64 || __amd64__ || __x86_64__ || __MINGW64__ || __aarch64__ || __powerpc64__
	socket.lowest_layer().set_option(socket_base::send_buffer_size(65536));
	socket.lowest_layer().set_option(socket_base::receive_buffer_size(65536));
	#else //for 32-bit
	socket.lowest_layer().set_option(socket_base::send_buffer_size(32768));
	socket.lowest_layer().set_option(socket_base::receive_buffer_size(32768));
	#endif //Processor architecture
	#endif //TGBOT_CHANGE_SOCKET_BUFFER_SIZE

	socket.set_verify_mode(ssl::verify_none);
	socket.set_verify_callback(ssl::rfc2818_verification(url.host));
	socket.handshake(ssl::stream<tcp::socket>::client);

	string requestText = HttpParser::getInstance().generateRequest(url, args, false);
	write(socket, buffer(requestText.c_str(), requestText.length()));

	string response;

	#ifdef TGBOT_CHANGE_READ_BUFFER_SIZE
	#if _WIN64 || __amd64__ || __x86_64__ || __MINGW64__ || __aarch64__ || __powerpc64__
	char buff[65536];
	#else //for 32-bit
	char buff[32768];
	#endif //Processor architecture
	#else
	char buff[1024];
	#endif //TGBOT_CHANGE_READ_BUFFER_SIZE
	
	boost::system::error_code error;
	while (!error) {
		size_t bytes = read(socket, buffer(buff), error);
		response += string(buff, bytes);
	}

	return HttpParser::getInstance().parseResponse(response);
}

#ifdef HAVE_CURL

CurlHttpClient::CurlHttpClient() {
    curlSettings = curl_easy_init();
}

CurlHttpClient::~CurlHttpClient() {
    curl_easy_cleanup(curlSettings);
}

CurlHttpClient& CurlHttpClient::getInstance() {
    static CurlHttpClient result;
    return result;
}

static size_t curl_write_string(char *ptr, size_t size, size_t nmemb, void *userdata)
{
    std::string &s = *(std::string *)userdata;
    auto read = size * nmemb;
    s.append(ptr, ptr + read);
    return read;
};

string CurlHttpClient::makeRequest(const Url& url, const vector<HttpReqArg>& args) const {
    // Copy settings for each call because we change CURLOPT_URL and other stuff.
    // This also protects multithreaded case.
    auto curl = curl_easy_duphandle(curlSettings);

    auto u = url.protocol + "://" + url.host + url.path;
    curl_easy_setopt(curl, CURLOPT_URL, u.c_str());

    if (!args.empty())
    {
        std::string data;
        for (auto &a : args)
            data += a.name + "=" + a.value + "&";
        data.resize(data.size() - 1);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data.c_str());
    }

    std::string response;
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, curl_write_string);

    auto res = curl_easy_perform(curl);
    long http_code;
    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_code);
    curl_easy_cleanup(curl);

    if (res != CURLE_OK)
        throw std::runtime_error("curl error: "s + curl_easy_strerror(res));
    if (http_code != 200)
        throw std::runtime_error("curl request returned with code = " + std::to_string(http_code));

    return HttpParser::getInstance().parseResponse(response);
}

#endif

}
