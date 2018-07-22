//
// Created by Oleg Morozenkov on 25.01.17.
//

#include "tgbot/types/InputFile.h"

#include <fstream>

#include "tgbot/tools/StringTools.h"
#include "tgbot/tools/FileTools.h"

using namespace std;

namespace TgBot {

InputFile::Ptr InputFile::fromFile(const string& filePath, const string& mimeType) {
    auto result(make_shared<InputFile>());
    result->data = FileTools::read(filePath);
    result->mimeType = mimeType;
    result->fileName = StringTools::split(filePath, '/').back();
    return result;
}

};
