#include "tgbot/CurlHttpClient.h"

#include <atomic>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <span>
#include <string>
#include <variant>

namespace TgBot {

namespace {

struct RequestCancelState {
    RequestCancelState(const std::atomic<bool>* const isEternalCancel,
                       const std::atomic<uint64_t>* const globalCancelEpoch, const uint64_t currentCancelEpoch)
        : isEternalCancel(isEternalCancel)
        , globalCancelEpoch(globalCancelEpoch)
        , currentCancelEpoch(currentCancelEpoch) {
    }

    const std::atomic<bool>* const isEternalCancel = nullptr;
    const std::atomic<uint64_t>* const globalCancelEpoch = nullptr;
    const uint64_t currentCancelEpoch = 0;
};
} // namespace

CurlHttpClient::CurlHttpClient() {
}

CurlHttpClient::~CurlHttpClient() {
    std::lock_guard<std::mutex> lock(curlHandlesMutex);
    for (auto& c : curlHandles) {
        curl_easy_cleanup(c.second);
    }
}

static CURL* getCurlHandle(const CurlHttpClient* c_) {
    CurlHttpClient* c = const_cast<CurlHttpClient*>(c_);

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

static int curlProgressCallback(void* clientp, curl_off_t dltotal, curl_off_t dlnow, curl_off_t ultotal,
                                curl_off_t ulnow) {
    const RequestCancelState* const state = static_cast<const RequestCancelState* const>(clientp);
    if (state
        && ((state->isEternalCancel && state->isEternalCancel->load())
            || (state->globalCancelEpoch && state->currentCancelEpoch < state->globalCancelEpoch->load()))) {
        return 1;
    }

    return 0;
}

static std::size_t curlWriteString(char* ptr, std::size_t size, std::size_t nmemb, void* userdata) {
    static_cast<std::string*>(userdata)->append(ptr, size * nmemb);
    return size * nmemb;
}

std::string CurlHttpClient::makeRequest(const std::string& url, std::span<const HttpFormField> fields) const {
    CURL* curl = getCurlHandle(this);

    curl_easy_reset(curl);
    curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, _connectTimeout);
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, _timeout);
    curl_easy_setopt(curl, CURLOPT_PROXY, _proxyUrl);

    const RequestCancelState state { &_isEternalCancel, &_cancelEpoch, _cancelEpoch.load() };

    curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 0L);
    curl_easy_setopt(curl, CURLOPT_XFERINFOFUNCTION, curlProgressCallback);
    curl_easy_setopt(curl, CURLOPT_XFERINFODATA, &state);

    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

    curl_mime* mime;
    curl_mimepart* part;
    mime = curl_mime_init(curl);
    if (!fields.empty()) {
        for (const HttpFormField& field : fields) {
            part = curl_mime_addpart(mime);

            curl_mime_name(part, field.name.c_str());
            if (const auto* file = std::get_if<HttpFile>(&field.value)) {
                curl_mime_data(part, file->data.c_str(), file->data.size());
                curl_mime_type(part, file->mimeType.c_str());
                curl_mime_filename(part, file->fileName.c_str());
            } else {
                const std::string& value = std::get<std::string>(field.value);
                curl_mime_data(part, value.c_str(), value.size());
                curl_mime_type(part, "text/plain");
            }
        }
        curl_easy_setopt(curl, CURLOPT_MIMEPOST, mime);
    }

    std::string response;
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, curlWriteString);

    char errbuf[CURL_ERROR_SIZE] { };
    curl_easy_setopt(curl, CURLOPT_ERRORBUFFER, errbuf);

    auto res = curl_easy_perform(curl);
    curl_mime_free(mime);

    if (res == CURLcode::CURLE_ABORTED_BY_CALLBACK
        && ((state.isEternalCancel && state.isEternalCancel->load())
            || (state.globalCancelEpoch && state.currentCancelEpoch < state.globalCancelEpoch->load()))) {
        const size_t slashPos = url.rfind('/');

        throw std::runtime_error(slashPos == std::string::npos
                                     ? getCancelExceptionText()
                                     : getCancelExceptionText() + ": " + url.substr(slashPos + 1));
    }

    // If the request did not complete correctly, show the error
    // information. If no detailed error information was written to errbuf
    // show the more generic information from curl_easy_strerror instead.
    if (res != CURLE_OK) {
        size_t len = strlen(errbuf);
        std::string errmsg;
        if (len) {
            errmsg = std::string(errbuf) + ((errbuf[len - 1] != '\n') ? "\n" : "");
        } else {
            errmsg = curl_easy_strerror(res);
        }
        throw std::runtime_error(std::string("curl error: ") + errmsg);
    }

    return response;
}

} // namespace TgBot
