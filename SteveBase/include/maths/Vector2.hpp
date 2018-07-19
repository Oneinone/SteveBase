#pragma once

namespace SteveBase::Maths {
    class Vector2 {
        float m_x;
        float m_y;

    public:
        Vector2(float x = 0.0f, float y = 0.0f) {
            m_x = x;
            m_y = y;
        }

        float &X() {
            return m_x;
        }
        float &Y() {
            return m_y;
        }
    };
}