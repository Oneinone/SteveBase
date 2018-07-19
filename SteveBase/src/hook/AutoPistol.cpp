#include <GlobalDefines.hpp>
#include <hook/AutoPistol.hpp>

#include <manager/VariableManager.hpp>
#include <misc/TemplateMetaprogramming.hpp>

namespace SteveBase::Hook {
    using namespace Manager;
    using namespace Misc;
    using namespace Utility;
    using namespace SourceEngine::Define;
    using namespace SourceEngine::Structure;
    using namespace SourceEngine::Virtual;

    void AutoPistol::CreateMove(CUserCmd *cmd, Tuple<CCSPlayer *, CBaseCombatWeapon *> cache) {
        if (!DynamicVariable(misc.autopistol).Get<bool>())
            return;

        CCSPlayer *localPlayer;
        CBaseCombatWeapon *localActiveWeapon;
        cache.Deconstruct(localPlayer, localActiveWeapon);

        if (!localPlayer || !localActiveWeapon)
            return;
        if (localPlayer->GetLifeState() != LifeState::Alive)
            return;
        if (!localActiveWeapon->IsPistol())
            return;

        auto &state = cmd->GetAttackButtonStateRef();

        if (is_one_of(localActiveWeapon->GetItemDefinition())(Weapons::Tec9, Weapons::FiveSeven, Weapons::DualElites, Weapons::Glock18)) {
            if (state & AttackButtonState::InAttack) {
                if (localActiveWeapon->CanAttack()) {
                    state |= AttackButtonState::InAttack;
                } else {
                    state &= ~AttackButtonState::InAttack;
                }
            }
        }
    }
}
