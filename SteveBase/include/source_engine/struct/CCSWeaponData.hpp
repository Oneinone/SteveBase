#pragma once

#include <misc/Macro.hpp>

namespace SteveBase::SourceEngine::Structure {
    struct CCSWeaponData {
        virtual ~CCSWeaponData() {}; // 0x0000
        /*Parse(KeyValues *, char const*)
        RefreshDynamicParameters(void)
        GetPrimaryClipSize(C_EconItemView const*, int, float)const
        GetSecondaryClipSize(C_EconItemView const*, int, float)const
        GetDefaultPrimaryClipSize(C_EconItemView const*, int, float)const
        GetDefaultSecondaryClipSize(C_EconItemView const*, int, float)const
        GetPrimaryReserveAmmoMax(C_EconItemView const*, int, float)const
        GetSecondaryReserveAmmoMax(C_EconItemView const*, int, float)const*/

        char*		consoleName;			// 0x0004
        Pad(0xC);            // 0x0008
        int			iMaxClip1;				// 0x0014
        int			iMaxClip2;				// 0x0018
        int			iDefaultClip1;		// 0x001C
        int			iDefaultClip2;		// 0x0020
        Pad(0x8);            // 0x0028
        char*		szWorldModel;			// 0x002C
        char*		szViewModel;			// 0x0030
        char*		szDroppedModel;		// 0x0034
        Pad(0x4);            // 0x0038
        Pad(0x4);            // 0x003C
        Pad(0x38);           // 0x0040
        char*		szEmptySound;     // 0x0078
        Pad(0x4);            // 0x007C
        char*		szBulletType;			// 0x0080
        Pad(0x4);            // 0x0084
        char*		szHudName;				// 0x0088
        char*		szWeaponName;			// 0x008C
        Pad(0x38);           // 0x0090
        int 		WeaponType;				// 0x00C8
        int			iWeaponPrice;			// 0x00CC
        int			iKillAward;				// 0x00D0
        char*		szAnimationPrefix;// 0x00D4
        float		flCycleTime;			// 0x00D8
        float		flCycleTimeAlt;	  // 0x00DC
        float		flTimeToIdle;			// 0x00E0
        float		flIdleInterval;		// 0x00E4
        bool		bFullAuto;				// 0x00E8
        Pad(0x3);            // 0x00E9
        int			iDamage;				  // 0x00EC
        float		flArmorRatio;			// 0x00F0
        int			iBullets;				  // 0x00F4
        float		flPenetration;		// 0x00F8
        float		flFlinchVelocityModifierLarge;	// 0x00FC
        float		flFlinchVelocityModifierSmall;	// 0x0100
        float		flRange;				    // 0x0104
        float		flRangeModifier;		// 0x0108
        float		flThrowVelocity;		// 0x010C
        Pad(0xC);              // 0x0110
        bool		bHasSilencer;			  // 0x011C
        Pad(0x3);              // 0x011D
        char*		pSilencerModel;			// 0x0120
        int			iCrosshairMinDistance;	// 0x0124
        int			iCrosshairDeltaDistance;// 0x0128 - iTeam?
        float		flMaxPlayerSpeed;		    // 0x012C
        float		flMaxPlayerSpeedAlt;	  // 0x0130
        float		flSpread;				        // 0x0134
        float		flSpreadAlt;			      // 0x0138
        float		flInaccuracyCrouch;		  // 0x013C
        float		flInaccuracyCrouchAlt;	// 0x0140
        float		flInaccuracyStand;		  // 0x0144
        float		flInaccuracyStandAlt;	  // 0x0148
        float		flInaccuracyJumpInitial;// 0x014C
        float		flInaccuracyJump;		    // 0x0150
        float		flInaccuracyJumpAlt;	  // 0x0154
        float		flInaccuracyLand;		    // 0x0158
        float		flInaccuracyLandAlt;	  // 0x015C
        float		flInaccuracyLadder;		  // 0x0160
        float		flInaccuracyLadderAlt;	// 0x0164
        float		flInaccuracyFire;		    // 0x0168
        float		flInaccuracyFireAlt;	  // 0x016C
        float		flInaccuracyMove;		    // 0x0170
        float		flInaccuracyMoveAlt;	  // 0x0174
        float		flInaccuracyReload;		  // 0x0178
        int			iRecoilSeed;			      // 0x017C
        float		flRecoilAngle;			    // 0x0180
        float		flRecoilAngleAlt;		    // 0x0184
        float		flRecoilAngleVariance;	// 0x0188
        float		flRecoilAngleVarianceAlt;	// 0x018C
        float		flRecoilMagnitude;		    // 0x0190
        float		flRecoilMagnitudeAlt;	    // 0x0194
        float		flRecoilMagnitudeVariance;	  // 0x0198
        float		flRecoilMagnitudeVarianceAlt;	// 0x019C
        float		flRecoveryTimeCrouch;	        // 0x01A0
        float		flRecoveryTimeStand;	        // 0x01A4
        float		flRecoveryTimeCrouchFinal;	  // 0x01A8
        float		flRecoveryTimeStandFinal;	    // 0x01AC
        int			iRecoveryTransitionStartBullet; // 0x01B0 
        int			iRecoveryTransitionEndBullet;	  // 0x01B4
        bool		bUnzoomAfterShot;		  // 0x01B8
        bool		bHideViewModelZoomed;	// 0x01B9
        Pad(0x2);                // 0x01BA
        char		iZoomLevels[3];			  // 0x01BC
        int			iZoomFOV[2];			    // 0x01C0
        float		fZoomTime[3];			    // 0x01C4
        char*		szWeaponClass;			  // 0x01D4
        float		flAddonScale;			    // 0x01D8
        Pad(0x4);                // 0x01DC
        char*		szEjectBrassEffect;		// 0x01E0
        char*		szTracerEffect;			  // 0x01E4
        int			iTracerFrequency;		  // 0x01E8
        int			iTracerFrequencyAlt;	// 0x01EC
        char*		szMuzzleFlashEffect_1stPerson; // 0x01F0

        Pad(0x4);                          // 0x01F4
        char*		szMuzzleFlashEffect_3rdPerson; // 0x01F8

        Pad(0x4);                // 0x01FC
        char*		szMuzzleSmokeEffect;	// 0x0200
        float		flHeatPerShot;			// 0x0204
        char*		szZoomInSound;			// 0x0208
        char*		szZoomOutSound;			// 0x020C
        float		flInaccuracyPitchShift;	// 0x0210
        float		flInaccuracySoundThreshold;	// 0x0214
        float		flBotAudibleRange;		// 0x0218
        Pad(0x8);                // 0x0220
        char*		pWrongTeamMsg;			// 0x0224
        bool		bHasBurstMode;			// 0x0228
        Pad(0x3);            // 0x0229
        bool		bIsRevolver;			// 0x022C
        bool		bCannotShootUnderwater;	// 0x0230
    public:
        bool IsFullAuto() const {
            return bFullAuto;
        }
        int GetPrice() const {
            return iWeaponPrice;
        }
        float GetArmorRatio() const {
            return flArmorRatio;
        }
        float GetArmorPenetration() const {
            return flPenetration;
        }
        int GetDamage() const {
            return iDamage;
        }
        float GetMaxHitRange() const {
            return flRange;
        }
        float GetMaxHitRangeModifier() const {
            return flRangeModifier;
        }
        float GetCycleTime() const {
            return flCycleTime;
        }
        float GetSpread() const {
            return flSpread;
        }
    };
}