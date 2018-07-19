#pragma once

#include <misc/ProxiedClass.hpp>

namespace SteveBase::SourceEngine::Virtual {
    
    interface IGameEvent extends Misc::ProxiedClass {
        DefineVFunc(GetName, () -> const char *)(1)();
        DefineVFunc(GetInt, (const char *keyName, int defaultValue) -> int)(6)(keyName, defaultValue);
        DefineVFunc(GetString, (const char *keyName, const char *defaultValue) -> const char *)(9)(keyName, defaultValue);
    };


}