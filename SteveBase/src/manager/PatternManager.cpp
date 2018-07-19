#include <GlobalDefines.hpp>
#include <manager/PatternManager.hpp>

#include <utility/SystemUtility.hpp>
#include <misc/TypeAliases.hpp>
#include <vendor/hash/hash.h>

#if DEBUG
#include <utility/Logger.hpp>
#endif

#include <windows.h>

#if DEBUG
#include <string>
#endif

namespace SteveBase::Manager {
    using namespace Utility;
    using namespace Misc;

#if DEBUG
    SortedDictionary<constexpr_hash_t, std::string> reverseHashTableForPatterns;

    constexpr_hash_t PutReverHashTableEntry(constexpr_hash_t hash, std::string str) {
        reverseHashTableForPatterns[hash] = str;
        return hash;
    }
#endif

    extern ScanModuleEntry patterns[4];

    SortedDictionary<constexpr_hash_t, void *> resolvedPattern;

    void *PatternManager::GetPatternImpl(constexpr_hash_t hash) {
        return resolvedPattern[hash];
    }

    void *PatternManager::GetPatternDynamically(const char *dllName, const char *pattern) {
        const auto hash = run_time_hash(dllName) * run_time_hash(pattern);
        if (GetPatternImpl(hash) == nullptr) {
            const auto pat = SystemUtility::FindModulePattern(dllName, pattern);
            resolvedPattern[hash] = (void *)pat;
        }
        return GetPatternImpl(hash);
    }

    void PatternManager::Init() {
        for (auto &it1 : patterns) {
            const auto dllName = it1.first;
            const auto dllHash = run_time_hash(dllName);

            for (auto &it2 : it1.second) {
                const constexpr_hash_t &nameHash = it2.first;
                const char *pattern = it2.second.first;
                const int &offset = it2.second.second;
                const auto key = dllHash * nameHash;
                const auto result = SystemUtility::FindModulePattern(dllName, pattern);

                if (result) {
                    resolvedPattern[key] = (void *)(result + offset);
#if DEBUG
                    LoggerDebug(R"(Pattern Found, From "{0}", Named {1}, Address Is 0x{x}...)", dllName, reverseHashTableForPatterns[nameHash].data(), (uintptr_t)resolvedPattern[key]);
#endif
                } else {
#if DEBUG
                    LoggerDebug(R"(Pattern Not Found, From "{0}", Named {1})", dllName, reverseHashTableForPatterns[nameHash].data());
#endif
                }

                free((void *)pattern);
            }

            free((void *)dllName);
        }
        SecureZeroMemory(&patterns, sizeof patterns); // BURN
    }
}
