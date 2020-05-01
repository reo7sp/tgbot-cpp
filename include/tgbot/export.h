#ifndef TGBOT_EXPORT_H
#define TGBOT_EXPORT_H

#ifndef TGBOT_API
    #ifdef TGBOT_DLL
        #if defined _WIN32 || defined __CYGWIN__
            #define TGBOT_HELPER_DLL_EXPORT __declspec(dllexport)
            #define TGBOT_HELPER_DLL_IMPORT __declspec(dllimport)
        #else
            #if __GNUC__ >= 4
                #define TGBOT_HELPER_DLL_EXPORT __attribute__ ((visibility ("default")))
                #define TGBOT_HELPER_DLL_IMPORT __attribute__ ((visibility ("default")))
            #else
                #define TGBOT_HELPER_DLL_EXPORT
                #define TGBOT_HELPER_DLL_IMPORT
            #endif
        #endif
        #ifdef TgBot_EXPORTS
            #define TGBOT_API TGBOT_HELPER_DLL_EXPORT
        #else
            #define TGBOT_API TGBOT_HELPER_DLL_IMPORT
        #endif
    #else
        #define TGBOT_API
    #endif
#endif

#endif //TGBOT_EXPORT_H
