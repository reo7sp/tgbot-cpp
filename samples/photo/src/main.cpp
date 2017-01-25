//
// Created by Oleg Morozenkov on 25.01.17.
//

#include <signal.h>
#include <stdio.h>
#include <exception>

#include <tgbot/tgbot.h>

using namespace std;
using namespace TgBot;

bool sigintGot = false;

int main() {
	const string photoFilePath = "example.jpg";
	const string photoMimeType = "image/jpeg";

	Bot bot("PLACE YOUR TOKEN HERE");
	bot.getEvents().onCommand("start", [&bot](Message::Ptr message) {
		bot.getApi().sendMessage(message->chat->id, "Hi!");
	});
	bot.getEvents().onCommand("photo", [&bot, &photoFilePath, &photoMimeType](Message::Ptr message) {
		bot.getApi().sendPhoto(message->chat->id, InputFile::fromFile(photoFilePath, photoMimeType));
	});

	signal(SIGINT, [](int s) {
		printf("SIGINT got");
		sigintGot = true;
	});
	try {
		printf("Bot username: %s\n", bot.getApi().getMe()->username.c_str());

		TgLongPoll longPoll(bot);
		while (!sigintGot) {
			printf("Long poll started\n");
			longPoll.start();
		}
	} catch (exception& e) {
		printf("error: %s\n", e.what());
	}

	return 0;
}
