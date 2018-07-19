#pragma once

#include <type_traits>

namespace SteveBase::Misc {

#define $$(expr) { return (expr); }

    // These classes are not written by me
    // All of them are copypasted from stackoverflow
    // How come would they be written by a puny motherfucker like me?

    template< class, class = std::void_t<> >
    struct needs_unapply : std::true_type {};

    template< class T >
    struct needs_unapply<T, std::void_t<decltype(std::declval<T>()())>> : std::false_type {};

    template <typename F>
    constexpr auto curry(F&& f);

    template <bool> struct curry_on;

    template <> struct
        curry_on<false> {
        template <typename F>
        constexpr static auto apply(F&& f) {
            return f();
        }
    };

    template <> struct
        curry_on<true> {
        template <typename F>
        constexpr static auto apply(F&& f) {
            return [=](auto&& x) {
                return curry(
                    [=](auto&&...xs) -> decltype(f(x, xs...)) {
                    return f(x, xs...);
                }
                );
            };
        }
    };

    template <typename F>
    constexpr auto curry(F&& f) {
        return curry_on<needs_unapply<decltype(f)>::value>::template apply(f);
    }

    // copypaste
    template<typename _function, typename _val>
    constexpr auto partial(_function foo, _val v) {
        return [foo, v](auto... rest) {
            return foo(v, rest...);
        };
    }

    template< typename _function, typename _val1, typename... _valrest >
    constexpr auto partial(_function foo, _val1 val, _valrest... valr) {
        return[foo, val, valr...](auto... frest) {
            return partial(partial(foo, val), valr...)(frest...);
        };
    }
}