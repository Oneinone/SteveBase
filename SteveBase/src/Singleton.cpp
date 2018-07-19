#include <GlobalDefines.hpp>
#include <Singleton.hpp>

#include <misc/TypeAliases.hpp>

namespace SteveBase {
    Misc::SortedDictionary<constexpr_hash_t, void *> singletonMap;

    void *GetSingletonImpl(const interface_hash_t hash) {
        return singletonMap[hash];
    }

    void SetSingletonImpl(const interface_hash_t hash, void *ptr) {
        singletonMap[hash] = ptr;
    }
}
