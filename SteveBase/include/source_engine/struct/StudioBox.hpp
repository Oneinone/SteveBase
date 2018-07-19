#pragma once

#include <string_view>
#include <maths/Vector3.hpp>

namespace SteveBase::SourceEngine::Sturcture {
    using namespace Maths;

    struct StudioModelBoundaryBox {
        int		bone;
        int		group; // intersection group
        Vector3	bbmin; // bounding box 
        Vector3	bbmax;
        int		hitboxnameindex; // offset to the name of the hitbox.
        int		pad[3];
        float	radius;
        int		pad2[4];

        std::string_view GetHitboxName() {
            return hitboxnameindex != 0 ? (char*)this + hitboxnameindex : "";
        }
    };
}

