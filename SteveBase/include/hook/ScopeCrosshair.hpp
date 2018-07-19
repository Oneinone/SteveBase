#pragma once

#include <utility/Tuple.hpp>

namespace SteveBase::SourceEngine::Virtual {
    class CBaseCombatWeapon;
    class CCSPlayer;
}

namespace SteveBase::Hook {
    using namespace Utility;
    using namespace SourceEngine::Virtual;

    class ScopeCrosshair {
    public:
        void CreateMove(Tuple<CCSPlayer *, CBaseCombatWeapon *> cache);
    };
}
