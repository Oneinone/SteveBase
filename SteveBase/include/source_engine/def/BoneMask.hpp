#pragma once

namespace SteveBase::SourceEngine::Define {
    enum BoneMask {
        CalculateMask = 0x1F,
        PhysicallySimulated = 0x01,
        PhysicsProcedural = 0x02,
        AlwaysProcedural = 0x04,
        ScreenAlignSphere = 0x08,
        ScreenAlignCylinder = 0x10,
        UsedMask = 0x0007FF00,
        UsedByAnything = 0x0007FF00,
        UsedByHitbox = 0x00000100,
        UsedByAttachment = 0x00000200,
        UsedByVertexMask = 0x0003FC00,
        UsedByVertexLevelOfDetail0 = 0x00000400,
        UsedByVertexLevelOfDetail1 = 0x00000800,
        UsedByVertexLevelOfDetail2 = 0x00001000,
        UsedByVertexLevelOfDetail3 = 0x00002000,
        UsedByVertexLevelOfDetail4 = 0x00004000,
        UsedByVertexLevelOfDetail5 = 0x00008000,
        UsedByVertexLevelOfDetail6 = 0x00010000,
        UsedByVertexLevelOfDetail7 = 0x00020000,
        UsedByMerge = 0x00040000,

        TypeMask = 0x00F00000,
        FixedAlignment = 0x00100000,

        HasSaveFramePosition = 0x00200000,
        HasSaveFrameRotation64 = 0x00400000,
        HasSaveFrameRotation32 = 0x00800000,
    };
}