#pragma once

#include <string>

#include <vendor/hash/hash.h>

namespace SteveBase::SourceEngine::Structure {
    struct RecvTable;
}

namespace SteveBase::Manager {

    using namespace SourceEngine::Structure;

    using netvar_hash_t = constexpr_hash_t;

    class NetVarManager {
    public:
        static void Init();
        static int GetNetVar(netvar_hash_t hash);
        static std::string DumpAsJson();
        static void SaveNetVarJsonToDisk();
    };

#define NetVar(tableName, varName) NetVarManager::GetNetVar(compile_time_hash(#tableName) * compile_time_hash(#varName))
}