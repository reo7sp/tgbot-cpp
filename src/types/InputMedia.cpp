#include "tgbot/types/InputMediaPhoto.h"
#include "tgbot/types/InputMediaVideo.h"
#include "tgbot/types/InputMediaAnimation.h"
#include "tgbot/types/InputMediaAudio.h"
#include "tgbot/types/InputMediaDocument.h"

#include <string>

using namespace TgBot;

const std::string InputMediaPhoto::TYPE = "photo";
const std::string InputMediaVideo::TYPE = "video";
const std::string InputMediaAnimation::TYPE = "animation";
const std::string InputMediaAudio::TYPE = "audio";
const std::string InputMediaDocument::TYPE = "document";
