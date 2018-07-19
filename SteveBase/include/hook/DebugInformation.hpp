#pragma once

#include <Interface.hpp>
#include <manager/VariableManager.hpp>

#include <source_engine/virtual/CBaseEntity.hpp>
#include <source_engine/virtual/CCSPlayer.hpp>
#include <source_engine/virtual/IClientEntityList.hpp>
#include <source_engine/virtual/ITraceFilter.hpp>

namespace SteveBase::SourceEngine::Virtual {
    class CBaseEntity;
    class CCSPlayer;
}

namespace SteveBase::Hook {
    using namespace Manager;
    using namespace SourceEngine::Virtual;

    class DebugInformation {
        LambdaTraceFilter filter = LambdaTraceFilter([](CBaseEntity *pEnt, int) -> bool {
            static auto entList = GetInterface<IClientEntityList>();

            if (pEnt == entList->GetClientEntity(0)) {
                return false; // no need to hit the world
            }

            if (pEnt == entList->GetLocalPlayer()) {
                return false; // should i hit mahself?
            }

            return true;
        });
    public:
        void OnPaintTraverse();
    };
}
