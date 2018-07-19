#pragma once

#include <maths/Vector3.hpp>

namespace SteveBase::SourceEngine::Virtual {
    class CBaseEntity;
}

namespace SteveBase::SourceEngine::Structure {
    using namespace Virtual;
    using namespace Maths;

    struct CGameTrace {
        struct cplane_t {
            Vector3 normal;
            float dist;
            char type;
            char signbits;
            char pad[2];
        };

        struct csurface_t {
            const char* name;
            short surfaceProps;
            unsigned short	flags;
        };

        Vector3 startpos;
        Vector3 endpos;
        cplane_t plane;
        float fraction;
        int contents;
        unsigned short dispFlags;
        bool allsolid;
        bool startsolid;
        float fractionleftsolid;
        csurface_t surface;
        int	hitgroup;
        short physicsbone;
        CBaseEntity* m_pEnt;
        int	hitbox;
    };
}