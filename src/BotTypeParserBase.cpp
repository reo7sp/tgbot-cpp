#include "maxbot/BotTypeParserBase.h"

namespace MaxBot {

/*static*/ void BotTypeParserBase::appendToJson(std::string& json, const std::string& varName, const std::string& value) {
    if (value.empty()) {
        return;
    }
    json += '"';
    json += varName;
    json += R"(":)";
    if (value.front() != '{') {
        json += '"';
    }
    json += value;
    if (value.back() != '}') {
        json += '"';
    }
    json += ',';
}

}
