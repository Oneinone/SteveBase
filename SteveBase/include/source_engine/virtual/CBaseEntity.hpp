#pragma once

#include <misc/Macro.hpp>
#include <misc/ProxiedClass.hpp>
#include <maths/EulerAngle.hpp>
#include <maths/Vector3.hpp>
#include <manager/NetVarManager.hpp>

namespace SteveBase::SourceEngine::Structure {
    struct CUserCmd;
    struct GlowObjectDefinition;
}

namespace SteveBase::SourceEngine::Virtual {
    using namespace Manager;
    using namespace Maths;

    using namespace Structure;

    class CBaseCombatWeapon;
    interface IClientNetworkable;
    interface IClientRenderable;

    /**
     * \class CBaseEntity
     * \brief The CBaseEntity is the origin of all game entities
     */
    class CBaseEntity extends Misc::ProxiedClass {
        NetVarAccessor(Origin, ()->Vector3)(DT_BaseEntity, m_vecOrigin);
        NetVarAccessor(Rotation, ()->EulerAngle)(DT_BaseEntity, m_angRotation);
    public:
        NetVarAccessor(IsSpotted, () -> bool)(DT_BaseEntity, m_bSpotted);
        NetVarAccessor(GetTeam, () -> int)(DT_BaseEntity, m_iTeamNum);
    private:
        PODAccessor(EyeAngle, ()->EulerAngle)(0xAA08);
    public:
        PODAccessor(IsDormant, () -> bool)(0x00E9);
        PODAccessor(GetGlowIndex, () -> int)(0xA310);

        PODAccessor(GetCurrentCommand, ()->CUserCmd *)(0x3334);

    public:
        EulerAngle GetEyeAngle() {
            return EyeAngle();
        }

        void SetEyeAngle(EulerAngle angle) {
            EyeAngle() = angle;
        }

        IClientNetworkable *GetNetworkable() {
            return Pointer<IClientNetworkable>(0x8);
        }

        IClientRenderable *GetRenderable() {
            return Pointer<IClientRenderable>(0x4);
        }

        Vector3 GetOrigin() {
            return Origin();
        }

        void SetOrigin(Vector3 origin) {
            Origin() = origin;
        }

        EulerAngle GetRotation() {
            return Rotation();
        }

        void SetRotation(EulerAngle angle) {
            Rotation() = angle;
        }

        bool IsPlayer();
        bool IsGrenade();
        bool IsPlantedC4();
        GlowObjectDefinition *GetGlowObject(bool useInternalIndex = true);
    };
}