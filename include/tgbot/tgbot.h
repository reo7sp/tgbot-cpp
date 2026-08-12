#pragma once

#include "tgbot/Api.h"
#include "tgbot/ApiCodec.h"
#include "tgbot/Bot.h"
#include "tgbot/CurlHttpClient.h"
#include "tgbot/EventBroadcaster.h"
#include "tgbot/EventHandler.h"
#include "tgbot/HttpClient.h"
#include "tgbot/HttpFormField.h"
#include "tgbot/HttpServer.h"
#include "tgbot/InputFile.h"
#include "tgbot/Json.h"
#include "tgbot/TgException.h"
#include "tgbot/TgLongPoll.h"
#include "tgbot/TgWebhookLocalServer.h"
#include "tgbot/TgWebhookServer.h"
#include "tgbot/TgWebhookTcpServer.h"
#include "tgbot/Types.h"

/** @defgroup general General
 * @brief Bot lifecycle, event handling, and errors.
 */

/** @defgroup net Network
 * @brief HTTP clients, servers, and update transports.
 */

/** @defgroup api API
 * @brief API methods and objects defined by the Telegram Bot API.
 */

/** @mainpage
 * Documentation for the tgbot-cpp library.
 *
 * [GitHub](https://github.com/reo7sp/tgbot-cpp)
 */
