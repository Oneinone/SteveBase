#pragma once

#include <source_engine/def/_EngineTypes.hpp>

#include <vendor/hash/hash.h>

namespace SteveBase::Manager {
    using namespace SourceEngine::Define;

    class FontManager {
    public:
        static void Init();
        static void ResetFont();
        
        static bool IsInitialized();

        static HFont GetFontImpl(constexpr_hash_t hash);
        static void SetFontImpl(constexpr_hash_t hash, HFont font);

        template<class T>
        constexpr static HFont GetFont() {
            return GetFontImpl(MakeTypeHash<T>());
        }

        template<class T>
        constexpr static void SetFont(const HFont font) {
            SetFontImpl(MakeTypeHash<T>(), font);
        }
    };

}