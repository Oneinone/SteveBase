#pragma once

#include <cstdint>

namespace SteveBase::SourceEngine::Define {
    enum ContentFlags : uint32_t {
        Empty = 0,
        Solid = 1 << 0,
        Window = 1 << 1,		// translucent, but not watery (glass)
        Aux = 1 << 2,
        Grate = 1 << 3,	// alpha-tested "grate" textures.  Bullets/sight pass through, but solids don't
        Slime = 1 << 4,
        Water = 1 << 5,
        BlockLineOfSight = 1 << 6,	// block AI line of sight
        Opaque = 1 << 7,	// things that cannot be seen through (may be non-solid though)
        LastVisible = Opaque,
        AllVisible = LastVisible | LastVisible - 1,
        TestFogVolume = 1 << 8,
        NotUsed = 1 << 9,
        BlockLight = 1 << 10,
        Team1 = 1 << 11,
        Team2 = 1 << 12,
        IgnoreNoDrawOpaque = 1 << 13,
        Moveable = 1 << 14,
        AreaPortal = 1 << 15,
        PlayerClip = 1 << 16,
        MonsterClip = 1 << 17,
        Current0 = 1 << 18,
        Current90 = 1 << 19,
        Current180 = 1 << 20,
        Current270 = 1 << 21,
        CurrentUp = 1 << 22,
        CurrentDown = 1 << 23,
        Origin = 1 << 24,
        Monster = 1 << 25,
        Debris = 1 << 26,
        Detail = 1 << 27,
        Translucent = 1 << 28,
        Ladder = 1 << 29,
        Hitbox = 1 << 30,
    };
}
