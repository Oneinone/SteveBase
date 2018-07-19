#pragma once

#include <misc/FunctionalProgramming.hpp>
#include <misc/TemplateMetaprogramming.hpp>

#include <manager/NetVarManager.hpp>

#include <source_engine/def/_EngineTypes.hpp>
#include <source_engine/def/weapon_definitions.hpp>
#include <source_engine/struct/CCSWeaponData.hpp>
#include <source_engine/virtual/CBaseEntity.hpp>

#include <vendor/hash/hash.h>

namespace SteveBase::SourceEngine::Virtual {
    using namespace Define;
    using namespace Structure;
    using namespace Misc;

    class CCSPlayer;
    class CEconItem;

    /**
     * \class CBaseCombatWeapon
     * \brief CBaseCombatWeapon is a base class for all game weapons
     */
    class CBaseCombatWeapon extends CBaseEntity {
    public:
        /**
         * \fn float CBaseCombatWeapon::GetSpread()
         * Retrieves this weapon's spread dynamically using 440th virtual function
         * 
         * \sideeffect None.
        */
        DefineVFunc(GetSpread, () -> float)(439)();

        /**
         * \fn CCSWeaponData *CBaseCombatWeapon::GetWeaponData()
         * Retrieves this weapon's weapon data using 447th virtual function
         * 
         * \sideeffect None.
        */
        DefineVFunc(GetWeaponData, ()->CCSWeaponData *)(446)();

        /**
         * \fn float CBaseCombatWeapon::GetInaccuracy()
         * Retrieves this weapon's accuracy deficit using 470th virtual function
         * 
         * \sideeffect None.
        */
        DefineVFunc(GetInaccuracy, () -> float)(469)();

        /**
         * \fn void CBaseCombatWeapon::UpdateAccuracyPenalty()
         * Forcefully update this weapon's accuracy and recoil in the game 
         * world using 471th virtual function
         * 
         * \sideeffect 
         * The internal accuracy penalty will be affected.
         * Potentially the client game state will also be affected
         * so as to render visual changes
        */
        DefineVFunc(UpdateAccuracyPenalty, () -> void)(470)();

        /**
         * \fn EHANDLE CBaseCombatWeapon::GetOwnerHandle()
         * Retrieves this weapon's owner handle using 
         * networked variale pair: (DT_BaseCombatWeapon, m_hOwner)
         * 
         * \notice 
         * This is the entity dictionary version of weapon owner
         * Which is not yet part of client game entity system
         *
         * \sideeffect From observed results, none yet. 
        */
        NetVarAccessor(GetOwnerHandle, ()->EHANDLE)(DT_BaseCombatWeapon, m_hOwner);

        /**
         * \fn float CBaseCombatWeapon::GetNextPrimaryAttack()
         * Retrieves this weapon's next available primary attack tick using
         * networked variale pair: (DT_LocalActiveWeaponData, m_flNextPrimaryAttack)
         *
         * \notice 
         * This seems to return \b absolute seconds passed since the start of
         * game server.
         * 
         * \related .\source_engine\virtual\CBaseWeapon.cpp: CBaseCombatWeapon::CanAttack
         *
         * \sideeffect None.
        */
        NetVarAccessor(GetNextPrimaryAttack, () -> float)(DT_LocalActiveWeaponData, m_flNextPrimaryAttack);

        CEconItem *GetItem() {
            auto var =
                NetVar(DT_BaseAttributableItem, m_AttributeManager) +
                NetVar(DT_AttributeContainer, m_Item);

            return Pointer<CEconItem>(var);
        }

        Weapons GetItemDefinition() {
            auto var =
                NetVar(DT_BaseAttributableItem, m_AttributeManager) +
                NetVar(DT_AttributeContainer, m_Item) +
                NetVar(DT_ScriptCreatedItem, m_iItemDefinitionIndex);

            return Data<Weapons>(var);
        }

    public:
        bool IsPistol() {
            return is_one_of(GetItemDefinition(), {
                Weapons::CZ75Auto, Weapons::DesertEagle, Weapons::DualElites, Weapons::FiveSeven, 
                Weapons::Glock18, Weapons::P2000, Weapons::P250, Weapons::R8Revolver, 
                Weapons::Tec9, Weapons::USP_S
            });
        }

        bool IsRifle() {
            return is_one_of(GetItemDefinition(), {
                Weapons::AK47, Weapons::AUG, Weapons::FAMAS, Weapons::GailiAR, 
                Weapons::M4A1, Weapons::M4A1_S, Weapons::SG553
            });
        }

        bool IsSubmachineGun() {
            return is_one_of(GetItemDefinition(), {
                Weapons::MP7, Weapons::MP9, Weapons::PPBizon, Weapons::MAC10, Weapons::P90, Weapons::UMP45,
            });
        }

        bool IsShotgun() {
            return is_one_of(GetItemDefinition(), {
                Weapons::MAG7, Weapons::Nova, Weapons::SawedOff, Weapons::XM1014,
            });
        }

        bool IsGrenade() {
            return is_one_of(GetItemDefinition(), {
                Weapons::DecoyGrenade, Weapons::FlashbangGrenade, Weapons::HighExplosiveGrenade, 
                Weapons::IncendiaryGrenade, Weapons::Molotov, Weapons::SmokeGrenade,
            });
        }

        bool IsMachineGun() {
            return is_one_of(GetItemDefinition(), {
                Weapons::M249,
                Weapons::Negev,
            });
        }

        bool IsSingleShotSniperRifle() {
            return is_one_of(GetItemDefinition(), {
                Weapons::AWP,
                Weapons::SSG08,
            });
        }

        bool IsAutoShotSniperRifle() {
            return is_one_of(GetItemDefinition(), {
                Weapons::G3SG1,
                Weapons::SCAR20,
            });
        }

        bool IsSniperRifle() {
            return IsSingleShotSniperRifle() || IsAutoShotSniperRifle();
        }

        bool IsMelee() {
            return is_one_of(GetItemDefinition(), {
                Weapons::Knife, Weapons::BayonetKnife, Weapons::BowieKnife, Weapons::ButterflyKnife,
                Weapons::FalchionKnife, Weapons::FlipKnife, Weapons::GutKnife, Weapons::HuntsmanKnife,
                Weapons::KarambitKnife, Weapons::M9BayonetKnife,	Weapons::ShadowDaggers, Weapons::KnifeT,
                Weapons::ZeusX27,
            });
        }

        bool IsC4() {
            return GetItemDefinition() == Weapons::C4;
        }

        CCSPlayer *GetOwner();
        bool CanAttack();
    };
}
