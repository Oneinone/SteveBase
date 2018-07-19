#pragma once

#include <misc/Macro.hpp>

namespace SteveBase::SourceEngine::Virtual {
    interface IClientRenderable;
}

namespace SteveBase::Maths {
    class ViewMatrix;
}

namespace SteveBase::SourceEngine::Structure {
    using namespace Virtual;
    using namespace Maths;

    struct studiohdr_t;
    struct studiohwdata_t;

    struct DrawModelState_t {
        studiohdr_t*			m_pStudioHdr;
        studiohwdata_t*			m_pStudioHWData;
        IClientRenderable*		m_pRenderable;
        const ViewMatrix		*m_pModelToWorld;
        void*					m_decals;
        int						m_drawFlags;
        int						m_lod;
    };
}