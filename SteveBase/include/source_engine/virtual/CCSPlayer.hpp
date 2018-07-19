#pragma once

#include <maths/EulerAngle.hpp>
#include <maths/Vector3.hpp>
#include <misc/ProxiedClass.hpp>

#include <source_engine/def/_EngineTypes.hpp>
#include <source_engine/def/LifeState.hpp>
#include <source_engine/virtual/CBaseEntity.hpp>

namespace SteveBase::SourceEngine::Virtual {
    using namespace Define;

    // CCSPlayer class
    // aka gay bloated shit
    class CCSPlayer extends CBaseEntity {
        PODAccessor(PlayerState, () -> void *)(0x31C0);
        PODAccessor(UserCommand, () -> CUserCmd *)(0x326C);

        EulerAngle &AimPunchAngle() {
            auto netvar = NetVar(DT_LocalPlayerExclusive, m_Local) + NetVar(DT_Local, m_aimPunchAngle);
            return Data<EulerAngle>(netvar);
        }
        
        EulerAngle &AimPunchAngleVelocity() {
            auto netvar = NetVar(DT_LocalPlayerExclusive, m_Local) + NetVar(DT_Local, m_aimPunchAngleVel);
            return Data<EulerAngle>(netvar);
        }
        
        EulerAngle &ViewPunchAngle() {
            auto netvar = NetVar(DT_LocalPlayerExclusive, m_Local) + NetVar(DT_Local, m_viewPunchAngle);
            return Data<EulerAngle>(netvar);
        }

    public:
        
        NetVarAccessor(CanMoveDuringFreezePeriod, () -> bool)(DT_CSPlayer, m_bCanMoveDuringFreezePeriod);
        NetVarAccessor(GetAccount, () -> int)(DT_CSPlayer, m_iAccount);
        NetVarAccessor(GetActiveWeaponHandle, ()->EHANDLE)(DT_BaseCombatCharacter, m_hActiveWeapon);
        NetVarAccessor(GetActiveWeaponHandles_Raw, ()->EHANDLE *)(DT_BaseCombatCharacter, m_hActiveWeapon);
        NetVarAccessor(GetAmmo, () -> int)(DT_BasePlayer, m_iAmmo);
        NetVarAccessor(GetArmorValue, () -> unsigned int)(DT_CSPlayer, m_ArmorValue);
        NetVarAccessor(GetDuckAmount, () -> float)(DT_CSPlayer, m_flDuckAmount);
        NetVarAccessor(GetDuckSpeed, () -> float)(DT_CSPlayer, m_flDuckSpeed);
        NetVarAccessor(GetFOV, () -> int)(DT_CSPlayer, m_iFOV);
        NetVarAccessor(GetFOVStart, () -> int)(DT_CSPlayer, m_iFOVStart);
        NetVarAccessor(GetFOVTime, () -> float)(DT_CSPlayer, m_flFOVTime);
        NetVarAccessor(GetFlags, () -> unsigned int)(DT_BasePlayer, m_fFlags);
        NetVarAccessor(GetHealth, () -> int)(DT_BasePlayer, m_iHealth);
        NetVarAccessor(GetLastPlaceName, () -> const char *)(DT_CSPlayer, m_szLastPlaceName);
        NetVarAccessor(GetLifeState, () -> LifeState)(DT_BasePlayer, m_lifeState);
        NetVarAccessor(GetLowerBodyYawTarget, () -> float)(DT_CSPlayer, m_flLowerBodyYawTarget);
        NetVarAccessor(GetMaxSpeed, () -> float)(DT_CSPlayer, m_flMaxspeed);
        NetVarAccessor(GetObserverMode, () -> int)(DT_CSPlayer, m_iObserverMode);
        NetVarAccessor(GetObserverTargetHandle, () -> EHANDLE)(DT_CSPlayer, m_hObserverTarget);
        NetVarAccessor(GetPlayerState, () -> int)(DT_CSPlayer, m_iPlayerState);
        NetVarAccessor(GetStamina, () -> float)(DT_CSLocalPlayerExclusive, m_flStamina);
        NetVarAccessor(GetTickBase, () -> unsigned int)(DT_LocalPlayerExclusive, m_nTickBase);
        NetVarAccessor(GetVelocity, () -> Vector3)(DT_LocalPlayerExclusive, m_vecVelocity[0]);
        NetVarAccessor(GetViewOffset, () -> Vector3)(DT_LocalPlayerExclusive, m_vecViewOffset[0]);
        NetVarAccessor(HasDefuser, () -> bool)(DT_CSPlayer, m_bHasDefuser);
        NetVarAccessor(HasHeavyArmor, () -> bool)(DT_CSPlayer, m_bHasHeavyArmor);
        NetVarAccessor(HasHelmet, () -> bool)(DT_CSPlayer, m_bHasHelmet);
        NetVarAccessor(HasMovedSinceSpawn, () -> bool)(DT_CSPlayer, m_bHasMovedSinceSpawn);
        NetVarAccessor(IsDefusing, () -> bool)(DT_CSPlayer, m_bIsDefusing);
        NetVarAccessor(IsGrabbingHostage, () -> bool)(DT_CSPlayer, m_bIsGrabbingHostage);
        NetVarAccessor(IsGunGameImmunity, () -> bool)(DT_CSPlayer, m_bGunGameImmunity);
        NetVarAccessor(IsScoped, () -> bool)(DT_CSPlayer, m_bIsScoped);
        NetVarAccessor(IsStrafing, () -> bool)(DT_CSPlayer, m_bStrafing);
        NetVarAccessor(IsWalking, () -> bool)(DT_CSPlayer, m_bIsWalking);

