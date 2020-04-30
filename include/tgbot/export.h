#ifndef TGBOT_EXPORT_H
#define TGBOT_EXPORT_H

#ifndef TGBOT_API
#ifdef _MSC_VER
#ifdef TGBOT_DLL
#ifdef TgBot_EXPORTS
#define TGBOT_API __declspec(dllexport)
#else
#define TGBOT_API __declspec(dllimport)
#endif
#else
#define TGBOT_API
#endif
#else
#define TGBOT_API
#endif
#endif

#endif //TGBOT_EXPORT_H
