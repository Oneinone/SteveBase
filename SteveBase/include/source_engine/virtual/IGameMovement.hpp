#pragma once

#include <misc/ProxiedClass.hpp>

namespace SteveBase::SourceEngine::Virtual {
    class CBaseEntity;

    interface IGameMovement extends Misc::ProxiedClass {
        DefineVFunc(ProcessMovement, (CBaseEntity *player, void *moveData) -> void)(1)(player, moveData);

        void ProcessMovement(CBaseEntity *player) {
            char buf[512] = { 0 };
            return ProcessMovement(player, &buf);
        }
    };
}
