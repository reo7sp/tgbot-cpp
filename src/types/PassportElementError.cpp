#include "tgbot/types/PassportElementErrorDataField.h"
#include "tgbot/types/PassportElementErrorFrontSide.h"
#include "tgbot/types/PassportElementErrorReverseSide.h"
#include "tgbot/types/PassportElementErrorSelfie.h"
#include "tgbot/types/PassportElementErrorFile.h"
#include "tgbot/types/PassportElementErrorFiles.h"
#include "tgbot/types/PassportElementErrorTranslationFile.h"
#include "tgbot/types/PassportElementErrorTranslationFiles.h"
#include "tgbot/types/PassportElementErrorUnspecified.h"

#include <string>

using namespace TgBot;

const std::string PassportElementErrorDataField::SOURCE = "data";
const std::string PassportElementErrorFrontSide::SOURCE = "front_side";
const std::string PassportElementErrorReverseSide::SOURCE = "reverse_side";
const std::string PassportElementErrorSelfie::SOURCE = "selfie";
const std::string PassportElementErrorFile::SOURCE = "file";
const std::string PassportElementErrorFiles::SOURCE = "files";
const std::string PassportElementErrorTranslationFile::SOURCE = "translation_file";
const std::string PassportElementErrorTranslationFiles::SOURCE = "translation_files";
const std::string PassportElementErrorUnspecified::SOURCE = "unspecified";
