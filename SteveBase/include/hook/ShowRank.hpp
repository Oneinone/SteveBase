#pragma once

#include <manager/PatternManager.hpp>
#include <manager/VariableManager.hpp>

#include <misc/TypeAliases.hpp>

namespace SteveBase::SourceEngine::Structure {
    struct CUserCmd;
}

namespace SteveBase::Hook {
    using namespace Manager;
    using namespace Misc;
    using namespace SourceEngine::Structure;

    class ShowRank {
        Func<bool(int*)> revealAll = static_cast<Func<bool(int *)>>(GetPattern("client.dll")("RevealAll"));
        int input[3] = { 0 };
        const bool &var = DynamicVariable(misc.showranks).Get<bool>();
    public:
        void CreateMove(CUserCmd *cmd);
    };
}