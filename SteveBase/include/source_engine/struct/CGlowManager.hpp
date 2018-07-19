#pragma once

#include <misc/Macro.hpp>
#include <source_engine/struct/CUtlVector.hpp>

namespace SteveBase::SourceEngine::Virtual {
    class CBaseEntity;
}

namespace SteveBase::SourceEngine::Structure {
    using namespace Virtual;

    struct GlowObjectDefinition;

    struct CGlowManager {
        Pad(4);
        CUtlVector<GlowObjectDefinition> m_GlowObjectDefinitions;
        Pad(4); // lol why
        int m_nFirstFreeSlot;

        GlowObjectDefinition *FindGlowObjectDefinitionsForEntity(CBaseEntity *entity, bool registerIfNotFound = true);
        GlowObjectDefinition *GetGlowObjectDefinitionsAt(int i);

        int RegisterGlowObject(CBaseEntity *entity);
        void UnregisterGlowObject(int index);
    };
}
