#pragma once

#include <source_engine/virtual/CCSPlayer.hpp>
#include <source_engine/struct/CUserCmd.hpp>

namespace SteveBase::Hook {
    using namespace SourceEngine::Structure;
    using namespace SourceEngine::Virtual;

    class BunnyHop {
        bool m_lastJumped = false;
        bool m_shouldFake = false;
    public:
        void CreateMove(CUserCmd *cmd, CCSPlayer *localPlayer);
    };
}