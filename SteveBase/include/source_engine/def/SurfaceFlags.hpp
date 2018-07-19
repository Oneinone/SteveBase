#pragma once

#include <cstdint>

namespace SteveBase::SourceEngine::Define {
    enum SurfaceFlags : uint16_t {
        // NOTE: These are stored in a short in the engine now.  Don't use more than 16 bits
        Light = 1 << 0,		// value will hold the light strength
        Sky2D = 1 << 1,		// don't draw, indicates we should skylight + draw 2d sky but not draw the 3D skybox
        Sky = 1 << 2,	// don't draw, but add to skybox
        Warp = 1 << 3,	// turbulent water warp
        Trans = 1 << 4,
        NoPortal = 1 << 5,// the ace can not have a portal placed on it
        SurfaceTrigger = 1 << 6,	// FIXME: This is an xbox hack to work around elimination of trigger aces, which breaks occluders
        SurfaceNoDraw = 1 << 7,// don't bother referencing the texture

        Hint = 1 << 8,	// make a primary bsp splitter

        Skip = 1 << 9,// completely ignore, allowing non-closed brushes
        NoLight = 1 << 10,	// Don't calculate light
        BumpLight = 1 << 11,	// calculate three lightmaps for the ace for bumpmapping
        NoShadows = 1 << 12,// Don't receive shadows
        NoDecals = 1 << 13,	// Don't receive decals
        NoPaint = NoDecals,	// the ace can not have paint placed on it
        NoChop = 1 << 14,// Don't subdivide patches on this ace 
        SurfaceHitbox = 1 << 15,	// ace is part of a hitbox
    };
}
