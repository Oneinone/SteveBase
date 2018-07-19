#include <GlobalDefines.hpp>
#include <hook/ShowRank.hpp>
#include <source_engine/index.hpp>

namespace SteveBase::Hook {
    void ShowRank::CreateMove(CUserCmd *cmd) {
        if (!var) {
            return;
        }

        auto &state = cmd->GetAttackButtonStateRef();

        if (state & SourceEngine::Define::AttackButtonState::InScoreboard) {
            revealAll(input);
        }
    }
}
