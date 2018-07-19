#pragma once

#include <algorithm>
#include <initializer_list>
#include <type_traits>

#include <vendor/XorStr/XorStr.h>

namespace SteveBase::Misc {
    template<class T>
    constexpr bool is_one_of(T input, std::initializer_list<T> predicates) {
        return std::find(predicates.begin(), predicates.end(), input) != predicates.end();
    }

    template<class T, class U>
    constexpr bool is_one_of(T &&a, U &&b) {
        return a == b;
    }

    template<class T, class U, class ...Args>
    constexpr bool is_one_of(T &&a, U &&b, Args &&...args) {
        return a == b || is_one_of(a, args...);
    }

    template<class T>
    constexpr auto is_one_of(T &&a) {
        return [&](auto b, auto &&...args) {
            return is_one_of(a, b, args...);
        };
    }

    template <typename T>
    constexpr auto to_underlying(T e) {
        return static_cast<std::underlying_type_t<T>>(e);
    }

    template<class T>
    using enum_only = typename std::enable_if<std::is_enum<T>::value, T>::type;

    template<class T>
    constexpr enum_only<T> operator & (T lhs, T rhs) {
        return static_cast<T>(to_underlying(lhs) & to_underlying(rhs));
    }

    template<class T>
    constexpr enum_only<T> operator | (T lhs, T rhs) {
        return static_cast<T>(to_underlying(lhs) | to_underlying(rhs));
    }

    template<class T>
    constexpr enum_only<T> operator ~ (T in) {
        return static_cast<T>(~to_underlying(in));
    }

    template<class T>
    constexpr enum_only<T> &operator &= (T &lhs, T rhs) {
        return lhs = lhs & rhs;
    }

    template<class T>
    constexpr enum_only<T> &operator |= (T &lhs, T rhs) {
        return lhs = lhs | rhs;
    }

    template<class T>
    constexpr const char *GetTypeName() { // MSVC only compile time type name getter
        static std::string name;

        if (name.empty()) {
            name = text(__FUNCSIG__); // some compiler magic here => 
                                      // __FUNCSIG__ == "const char *__cdecl GetTypeName<`T`>(void)" where T is our stringified template parameter T
                                      // no support for: type aliased types (e.g. string, vector) as they will be resolved by compiler
            size_t type_dataType;

            auto tmpl_func_name = name.find(text(">(void)")); // find the paramter signature of this template function 
            auto tmpl_begin = name.find(text("<")); // find the bracket between type parameter

            if ((type_dataType = name.find(text(" "), tmpl_begin)) != -1) {
                type_dataType += 1; // space between data type and type name begin found 
            } else if ((type_dataType = name.find(text("class"), tmpl_begin)) != -1) { // for some reason msvc forgots to insert space with pointer to type
                type_dataType += 5; // 'class' data type found
            } else if ((type_dataType = name.find(text("struct"), tmpl_begin)) != -1) {
                type_dataType += 6; // 'struct' data type found
            } else {
                type_dataType = tmpl_begin + 1; // last resort, resolve the entire type parameter
            }

            name = name.substr(type_dataType, tmpl_func_name - type_dataType); // cut the type parameter out but substr does not support a range substring
        }

        return name.c_str();
    }

    template<class T>
    constexpr bool IsEightBit() {
        return std::is_same<T, int8_t>() || std::is_same<T, uint8_t>();
    }

    template<class T>
    constexpr bool IsSixteenBit() {
        return std::is_same<T, int16_t>() || std::is_same<T, uint16_t>();
    }

    template<class T>
    constexpr bool IsThirtyTwoBit() {
        return std::is_same<T, int32_t>() || std::is_same<T, uint32_t>();
    }

    template<class T>
    constexpr bool IsSixtyFourBit() {
        return std::is_same<T, int64_t>() || std::is_same<T, uint64_t>();
    }

    template<class T>
    constexpr bool IsDouble() {
        return std::is_same<T, double>() || std::is_same<T, double_t>();
    }

    template<class T>
    constexpr bool IsFloat() {
        return std::is_same<T, float>() || std::is_same<T, float_t>();
    }

    template<class T>
    constexpr bool IsReal() {
        return IsDouble<T>() || IsFloat<T>();
    }

    template <class T = void, class... Args>
    constexpr auto make_array(Args&&... t) {
        // T is not void: deduced array type is T
        if constexpr (!std::is_same<T, void>()) {
            return std::array<T, sizeof...(Args)> { std::forward<Args>(t)... };
        }
        // T is void: deduced array type is U = std::common_type_t<Args...>
        using U = std::common_type_t<Args...>;

        // T is void and one of the argument is a specialization of std::reference_wrapper<U>: ill-formed
        static_assert(!std::disjunction_v<std::is_same<std::reference_wrapper<U>, Args>...>, "reference_wrappers are not allowed");

        return std::array<U, sizeof...(Args)> { std::forward<Args>(t)... };
    }
}
