#include "tgbot/Api.h"

#include "tgbot/HttpClient.h"
#include "tgbot/TgException.h"

#include <nlohmann/json.hpp>

#include <utility>

namespace TgBot {

Api::Api(std::string token, const HttpClient& httpClient, std::string url)
    : _httpClient(httpClient)
    , _token(std::move(token))
    , _url(std::move(url)) {
}

std::string Api::downloadFile(std::string_view filePath, const std::vector<HttpFormField>& fields) const {
    std::string url;
    url.reserve(_url.size() + _token.size() + filePath.size() + 10);
    url.append(_url).append("/file/bot").append(_token).append("/").append(filePath);
    return _httpClient.makeRequest(url, fields);
}

nlohmann::json Api::sendRequest(std::string_view method, const std::vector<HttpFormField>& fields) const {
    std::string url;
    url.reserve(_url.size() + _token.size() + method.size() + 6);
    url.append(_url).append("/bot").append(_token).append("/").append(method);
    const std::string body = _httpClient.makeRequest(url, fields);
    if (body.starts_with("<html>")) {
        throw TgException("tgbot-cpp received HTML instead of a Telegram Bot API response",
                          TgException::ErrorCode::HtmlResponse);
    }

    nlohmann::json response;
    try {
        response = nlohmann::json::parse(body);
    } catch (const nlohmann::json::parse_error& exception) {
        throw TgException(exception.what(), TgException::ErrorCode::InvalidJson);
    }
    if (!response.value("ok", false)) {
        throw TgException(response.value("description", "Telegram Bot API request failed"),
                          static_cast<TgException::ErrorCode>(response.value("error_code", 0)));
    }

    return response.at("result");
}

} // namespace TgBot
