#include <GlobalDefines.hpp>
#include <source_engine/virtual/CBaseEntity.hpp>

#include <Interface.hpp>
#include <source_engine/index.hpp>

#include <vendor/XorStr/XorStr.h>

namespace SteveBase::SourceEngine::Virtual {
    using namespace Manager;

    bool CBaseEntity::IsPlayer() {
        return GetNetworkable()->GetClientClass()->GetName() == text("CCSPlayer");
    }

    bool CBaseEntity::IsGrenade() {
        auto name = GetNetworkable()->GetClientClass()->GetName();
        return name == text("CBaseCSGrenadeProjectile")
            || name == text("CDecoyProjectile")
            || name == text("CMolotovProjectile")
            || name == text("CSmokeGrenadeProjectile")
            || name == text("CFlashbang");
    }

    bool CBaseEntity::IsPlantedC4() {
        return GetNetworkable()->GetClientClass()->GetName() == text("CPlantedC4");
    }

    GlowObjectDefinition *CBaseEntity::GetGlowObject(bool useInternalIndex) {
        if (useInternalIndex) {
            auto index = this->GetGlowIndex();
            auto obj = Get<CGlowManager>()->GetGlowObjectDefinitionsAt(index);

            if (obj == nullptr) {
                goto default_procedure;
            }
            if (obj->m_hEntity != this) { // LUL
                return nullptr;
            }
            return obj;
        }
    default_procedure:
        return Get<CGlowManager>()->FindGlowObjectDefinitionsForEntity(this);
    }
}
