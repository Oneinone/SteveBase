#include <GlobalDefines.hpp>
#include <manager/FontManager.hpp>

#include <Interface.hpp>
#include <assets/Fonts.hpp>
#include <source_engine/def/EFontFlags.hpp>
#include <source_engine/virtual/ISurface.hpp>

#include <windows.h>

namespace SteveBase::Manager {
    using namespace Assets;
    using namespace SourceEngine::Define;
    using namespace SourceEngine::Virtual;

    bool m_fontManagerInitialized = false;

    void FontManager::Init() {
        ResetFont();

        m_fontManagerInitialized = true;
    }

    void FontManager::ResetFont() {
        SetFont<Fonts::CSWeaponFont::Small>(Fonts::CSWeaponFont::Small::GetOffset());
        SetFont<Fonts::CSWeaponFont::Big>(Fonts::CSWeaponFont::Big::GetOffset());

        SetFont<Fonts::ESP::Small>(Get<ISurface>()->CreateFontAndSetGlyph(
            Fonts::ESP::GetFontFamily().c_str(), Fonts::ESP::Small::GetSize(), FW_NORMAL, 0, 0, EFontFlags::DropShadow
        ));

        SetFont<Fonts::ESP::Regular>(Get<ISurface>()->CreateFontAndSetGlyph(
            Fonts::ESP::GetFontFamily().c_str(), Fonts::ESP::Regular::GetSize(), FW_NORMAL, 0, 0, EFontFlags::DropShadow
        ));

        SetFont<Fonts::ESP::Big>(Get<ISurface>()->CreateFontAndSetGlyph(
            Fonts::ESP::GetFontFamily().c_str(), Fonts::ESP::Big::GetSize(), FW_NORMAL, 0, 0, EFontFlags::DropShadow
        ));

        SetFont<Fonts::ESP::ExtraLarge>(Get<ISurface>()->CreateFontAndSetGlyph(
            Fonts::ESP::GetFontFamily().c_str(), Fonts::ESP::ExtraLarge::GetSize(), FW_NORMAL, 0, 0, EFontFlags::DropShadow
        ));

        SetFont<Fonts::ESP>(GetFont<Fonts::ESP::Regular>());
    }

    bool FontManager::IsInitialized() {
        return m_fontManagerInitialized;
    }

    SortedDictionary<constexpr_hash_t, HFont> fontContainer;

    HFont FontManager::GetFontImpl(const constexpr_hash_t hash) {
        return fontContainer[hash];
    }

    void FontManager::SetFontImpl(const constexpr_hash_t hash, HFont font) {
        fontContainer[hash] = font;
    }
}
