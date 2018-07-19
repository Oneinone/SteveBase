#pragma once

#include <source_engine/struct/CUtlMemory.hpp>

namespace SteveBase::SourceEngine::Structure {
    template< class T >
    struct CUtlVector {
        CUtlMemory<T> m_Memory;
        int m_Size;
    };
}