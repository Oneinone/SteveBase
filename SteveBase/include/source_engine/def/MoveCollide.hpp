#pragma once

namespace SteveBase::SourceEngine::Define {
    enum class MoveCollide {
        Default = 0,

        // These ones only work for MOVETYPE_FLY + MOVETYPE_FLYGRAVITY
        FlyBounce,	// bounces, reflects, based on elasticity of surface and object - applies friction (adjust velocity)
        FlyCustom,	// Touch() will modify the velocity however it likes
        FlySlide,  // slides along surfaces (no bounce) - applies friciton (adjusts velocity)

        Count,

        MaxBits = 3
    };
}