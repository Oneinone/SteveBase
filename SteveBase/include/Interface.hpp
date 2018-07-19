#pragma once

#include <utility/Logger.hpp>
#include <vendor/hash/hash.h>

#if DEBUG
#include <misc/TemplateMetaprogramming.hpp>
#endif

namespace SteveBase {
    using namespace Utility;

    using interface_hash_t = constexpr_hash_t;

#if DEBUG
    void ConnectHashToName(interface_hash_t typeHash, const char *name);
    const char *GetNameForHash(interface_hash_t typeHash);
#endif

    template<class T>
    constexpr interface_hash_t GetHashForType() {
        constexpr auto hash = MakeTypeHash<T>();
#if DEBUG
        ConnectHashToName(hash, GetTypeName<T>());
#endif
        return hash;
    }

    void *GetInterfaceImpl(const interface_hash_t hash);
    void SetInterfaceImpl(const interface_hash_t hash, void *ptr);

    template<class T>
    constexpr T *GetInterface() {
        return (T *)GetInterfaceImpl(GetHashForType<T>());
    }

    template<class T>
    constexpr T *Get() {
        return GetInterface<T>();
    }

    template<class T>
    constexpr void SetInterface(T *ptr) {
        SetInterfaceImpl(GetHashForType<T>(), ptr);
    }
}