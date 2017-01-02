#include <signal.h>
#include <stdio.h>
#include <exception>

#include <tgbot/tgbot.h>

using namespace std;
using namespace TgBot;

bool sigintGot = false;

int main() {
	signal(SIGINT, [](int s) {
		printf("SIGINT got");
		sigintGot = true;
	});

	Bot bot("PLACE YOUR TOKEN HERE");

	// Thanks Pietro Falessi for code
	TgBot::InlineKeyboardMarkup::Ptr Keyboard(new TgBot::InlineKeyboardMarkup);
	std::vector<InlineKeyboardButton::Ptr> Row0;
	TgBot::InlineKeyboardButton::Ptr CheckButton(new TgBot::InlineKeyboardButton);
	CheckButton->text="Check";
	CheckButton->callbackData="Check";
	Row0.push_back(CheckButton);
	Keyboard->inlineKeyboard.push_back(Row0);

	bot.getEvents().onCommand("start", [&bot, &Keyboard](Message::Ptr message) {
		bot.getApi().sendMessage(message->chat->id, "Hi!",false,0, Keyboard);
	});
	bot.getEvents().onCommand("check", [&bot, &Keyboard](Message::Ptr message) {
		string response = CheckCluster();
		bot.getApi().sendMessage(message->chat->id, response, false, 0, Keyboard,"Markdown");
	});
	bot.getEvents().onCallbackQuery([&bot, &Keyboard](CallbackQuery::Ptr query) {
		if (StringTools::startsWith(query->data, "Check")) {
			string response = CheckCluster();
			bot.getApi().sendMessage(query->message->chat->id, response, false, 0, Keyboard,"Markdown");
		}
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
