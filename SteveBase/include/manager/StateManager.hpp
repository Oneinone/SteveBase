#pragma once

namespace SteveBase::Manager {
    class GameHookManager;
    class DrawManager;

    class StateManager {
        friend class GameHookManager;
        friend class DrawManager;
#if SIMULATOR
    public:
#endif
        static bool m_isMenuActivated;

    public:
        static bool IsMenuActivated();
    };
}