#pragma once

#include <misc/Macro.hpp>
#include <misc/ProxiedClass.hpp>

namespace SteveBase::SourceEngine::Structure {
    struct KeyValues;
}

namespace SteveBase::SourceEngine::Virtual {
    using namespace Misc;

    interface IKeyValuesSystem extends ProxiedClass {
        DefineVFunc(AllocKeyValuesMemory, (int size) -> void *)(1)(size);
        DefineVFunc(FreeKeyValuesMemory, (void *mem) -> void)(2)(mem);
    };
}