#pragma once

#include <cmath>

namespace SteveBase::Maths {
    class Math {
    public:
        // Given the formula c^2 = a^2 + b^2 and tuple (a, b), find c
        template <class T>
        constexpr static T Pythagoras(T a, T b) {
            // i bet everyone knows it...
            return std::sqrt(a * a + b * b);
        }

        // Given c^2 = a^2 + b^2 and tuple (c, a), find b
        // should work for a as well if the argument becomes (c, b)
        template <class T>
        constexpr static T PythagorasConverse(T c, T a) {
            return std::sqrt(c * c - a * a);
        }

        template <class T>
        constexpr static T Square(T x) {
            return x * x;
        }

        template <class T>
        constexpr static T Cube(T x) {
            return x * x * x;
        }
    };
}
