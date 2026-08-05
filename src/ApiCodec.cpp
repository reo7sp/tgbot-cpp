#include "tgbot/ApiCodec.h"

namespace TgBot::ApiRequest {

void appendField(std::vector<HttpFormField>& fields, const char* name, const std::string& value) {
    fields.push_back({ name, value });
}

void appendField(std::vector<HttpFormField>& fields, const char* name, const std::shared_ptr<InputFile>& value) {
    if (value) {
        fields.push_back({
            name,
            HttpFile { value->data, value->mimeType, value->fileName },
        });
    }
}

void appendOptionalField(std::vector<HttpFormField>& fields, const char* name, const std::string& value) {
    if (!value.empty()) {
        appendField(fields, name, value);
    }
}

void appendOptionalField(std::vector<HttpFormField>& fields, const char* name, const nlohmann::json& value) {
    if (!value.is_null()) {
        appendField(fields, name, value.dump());
    }
}

} // namespace TgBot::ApiRequest
