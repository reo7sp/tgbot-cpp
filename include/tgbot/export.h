#pragma once

#ifndef TGBOT_API
#    if !defined(TGBOT_DLL)
#        define TGBOT_API
#    elif defined(_WIN32) || defined(__CYGWIN__)
#        if defined(TgBot_EXPORTS)
#            define TGBOT_API __declspec(dllexport)
#        else
#            define TGBOT_API __declspec(dllimport)
#        endif
#    elif defined(__GNUC__) && __GNUC__ >= 4
#        define TGBOT_API __attribute__((visibility("default")))
#    else
#        define TGBOT_API
#    endif
#endif
