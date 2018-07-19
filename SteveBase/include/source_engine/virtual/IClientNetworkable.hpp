#pragma once

#include <misc/ProxiedClass.hpp>

namespace SteveBase::SourceEngine::Structure {
    struct ClientClass;
}

namespace SteveBase::SourceEngine::Virtual {
    using namespace Structure;

    interface IClientNetworkable extends Misc::ProxiedClass {
        DefineVFunc(GetClientClass, ()->ClientClass *)(2)();
        DefineVFunc(GetIndex, () -> int)(9)();
    };
}