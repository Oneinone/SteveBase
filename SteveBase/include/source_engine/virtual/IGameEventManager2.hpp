#pragma once

#include <misc/ProxiedClass.hpp>

#include <source_engine/virtual/IGameEventListener2.hpp>

namespace SteveBase::SourceEngine::Virtual {
    interface IGameEventManager2 extends Misc::ProxiedClass {
        DefineVFunc(AddListener, (IGameEventListener2 *listener, const char *name, bool bServerSide) -> bool)(3)(listener, name, bServerSide);
        DefineVFunc(FindListener, (IGameEventListener2 *listener, const char * name) -> bool)(4)(listener, name);
        DefineVFunc(RemoveListener, (IGameEventListener2 *listener) -> void)(5)(listener);
        DefineVFunc(CreateEvent, (const char *name, bool bForce)->IGameEvent *)(6)(name, bForce);
        DefineVFunc(FireEvent, (IGameEvent *event, bool bDontBroadcast) -> bool)(7)(event, bDontBroadcast);
        DefineVFunc(FireEventClientSide, (IGameEvent *event) -> bool)(8)(event);
    };
}
