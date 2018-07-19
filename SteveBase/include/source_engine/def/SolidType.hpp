#pragma once

#include "SolidFlags.hpp"

namespace SteveBase::SourceEngine::Define {

    // edict->solid values
    // NOTE: Some movetypes will cause collisions independent of SOLID_NOT/SOLID_TRIGGER when the entity moves
    // SOLID only effects OTHER entities colliding with this one when they move - UGH!

    // Solid type basically describes how the bounding volume of the object is represented
    // NOTE: SOLID_BBOX MUST BE 2, and SOLID_VPHYSICS MUST BE 6
    // NOTE: These numerical values are used in the FGD by the prop code (see prop_dynamic)

    enum class SolidType {
        None = 0,	// no  model
        Bsp = 1,	// a BSP tree
        Bbox = 2,	// an AABB
        Obb = 3,	// an OBB (not implemented yet)
        ObbYaw = 4,	// an OBB, constrained so that it can only yaw
        Custom = 5,	// Always call into the entity for tests
        VPhysics = 6,	//  vphysics object, get vcollide from the model and collide with that
        Last,
    };

    inline bool IsSolid(SolidType solidType, int nSolidFlags) {
        return solidType != SolidType::None && (nSolidFlags & SolidFlags::NotSolid) == 0;
    }
}