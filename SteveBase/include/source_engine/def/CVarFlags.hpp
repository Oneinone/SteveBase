#pragma once

namespace SteveBase::SourceEngine::Define {
    enum CVarFlags {
        None = 0, // Pure 0

        // Command to ConVars and ConCommands
        // ConVar Systems
        Unregistered = 1 << 0,	// If this is set, don't add to linked list, etc.
        DevelopmentOnly = 1 << 1,	// Hidden in released products. Flag is removed automatically if ALLOW_DEVELOPMENT_CVARS is defined.
        GameDLL = 1 << 2,	// defined by the game DLL
        ClientDLL = 1 << 3,  // defined by the client DLL
        Hidden = 1 << 4,	// Hidden. Doesn't appear in find or autocomplete. Like DEVELOPMENTONLY, but can't be compiled out.

        // ConVar only
        Protected = 1 << 5,  // It's a server cvar, but we don't send the data since it's a password, etc.  Sends 1 if it's not bland/zero, 0 otherwise as value
        SpOnly = 1 << 6,  // This cvar cannot be changed by clients connected to a multiplayer server.
        Archive = 1 << 7,	// set to cause it to be saved to vars.rc
        Notify = 1 << 8,	// notifies players when changed
        UserInfo = 1 << 9,	// changes the client's info string
        PrintableOnly = 1 << 10,  // This cvar's string cannot contain unprintable characters ( e.g., used for player name etc ).
        UnLogged = 1 << 11,  // If this is a _SERVER, don't log changes to the log file / console if we are creating a log
        NeverAsString = 1 << 12,  // never try to print that cvar
        Replicated = 1 << 13,	// server setting enforced on clients, TODO rename to FCAR_SERVER at some time
        Cheat = 1 << 14, // Only useable in singleplayer / debug / multiplayer & sv_cheats

        Empty1 = 1 << 15,

        // It's a ConVar that's shared between the client and the server.
        // At signon, the values of all such ConVars are sent from the server to the client (skipped for local
        //  client, of course )
        // If a change is requested it must come from the console (i.e., no remote client changes)
        // If a value is changed while a server is active, it's replicated to all connected clients

        Demo = 1 << 16,  // record this cvar when starting a demo file
        DoNotRecord = 1 << 17,  // don't record these command in demofiles

        Empty2 = 1 << 18,
        Empty3 = 1 << 19,

        ReloadMaterials = 1 << 20,	// If this cvar changes, it forces a material reload
        ReloadTextures = 1 << 21,	// If this cvar changes, if forces a texture reload

        NotConnected = 1 << 22,	// cvar cannot be changed by a client that is connected to a server
        MaterialSystemThread = 1 << 23,	// Indicates this cvar is read from the material system thread
        ArchiveXbox = 1 << 24, // cvar written to config.cfg on the Xbox

        AccessibleFromThreads = 1 << 25,	// used as a debugging tool necessary to check material system thread convars

        Empty4 = 1 << 26,
        Empty5 = 1 << 27,

        ServerCanExecute = 1 << 28,// the server is allowed to execute this command on clients via ClientCommand/NET_StringCmd/CBaseClientState::ProcessStringCmd.
        ServerCannotQuery = 1 << 29,// If this is set, then the server is not allowed to query this cvar's value (via IServerPluginHelpers::StartQueryCvarValue).
        ClientCommandCanExecute = 1 << 30,	// IVEngineClient::ClientCmd is allowed to execute this command. 
    };

}
