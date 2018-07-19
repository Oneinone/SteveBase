#pragma once

#if (DEBUG || SIMULATOR)
#include <ctime>

#include <utility/GameUtility.hpp>

#include <vendor/ggformat/ggformat.h>
#endif

namespace SteveBase::Utility {
#if (DEBUG || SIMULATOR)
    inline std::string GetTimeStamp() {
        time_t rawtime;
        char timebuffer[128];

        std::time(&rawtime);
        auto timeinfo = localtime(&rawtime);

        std::strftime(timebuffer, sizeof timebuffer, "%Y-%m-%d %H:%M:%S", timeinfo);

        return std::string(timebuffer);
    }

#define LoggerDebug(logFormat, ...)   do { auto msg = ggformat_to_string("[{}] [DEBUG] {}: {}\n",   GetTimeStamp(), __FUNCTION__, ggformat_to_string(logFormat, __VA_ARGS__)); GameUtility::Msg(msg.c_str()); ggprint(msg.c_str()); } while(0)
#define LoggerNotice(logFormat, ...)  do { auto msg = ggformat_to_string("[{}] [NOTICE] {}: {}\n",  GetTimeStamp(), __FUNCTION__, ggformat_to_string(logFormat, __VA_ARGS__)); GameUtility::Msg(msg.c_str()); ggprint(msg.c_str()); } while(0)
#define LoggerWarning(logFormat, ...) do { auto msg = ggformat_to_string("[{}] [WARNING] {}: {}\n", GetTimeStamp(), __FUNCTION__, ggformat_to_string(logFormat, __VA_ARGS__)); GameUtility::Warning(msg.c_str()); ggprint(msg.c_str()); } while(0)
#define LoggerError(logFormat, ...)   do { auto msg = ggformat_to_string("[{}] [ERROR] {}: {}\n",   GetTimeStamp(), __FUNCTION__, ggformat_to_string(logFormat, __VA_ARGS__)); GameUtility::Warning(msg.c_str()); ggprint(msg.c_str()); } while(0)

#else

    // nullify all Logger Calls
#define LoggerDebug(...) ((void) 0)
#define LoggerNotice(...) ((void) 0)
#define LoggerWarning(...) ((void) 0)
#define LoggerError(...) ((void) 0)

#endif
}