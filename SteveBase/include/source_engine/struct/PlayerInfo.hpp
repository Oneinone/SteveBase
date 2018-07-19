#pragma once

#include <array>
#include <misc/Macro.hpp>

namespace SteveBase::SourceEngine::Structure {
    struct PlayerInfo {
        Pad(0x8);

        int xuidlow;
        int xuidhigh;

        char name[128];
        int userid;
        char guid[33];

        Pad(0x17B);

        std::array<char, 128> &GetName() {
            return reinterpret_cast<std::array<char, 128> &>(name);
        }
    };
}