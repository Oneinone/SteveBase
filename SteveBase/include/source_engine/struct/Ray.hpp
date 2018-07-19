#pragma once

#include <maths/Vector4.hpp>

namespace SteveBase::SourceEngine::Structure {
    using namespace Maths;

    struct Ray {
        Vector4  m_Start;
        Vector4  m_Delta;
        Vector4  m_StartOffset;
        Vector4  m_Extents;
        bool m_IsRay;
        bool m_IsSwept;

        Ray() {

        }

        Ray(Vector3& start, Vector3& end) {
            Init(start, end);
        }

        void Init(Vector3& start, Vector3& end) {
            m_Start = start;
            m_Delta = end - start;
            m_StartOffset.Init();
            m_Extents.Init();
            m_IsRay = true;
            m_IsSwept = (m_Delta.Area() != 0);
        }
    };
}