#include "tgbot/types/InlineQueryResultCachedAudio.h"
#include "tgbot/types/InlineQueryResultCachedDocument.h"
#include "tgbot/types/InlineQueryResultCachedGif.h"
#include "tgbot/types/InlineQueryResultCachedMpeg4Gif.h"
#include "tgbot/types/InlineQueryResultCachedPhoto.h"
#include "tgbot/types/InlineQueryResultCachedSticker.h"
#include "tgbot/types/InlineQueryResultCachedVideo.h"
#include "tgbot/types/InlineQueryResultCachedVoice.h"
#include "tgbot/types/InlineQueryResultAudio.h"
#include "tgbot/types/InlineQueryResultContact.h"
#include "tgbot/types/InlineQueryResultGame.h"
#include "tgbot/types/InlineQueryResultDocument.h"
#include "tgbot/types/InlineQueryResultLocation.h"
#include "tgbot/types/InlineQueryResultVenue.h"
#include "tgbot/types/InlineQueryResultVoice.h"
#include "tgbot/types/InlineQueryResultArticle.h"
#include "tgbot/types/InlineQueryResultGif.h"
#include "tgbot/types/InlineQueryResultMpeg4Gif.h"
#include "tgbot/types/InlineQueryResultPhoto.h"
#include "tgbot/types/InlineQueryResultVideo.h"

#include <string>

using namespace TgBot;

const std::string InlineQueryResultCachedAudio::TYPE = "audio";
const std::string InlineQueryResultCachedDocument::TYPE = "document";
const std::string InlineQueryResultCachedGif::TYPE = "gif";
const std::string InlineQueryResultCachedMpeg4Gif::TYPE = "mpeg4_gif";
const std::string InlineQueryResultCachedPhoto::TYPE = "photo";
const std::string InlineQueryResultCachedSticker::TYPE = "sticker";
const std::string InlineQueryResultCachedVideo::TYPE = "video";
const std::string InlineQueryResultCachedVoice::TYPE = "voice";

const std::string InlineQueryResultArticle::TYPE = "article";
const std::string InlineQueryResultAudio::TYPE = "audio";
const std::string InlineQueryResultContact::TYPE = "contact";
const std::string InlineQueryResultGame::TYPE = "game";
const std::string InlineQueryResultDocument::TYPE = "document";
const std::string InlineQueryResultGif::TYPE = "gif";
const std::string InlineQueryResultLocation::TYPE = "location";
const std::string InlineQueryResultMpeg4Gif::TYPE = "mpeg4_gif";
const std::string InlineQueryResultPhoto::TYPE = "photo";
const std::string InlineQueryResultVenue::TYPE = "venue";
const std::string InlineQueryResultVideo::TYPE = "video";
const std::string InlineQueryResultVoice::TYPE = "voice";
