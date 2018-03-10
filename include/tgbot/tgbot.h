/*
 * Copyright (c) 2015 Oleg Morozenkov
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef TGBOT_TGBOT_H
#define TGBOT_TGBOT_H

#include "tgbot/Bot.h"
#include "tgbot/Api.h"
#include "tgbot/TgException.h"
#include "tgbot/TgTypeParser.h"
#include "tgbot/EventBroadcaster.h"
#include "tgbot/EventHandler.h"
#include "tgbot/types/Audio.h"
#include "tgbot/types/Contact.h"
#include "tgbot/types/Document.h"
#include "tgbot/types/ForceReply.h"
#include "tgbot/types/GenericReply.h"
#include "tgbot/types/InputFile.h"
#include "tgbot/types/Location.h"
#include "tgbot/types/Message.h"
#include "tgbot/types/PhotoSize.h"
#include "tgbot/types/ReplyKeyboardRemove.h"
#include "tgbot/types/ReplyKeyboardMarkup.h"
#include "tgbot/types/Sticker.h"
#include "tgbot/types/Update.h"
#include "tgbot/types/User.h"
#include "tgbot/types/UserProfilePhotos.h"
#include "tgbot/types/Video.h"
#include "tgbot/types/InlineQuery.h"
#include "tgbot/types/InlineQueryResult.h"
#include "tgbot/types/InlineQueryResultArticle.h"
#include "tgbot/types/InlineQueryResultGif.h"
#include "tgbot/types/InlineQueryResultMpeg4Gif.h"
#include "tgbot/types/InlineQueryResultPhoto.h"
#include "tgbot/types/InlineQueryResultVideo.h"
#include "tgbot/types/ChosenInlineResult.h"
#include "tgbot/tools/StringTools.h"
#include "tgbot/tools/FileTools.h"
#include "tgbot/net/HttpClient.h"
#include "tgbot/net/HttpParser.h"
#include "tgbot/net/HttpReqArg.h"
#include "tgbot/net/HttpServer.h"
#include "tgbot/net/TgLongPoll.h"
#include "tgbot/net/TgWebhookLocalServer.h"
#include "tgbot/net/TgWebhookServer.h"
#include "tgbot/net/TgWebhookTcpServer.h"
#include "tgbot/net/Url.h"

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
 * All samples are located [here](https://github.com/reo7sp/tgbot-cpp/tree/master/samples)
 *
 * @section Feedback
 * Feel free to [create new issues on GitHub](https://github.com/reo7sp/tgbot-cpp/issues) or [contact me on Telegram](https://t.me/reo7sp)
 *
 * @section Licence
 * [The MIT License](http://opensource.org/licenses/MIT)
 */

#endif //TGBOT_TGBOT_H
