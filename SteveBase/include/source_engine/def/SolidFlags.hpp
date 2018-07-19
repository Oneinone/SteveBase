#pragma once

namespace SteveBase::SourceEngine::Define {
    enum SolidFlags {
        CustomRayTest = 0x0001,	// Ignore solid type + always call into the entity for ray tests
        CustomBoxTest = 0x0002,	// Ignore solid type + always call into the entity for swept box tests
        NotSolid = 0x0004,	// Are we currently not solid?
        Trigger = 0x0008,	// This is something may be collideable but fires touch functions
        NotStandable = 0x0010,	// You can't stand on this
        VolumeContents = 0x0020,	// Contains volumetric contents (like water)
        ForceWorldAligned = 0x0040,	// Forces the collision rep to be world-aligned even if it's SOLID_BSP or SOLID_VPHYSICS
        UseTriggerBounds = 0x0080,	// Uses a special trigger bounds separate from the normal OBB
        RootParentAligned = 0x0100,	// Collisions are defined in root parent's local coordinate space
        TriggerTouchDebris = 0x0200,	// This trigger will touch debris objects
        MaxBits = 10
    };
}