#pragma once

namespace SteveBase::SourceEngine::Define {
    enum class TraceType {
        Everything = 0,
        WorldOnly,				// NOTE: This does *not* test static props!!!
        EntitiesOly,			// NOTE: This version will *not* test static props
        EverythingButFilterProps,	// NOTE: This version will pass the IHandleEntity for props through the filter, unlike all other filters
    };
}
