#pragma once

#include <misc/ProxiedClass.hpp>

namespace SteveBase::SourceEngine::Structure {
    struct ClientClass;
}

namespace SteveBase::SourceEngine::Virtual {
    using namespace Structure;

    // interface: https://github.com/ValveSoftware/source-sdk-2013/blob/master/sp/src/public/cdll_int.h#L577
    // implementation: https://github.com/ValveSoftware/source-sdk-2013/blob/master/mp/src/game/client/cdll_client_int.cpp#L598
    interface IBaseClientDLL extends Misc::ProxiedClass {
        DefineVFunc(GetAllClasses, ()->ClientClass *)(8)();
    };
}