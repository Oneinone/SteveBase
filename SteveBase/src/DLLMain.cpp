#include <GlobalDefines.hpp>

#include <manager/CVarManager.hpp>
#include <manager/DrawManager.hpp>
#include <manager/GameHookManager.hpp>
#include <manager/InterfaceManager.hpp>
#include <manager/NetVarManager.hpp>
#include <manager/PatternManager.hpp>
#include <manager/VariableManager.hpp>
#include <utility/GameUtility.hpp>
#include <utility/Logger.hpp>
#include <utility/SystemUtility.hpp>

#include <vendor/XorStr/XorStr.h>

#if DEBUG
#include <vendor/CValveFileFormat/CValveFileFormat.hpp>
#endif

#include <windows.h>

namespace {
    using namespace SteveBase;
    using namespace Manager;
    using namespace Utility;

    void KillHack(HMODULE moduleDll) {
        LoggerNotice("Hack Unloaded");

        GameHookManager::StopHook();

#if DEBUG
        ShowWindow(GetConsoleWindow(), SW_HIDE);
        FreeConsole();
#endif

#if RELEASE
        SystemUtility::RelinkModuleToPEB(moduleDll);
#endif

        FreeLibraryAndExitThread(moduleDll, EXIT_SUCCESS);

    }

    DWORD WINAPI CheatThread(LPVOID param) {
        //DisableThreadLibraryCalls(thisModule);

#if DEBUG
        AllocConsole() ? freopen("CONOUT$", "w", stdout) : 0;
#endif

#if RELEASE
        SystemUtility::RemovePeHeader((HANDLE)param);
        SystemUtility::UnlinkModuleFromPEB((HMODULE)param);
#endif
        GameUtility::SetHackDirectory(SystemUtility::ProduceModulePath((HINSTANCE)param));

        LoggerNotice("Hello World!");
        LoggerNotice("Hack DLL Directory: {0}", GameUtility::GetHackDirectory());

        
        VariableManager::Init();
        LoggerNotice("Variable Manager Initialized.");

        HWND window;
        do {
            window = FindWindow(text("Valve001"), nullptr);
            Sleep(1);
        } while (window == nullptr);

        LoggerNotice("Window Found, Starting Managers.");
        
        GameHookManager::SetGameWindowHandle(window);

        PatternManager::Init();
        LoggerNotice("Pattern Manager Initialized.");
        
        InterfaceManager::Init();
        LoggerNotice("Interface Manager Initialized.");

        NetVarManager::Init();
        LoggerNotice("NetVar Manager Initialized.");
        
        DrawManager::Init();
        LoggerNotice("Draw Manager Initialized.");

        GameHookManager::StartHook();
        LoggerNotice("Game Hooks Started.");

        CVarManager::Init();
        LoggerNotice("ConVar Spoof Manager Initialized.");

        LoggerNotice("All Set. Have A Nice Day!");
        GameUtility::SetCheatRunning(true);

#if DEBUG
        auto lol = Valve::ValveFileFormat::Parser{}.ParseString(R"(
            "test"
            {
                "hello" "world"
            }
        )")->ToJson();
        LoggerDebug("{}", lol["hello"].get<std::string>());

        while (GameUtility::GetCheatRunning() && !GetAsyncKeyState(VK_DELETE)) {
            Sleep(1000);
        }

        GameUtility::SetCheatRunning(false);
        KillHack((HMODULE)param);
#endif

#if 0
        CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)[](LPVOID param2) -> DWORD {
            for (; !SystemUtility::IsDebuggerFound(); Sleep(1));
            GameUtility::SetCheatRunning(false);
            KillHack((HMODULE)param2);
        }, param, 0, nullptr);
#endif

        return 0;

    }
}

BOOLEAN WINAPI DllMain(
    IN HINSTANCE dllHandle,
    IN DWORD     reason,
    IN LPVOID    reserved
) {
    if (reason == DLL_PROCESS_ATTACH) {
        CreateThread(nullptr, 0, CheatThread, dllHandle, 0, nullptr);
    }

    return TRUE;
}
