#include <tgbot/tgbot.h>

using namespace std;
using namespace TgBot;

bool sigintGot = false;

int main() {
	Bot bot("PLACE YOUR TOKEN HERE");
	bot.getEvents().onCommand("start", [&bot](Message::Ptr message) {
		bot.getApi().sendMessage(message->chat->id, "Hi!");
	});
	bot.getEvents().onAnyMessage([&bot](Message::Ptr message) {
		printf("User wrote %s\n", message->text.c_str());
		if (StringTools::startsWith(message->text, "/start")) {
			return;
		}
		bot.getApi().sendMessage(message->chat->id, "Your message is: " + message->text);
	});
}
