#include "maxbot/types/InlineQueryResultCachedAudio.h"
#include "maxbot/types/InlineQueryResultCachedDocument.h"
#include "maxbot/types/InlineQueryResultCachedGif.h"
#include "maxbot/types/InlineQueryResultCachedMpeg4Gif.h"
#include "maxbot/types/InlineQueryResultCachedPhoto.h"
#include "maxbot/types/InlineQueryResultCachedSticker.h"
#include "maxbot/types/InlineQueryResultCachedVideo.h"
#include "maxbot/types/InlineQueryResultCachedVoice.h"
#include "maxbot/types/InlineQueryResultAudio.h"
#include "maxbot/types/InlineQueryResultContact.h"
#include "maxbot/types/InlineQueryResultGame.h"
#include "maxbot/types/InlineQueryResultDocument.h"
#include "maxbot/types/InlineQueryResultLocation.h"
#include "maxbot/types/InlineQueryResultVenue.h"
#include "maxbot/types/InlineQueryResultVoice.h"
#include "maxbot/types/InlineQueryResultArticle.h"
#include "maxbot/types/InlineQueryResultGif.h"
#include "maxbot/types/InlineQueryResultMpeg4Gif.h"
#include "maxbot/types/InlineQueryResultPhoto.h"
#include "maxbot/types/InlineQueryResultVideo.h"

#include <string>

using namespace MaxBot;

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
