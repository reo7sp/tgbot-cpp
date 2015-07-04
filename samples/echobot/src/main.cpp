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

#include <signal.h>
#include <stdio.h>
#include <exception>

#include <tgbot/Bot.h>
#include <tgbot/tools/StringTools.h>
#include <tgbot/TgException.h>

using namespace std;
using namespace TgBot;

bool sigintGot = false;

int main() {
    signal(SIGINT, [](int s) {
        printf("SIGINT got");
        sigintGot = true;
    });

    Bot bot("PLACE_YOUR_TOKEN_HERE");
    bot.getEvents().onCommand("start", [](Message::Ptr message, Bot* const bot) {
        bot->getApi().sendMessage(message->chat->id, "Hi!");
    });
    bot.getEvents().onAnyMessage([](Message::Ptr message, Bot* const bot) {
        printf("User wrote %s\n", message->text.c_str());
        if (StringTools::startsWith(message->text, "/start")) {
            return;
        }
        bot->getApi().sendMessage(message->chat->id, "Your message is: " + message->text);
    });

    try {
        printf("Bot username: %s\n", bot.getApi().getMe()->username.c_str());

        while (!sigintGot) {
            printf("Long poll started\n");
            bot.startLongPoll();
        }
    } catch (TgException& e) {
        printf("error: %s\n", e.what());
    }

    return 0;
}
