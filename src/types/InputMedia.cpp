#include "maxbot/types/InputMediaPhoto.h"
#include "maxbot/types/InputMediaVideo.h"
#include "maxbot/types/InputMediaAnimation.h"
#include "maxbot/types/InputMediaAudio.h"
#include "maxbot/types/InputMediaDocument.h"

#include <string>

using namespace MaxBot;

const std::string InputMediaPhoto::TYPE = "photo";
const std::string InputMediaVideo::TYPE = "video";
const std::string InputMediaAnimation::TYPE = "animation";
const std::string InputMediaAudio::TYPE = "audio";
const std::string InputMediaDocument::TYPE = "document";
