#pragma once

namespace SteveBase::SourceEngine::Define {
    enum class EntityEffects {
        BoneMerge = 0x001,	            // Performs bone merge on client side
        BrightLight = 0x002,	        // DLIGHT centered at entity origin
        DimLight = 0x004,	            // player flashlight
        NoInterp = 0x008,	            // don't interpolate the next frame
        NoShadow = 0x010,	            // Don't cast no shadow
        NoDraw = 0x020,	                // don't draw entity
        NoReceiveShadow = 0x040,	    // Don't receive no shadow
        BoneMergeWithFastcull = 0x080,	// For use with EF_BONEMERGE. If this is set, then it places this ent's origin at its
                                        // parent and uses the parent's bbox + the max extents of the aiment.
                                        // Otherwise, it sets up the parent's bones every frame to figure out where to place
                                        // the aiment, which is inefficient because it'll setup the parent's bones even if
                                        // the parent is not in the PVS.
        ItemBlink = 0x100,	            // blink an item so that the user notices it.
        ParentAnimates = 0x200,	        // always assume that the parent entity is animating
        MaxBits = 10
    };
}