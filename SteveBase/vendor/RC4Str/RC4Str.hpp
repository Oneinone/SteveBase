#pragma once

#include <array>
#include <utility>
#include <string>

namespace CompileTimeRandomNumber {
    constexpr auto time = __TIME__;
    constexpr auto seed = static_cast<int>(time[7]) + static_cast<int>(time[6]) * 10 + static_cast<int>(time[4]) * 60 + static_cast<int>(time[3]) * 600 + static_cast<int>(time[1]) * 3600 + static_cast<int>(time[0]) * 36000;

    template < int N >
    struct RandomGenerator {
    private:
        static constexpr unsigned a = 16807; // 7^5
        static constexpr unsigned m = 2147483647; // 2^31 - 1

        static constexpr unsigned s = RandomGenerator< N - 1 >::value;
        static constexpr unsigned lo = a * (s & 0xFFFF); // Multiply lower 16 bits by 16807
        static constexpr unsigned hi = a * (s >> 16); // Multiply higher 16 bits by 16807
        static constexpr unsigned lo2 = lo + ((hi & 0x7FFF) << 16); // Combine lower 15 bits of hi with lo's upper bits
        static constexpr unsigned hi2 = hi >> 15; // Discard lower 15 bits of hi
        static constexpr unsigned lo3 = lo2 + hi;

    public:
        static constexpr unsigned max = m;
        static constexpr unsigned value = lo3 > m ? lo3 - m : lo3;
    };

    template <>
    struct RandomGenerator< 0 > {
        static constexpr unsigned value = seed;
    };

    template < int N, int M >
    struct RandomInt {
        static constexpr auto value = RandomGenerator< N + 1 >::value % M;
    };

    template < int N >
    struct RandomChar {
        static const char value = static_cast<char>(1 + RandomInt< N, 0x7F - 1 >::value);
    };
}

namespace CompileTimeEncryption {
    using namespace std;

    template<class C, class T, size_t N, size_t... I> constexpr
        array<C, N> convert_array(const array<T, N>& lhs, index_sequence<I...>) {
        return { static_cast<C>(lhs[I])... };
    }

    template<class C, class T, size_t N> constexpr
        decltype(auto) convert_array(const array<T, N>& lhs) {
        return convert_array<C>(lhs, make_index_sequence<N>());
    }

    template<class T, size_t N, size_t... I> constexpr
        array<T, N> make_array(const T(&lhs)[N], index_sequence<I...>) {
        return { lhs[I]... };
    }

    template<class T, size_t N> constexpr
        decltype(auto) make_array(const T(&lhs)[N]) {
        return make_array(lhs, make_index_sequence<N>());
    }

    template<class T, size_t a, size_t b, size_t... I1, size_t... I2> constexpr
        array<T, a + b> concat_array(const array<T, a>& lhs, index_sequence<I1...>,
            const array<T, b>& rhs, index_sequence<I2...>) {
        return{ lhs[I1]..., rhs[I2]... };
    }

    template<class T, size_t a, size_t b> constexpr
        array<T, a + b> concat_array(const array<T, a>& lhs, const array<T, b>& rhs) {
        return concat_array(lhs, make_index_sequence<a>(), rhs, make_index_sequence<b>());
    }

    template<size_t x, size_t y, class T, size_t N, size_t... I> constexpr
        array<T, y - x> partition_array(const array<T, N>& lhs, index_sequence<I...>) {
        return{ { lhs[x + I] ... } };
    }

    template<size_t x, size_t y, class T, size_t N> constexpr
        decltype(auto) partition_array(const array<T, N>& lhs) {
        return partition_array<x, y>(lhs, make_index_sequence<y - x>());
    }

    template<size_t x_index, size_t y_index, class T, size_t N> constexpr
        array<T, N> _array_swap_elements(const array<T, N>& lhs) {
#define offset (x_index == y_index ? 0 : 1)
        return 	concat_array(partition_array<0, x_index>(lhs),
            concat_array(partition_array<y_index, y_index + offset>(lhs),
                concat_array(partition_array<x_index + offset, y_index>(lhs),
                    concat_array(partition_array<x_index, x_index + offset>(lhs),
                        partition_array<y_index + offset, N>(lhs)
                    )
                )
            )
        );
    }

    template<size_t x_index, size_t y_index, class T, size_t N> constexpr
        array<T, N> array_swap_elements(const array<T, N>& lhs) {
        return _array_swap_elements<min(x_index, y_index), max(x_index, y_index)>(lhs);
    }

    template <uint8_t index>
    struct key {
        static constexpr auto _key = make_array({
            CompileTimeRandomNumber::RandomChar<__COUNTER__>::value
        });
        static constexpr uint8_t val = get<index % _key.size()>(_key);// ];	
    };

#define SBOX_SIZE 0x100

