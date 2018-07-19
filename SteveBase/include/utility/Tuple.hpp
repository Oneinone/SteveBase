#pragma once

#include <tuple>

namespace SteveBase::Utility {
    // C# tuple meme

    template<class... T>
    struct Tuple : std::tuple<T...> {
        using super_t = std::tuple<T...>;
        using super_t::super_t;

        Tuple() : super_t() {}
        Tuple(super_t t) : super_t(t) {}

        template<size_t N>
        constexpr auto &Item() {
            return std::get<N>(*this);
        }

        constexpr void Deconstruct(T&... args) {
            std::tie(args...) = *this;
        }

        static constexpr Tuple<T...> Create(T... args) {
            return std::make_tuple(args...);
        }

        constexpr auto &ToRawTuple() {
            return (super_t &)*this;
        }

        operator super_t&() {
            return ToRawTuple();
        }

        operator super_t() {
            return ToRawTuple();
        }
    };

    template <>
    struct Tuple<> {
        template<class... T>
        static constexpr Tuple<T...> Create(T... args) {
            return std::make_tuple(args...);
        }
    };
}