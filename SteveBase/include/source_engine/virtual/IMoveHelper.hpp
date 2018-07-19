#pragma once

#include <misc/ProxiedClass.hpp>

namespace SteveBase::SourceEngine::Virtual {
    class CBaseEntity;

    interface IMoveHelper extends Misc::ProxiedClass {
        DefineVFunc(SetHost, (CBaseEntity *ent) -> void)(1)(ent);
    };
}
