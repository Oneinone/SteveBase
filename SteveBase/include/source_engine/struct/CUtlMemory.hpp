#pragma once

namespace SteveBase::SourceEngine::Structure {
    template< class T >
    struct CUtlMemory {
        T *m_pMemory;
        int m_nAllocationCount;
        int m_nGrowSize;
    };
}