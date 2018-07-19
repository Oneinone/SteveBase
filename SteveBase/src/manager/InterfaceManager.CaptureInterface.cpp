#include <GlobalDefines.hpp>
#include <manager/InterfaceManager.hpp>

#include <Interface.hpp>
#include <misc/Macro.hpp>
#include <source_engine/index.hpp>

#include <vendor/XorStr/XorStr.h>

namespace SteveBase::Manager {
    struct CaptureModule {
        const char *name = nullptr;

        template<size_t N>
        constexpr FORCEINLINE CaptureModule(const char(&name)[N]) {
            this->name = textdup(name);
        }

        CaptureModuleEntry operator =(std::initializer_list<InterfaceBindPair> &&bindList) {
            return CaptureModuleEntry{ name, bindList };
        }
    };

    template<class T, size_t N>
    constexpr FORCEINLINE InterfaceBindPair BindInterface(const char(&ifaceName)[N]) {
        return { textdup(ifaceName), GetHashForType<T>() };
    }

    CaptureModuleEntry interfaceBindMap[] = {
        CaptureModule("client.dll") = {
            BindInterface<IBaseClientDLL>("VClient"),
            BindInterface<IClientEntityList>("VClientEntityList"),
            BindInterface<IPrediction>("VClientPrediction"),
            BindInterface<IGameMovement>("GameMovement"),
        },

        CaptureModule("engine.dll") = {
            BindInterface<IEngineClient>("VEngineClient"),
            BindInterface<IEngineTrace>("EngineTraceClient"),
            BindInterface<IEngineVGui>("VEngineVGui"),
            BindInterface<IGameEventManager2>("GAMEEVENTSMANAGER002"),
            BindInterface<IVDebugOverlay>("VDebugOverlay"),
            BindInterface<IVModelInfo>("VModelInfoClient"),
            BindInterface<IVModelRender>("VEngineModel"),
        },

        CaptureModule("vgui2.dll") = {
            BindInterface<IPanel>("VGUI_Panel")
        },

        CaptureModule("vguimatsurface.dll") = {
            BindInterface<ISurface>("VGUI_Surface")
        },

        CaptureModule("vstdlib.dll") = {
            BindInterface<ICVar>("VEngineCvar")
        },

        CaptureModule("inputsystem.dll") = {
            BindInterface<IInputSystem>("InputSystemVersion")
        },

        CaptureModule("materialsystem.dll") = {
            BindInterface<IMaterialSystem>("VMaterialSystem")
        },

        CaptureModule("studiorender.dll") = {
            BindInterface<IStudioRender>("VStudioRender026")
        }
    };
}