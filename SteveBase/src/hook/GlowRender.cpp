#include <GlobalDefines.hpp>
#include <hook/GlowRender.hpp>

#include <Interface.hpp>
#include <manager/VariableManager.hpp>

#include <source_engine/index.hpp>

#include <vendor/hash/hash.h>

namespace SteveBase::Hook {
    using namespace SourceEngine::Define;
    using namespace SourceEngine::Structure;

    void GlowRender::ApplyGlowToPlayer(CCSPlayer *player) {
        auto glowObject = player->GetGlowObject();

        if (!glowObject) {
            return;
        }

        auto healthPercentage = (float) player->GetHealth() / (float) player->GetMaxHealth();

        glowObject->m_vGlowColor = healthPercentage >= 0.6f
                                       ? m_highHealthColor
                                       : (healthPercentage <= 0.3f ? m_lowHealthColor : m_mediumHealthColor);
        glowObject->m_flGlowAlpha = 1.0f;

        glowObject->m_bRenderWhenOccluded = true;
    }

    void GlowRender::ApplyGlowToGrenades(CBaseEntity *entity) {
        auto glowObject = entity->GetGlowObject(false);

        if (!glowObject) {
            return;
        }

        glowObject->m_vGlowColor = Vector3(1.0f, 1.0f, 1.0f);
        glowObject->m_flGlowAlpha = 1.0f;
        glowObject->m_bRenderWhenOccluded = true;
    }

    void GlowRender::ApplyGlowToPlantedC4(CBaseEntity *entity) {
        auto glowObject = entity->GetGlowObject(false);

        if (!glowObject) {
            return;
        }

        glowObject->m_vGlowColor = Vector3(1.0f, 1.0f, 1.0f);
        glowObject->m_flGlowAlpha = 1.0f;
        glowObject->m_bRenderWhenOccluded = true;
    }

    void GlowRender::BeginFrame() {
        auto drawGrenade = DynamicVariable(esp.world.grenades).Get<bool>();
        auto drawC4 = DynamicVariable(esp.world.plantedc4).Get<bool>();

        if (drawGrenade || drawC4) {
            for (auto entity : GetInterface<IClientEntityList>()->GetAllEntities()) {
                if (entity->IsGrenade() && drawGrenade) {
                    ApplyGlowToGrenades(entity);
                }

                if (entity->IsPlantedC4() && drawC4) {
                    ApplyGlowToPlantedC4(entity);
                }
            }
        }
        if (DynamicVariable(esp.player.drawglow).Get<bool>()) {
            const auto localPlayer = GetInterface<IClientEntityList>()->GetLocalPlayer();

            if (!localPlayer) {
                return;
            }

            for (auto player : GetInterface<IClientEntityList>()->GetAllPlayers()) {
                if (player->IsEnemyTo(localPlayer)) {
                    if (player->GetLifeState() != LifeState::Alive) {
                        continue;
                    }

                    ApplyGlowToPlayer(player);
                }
            }
        }
    }
}
