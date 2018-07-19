#pragma once

#include <source_engine/virtual/CCSPlayer.hpp>

namespace SteveBase::Hook {
    using namespace SourceEngine::Virtual;

    class RadarSpotted {
    public:
        void CreateMove(CCSPlayer *localPlayer);
    };
}