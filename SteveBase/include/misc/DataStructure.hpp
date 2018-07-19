#pragma once

#include <string>
#include <memory>

#include "FunctionalProgramming.hpp"

namespace SteveBase::Misc {
    // Not really data strucuture related tho
    template <class T>
    constexpr auto ShallowCopy(T *to, T *from) {
        return (T *)memcpy(to, from, sizeof T);
    }

    template <class T>
    constexpr auto ShallowCopy(T *to) {
        return partial([](T *to, T *from) {
            return ShallowCopy<T>(to, from);
        }, to);
    }

    template <class T>
    constexpr std::shared_ptr<T> ShallowClone(T *src) {
        std::shared_ptr<T> mem((T *)std::malloc(sizeof T), free);
        ShallowCopy(mem.get(), src); // kind of dangerous
        return mem;
    }

    // copypasted: https://stackoverflow.com/a/39018368/3289081
    std::wstring ConvertStringOfBytesToWides(std::string str);

    std::string ConvertStringOfWidesToBytes(std::wstring str);
}
