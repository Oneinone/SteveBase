#pragma once

#include <source_engine/virtual/CBaseEntity.hpp>

namespace SteveBase::SourceEngine::Virtual {
    class CPlantedC4 extends CBaseEntity {
    public:
        bool IsBombDefused();
        int GetBombExplosionTime();
        int GetBombTimeRemaining();
    };
}