    template<size_t... I> constexpr
        array<size_t, sizeof...(I)> init_sbox(integer_sequence<size_t, I...>) {
        return{ { (I)... } };
    }

    constexpr decltype(auto) init_sbox() {
        return init_sbox(make_integer_sequence<size_t, SBOX_SIZE>());
    }

    template <size_t round>
    struct state {
        using prev = state<round - 1>;
#define select_elem(index)  get<index>(prev::sbox)

        static constexpr uint8_t j = ((prev::j + select_elem(round - 1) + key<round - 1>::val) % 0x100);
        static constexpr auto sbox = array_swap_elements<round - 1, j>(prev::sbox);
    };

    template <>
    struct state<0> {
        static constexpr auto sbox = init_sbox();
        static constexpr uint8_t val = get<0>(sbox);
        static constexpr uint8_t j = 0;
    };

#define INITIAL_ROUNDS 0x100

    using initial_state = state<INITIAL_ROUNDS>;

    template <size_t round>
    struct PRGA {
        using prev = PRGA<round - 1>;
#define select_elem(index)  get<index>(prev::sbox)
#define sce(index) get<index>(sbox)

        static constexpr uint8_t i = prev::i + 1;
        static constexpr uint8_t j = prev::j + select_elem(i);
        static constexpr auto sbox = array_swap_elements<i, j>(prev::sbox);
        static constexpr uint8_t val = sce((sce(i) + sce(j)) % 0x100);
    };

    template <>
    struct PRGA<0> {
        static constexpr auto sbox = initial_state::sbox;
        static constexpr uint8_t j = 0;
        static constexpr uint8_t i = 0;
    };

    template<size_t i>
    using prga_state = PRGA<i + 1>;

    template<size_t... I> constexpr
        array<uint8_t, sizeof...(I)> generate_rc4_material(index_sequence<I...>) {
        return { prga_state<I>::val... };
    }

    template<size_t N>
    constexpr decltype(auto) generate_rc4_material() {
        return generate_rc4_material(make_index_sequence<N>());
    }

    constexpr void ksa(unsigned char state[], unsigned char key[], int len) {
        int j = 0;

        for (int i = 0; i < 256; ++i)
            state[i] = i;
        for (int i = 0; i < INITIAL_ROUNDS; ++i) {
            j = (j + state[i] + key[i % len]) % 256;
            int t = state[i];
            state[i] = state[j];
            state[j] = t;
        }
    }

    constexpr void prga(unsigned char state[], unsigned char out[], int len) {
        int i = 0, j = 0;

        for (int x = 0; x < len; ++x) {
            i = (i + 1) % 256;
            j = (j + state[i]) % 256;
            int t = state[i];
            state[i] = state[j];
            state[j] = t;
            out[x] = state[(state[i] + state[j]) % 256];
        }
    }

    constexpr void rc4_crypt(unsigned char state[], const unsigned char in[], unsigned char out[], int len) {
        int i = 0, j = 0, x = 0;

        for (; x < len; ++x) {
            i = (i + 1) % 256;
            j = (j + state[i]) % 256;
            int t = state[i];
            state[i] = state[j];
            state[j] = t;
            out[x] = in[x] ^ (state[(state[i] + state[j]) % 256]);
        }
    }

    constexpr decltype(auto) get_init_prga() {
        return initial_state::sbox;
    }

    template<size_t... I, class T, size_t N> constexpr
        array<T, sizeof...(I)> do_xor(const array<T, N>& pt, const array<T, N>& prga, index_sequence<I...>) {
        return { static_cast<T>(get<I>(pt) ^ get<I>(prga))... };
    }

    template<typename T, size_t N> constexpr
        decltype(auto) encrypted_string(const array<T, N>& pt) {
        return do_xor(pt, generate_rc4_material<N>(), make_index_sequence<N>());
    }

    template <size_t N>
    constexpr array<uint8_t, N> decrypt_string(const array<unsigned char, N> cipherText) {
        array<uint8_t, N> decrypted;
        array<unsigned char, SBOX_SIZE> sbox;

        CompileTimeEncryption::ksa(sbox.data(), (unsigned char*)CompileTimeEncryption::key<0>::_key.data(), CompileTimeEncryption::key<0>::_key.size());
        CompileTimeEncryption::rc4_crypt(sbox.data(), cipherText.data(), decrypted.data(), N);

        return decrypted;
    }
}


#ifndef _DEBUG

#ifndef text
#define text(x) (std::string((char *) CompileTimeEncryption::decrypt_string(CompileTimeEncryption::encrypted_string(CompileTimeEncryption::convert_array<uint8_t>(CompileTimeEncryption::make_array(x)))).data()))
#endif

#else

#ifndef text
#define text(s) (std::string(s))
#endif

#endif