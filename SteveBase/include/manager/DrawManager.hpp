#pragma once

#include <array>

namespace SteveBase::Manager {

    struct ScreenSize : std::array<int, 2> {
        using std::array<int, 2>::array;

        constexpr auto &Width() { return data()[0]; }
        constexpr auto &Height() { return data()[1]; }
    };

    class DrawManager {
        friend class GameHookManager;
        static void SetInitialized(bool init);
    public:
        static void Init();
        static void Render();

        static bool IsInitialized();

        static ScreenSize &GetScreenSize();
    };
}