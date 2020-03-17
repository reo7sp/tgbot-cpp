#include "tgbot/types/InputFile.h"
#include "tgbot/tools/StringTools.h"
#include "tgbot/tools/FileTools.h"

#include <memory>
#include <string>

using namespace std;

namespace TgBot {

InputFile::Ptr InputFile::fromFile(const string& filePath, const string& mimeType) {
    auto result(make_shared<InputFile>());
    result->data = FileTools::read(filePath);
    result->mimeType = mimeType;
    result->fileName = StringTools::split(filePath, '/').back();
    return result;
}

}
