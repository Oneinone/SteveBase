#include <GlobalDefines.hpp>
#include <hook/BunnyHop.hpp>

#include <manager/VariableManager.hpp>
#include <source_engine/index.hpp>

#include <vendor/hash/hash.h>

namespace SteveBase::Hook {
    using namespace SourceEngine::Define;
    using namespace SourceEngine::Structure;
    using namespace SourceEngine::Virtual;

    void BunnyHop::CreateMove(CUserCmd *cmd, CCSPlayer *localPlayer) {
        if (!DynamicVariable(misc.bunnyhop).Get<bool>()) {
            return;
        }

        if (!localPlayer) {
            return;
        }

        if (localPlayer->GetLifeState() != LifeState::Alive) {
            return;
        }

        auto &state = cmd->GetAttackButtonStateRef();

        if (state & AttackButtonState::InDuck) {
            return;
        }

        if (!m_lastJumped && m_shouldFake) {
            m_shouldFake = false;
            state |= AttackButtonState::InJump;
        }
        else if (state & AttackButtonState::InJump) {
            if (localPlayer->GetFlags() & FL_ONGROUND) {
                m_lastJumped = true;
                m_shouldFake = true;
            }
            else {
                state &= ~AttackButtonState::InJump;
                m_lastJumped = false;
            }
        }
        else {
            m_lastJumped = false;
            m_shouldFake = false;
        }
    }
}
