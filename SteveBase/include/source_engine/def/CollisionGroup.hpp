#pragma once

namespace SteveBase::SourceEngine::Define {
    enum class CollisionGroup {
        None = 0,
        Debris,                // Collides with nothing but world and static stuff
        DebrisTrigger,         // Same as debris, but hits triggers
        InteractiveDebris,     // Collides with everything except other interactive debris or debris
        Interactive,           // Collides with everything except interactive debris or debris
        Player,
        BreakableGlass,
        Vehicle,
        PlayerMovement,        // For HL2, same as Player, for
                               // TF2, this filters out other players and CBaseObjects
        Npc,                   // Generic NPC group
        InVehicle,             // for any entity inside a vehicle
        Weapon,                // for any weapons that need collision detection
        VehicleClip,           // vehicle clip brush to restrict vehicle movement
        Projectile,            // Projectiles!
        DoorBlocker,           // Blocks entities not permitted to get near moving doors
        PassableDoor,          // Doors that the player shouldn't collide with
        Dissolving,            // Things that are dissolving are in this group
        PushAway,              // Nonsolid on client and server, pushaway in player code

        NpcActor,              // Used so NPCs in scripts ignore the player.
        NpcScripted,           // USed for NPCs in scripts that should not collide with each other
        PZClip,
        DebrisBlockProjectile, // Only collides with bullets
        TotalNumberOfCollisionGroups,
    };
}
