#include <GlobalDefines.hpp>
#include <source_engine/struct/CGlowManager.hpp>

#include <Interface.hpp>
#include <source_engine/index.hpp>

namespace SteveBase::SourceEngine::Structure {
    using namespace Virtual;

    GlowObjectDefinition *CGlowManager::FindGlowObjectDefinitionsForEntity(CBaseEntity *entity, bool registerIfNotFound) {
        for (int i = 0; i < this->m_GlowObjectDefinitions.m_Memory.m_nAllocationCount; i++) {
            auto &glowDefinitions = this->m_GlowObjectDefinitions.m_Memory.m_pMemory[i];
            if (glowDefinitions.m_hEntity == entity) return &glowDefinitions;
        }
        if (registerIfNotFound && RegisterGlowObject(entity) != -1) {
            LoggerDebug("0x{x} is not found in the glow list, auto registering.", (uintptr_t)entity);
            return FindGlowObjectDefinitionsForEntity(entity);
        }
        return nullptr;
    }

    GlowObjectDefinition *CGlowManager::GetGlowObjectDefinitionsAt(int i) {
        if (i < 0 || i > this->m_GlowObjectDefinitions.m_Memory.m_nAllocationCount - 1) {
            return nullptr;
        }

        return &this->m_GlowObjectDefinitions.m_Memory.m_pMemory[i];
    }

#define END_OF_FREE_LIST -1
#define ENTRY_IN_USE -2
    int CGlowManager::RegisterGlowObject(CBaseEntity *entity) {
        // FIXME: No remaining slots, see issue #158.
        if (m_nFirstFreeSlot == END_OF_FREE_LIST) {
            return -1;
        }

        int index = m_nFirstFreeSlot;
        m_nFirstFreeSlot = m_GlowObjectDefinitions.m_Memory.m_pMemory[index].m_nNextFreeSlot;

        memset(&m_GlowObjectDefinitions.m_Memory.m_pMemory[index], 0, sizeof GlowObjectDefinition);
        m_GlowObjectDefinitions.m_Memory.m_pMemory[index].m_hEntity = entity;
        m_GlowObjectDefinitions.m_Memory.m_pMemory[index].m_nSplitScreenSlot = -1;
        m_GlowObjectDefinitions.m_Memory.m_pMemory[index].m_nNextFreeSlot = ENTRY_IN_USE;

        return index;
    }

    void CGlowManager::UnregisterGlowObject(int index) {
        m_GlowObjectDefinitions.m_Memory.m_pMemory[index].m_nNextFreeSlot = m_nFirstFreeSlot;
        m_GlowObjectDefinitions.m_Memory.m_pMemory[index].m_hEntity = NULL;
        m_nFirstFreeSlot = index;
    }
}
