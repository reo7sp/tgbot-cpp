// Example of using array of proxies wth maxbot-cpp library.
// Based on original code (c) Oleg Morozenkov [reo7sp] https://github.com/reo7sp
// https://github.com/reo7sp/maxbot-cpp/blob/master/samples/echobot-curl-client/src/main.cpp

#include <csignal>
#include <cstdio>
#include <cstdlib>
#include <exception>
#include <string>
#include <vector>

#ifndef HAVE_CURL
#define HAVE_CURL
#endif

#include <maxbot/net/CurlHttpClient.h>
#include <maxbot/maxbot.h>

using namespace std;
using namespace MaxBot;

#define CONNECT_TIMEOUT 10L

int main() {
  // Filling array of proxies.
  vector<const char*> proxies;
  // NULL = no proxy, direct connection to API.
  proxies.push_back(NULL);  // [0]
  // All proxy-URLs below are fake. Use yuor own.
  proxies.push_back("socks5://user:password@10.20.30.40:1080");  // [1]
  proxies.push_back("http://user:password@192.168.50.70:3128");  // [2]
  proxies.push_back("http://user:password@192.168.80.90:3128");  // [3]
  // Choose "staring" index of proxy. In this example [0] - NULL=no proxy.
  size_t proxy_now = 0;

  string token(getenv("TOKEN"));
  printf("Token: %s\n", token.c_str());

  CurlHttpClient curlHttpClient;
  Bot bot(token, curlHttpClient);

  bot.getEvents().onCommand("start", [&bot](Message::Ptr message) {
    bot.getApi().sendMessage(message->chat->id, "Hi!");
  });
  bot.getEvents().onAnyMessage([&bot](Message::Ptr message) {
    printf("User wrote %s\n", message->text.c_str());
    if (StringTools::startsWith(message->text, "/start")) return;
    bot.getApi().sendMessage(message->chat->id,
                             "Your message is: " + message->text);
  });

  signal(SIGINT, [](int s) {
    printf("SIGINT got: %i\n", s);
    exit(0);
  });

  while (true) {
    try {
      printf("Bot username: %s\n", bot.getApi().getMe()->username.c_str());
      bot.getApi().deleteWebhook();

      BotLongPoll longPoll(bot);
      while (true) {
        printf("Long poll started\n");
        longPoll.start();
      }
    } catch (exception &e) {
      printf("Proxy[%li]: %s error\n", proxy_now, proxies[proxy_now]);
      printf("%s\n", e.what());
      // Assumption:
      // the reason of exception was - disconnect,
      // connection timeout or other network problem.
      // Trying to switch (cycle) to next proxy in array.
      proxy_now++;
      if (proxy_now >= proxies.size()) proxy_now = 0;
      curlHttpClient.setProxy(proxies[proxy_now], CONNECT_TIMEOUT);
      printf("Switch proxy[%li]: %s\n", proxy_now, proxies[proxy_now]);
    }
  }
  return 0;
}

// eof
