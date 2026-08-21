#include "tgbot/InputFile.h"

#include <filesystem>
#include <memory>
#include <string>
#include <utility>

namespace TgBot {

std::shared_ptr<InputFile> InputFile::fromData(std::string data, std::string mimeType, std::string fileName) {
    auto result = std::make_shared<InputFile>();
    result->data = std::move(data);
    result->mimeType = std::move(mimeType);
    result->fileName = std::move(fileName);

    return result;
}

std::shared_ptr<InputFile> InputFile::fromFile(std::string_view filePath, std::string mimeType) {
    const std::filesystem::path path(filePath);

    auto result(std::make_shared<InputFile>());
    result->mimeType = std::move(mimeType);
    result->fileName = path.filename().string();
    result->filePath = path.string();

    return result;
}

} // namespace TgBot
