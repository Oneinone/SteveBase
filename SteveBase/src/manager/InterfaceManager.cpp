#include <GlobalDefines.hpp>
#include <manager/InterfaceManager.hpp>

#include <Interface.hpp>
#include <manager/PatternManager.hpp>
#include <source_engine/index.hpp>

#include <utility/SystemUtility.hpp>
#include <vendor/hash/hash.h>
#include <vendor/XorStr/XorStr.h>

#if DEBUG
#include <utility/Logger.hpp>
#endif

#include <windows.h>
#include <d3d9.h>

namespace SteveBase::Manager {
    using namespace Misc;
    using namespace SourceEngine::Virtual;
    using namespace Utility;

    extern CaptureModuleEntry interfaceBindMap[8];

#if DEBUG
    inline void DumpModuleRegister(const char *dllModule) {
        auto sig = SystemUtility::FindModulePattern(dllModule, text("8B 35 ? ? ? ? 57 85 F6 74 38"));

        if (sig == nullptr) return;

        sig += 2;

        const auto regs = **(InterfaceReg***)sig;

        if (regs == nullptr) return;

        for (auto cur = regs; cur; cur = cur->m_pNext) {
            LoggerDebug("{0}: {1}", dllModule, cur->GetName()); // dump all registry name
        }
    }
#endif


    void InterfaceManager::Init() {
#if DEBUG
        DumpModuleRegister("client.dll");
        DumpModuleRegister("engine.dll");
        DumpModuleRegister("studiorender.dll");
        DumpModuleRegister("vgui2.dll");
        DumpModuleRegister("vguimatsurface.dll");
        DumpModuleRegister("vstdlib.dll");
        DumpModuleRegister("inputsystem.dll");
        DumpModuleRegister("materialsystem.dll");
#endif

        // get IDirect3DDevice9
        if (const auto d3d9Sig = GetPattern("shaderapidx9.dll")("D3D9"); d3d9Sig)
            SetInterface(**(IDirect3DDevice9***)d3d9Sig);

        // get pointer to CGameRules
        if (const auto gameRulesSig = GetPattern("client.dll")("GameRules"); gameRulesSig)
            SetInterface(*(CGameRules ***)gameRulesSig);

        // get pointer to CPlayerResource
        if (const auto playerResourceSig = GetPattern("client.dll")("PlayerResource");  playerResourceSig)
            SetInterface(*(CPlayerResource***)playerResourceSig);

        // get IMoveHelper
        if (const auto moveHelperSig = GetPattern("client.dll")("MoveHelper"); moveHelperSig)
            SetInterface(**(IMoveHelper***)moveHelperSig);

        // get CGlowManager
        if (const auto glowManagerSig = GetPattern("client.dll")("GlowManager"); glowManagerSig)
            SetInterface(*(CGlowManager**)glowManagerSig);

        if (const auto viewRenderSig = GetPattern("client.dll")("ViewRenderBeams"); viewRenderSig)
            SetInterface(*(IViewRenderBeams**)viewRenderSig);

        if (const auto clientStateSig = GetPattern("engine.dll")("ClientState"); clientStateSig)
            SetInterface(**(CClientState***)clientStateSig);

        if (const auto gameEventManagerSig = GetPattern("engine.dll")("GameEventManager"); gameEventManagerSig)
            SetInterface(*(IGameEventManager2**)gameEventManagerSig);

        const auto fnKeyValuesSystem = (Func<IKeyValuesSystem *()>) GetProcAddress(SystemUtility::SafeGetModuleHandle(text("vstdlib.dll")), text("KeyValuesSystem"));
        if (fnKeyValuesSystem) SetInterface(fnKeyValuesSystem());

        for (auto &it : interfaceBindMap) {
            const char *dllModule = it.first;
            const auto &bindList = it.second;

            for (auto &bind : bindList) {
                const char *ifaceName = bind.first;
                const constexpr_hash_t &typeHash = bind.second;

                // since we know the type is presumably correct in compile time
                // we could just put it directly to interface registry
                SetInterfaceImpl(typeHash, RetrieveInterface(dllModule, ifaceName));
                free((void *)ifaceName);
            }
            free((void *)dllModule);
        }

        SecureZeroMemory(&interfaceBindMap, sizeof interfaceBindMap); // BURN THEM ALL

        // Credits to hexagone
        // https://www.unknowncheats.me/forum/1471544-post1.html?s=8eccbc977ca19bcdfc6c9a5bd8bd50f2
        // wait until IClientModeShared is initialized (in game menu)
        for (; Get<IClientModeShared>() == nullptr; Sleep(1)) {
            // 10th entry is HudProcessInput
            // https://github.com/ValveSoftware/source-sdk-2013/blob/master/mp/src/game/client/cdll_client_int.cpp#L1254
            // first mov ecx, 0xXXXXXXXX is offset to ref to ptr to IClientModeShared
            // double reference

            if (const auto vm = (PBYTE)Get<IBaseClientDLL>()->GetVFunc(10); vm != nullptr) {
                const auto pat = SystemUtility::FindPattern(vm, 0x60, text("8B 0D")) + 2;
                SetInterface(**(IClientModeShared***)pat);
            }
        }

        for (; Get<CGlobalVarsBase>() == nullptr; Sleep(1)) {
            // 11th entry is HudUpdate
            // https://github.com/ValveSoftware/source-sdk-2013/blob/master/mp/src/game/client/cdll_client_int.cpp#L1261
            if (const auto vm = (PBYTE)Get<IBaseClientDLL>()->GetVFunc(11); vm != nullptr) {
                const auto pat = SystemUtility::FindPattern(vm, 0x60, text("A1")) + 1;
                SetInterface(**(CGlobalVarsBase***)pat);
            }
        }
    }

    void *InterfaceManager::RetrieveInterface(const char *dllModule, const char *name) {
        std::string resolvedName = name;

        if (!isdigit(name[strlen(name) - 1])) resolvedName += '0'; // name collison you know it
        if (strlen(dllModule) < 1) return nullptr;

        auto sig = SystemUtility::FindModulePattern(dllModule, text("8B 35 ? ? ? ? 57 85 F6 74 38"));
        if (sig == nullptr) return nullptr;

        sig += 2;

        const auto regs = **(InterfaceReg***)sig;

        if (regs == nullptr) return nullptr;

        for (auto &cur : regs->Traverse()) {
            if (strncmp(cur->GetName(), resolvedName.c_str(), resolvedName.length()) == 0) { // compare registry name against the string of required name
                                                                                             // we cannot just hash it because the version number is ignored
                return cur->GetPointer(); // call createFn and get the pointer
            }
        }

        return nullptr;
    }

}
