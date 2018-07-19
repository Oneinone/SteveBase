#pragma once

namespace SteveBase::SourceEngine::Define {
    enum class RenderFx {
        None = 0,
        PulseSlow,
        PulseFast,
        PulseSlowWide,
        PulseFastWide,
        FadeSlow,
        FadeFast,
        SolidSlow,
        SolidFast,
        StrobeSlow,
        StrobeFast,
        StrobeFaster,
        FlickerSlow,
        FlickerFast,
        NoDissipation,
        Distort,			// Distort/scale/translate flicker
        Hologram,			// Distort + distance fade
        Explode,			// Scale up really big!
        GlowShell,			// Glowing Shell
        ClampMinScale,		// Keep this sprite from getting very small (SPRITES only!)
        EnvRain,			// for environmental rendermode, make rain
        EnvSnow,			//  "        "            "    , make snow
        Spotlight,			// TEST CODE for experimental spotlight
        Ragdoll,			// HACKHACK: TEST CODE for signalling death of a ragdoll character
        PulseFastWider,
        Max
    };
}