    public:
        float *GetFlashDurationPtr() {
            auto var = NetVar(DT_CSPlayer, m_flFlashDuration);
            return Pointer<float>(var);
        }

        float *GetFlashMaxAlphaPtr() {
            auto var = NetVar(DT_CSPlayer, m_flFlashMaxAlpha);
            return Pointer<float>(var);
        }

        EulerAngle GetEyeAngle() {
            auto var0 = NetVar(DT_CSPlayer, m_angEyeAngles[0]);
            auto var1 = NetVar(DT_CSPlayer, m_angEyeAngles[1]);
            // there's no m_angEyeAngles[2]

            return EulerAngle(Data<float>(var0), Data<float>(var1), 0);
        }

        void SetEyeAngle(EulerAngle angle) {
            auto var0 = NetVar(DT_CSPlayer, m_angEyeAngles[0]);
            auto var1 = NetVar(DT_CSPlayer, m_angEyeAngles[1]);
            // there's no m_angEyeAngles[2]

            Data<float>(var0) = angle.Alpha();
            Data<float>(var1) = angle.Beta();
        }

        EulerAngle GetAimPunchAngle() {
            return AimPunchAngle();
        }

        void SetAimPunchAngle(EulerAngle angle) {
            AimPunchAngle().Alpha() = angle.Alpha();
            AimPunchAngle().Beta() = angle.Beta();
            AimPunchAngle().Gamma() = angle.Gamma();
        }

        EulerAngle GetViewPunchAngle() {
            return ViewPunchAngle();
        }

        void SetViewPunchAngle(EulerAngle angle) {
            ViewPunchAngle().Alpha() = angle.Alpha();
            ViewPunchAngle().Beta() = angle.Beta();
            ViewPunchAngle().Gamma() = angle.Gamma();
        }

        EulerAngle GetAimPunchAngleVelocity() {
            return AimPunchAngleVelocity();
        }

        void SetAimPunchAngleVelocity(EulerAngle angle) {
            AimPunchAngleVelocity() = angle;
        }

        std::array<EHANDLE, 64> &GetActiveWeaponHandles() {
            return (std::array<EHANDLE, 64> &) GetActiveWeaponHandles_Raw();
        }

        int GetMaxHealth() {
            //int var = NetVar(DT_CSPlayer, m_iMaxHealth);
            //return Data<int>(this, var);
            return 100; // TODO
        }

        Vector3 GetEyePosition() {
            return GetOrigin() + GetViewOffset();
        }

        int GetMoney() {
            return GetAccount();
        }

        bool IsTeamMateTo(CCSPlayer *other);

        bool IsEnemyTo(CCSPlayer *other) {
            return !IsTeamMateTo(other);
        }

        int *GetPointerLastOcclusionCheck();
        int *GetPointerToOcclusionFlags();

        float GetServerTime();
        CBaseEntity *GetObserverTarget();
        CBaseCombatWeapon *GetActiveWeapon();
    };
}
