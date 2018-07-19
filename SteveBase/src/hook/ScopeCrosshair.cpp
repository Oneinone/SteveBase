#include <GlobalDefines.hpp>
#include <hook/ScopeCrosshair.hpp>

#include <Interface.hpp>
#include <source_engine/index.hpp>

#include <vendor/ggformat/ggformat.h>

namespace SteveBase::Hook {
    void ScopeCrosshair::CreateMove(Tuple<CCSPlayer *, CBaseCombatWeapon *> cache) {
        CCSPlayer *localPlayer;
        CBaseCombatWeapon *localWeapon;
        cache.Deconstruct(localPlayer, localWeapon);

        static IConVar *weapon_debug_spread_show = Get<ICVar>()->FindVar(text("weapon_debug_spread_show"));
        weapon_debug_spread_show->m_nFlags &= ~SourceEngine::Define::CVarFlags::Cheat;

        if (localPlayer != nullptr && localWeapon != nullptr) {
            if (auto owner = localWeapon->GetOwner(); owner != nullptr) {
                auto scoped = owner->IsScoped();
                auto isSniper = localWeapon->IsSniperRifle();
                auto fmt = ggformat_to_string(text("weapon_debug_spread_show {}"), isSniper && !scoped ? 3 : 0);
                Get<IEngineClient>()->ClientCmd_Unrestricted(fmt.c_str());
            }
        }
    }
}
