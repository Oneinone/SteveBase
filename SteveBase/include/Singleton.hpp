#pragma once

#include <Interface.hpp>

namespace SteveBase {
    void *GetSingletonImpl(interface_hash_t hash);

    template<class T>
    constexpr T *GetSingleton() {
        extern void SetSingletonImpl(interface_hash_t hash, void *ptr);

        if (GetSingletonImpl(MakeTypeHash<T>()) == nullptr) {
            SetSingletonImpl(MakeTypeHash<T>(), new T);
        }

        return (T *)GetSingletonImpl(MakeTypeHash<T>());
    }
}
