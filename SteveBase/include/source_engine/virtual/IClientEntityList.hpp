#pragma once

#include <misc/Macro.hpp>
#include <misc/ProxiedClass.hpp>

#include <source_engine/def/_EngineTypes.hpp>

#include <experimental/generator>

namespace SteveBase::SourceEngine::Virtual {
    using namespace std::experimental;
    using namespace Define;

    class CBaseEntity;
    class CCSPlayer;
    class CPlantedC4;

    interface IClientEntityList extends Misc::ProxiedClass {
        DefineVFunc(GetClientEntity, (int entNum)->CBaseEntity *)(3)(entNum);
        DefineVFunc(GetClientEntityFromHandle, (EHANDLE hEnt)->CBaseEntity *)(4)(hEnt);
        DefineVFunc(GetHighestEntityIndex, () -> int)(6)();

        generator<CBaseEntity *> GetAllEntities();
        generator<CCSPlayer *> GetAllPlayers();
        CCSPlayer *GetLocalPlayer();
    };
}
