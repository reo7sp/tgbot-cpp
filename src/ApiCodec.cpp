#include "tgbot/ApiCodec.h"

#include <stdexcept>

namespace TgBot::ApiRequest {

void appendField(std::vector<HttpFormField>& fields, std::string_view name, std::string_view value) {
    fields.push_back({ std::string(name), std::string(value) });
}

void appendField(std::vector<HttpFormField>& fields, std::string_view name, const std::shared_ptr<InputFile>& value) {
    if (value) {
        fields.push_back({
            std::string(name),
            HttpFile { value->data, value->mimeType, value->fileName, value->filePath },
        });
    }
}

void appendOptionalField(std::vector<HttpFormField>& fields, std::string_view name, std::string_view value) {
    if (!value.empty()) {
        appendField(fields, name, value);
    }
}

void appendOptionalField(std::vector<HttpFormField>& fields, std::string_view name, const std::string& value) {
    appendOptionalField(fields, name, std::string_view(value));
}

void appendOptionalField(std::vector<HttpFormField>& fields, std::string_view name, const nlohmann::json& value) {
    if (!value.is_null()) {
        appendField(fields, name, value.dump());
    }
}

void appendOptionalField(std::vector<HttpFormField>& fields, std::string_view,
                         const std::vector<InputFileAttachment>& value) {
    for (const auto& attachment : value) {
        if (attachment.name.empty()) {
            throw std::invalid_argument("Multipart attachment name must not be empty");
        }
        if (!attachment.file) {
            throw std::invalid_argument("Multipart attachment file must not be null: " + attachment.name);
        }
        appendField(fields, attachment.name, attachment.file);
    }
}

} // namespace TgBot::ApiRequest
