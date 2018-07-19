#pragma once

#include "ContentFlags.hpp"
#include <cstdint>

namespace SteveBase::SourceEngine::Define {
    enum ContentMask : uint32_t {
        EveryThing = 0xFFFFFFFF,
        Shot = ContentFlags::Solid | ContentFlags::Moveable | ContentFlags::Monster | ContentFlags::Window | ContentFlags::Debris | ContentFlags::Hitbox,
        MaskSolid = ContentFlags::Solid | ContentFlags::Moveable | ContentFlags::Window | ContentFlags::Monster | ContentFlags::Grate,
        PlayerSolid = ContentFlags::Solid | ContentFlags::Moveable | ContentFlags::PlayerClip | ContentFlags::Window | ContentFlags::Monster | ContentFlags::Grate,
        NPCSolid = ContentFlags::Solid | ContentFlags::Moveable | ContentFlags::MonsterClip | ContentFlags::Window | ContentFlags::Monster | ContentFlags::Grate,
        NPCFluid = ContentFlags::Solid | ContentFlags::Moveable | ContentFlags::MonsterClip | ContentFlags::Window | ContentFlags::Monster,
        WaterMask = ContentFlags::Water | ContentFlags::Moveable | ContentFlags::Slime,
        OpaqueMask = ContentFlags::Solid | ContentFlags::Moveable | ContentFlags::Opaque,
        NPCs = ContentFlags::Monster,
        OpaqueAndNPCs = OpaqueMask | NPCs,
        BlockLineOfSightMask = ContentFlags::Solid | ContentFlags::Moveable | ContentFlags::BlockLineOfSight,
        BlockLineOfSightAndNPCs = BlockLineOfSightMask | ContentFlags::Monster,
        Visible = OpaqueMask | ContentFlags::IgnoreNoDrawOpaque,
        VisibleAndNPCs = Visible | NPCs,
        ShotBrushOnly = ContentFlags::Solid | ContentFlags::Moveable | ContentFlags::Window | ContentFlags::Debris,
        ShotHull = ContentFlags::Solid | ContentFlags::Moveable | ContentFlags::Monster | ContentFlags::Window | ContentFlags::Debris | ContentFlags::Grate,
        ShotPortal = ContentFlags::Solid | ContentFlags::Moveable | ContentFlags::Window | ContentFlags::Monster,
        SolidBrushOnly = ContentFlags::Solid | ContentFlags::Moveable | ContentFlags::Window | ContentFlags::Grate,
        PlayerSolidBrushOnly = ContentFlags::Solid | ContentFlags::Moveable | ContentFlags::Window | ContentFlags::PlayerClip | ContentFlags::Grate,
        NPCSolidBrushOnly = ContentFlags::Solid | ContentFlags::Moveable | ContentFlags::Window | ContentFlags::MonsterClip | ContentFlags::Grate,
        NPCWorldStatic = ContentFlags::Solid | ContentFlags::Window | ContentFlags::MonsterClip | ContentFlags::Grate,
        NPCWorldStaticFluid = ContentFlags::Solid | ContentFlags::Window | ContentFlags::MonsterClip,
        SplitAreaPortal = ContentFlags::Water | ContentFlags::Slime,
        Current = ContentFlags::Current0 | ContentFlags::Current90 | ContentFlags::Current180 | ContentFlags::Current270 | ContentFlags::CurrentUp | ContentFlags::CurrentDown,
        DeadSolid = ContentFlags::Solid | ContentFlags::PlayerClip | ContentFlags::Window | ContentFlags::Grate
    };
}
