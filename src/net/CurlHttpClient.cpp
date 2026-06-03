#ifdef HAVE_CURL

#include "maxbot/net/CurlHttpClient.h"

#include <cstddef>
#include <string>

namespace MaxBot {

CurlHttpClient::CurlHttpClient(const std::string& token)
	: _httpParser()
	, _authHeader { "Authorization: " + token }
{ }

CurlHttpClient::~CurlHttpClient() {
    std::lock_guard<std::mutex> lock(curlHandlesMutex);
    for (auto& c : curlHandles) {
        curl_easy_cleanup(c.second);
    }
}

static CURL* getCurlHandle(const CurlHttpClient *c_) {
    CurlHttpClient *c = const_cast<CurlHttpClient *>(c_);

    std::lock_guard<std::mutex> lock(c->curlHandlesMutex);
    auto id = std::this_thread::get_id();
    auto it = c->curlHandles.find(id);
    if (it == c->curlHandles.end()) {
        CURL* curl = curl_easy_init();
        if (!curl) {
            throw std::runtime_error("curl_easy_init() failed");
        }
        c->curlHandles[id] = curl;
        return curl;
    }

    return it->second;
}

static std::size_t curlWriteString(char* ptr, std::size_t size, std::size_t nmemb, void* userdata) {
    static_cast<std::string*>(userdata)->append(ptr, size * nmemb);
    return size * nmemb;
}

std::pair<long, std::string> CurlHttpClient::makeRequest(const Url& url, const std::vector<HttpReqArg>& args, const std::string& customMethod) const {
    CURL* curl = getCurlHandle(this);

    curl_easy_reset(curl);
    curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, _connectTimeout);
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, _timeout);
    curl_easy_setopt(curl, CURLOPT_PROXY, _proxyUrl);

    std::string u = url.protocol + "://" + url.host + url.path;
    if (args.empty()) {
        u += "?" + url.query;
    }
    curl_easy_setopt(curl, CURLOPT_URL, u.c_str());

	// Добавляет загаловок с токеном авторизации
	auto headers = curl_slist_append(nullptr, _authHeader.c_str());

    curl_mime* mime;
    curl_mimepart* part;
    mime = curl_mime_init(curl);
	if (args.size() == 1 && args.front().name.empty() && args.front().mimeType == "application/json")
	{
		headers = curl_slist_append(headers, "Content-Type: application/json");
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, args.front().value.c_str());
	}
	else if (!args.empty())
	{
        for (const HttpReqArg& a : args) {
            part = curl_mime_addpart(mime);

            curl_mime_data(part, a.value.c_str(), a.value.size());
            curl_mime_type(part, a.mimeType.c_str());
            curl_mime_name(part, a.name.c_str());
            if (a.isFile) {
                curl_mime_filename(part, a.fileName.c_str());
            }
        }
        curl_easy_setopt(curl, CURLOPT_MIMEPOST, mime);
    }

    std::string response;
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, curlWriteString);

    char errbuf[CURL_ERROR_SIZE] {};
    curl_easy_setopt(curl, CURLOPT_ERRORBUFFER, errbuf);

	if (!customMethod.empty())
		curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, customMethod.c_str());

	curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

    auto res = curl_easy_perform(curl);
	curl_slist_free_all(headers); // Освобождаем список заголовков
    curl_mime_free(mime);

    // If the request did not complete correctly, show the error
    // information. If no detailed error information was written to errbuf
    // show the more generic information from curl_easy_strerror instead.
    if (res != CURLE_OK) {
        size_t len = strlen(errbuf);
        std::string errmsg;
        if (len) {
            errmsg = std::string(errbuf) + ((errbuf[len - 1] != '\n') ? "\n" : "");
        }
        else {
            errmsg = curl_easy_strerror(res);
        }
        throw std::runtime_error(std::string("curl error: ") + errmsg);
    }

	long httpCode = 0;
	res = curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &httpCode);
	if (res != CURLE_OK)
		throw std::runtime_error("Ошибка при получении HTTP-кода: " + std::string(curl_easy_strerror(res)));

    return std::make_pair(httpCode, _httpParser.extractBody(response));
}

}

#endif
