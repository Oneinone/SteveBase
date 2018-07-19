#pragma once

namespace SteveBase::SourceEngine::Structure {
    struct SurfaceData {
        struct {
            float			friction;
            float			elasticity;
            float			density;
            float			thickness;
            float			dampening;
        } physics;

        struct {
            float			reflectivity;
            float			hardnessFactor;
            float			roughnessFactor;
            float			roughThreshold;
            float			hardThreshold;
            float			hardVelocityThreshold;
        } audio;

        struct {
            unsigned short	walkStepLeft;
            unsigned short	walkStepRight;
            unsigned short	runStepLeft;
            unsigned short	runStepRight;
            unsigned short	impactSoft;
            unsigned short	impactHard;
            unsigned short	scrapeSmooth;
            unsigned short	scrapeRough;
            unsigned short	bulletImpact;
            unsigned short	rolling;
            unsigned short	breakSound;
            unsigned short	strainSound;
        } sounds;

        struct {
            float				maxSpeedFactor;
            float				jumpFactor;
            char				pad00[0x4];
            float				flPenetrationModifier;
            float				flDamageModifier;
            unsigned short		material;
            char				pad01[0x3];
        } game;

        struct {
            short	walkStepLeft;
            short	walkStepRight;
            short	runStepLeft;
            short	runStepRight;
            short	impactSoft;
            short	impactHard;
            short	scrapeSmooth;
            short	scrapeRough;
            short	bulletImpact;
            short	rolling;
            short	breakSound;
            short	strainSound;
        } soundhandles;

    };
}