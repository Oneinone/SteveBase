#pragma once

#include <string>

#include <source_engine/def/_EngineTypes.hpp>
#include <vendor/XorStr/XorStr.h>

namespace SteveBase::Assets {
    using namespace SourceEngine::Define;

    struct Fonts {
        struct ESP {
            static std::string GetFontFamily() { return textpp("Verdana Bold"); }

            struct Small {
                constexpr static int GetSize() { return 10; }
            };
            struct Regular {
                constexpr static int GetSize() { return 12; }
            };
            struct Big {
                constexpr static int GetSize() { return 15; }
            };
            struct ExtraLarge {
                constexpr static int GetSize() { return 18; }
            };
        };
        struct CSWeaponFont {
            struct Small {
                constexpr static HFont GetOffset() { return 0xA0;}
            };
            struct Big {
                constexpr static HFont GetOffset() { return 0xA1; }
            };
        };
    };
}
