#include <GlobalDefines.hpp>
#include <source_engine/virtual/CBaseCombatWeapon.hpp>

#include <Interface.hpp>

#include <source_engine/virtual/CCSPlayer.hpp>
#include <source_engine/virtual/IClientEntityList.hpp>

namespace SteveBase::SourceEngine::Virtual {
	CCSPlayer *CBaseCombatWeapon::GetOwner() {
		return (CCSPlayer *)Get<IClientEntityList>()->GetClientEntityFromHandle(GetOwnerHandle());
	}

	bool CBaseCombatWeapon::CanAttack() {
		return GetNextPrimaryAttack() < GetOwner()->GetServerTime();
	}
}
