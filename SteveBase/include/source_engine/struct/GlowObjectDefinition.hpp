#pragma once

#include <maths/Vector3.hpp>

namespace SteveBase::SourceEngine::Virtual {
    class CBaseEntity;
}

namespace SteveBase::SourceEngine::Structure {
    using namespace Maths;
    using namespace Virtual;

    struct GlowObjectDefinition {
        CBaseEntity *m_hEntity;
        Vector3 m_vGlowColor;
        float m_flGlowAlpha;

        Pad(8);
        float m_flBloomAmount;
        Pad(4);

        bool m_bRenderWhenOccluded; // glow when target is in player viewport // visible and renderable
        bool m_bRenderWhenUnoccluded; // glow when target is not in player viewport // not visible and renderable
        bool m_bFullBloom;
        Pad(1); // int = 4 bools = 4 bytes
        Pad(8);
        int m_nSplitScreenSlot;
        int m_nNextFreeSlot;

        static const int END_OF_FREE_LIST = -1;
        static const int ENTRY_IN_USE = -2;
    };
}