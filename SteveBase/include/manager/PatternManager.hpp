#pragma once

#include <misc/TypeAliases.hpp>

#include <vendor/hash/hash.h>

namespace SteveBase::Manager {
    using namespace Misc;

    class PatternManager {
    public:
        static void Init();

        static void *GetPatternImpl(constexpr_hash_t hash);
        static void *GetPatternDynamically(const char *dllName, const char *pattern);
    };

    using PatternOffsetPair = Pair<const char *, int>;
    using PatternNamePatternOffsetPair = Pair<constexpr_hash_t, PatternOffsetPair>;
    using PatternList = List<PatternNamePatternOffsetPair>;
    using ScanModuleEntry = Pair<const char *, PatternList>;

#define GenGetPattern(patternName) compile_time_hash(patternName))
#define GetPattern(dllName) SteveBase::Manager::PatternManager::GetPatternImpl(compile_time_hash(dllName) * GenGetPattern
}