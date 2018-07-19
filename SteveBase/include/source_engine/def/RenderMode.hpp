#pragma once

namespace SteveBase::SourceEngine::Define {
    // Rendering constants
    // if this is changed, update common/MaterialSystem/Sprite.cpp
    enum class RenderMode {
        Normal = 0,		// src
        TransColor,		// c*a+dest*(1-a)
        TransTexture,	// src*a+dest*(1-a)
        Glow,			// src*a+dest -- No Z buffer checks -- Fixed size in screen space
        TransAlpha,		// src*srca+dest*(1-srca)
        TransAdd,		// src*a+dest
        Environmental,	// not drawn, used for environmental effects
        TransAddFrameBlend, // use a fractional frame value to blend between animation frames
        TransAlphaAdd,	// src + dest*(1-a)
        WorldGlow,		// Same as Glow but not fixed size in screen space
        None,			// Don't render.

        ModeCount,		// must be last
    };
}