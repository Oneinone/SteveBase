#pragma once

#include <utility/Tuple.hpp>

#include <source_engine/struct/CUserCmd.hpp>
#include <source_engine/virtual/CBaseCombatWeapon.hpp>
#include <source_engine/virtual/CCSPlayer.hpp>

namespace SteveBase::Hook {
    using namespace Utility;
    using namespace SourceEngine::Structure;
    using namespace SourceEngine::Virtual;

    class AutoPistol {
    public:
        void CreateMove(CUserCmd *cmd, Tuple<CCSPlayer *, CBaseCombatWeapon *> cache);
    };
}
