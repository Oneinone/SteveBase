#pragma once

#include <Interface.hpp>
#include <misc/TypeAliases.hpp>
#include <misc/Macro.hpp>

namespace SteveBase::Manager {
    using namespace Misc;

    class InterfaceManager {
        static void *RetrieveInterface(const char *dll, const char *name);

    public:
        static void Init();
    };

    using InterfaceBindPair = Pair<const char *, interface_hash_t>;
    using InterfaceBindList = List<InterfaceBindPair>;
    using CaptureModuleEntry = Pair<const char *, InterfaceBindList>;
}
