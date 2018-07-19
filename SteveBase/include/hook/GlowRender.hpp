#pragma once

#include <maths/Vector3.hpp>
#include <source_engine/virtual/CBaseEntity.hpp>
#include <source_engine/virtual/CCSPlayer.hpp>

namespace SteveBase::Hook {
    using namespace SourceEngine::Virtual;

    class GlowRender {
        const Vector3 m_highHealthColor = { 0.33f, 0.75f, 0.23f };
        const Vector3 m_mediumHealthColor = { 0.75f, 0.75f, 0.23f };
        const Vector3 m_lowHealthColor = { 0.75f, 0.23f, 0.23f };
        void ApplyGlowToPlayer(CCSPlayer *player);
        void ApplyGlowToGrenades(CBaseEntity *entity);
        void ApplyGlowToPlantedC4(CBaseEntity *entity);

    public:
        void BeginFrame();
    };
}
