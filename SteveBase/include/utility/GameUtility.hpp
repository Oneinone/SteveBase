#pragma once

#include <misc/TypeAliases.hpp>
#include <utility/SystemUtility.hpp>
#include <vendor/XorStr/XorStr.h>

#include <string>

namespace SteveBase::Utility {

    using namespace Misc;

    using InterfaceFactory = Func<void *(const char *, int*)>;

    class GameUtility {
        using MsgFn = void(*)(const TCHAR *pMsg, ...);
    public:
        static void SetCheatRunning(bool running);
        static bool GetCheatRunning();

        static void SetHackDirectory(std::string modPath);
        static std::string GetHackDirectory();

        static void SetHackConfigLocation(std::string location);
        static std::string GetHackConfigLocation();

        static MsgFn GetExportedFnMsgCompatible(const char *name) {
#if !SIMULATOR
            auto mod = SystemUtility::SafeGetModuleHandle(text("tier0.dll"));
            return (MsgFn)GetProcAddress(mod, name);
#else 
            return nullptr;
#endif
        }
        static void Msg(const char *msg) {
            static auto msgFn = GetExportedFnMsgCompatible(text("Msg"));
            if (msgFn) msgFn(msg);
        }
        static void Warning(const char *msg) {
            static auto warningMsg = GetExportedFnMsgCompatible(text("Warning"));
            if (warningMsg != nullptr) warningMsg(msg);

        }
        static void Log(const char *msg) {
            static auto logMsg = GetExportedFnMsgCompatible(text("Log"));
            if (logMsg != nullptr) logMsg(msg);
        }
    };
}
