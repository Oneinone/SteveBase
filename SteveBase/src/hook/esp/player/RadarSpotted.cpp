#include <GlobalDefines.hpp>
#include <hook/RadarSpotted.hpp>

#include <Interface.hpp>
#include <manager/VariableManager.hpp>

#include <source_engine/index.hpp>

#include <vendor/hash/hash.h>

namespace SteveBase::Hook {
    void RadarSpotted::CreateMove(CCSPlayer *localPlayer) {
        static auto &var = DynamicVariable(esp.player.showradarspotted);

        if (!var.Get<bool>()) return;

        for (auto &player : Get<IClientEntityList>()->GetAllPlayers()) {
            if (player->IsEnemyTo(localPlayer)) {
                if (player->GetLifeState() == LifeState::Alive) {
                    player->IsSpotted() = true;
                }
            }
        }

    }
}
