#include <GlobalDefines.hpp>
#include <manager/PatternManager.hpp>

#include <misc/Macro.hpp>

#include <vendor/hash/hash.h>
#include <vendor/XorStr/XorStr.h>

namespace SteveBase::Manager {
    template<size_t N>
    constexpr FORCEINLINE PatternNamePatternOffsetPair MakePattern(const constexpr_hash_t hash, const char(&pat)[N], int offset = 0) {
        return { hash, { textdup(pat), offset } };
    }

    struct ScanModule {
        const char *name = nullptr;

        template<size_t N>
        constexpr FORCEINLINE ScanModule(const char(&name)[N]) {
            this->name = textdup(name);
        }

        ScanModuleEntry operator = (PatternList &&patternList) {
            return { name, patternList };
        }


    };

#define GenPattern(pat, ...) pat, __VA_ARGS__ )

#if DEBUG
    constexpr_hash_t PutReverHashTableEntry(constexpr_hash_t hash, std::string str);
#define Pattern(s) MakePattern( PutReverHashTableEntry(compile_time_hash(s), text(s)), GenPattern
#else
#define Pattern(s) MakePattern( compile_time_hash(s), GenPattern
#endif
    ScanModuleEntry patterns[] = {
        ScanModule("client.dll") = {
            Pattern("CalcPlayerView")("84 C0 75 08 57 8B CE E8 ? ? ? ? 8B 06"),
            Pattern("GameRules")("83 3D ? ? ? ? ? 75 0F 57", +2),
            Pattern("GlowManager")("A1 ? ? ? ? A8 01 75 4B", +1),
            Pattern("InitKeyValueEx")("55 8B EC 51 33 C0 C7 45"),
            Pattern("IsReady")("55 8B EC 83 E4 F8 83 EC 08 56 8B 35 ? ? ? ? 57 8B BE"),
            Pattern("LastOcclusionCheckTick")("8B B7 ? ? ? ? 89 75 F8 39 70 04", +2),
            Pattern("LoadFromBuffer")("55 8B EC 83 EC 48 53 56 57 8B F9 89 7D F4"),
            Pattern("MoveHelper")("8B 0D ? ? ? ? 8B 45 FC 51 8B D4", +2),
            Pattern("OcclusionCheckFlags")("83 8F ? ? ? ? ? 8D 4D DC", +2),
            Pattern("PlayerResource")("8B 3D ? ? ? ? 85 FF 0F 84 ? ? ? ? 81 C7", +2),
            Pattern("PredictionPlayer")("89 3D ? ? ? ? F3 0F 10 48 ?", +2),
            Pattern("PredictionRandomSeed")("8B 0D ? ? ? ? BA ? ? ? ? E8 ? ? ? ? 83 C4 04", +2),
            Pattern("RevealAll")("8B EC 8B 0D ? ? ? ? 68", -1),
            Pattern("TraceToExit")("55 8B EC 83 EC 30 F3 0F 10 75 ? 33 C0 F3 0F 10 6D ? 0F 57 DB F3 0F 10 65 ? 53 56 8B 75 20 8B DA 57 89 5D F0 8B F9 89 45 F4"),
            Pattern("ViewRenderBeams")("B9 ? ? ? ? A1 ? ? ? ? FF 10 A1 ? ? ? ? B9", +1),
            Pattern("WriteUserCmd")("55 8B EC 83 E4 F8 51 53 56 8B D9 8B 0D"),
            Pattern("g_nCachedScreenSize")("68 ? ? ? ? 68 ? ? ? ? 8B 01 FF 90 ? ? ? ? E8 ? ? ? ? C2 08 00", +6),
        },
        ScanModule("engine.dll") = {
            Pattern("ClientState")("8B 0D ? ? ? ? 68 ? ? ? ? 8D 49 08", +2),
            Pattern("ForceUpdate")("A1 ? ? ? ? B9 ? ? ? ? 56 FF 50 14 8B 34 85"),
            Pattern("GameEventManager")("B9 ? ? ? ? 57 FF 50 14 6A 40", +1),
            Pattern("Net_SetConVar")("8D 4C 24 1C E8 ? ? ? ? 56"),
            Pattern("SendClanTag")("53 56 57 8B DA 8B F9 FF 15"),
            Pattern("SendMove")("55 8B EC A1 ? ? ? ? 81 EC ? ? ? ? B9 ? ? ? ? 53 8B 98"),
        },
        ScanModule("shaderapidx9.dll") = {
            Pattern("D3D9")("A1 ? ? ? ? 50 8B 08 FF 51 0C", +1),
        },
        ScanModule("gameoverlayrenderer.dll") = {
            Pattern("OverlayPointer")("FF 15 ? ? ? ? 8B F8 85 DB 74 1F", +2)
        }
    };
}
