#pragma once

#include <maths/Vector2.hpp>

namespace SteveBase::SourceEngine::Structure {
    using namespace Maths;

    struct FontVertex {
        Vector2 m_Position;
        Vector2 m_TexCoord;

        FontVertex() {}
        FontVertex(Vector2 &pos, Vector2 &coord = Vector2(0, 0)) {
            m_Position = pos;
            m_TexCoord = coord;
        }
        void Init(Vector2 &pos, Vector2 &coord = Vector2(0, 0)) {
            m_Position = pos;
            m_TexCoord = coord;
        }
    };
}