#pragma once

#include <misc/ProxiedClass.hpp>

#include <source_engine/struct/CUserCmd.hpp>

namespace SteveBase::SourceEngine::Virtual {
    using namespace Structure;

    class CBaseEntity;
    interface IMoveHelper;

    interface IPrediction extends Misc::ProxiedClass {
        DefineVFunc(SetupMove, (CBaseEntity *player, CUserCmd *cmd, IMoveHelper *helper, void *move) -> void)(20)(player, cmd, helper, move);
        DefineVFunc(FinishMove, (CBaseEntity *player, CUserCmd *cmd, void *move) -> void)(21)(player, cmd, move);
    };
}