#include <GlobalDefines.hpp>
#include <source_engine/virtual/CCSPlayer.hpp>

#include <Interface.hpp>
#include <manager/PatternManager.hpp>
#include <source_engine/index.hpp>

#include <vendor/hash/hash.h>
#include <vendor/XorStr/XorStr.h>

namespace SteveBase::SourceEngine::Virtual {
    using namespace Structure;

    int *CCSPlayer::GetPointerLastOcclusionCheck() {
        static int m_offset = *(int*)GetPattern("client.dll")("LastOcclusionCheckTick");

        return Pointer<int>(m_offset);
    }

    int *CCSPlayer::GetPointerToOcclusionFlags() {
        static int m_offset = *(int*)GetPattern("client.dll")("OcclusionCheckFlags");

        return Pointer<int>(m_offset);
    }

    CBaseEntity *CCSPlayer::GetObserverTarget() {
        return Get<IClientEntityList>()->GetClientEntityFromHandle(this->GetObserverTargetHandle());
    }

    bool CCSPlayer::IsTeamMateTo(CCSPlayer *other) {
        static auto teammate_is_enemy = Get<ICVar>()->FindVar(text("mp_teammates_are_enemies"));
        return teammate_is_enemy->m_strString[0] == '0' && this->GetTeam() == other->GetTeam();
    }

    float CCSPlayer::GetServerTime() {
        return GetTickBase() * Get<CGlobalVarsBase>()->GetIntervalPerTick();
    }

    CBaseCombatWeapon *CCSPlayer::GetActiveWeapon() {
        return (CBaseCombatWeapon *)Get<IClientEntityList>()->GetClientEntityFromHandle(this->GetActiveWeaponHandle());
    }
}
