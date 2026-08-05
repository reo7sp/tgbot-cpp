#pragma once

#include "tgbot/HttpFormField.h"
#include "tgbot/export.h"
#include "tgbot/types/InputFile.h"
#include "tgbot/types/Sticker.h"
#include "tgbot/types/types_fwd.h"

#include <nlohmann/json_fwd.hpp>

#include <cstdint>
#include <memory>
#include <optional>
#include <string>
#include <variant>
#include <vector>

namespace TgBot {

class Bot;
class HttpClient;

/**
 * @brief Executes methods from the Telegram Bot API.
 *
 * Method declarations and their documentation are generated from the official
 * Telegram Bot API documentation.
 *
 * @ingroup general
 */
class TGBOT_API Api {
    friend class Bot;

public:
    Api(std::string token, const HttpClient& httpClient, std::string url);

#include "tgbot/ApiMethods.inc.h"

    /**
     * @brief Downloads a Telegram file and returns its contents.
     */
    std::string downloadFile(const std::string& filePath, const std::vector<HttpFormField>& fields = { }) const;

    const HttpClient& _httpClient;

protected:
    nlohmann::json sendRequest(const std::string& method, const std::vector<HttpFormField>& fields) const;

    const std::string _token;
    const std::string _url;
};

} // namespace TgBot
