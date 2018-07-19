#pragma once

namespace SteveBase::SourceEngine::Define {
    enum class MaterialPropertyTypes {
        NeedsLightMap = 0,		// bool
        Opacity,				// int (enum MaterialPropertyOpacityTypes_t)
        Reflectivity,		    // vec3_t
        NeedsBumpedLightMaps    // bool
    };
}
