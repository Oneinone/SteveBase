#pragma once

namespace SteveBase::SourceEngine::Define {
    enum class Flow {
        Outgoing = 0,
        Incoming = 1,
        Max = 2
    };

    // https://github.com/LestaD/SourceEngine2007/blob/43a5c90a5ada1e69ca044595383be67f40b33c61/src_main/common/netmessages.h#L78
    enum class NetMessageGroup {
        Generic = 0,	// must be first and is default group
        LocalPlayer,	// bytes for local player entity update
        OtherPlayers,	// bytes for other players update
        Entities,		// all other entity bytes
        Sounds,			// game sounds
        Events,			// event messages
        TemporaryEntities,		// temp entities
        UserMessages,	// user messages
        EntityMessages,	// entity messages
        Voice,			// voice data
        StringTable,	// a stringtable update
        Move,			// client move cmds
        StringCommand,		// string command
        SignOn,			// various signondata
        TotalNumberOfMessageGroups,			// must be last and is not a real group
    };
}