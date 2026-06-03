#ifndef MAXBOT_EXPORT_H
#define MAXBOT_EXPORT_H

#ifndef MAXBOT_API
    #ifdef MAXBOT_DLL
        #if defined _WIN32 || defined __CYGWIN__
            #define MAXBOT_HELPER_DLL_EXPORT __declspec(dllexport)
            #define MAXBOT_HELPER_DLL_IMPORT __declspec(dllimport)
        #else
            #if __GNUC__ >= 4
                #define MAXBOT_HELPER_DLL_EXPORT __attribute__ ((visibility ("default")))
                #define MAXBOT_HELPER_DLL_IMPORT __attribute__ ((visibility ("default")))
            #else
                #define MAXBOT_HELPER_DLL_EXPORT
                #define MAXBOT_HELPER_DLL_IMPORT
            #endif
        #endif
        #ifdef MaxBot_EXPORTS
            #define MAXBOT_API MAXBOT_HELPER_DLL_EXPORT
        #else
            #define MAXBOT_API MAXBOT_HELPER_DLL_IMPORT
        #endif
    #else
        #define MAXBOT_API
    #endif
#endif

#endif //MAXBOT_EXPORT_H
