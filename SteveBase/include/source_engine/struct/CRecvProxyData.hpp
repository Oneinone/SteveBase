#pragma once

#include <source_engine/struct/DVariant.hpp>

namespace SteveBase::SourceEngine::Structure {
    struct RecvProp;

    struct CRecvProxyData {
        RecvProp	   *m_pRecvProp;		// The property it's receiving.
        DVariant		m_Value;			// The value given to you to store.
        int				m_iElement;			// Which array element you're getting.
        int				m_ObjectID;			// The object being referred to.
    };
}