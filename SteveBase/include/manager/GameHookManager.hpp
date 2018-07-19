#pragma once

#include <windows.h>
#include <vector>

#include <Interface.hpp>
#include <misc/TypeAliases.hpp>

#include <vendor/vmthook/VMTHooks.h>

namespace SteveBase::Manager {
    using namespace Misc;

    class GameHookManager {
        static LRESULT WINAPI OnWindowProcedure(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
        static LRESULT WINAPI OnOverlayPresent(const RECT* pSourceRect, const RECT* pDestRect, HWND hDestWindowOverride, const RGNDATA* pDirtyRegion);
    public:
        static void StartHook();
        static void StopHook();

        static HWND GetGameWindowHandle();
        static void SetGameWindowHandle(HWND gameWindow);

        static void SetOldWindowProcedure(WNDPROC oldWindowHook);
        static WNDPROC GetOldWindowProcedure();

        static toolkit::VMTBaseManager &GetHookForInterfaceImpl(interface_hash_t hash);

        template<class T>
        constexpr static toolkit::VMTBaseManager &GetHookForInterface() {
            return GetHookForInterfaceImpl(GetHashForType<T>());
        }

        using InterfaceHookPair = Pair<void *, interface_hash_t>;
        using InterfaceHookList = List<InterfaceHookPair>;
        using HookInterfaceEntry = Pair<interface_hash_t, InterfaceHookList>;

        using InterfaceHookMap = std::vector<HookInterfaceEntry>;

        static const InterfaceHookMap interfaceHookMap;

    };

    template <void * Fn, interface_hash_t idx>
    constexpr FORCEINLINE GameHookManager::InterfaceHookPair Hook() { return { Fn, idx }; }

    template <interface_hash_t idx, class Fn>
    constexpr FORCEINLINE GameHookManager::InterfaceHookPair Hook(const Fn &&fn) { return { fn, idx }; }

    template <interface_hash_t idx, class T, class Fn>
    constexpr FORCEINLINE GameHookManager::InterfaceHookPair Hook(T, const Fn &&fn) { return { fn, idx }; }

    template<class T>
    struct HookInterface : GameHookManager::HookInterfaceEntry {
        constexpr FORCEINLINE HookInterface(std::initializer_list<GameHookManager::InterfaceHookPair> &&hooks) {
            first = GetHashForType<T>();
            second = hooks;
        }
    };
}
