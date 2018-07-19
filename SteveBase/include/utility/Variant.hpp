#pragma once

#include <variant>

namespace SteveBase::Utility {
    template<class... T>
    class Variant : public std::variant<T...> {
        using super_t = std::variant<T...>;
    public:
        using super_t::super_t;

        Variant() {}
        Variant(super_t t) : super_t(t) {}

        template<class U>
        constexpr U &Get() {
            return std::get<U>(*this);
        }

        template<int N>
        constexpr auto &Get() {
            return std::get<N>(*this);
        }

        template<class U>
        constexpr U *GetIf() {
            return std::get_if<U>(this);
        }

        template<class U>
        constexpr bool Holds() {
            return std::holds_alternative<U>(*this);
        }

        template<class U>
        constexpr U &ForceGet() {
            return *(U *)this;
        }
    };
}