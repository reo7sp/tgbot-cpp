#include "tgbot/types/InputFile.h"

#include <filesystem>
#include <fstream>
#include <memory>
#include <sstream>
#include <string>

namespace TgBot {

InputFile::Ptr InputFile::fromFile(const std::string& filePath, const std::string& mimeType) {
    std::ifstream input(filePath, std::ios::binary);
    input.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    std::ostringstream contents;
    contents << input.rdbuf();

    auto result(std::make_shared<InputFile>());
    result->data = contents.str();
    result->mimeType = mimeType;
    result->fileName = std::filesystem::path(filePath).filename().string();
    return result;
}

} // namespace TgBot
