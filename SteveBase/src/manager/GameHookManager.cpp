#include <GlobalDefines.hpp>
#include <manager/GameHookManager.hpp>

#include <Interface.hpp>

#include <assets/Fonts.hpp>
#include <hook/index.hpp>
#include <manager/DrawManager.hpp>
#include <manager/StateManager.hpp>
#include <source_engine/index.hpp>

#include <vendor/imgui/imgui.h>
#include <vendor/imgui/dx9/imgui_impl_dx9.h>
#include <vendor/vmthook/VMTHooks.h>
#include <vendor/hash/hash.h>
#include <vendor/XorStr/XorStr.h>

#include <complex.h>
#include <windows.h>

namespace SteveBase::Manager {
    using namespace Assets;
    using namespace SourceEngine::Define;
    using namespace SourceEngine::Structure;
    using namespace SourceEngine::Virtual;
    using namespace Utility;

    using Manager::GameHookManager;

    SortedDictionary<constexpr_hash_t, toolkit::VMTBaseManager> m_baseHookMap;
    HWND m_gameWindow = nullptr;
    WNDPROC m_oldWindowProc = nullptr;

    HWND GameHookManager::GetGameWindowHandle() {
        return m_gameWindow;
    }

    void GameHookManager::SetGameWindowHandle(HWND gameWindow) {
        m_gameWindow = gameWindow;
    }

    WNDPROC GameHookManager::GetOldWindowProcedure() {
        return m_oldWindowProc;
    }

    void GameHookManager::SetOldWindowProcedure(WNDPROC oldWindowProc) {
        m_oldWindowProc = oldWindowProc;
    }

    LRESULT GameHookManager::OnWindowProcedure(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
        static auto mouseEnable = Get<ICVar>()->FindVar(text("cl_mouseenable"));

        extern LRESULT ImGui_ImplDX9_WndProcHandler(HWND, UINT, WPARAM, LPARAM); // import the function from ImGui for window handler
        if (GetAsyncKeyState(VK_INSERT) & 0x0001) { // if insert is pressed
            StateManager::m_isMenuActivated = !StateManager::m_isMenuActivated; // flip the menu state
            if (mouseEnable) {
                mouseEnable->SetValue(std::to_string((int)!StateManager::IsMenuActivated()).data()); // disable mouse if menu is open or the game will move along with the movement of the mouse
            }

            if (!StateManager::IsMenuActivated()) { // if menu is closed
                VariableManager::SaveConfig();
            }
        }

        if (DrawManager::IsInitialized()) {
            if (StateManager::IsMenuActivated()) { // if menu is opened
                if (ImGui_ImplDX9_WndProcHandler(hWnd, uMsg, wParam, lParam)) { // if cursor movement was handled
                    return true; // Input was consumed by ImGui, disable default procedure
                }
            }
        }

        // Input was not consumed by the ImGUI, call original window procedure to pass the input to the game
        return CallWindowProc(GetOldWindowProcedure(), hWnd, uMsg, wParam, lParam);
    }

    FuncStdCall<LRESULT(const RECT *, const RECT *, HWND , const RGNDATA *)> origOverlayPresent;
    LRESULT GameHookManager::OnOverlayPresent(const RECT *pSourceRect, const RECT *pDestRect, HWND hDestWindowOverride, const RGNDATA *pDirtyRegion) {
        return origOverlayPresent(pSourceRect, pDestRect, hDestWindowOverride, pDirtyRegion);
    }

    void GameHookManager::StartHook() {
        if (m_gameWindow) { // if the game window presents
            const auto oldWindowProc = (WNDPROC)SetWindowLongPtr(m_gameWindow, GWLP_WNDPROC, (LONG)OnWindowProcedure);
            SetOldWindowProcedure(oldWindowProc);
            LoggerDebug("Game window hook set");
        }

        /*
        if (const auto presentFnRef = GetPattern("gameoverlayrenderer.dll")("OverlayPointer"); presentFnRef) {
            LoggerDebug("gameoverlayrenderer Present: 0x{0:X}, 0x{1:X}", (uintptr_t)presentFnRef, *(uintptr_t*)(presentFnRef));
            origOverlayPresent = (decltype(origOverlayPresent)) **(uintptr_t**)(presentFnRef);

            DWORD oldProtect;
            VirtualProtect(presentFnRef, 16, PAGE_READWRITE, &oldProtect);
            *(uintptr_t*)(presentFnRef) = (uintptr_t) &GameHookManager::OnOverlayPresent;
            VirtualProtect(presentFnRef, 16, oldProtect, nullptr);
        }
        */

        for (auto &it0 : interfaceHookMap) {
            auto typeHash = it0.first;
            auto &hookFnMap = it0.second;

            auto &hook = GetHookForInterfaceImpl(typeHash).Init(GetInterfaceImpl(typeHash));

            for (auto &it1 : hookFnMap) {
                auto fn = it1.first;
                auto idx = it1.second;
                std::tie(fn, idx) = it1;

                hook.HookMethod(fn, idx);
            }

            hook.Rehook();
#if DEBUG
            LoggerDebug("{0} hook set", GetNameForHash(typeHash));
#endif
        }

    }

    void GameHookManager::StopHook() {
        for (auto &hook : m_baseHookMap) {
            if (hook.second.IsInitialized()) {
                hook.second.Unhook();
            }
        }
        ImGui_ImplDX9_Shutdown();

        Sleep(1000);

        /*
        if (const auto presentFnRef = GetPattern("gameoverlayrenderer.dll")("OverlayPointer"); presentFnRef) {
            *(uintptr_t*)(presentFnRef) = (uintptr_t)origOverlayPresent;
        }
        */

        if (m_gameWindow && m_oldWindowProc) {
            SetWindowLongPtr(m_gameWindow, GWLP_WNDPROC, (LONG)m_oldWindowProc);
        }
    }

    toolkit::VMTBaseManager &GameHookManager::GetHookForInterfaceImpl(const interface_hash_t hash) {
        return m_baseHookMap[hash];
    }
}
