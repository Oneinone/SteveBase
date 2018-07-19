#pragma once

#include <optional>

namespace SteveBase::Utility {

    template<class T>
    class Optional : public std::optional<T> {
        using super_t = std::optional<T>;
    public:
        using super_t::super_t;

        Optional() {}
        Optional(super_t t) : super_t(t) {}
    };
}