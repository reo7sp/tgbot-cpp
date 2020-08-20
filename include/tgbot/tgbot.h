#ifndef TGBOT_TGBOT_H
#define TGBOT_TGBOT_H

#include "tgbot/Api.h"
#include "tgbot/Bot.h"
#include "tgbot/EventBroadcaster.h"
#include "tgbot/EventHandler.h"
#include "tgbot/TgException.h"
#include "tgbot/TgTypeParser.h"
#include "tgbot/net/BoostHttpOnlySslClient.h"
#include "tgbot/net/CurlHttpClient.h"
#include "tgbot/net/HttpClient.h"
#include "tgbot/net/HttpParser.h"
#include "tgbot/net/HttpReqArg.h"
#include "tgbot/net/HttpServer.h"
#include "tgbot/net/TgLongPoll.h"
#include "tgbot/net/TgWebhookLocalServer.h"
#include "tgbot/net/TgWebhookServer.h"
#include "tgbot/net/TgWebhookTcpServer.h"
#include "tgbot/net/Url.h"
#include "tgbot/tgbot.h"
#include "tgbot/tools/FileTools.h"
#include "tgbot/tools/StringTools.h"
#include "tgbot/types/Animation.h"
#include "tgbot/types/Audio.h"
#include "tgbot/types/CallbackGame.h"
#include "tgbot/types/CallbackQuery.h"
#include "tgbot/types/Chat.h"
#include "tgbot/types/ChatMember.h"
#include "tgbot/types/ChatPhoto.h"
#include "tgbot/types/ChosenInlineResult.h"
#include "tgbot/types/Contact.h"
#include "tgbot/types/Document.h"
#include "tgbot/types/File.h"
#include "tgbot/types/ForceReply.h"
#include "tgbot/types/Game.h"
#include "tgbot/types/GameHighScore.h"
#include "tgbot/types/GenericReply.h"
#include "tgbot/types/InlineKeyboardButton.h"
#include "tgbot/types/InlineKeyboardMarkup.h"
#include "tgbot/types/InlineQuery.h"
#include "tgbot/types/InlineQueryResult.h"
#include "tgbot/types/InlineQueryResultArticle.h"
#include "tgbot/types/InlineQueryResultAudio.h"
#include "tgbot/types/InlineQueryResultCachedAudio.h"
#include "tgbot/types/InlineQueryResultCachedDocument.h"
#include "tgbot/types/InlineQueryResultCachedGif.h"
#include "tgbot/types/InlineQueryResultCachedMpeg4Gif.h"
#include "tgbot/types/InlineQueryResultCachedPhoto.h"
#include "tgbot/types/InlineQueryResultCachedSticker.h"
#include "tgbot/types/InlineQueryResultCachedVideo.h"
#include "tgbot/types/InlineQueryResultCachedVoice.h"
#include "tgbot/types/InlineQueryResultContact.h"
#include "tgbot/types/InlineQueryResultDocument.h"
#include "tgbot/types/InlineQueryResultGame.h"
#include "tgbot/types/InlineQueryResultGif.h"
#include "tgbot/types/InlineQueryResultLocation.h"
#include "tgbot/types/InlineQueryResultMpeg4Gif.h"
#include "tgbot/types/InlineQueryResultPhoto.h"
#include "tgbot/types/InlineQueryResultVenue.h"
#include "tgbot/types/InlineQueryResultVideo.h"
#include "tgbot/types/InlineQueryResultVoice.h"
#include "tgbot/types/InputContactMessageContent.h"
#include "tgbot/types/InputFile.h"
#include "tgbot/types/InputLocationMessageContent.h"
#include "tgbot/types/InputMedia.h"
#include "tgbot/types/InputMediaPhoto.h"
#include "tgbot/types/InputMediaVideo.h"
#include "tgbot/types/InputMessageContent.h"
#include "tgbot/types/InputTextMessageContent.h"
#include "tgbot/types/InputVenueMessageContent.h"
#include "tgbot/types/Invoice.h"
#include "tgbot/types/KeyboardButton.h"
#include "tgbot/types/LabeledPrice.h"
#include "tgbot/types/Location.h"
#include "tgbot/types/MaskPosition.h"
#include "tgbot/types/Message.h"
#include "tgbot/types/MessageEntity.h"
#include "tgbot/types/OrderInfo.h"
#include "tgbot/types/PhotoSize.h"
#include "tgbot/types/PreCheckoutQuery.h"
#include "tgbot/types/ReplyKeyboardMarkup.h"
#include "tgbot/types/ReplyKeyboardRemove.h"
#include "tgbot/types/ResponseParameters.h"
#include "tgbot/types/ShippingAddress.h"
#include "tgbot/types/ShippingOption.h"
#include "tgbot/types/ShippingQuery.h"
#include "tgbot/types/Sticker.h"
#include "tgbot/types/StickerSet.h"
#include "tgbot/types/SuccessfulPayment.h"
#include "tgbot/types/Update.h"
#include "tgbot/types/User.h"
#include "tgbot/types/UserProfilePhotos.h"
#include "tgbot/types/Venue.h"
#include "tgbot/types/Video.h"
#include "tgbot/types/VideoNote.h"
#include "tgbot/types/Voice.h"
#include "tgbot/types/WebhookInfo.h"
#include "tgbot/types/BotCommand.h"


/**
 * @defgroup general
 * @defgroup types
 * @defgroup net
 * @defgroup tools
 *
 * @mainpage
 * [Go to GitHub](https://github.com/reo7sp/tgbot-cpp)
 *
 * @section lib_compile Library compilation
 *
 * Firstly you need to install some dependencies such as Boost and build tools such as CMake. On Debian-based distibutives you can do it with these commands:
 * @code{.sh}
 * sudo apt-get install g++ make binutils cmake libssl-dev libboost-system-dev
 * @endcode
 *
 * To compile the library execute this commands:
 * @code{.sh}
 * cd /path/where/you/have/cloned/the/library/repository
 * cmake .
 * make -j4
 * sudo make install
 * @endcode
 *
 * @section bot_compile Bot compilation
 * With CMake:
 * [Example CMakeLists.txt](samples/echobot/CMakeLists.txt)
 *
 * Without CMake:
 * @code{.sh}
 * g++ telegram_bot.cpp -o telegram_bot --std=c++11 -I/usr/local/include -lTgBot -lboost_system -lssl -lcrypto -lpthread
 * @endcode
 *
 * Also:
 * You can use Docker to build and run your bot. Set the base image of your's Dockerfile to [reo7sp/tgbot-cpp](https://hub.docker.com/r/reo7sp/tgbot-cpp/).
 *
 * @section Samples
 * All samples are located [here](https://github.com/reo7sp/tgbot-cpp/tree/master/samples).
 *
 * @section Licence
 * [The MIT License](https://github.com/reo7sp/tgbot-cpp/blob/master/LICENSE).
 */

#endif //TGBOT_TGBOT_H
