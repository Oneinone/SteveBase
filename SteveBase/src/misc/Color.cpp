#include <GlobalDefines.hpp>
#include <misc/Color.hpp>

#include <d3d9.h>

#pragma warning(disable: 4244)

namespace SteveBase::Misc {
    Color::Color(float hue, float saturation, float brightness) {
        const auto h = hue == 1.0f ? 0 : hue * 6.0f;
        const auto f = h - (int)h;
        const auto p = brightness * (1.0f - saturation);
        const auto q = brightness * (1.0f - saturation * f);
        const auto t = brightness * (1.0f - saturation * (1.0f - f));

        if (h < 1) {
            // vtp
            R() = brightness * 255;
            G() = t * 255;
            B() = p * 255;

        } else if (h < 2) {
            // qvp
            R() = q * 255;
            G() = brightness * 255;
            B() = p * 255;
        } else if (h < 3) {
            // pvt
            R() = p * 255;
            G() = brightness * 255;
            B() = t * 255;
        } else if (h < 4) {
            // pqv
            R() = p * 255;
            G() = q * 255;
            B() = brightness * 255;
        } else if (h < 5) {
            // tpv
            R() = t * 255;
            G() = p * 255;
            B() = brightness * 255;
        } else {
            // vpq
            R() = brightness * 255;
            G() = p * 255;
            B() = q * 255;
        }
        A() = 255;
    }
    float Color::GetHue() {
        if (R() == G() && G() == B()) { // r = g = b
            return 0.0f;
        }

        const auto percentR = PercentageR();
        const auto percentG = PercentageG();
        const auto percentB = PercentageB();

        auto percentDelta = GetMaxMinDifference();
        auto hue = 0.0f;

        if (percentR == GetMax()) {
            hue = (percentG - percentB) / percentDelta;
        } else if (percentG == GetMax()) {
            hue = 2 + (percentB - percentR) / percentDelta;
        } else if (percentB == GetMax()) {
            hue = 4 + (percentR - percentG) / percentDelta;
        }
        hue *= 60;

        if (hue < 0.0f) {
            hue += 360.0f;
        }
        return hue;

    }

    float Color::GetSaturation() {
        auto percentDelta = GetMaxMinDifference() / 255.f;

        return percentDelta / (GetBrightness() <= 0.5f ? (GetMax() + GetMin()) / 255.f : (2 - percentDelta));

    }

    float Color::GetBrightness() {
        return (GetMax() + GetMin()) / 2;
    }

    D3DCOLOR Color::GetD3DColor() const {
        // ARGB
        struct {
            byte_t a, r, g, b;
        } argb = { m_a, m_r, m_g, m_b };
        return *(D3DCOLOR*)&argb;
    }

    bool Color::Equals(const Color &rhs) const {
        return
            m_r == rhs.m_r &&
            m_g == rhs.m_g &&
            m_b == rhs.m_b &&
            m_a == rhs.m_a;
    }
}
