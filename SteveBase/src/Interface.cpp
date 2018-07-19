#include <GlobalDefines.hpp>
#include <Interface.hpp>

#include <misc/TypeAliases.hpp>

#if DEBUG
#include <utility/Logger.hpp>
#include <string>
#endif

namespace SteveBase {
    Misc::SortedDictionary<constexpr_hash_t, void *> interfaceMap;

    void *GetInterfaceImpl(const interface_hash_t hash) {
        return interfaceMap[hash];
    }

    void SetInterfaceImpl(const interface_hash_t hash, void *ptr) {
        interfaceMap[hash] = ptr;
#if DEBUG
        if (ptr != nullptr) {
            LoggerDebug("{0}: 0x{x}", GetNameForHash(hash), (DWORD)ptr);
        }
#endif
    }

#if DEBUG
    SortedDictionary<constexpr_hash_t, const char *> *reverseHashTable = nullptr;

    void ConnectHashToName(interface_hash_t typeHash, const char *name) {
        if (reverseHashTable == nullptr) {
            reverseHashTable = new SortedDictionary<constexpr_hash_t, const char *>;
        }

        (*reverseHashTable)[typeHash] = name;
    }

    const char *GetNameForHash(interface_hash_t typeHash) {
        return (*reverseHashTable)[typeHash];
    }

#endif
}
