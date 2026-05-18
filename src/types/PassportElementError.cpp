#include "maxbot/types/PassportElementErrorDataField.h"
#include "maxbot/types/PassportElementErrorFrontSide.h"
#include "maxbot/types/PassportElementErrorReverseSide.h"
#include "maxbot/types/PassportElementErrorSelfie.h"
#include "maxbot/types/PassportElementErrorFile.h"
#include "maxbot/types/PassportElementErrorFiles.h"
#include "maxbot/types/PassportElementErrorTranslationFile.h"
#include "maxbot/types/PassportElementErrorTranslationFiles.h"
#include "maxbot/types/PassportElementErrorUnspecified.h"

#include <string>

using namespace MaxBot;

const std::string PassportElementErrorDataField::SOURCE = "data";
const std::string PassportElementErrorFrontSide::SOURCE = "front_side";
const std::string PassportElementErrorReverseSide::SOURCE = "reverse_side";
const std::string PassportElementErrorSelfie::SOURCE = "selfie";
const std::string PassportElementErrorFile::SOURCE = "file";
const std::string PassportElementErrorFiles::SOURCE = "files";
const std::string PassportElementErrorTranslationFile::SOURCE = "translation_file";
const std::string PassportElementErrorTranslationFiles::SOURCE = "translation_files";
const std::string PassportElementErrorUnspecified::SOURCE = "unspecified";
