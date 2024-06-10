#include "tgbot/types/InputFile.h"
#include "tgbot/tools/FileTools.h"

#include <filesystem>
#include <memory>
#include <string>

namespace TgBot {

InputFile::Ptr InputFile::fromFile(const std::string& filePath, const std::string& mimeType) {
    auto result(std::make_shared<InputFile>());
    result->data = FileTools::read(filePath);
    result->mimeType = mimeType;
    result->fileName = std::filesystem::path(filePath).filename().string();
    return result;
}

}
