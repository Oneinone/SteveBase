#pragma once

#ifdef RELEASE
#define STRING_ENC
#endif

#ifdef STRING_ENC

#include <array>
#include <limits>

# ifdef _MSC_VER
#  pragma warning(push)
#  pragma warning(disable: 4307) 
# else
#  define __forceinline __attribute__((always_inline))
# endif
# define const_inline constexpr __forceinline
namespace Enc {
    template<class U> constexpr uint32_t djb2(const U *input) {
        uint32_t hash = 5381;
        for (int i = 0; input[i] != '\0'; i++) hash = hash * 33 + input[i];
        return hash;
    }
    template<class T, T val> constexpr static T forced_value_v = val;
    constexpr auto seed = forced_value_v<uint32_t, 1 + djb2(__DATE__ " " __TIME__ " " __FILE__)>;
    template <class T, intmax_t N, intmax_t M = std::numeric_limits<T>::max()>
    const_inline T Random() { return (((__COUNTER__ + 1) * seed) * (N + M) >> 7) % M; }
    template < class T, size_t N, T K = Enc::Random<T, ((__COUNTER__ + 1) * __LINE__ * N * 131 >> 7)>()>
    class Xor {
        const T k; std::array<T, N> _data;
        template<size_t i> const_inline T enc(const T c) const { return c ^ (1 + (k + i) % 0xFF); }
        __forceinline T dec(const T c, const size_t i) const { return c ^ (1 + (k + i) % 0xFF); }
        public: constexpr size_t size() const { return N; }
        __forceinline std::array<T, N> data() { for (size_t i = 0; i < N; ++i) _data[i] = dec(_data[i], i); return _data; }
# define XorCtor(...) \
template <size_t... Is> const_inline Xor(__VA_ARGS__, std::index_sequence<Is...>): k { Random<T, K>() }, _data { enc<Is>(arr[Is])... } { }
        XorCtor(const T(&arr)[N]) XorCtor(const std::array<T, N> arr)
    };
}
# undef XorCtor
# undef const_inline
# define array_type(arr) std::remove_cv_t<std::remove_reference_t<decltype((arr)[0])>>
# define encrypt(src, n) Enc::Xor<array_type(src), (n)>{src, std::make_index_sequence<(n)>()}.data()

# define array_encrypt(arr) encrypt(arr, (arr).size())
# define text(str) encrypt(str, sizeof((str)) / sizeof((str)[0])).data()

# ifdef _MSC_VER
#  pragma warning(pop)
# else
#  undef __forceinline
# endif

#else
# define array_encrypt(arr) (arr)
# define text(str) (str)
#endif 

#define textdup(s) _strdup(text(s))
#define textpp(s) std::string(text(s))

#ifdef USE_TEXT_MACRO
# ifdef TEXT
#  undef TEXT
# endif
# if (defined _UNICODE || defined USE_WIDE_CHAR)
#  define TEXT(x) text(L#x)
# else
#  define TEXT(x) text(x)
# endif
#endif