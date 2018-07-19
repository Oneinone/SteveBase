#pragma once

#define NOMINMAX

#include <d3d9.h>
#include <cstdint>
#include <algorithm>

namespace SteveBase::Misc {

    using byte_t = uint8_t;

    class Color {
        byte_t m_r;
        byte_t m_g;
        byte_t m_b;
        byte_t m_a; // RGBA

    public:
        Color(byte_t r = 0, byte_t g = 0, byte_t b = 0, byte_t a = 255) {
            R() = r;
            G() = g;
            B() = b;
            A() = a;
        }

        Color(float hue, float saturation, float brightness);

        byte_t &R() {
            return m_r;
        }
        byte_t &G() {
            return m_g;
        }
        byte_t &B() {
            return m_b;
        }
        byte_t &A() {
            return m_a;
        }

        float PercentageR() const {
            return m_r / 255.0f;
        }
        float PercentageG() const {
            return m_g / 255.0f;
        }
        float PercentageB() const {
            return m_b / 255.0f;
        }
        float PercentageA() const {
            return m_a / 255.0f;
        }

        float GetMax() {
            return std::max({ R(), G(), B() });
        }

        float GetMin() {
            return std::min({ R(), G(), B() });
        }

        float GetMaxMinDifference() {
            return GetMax() - GetMin();
        }

        float GetHue();
        float GetSaturation();
        float GetBrightness();
        float GetLuminosity() { // because fuck physics
            return GetBrightness();
        }

        D3DCOLOR GetD3DColor() const;

        uint32_t GetIntegerizedColor() {
            return *(uint32_t*)this;
        }

        bool Equals(const Color &rhs) const;

        bool operator ==(const Color &rhs) const {
            return Equals(rhs);
        }

        bool operator !=(const Color &rhs) const {
            return !Equals(rhs);
        }
    };
}
