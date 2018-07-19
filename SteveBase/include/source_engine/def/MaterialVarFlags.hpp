#pragma once

namespace SteveBase::SourceEngine::Define {
    enum MaterialVarFlags {
        Debug = 1 << 0,
        NoDebugOverride = 1 << 1,
        NoDraw = 1 << 2,
        UseInFillrateMode = 1 << 3,

        VertexColor = 1 << 4,
        VertexAlpha = 1 << 5,
        SelfIllumination = 1 << 6,
        Additive = 1 << 7,
        AlphaTest = 1 << 8,
        //	UNUSED					  = (1 << 9),
        ZNearer = 1 << 10,
        Model = 1 << 11,
        Flat = 1 << 12,
        NoCull = 1 << 13,
        NoFog = 1 << 14,
        IgnoreZBuffer = 1 << 15,
        Decal = 1 << 16,
        EnvmapSphere = 1 << 17, // OBSOLETE 
        //	UNUSED					  = (1 << 18),
        EnvmapCameraSpace = 1 << 19, // OBSOLETE 
        BaseAlphaEnvMapMask = 1 << 20,
        TranslucentMaterial = 1 << 21,
        NormalMapAlphaEnvmapMask = 1 << 22,
        NeedsSoftwareSkinning = 1 << 23, // OBSOLETE
        OpaqueTexture = 1 << 24,
        EnvmapMode = 1 << 25, // OBSOLETE
        SuppressDecals = 1 << 26,
        HalfLambert = 1 << 27,
        Wireframe = 1 << 28,
        AllowAlphaToCoverage = 1 << 29,
        AlphaModifiedByProxy = 1 << 30,
        VertexFog = 1 << 31,

        // NOTE: Only add flags here that either should be read from
        // .vmts or can be set directly from client code. Other, internal
        // flags should to into the flag enum in IMaterialInternal.h
    };
}