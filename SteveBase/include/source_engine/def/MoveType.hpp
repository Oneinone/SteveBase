#pragma once

namespace SteveBase::SourceEngine::Define {
    enum class MoveType {
        None = 0,	// never moves
        Isometric,			// For players -- in TF2 commander view, etc.
        Walk,				// Player only - moving on the ground
        Step,				// gravity, special edge handling -- monsters use this
        Fly,				// No gravity, but still collides with stuff
        FlyGravity,		// flies through the air + is affected by gravity
        VPhysics,			// uses VPHYSICS for simulation
        Push,				// no clip to world, push and crush
        Noclip,			// No gravity, no collisions, still do velocity/avelocity
        Ladder,			// Used by players only when going onto a ladder
        Observer,			// Observer movement, depends on player's observer mode
        Custom,			// Allows the entity to describe its own physics

        // should always be defined as the last item in the list
        Last = Custom,

        MaxBits = 4
    };
}