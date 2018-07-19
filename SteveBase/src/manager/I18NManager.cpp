#include <GlobalDefines.hpp>
#include <manager/I18NManager.hpp>

#include <misc/DataStructure.hpp>
#include <vendor/XorStr/XorStr.h>

namespace SteveBase::Manager {
    using namespace Misc;

#define BeginTranslation(localeName, readableName) { (m_localeProvider[text(#localeName)] = textdup(readableName), textdup(#localeName)), {
#define EndTranslation() } },
#define Translation(name, translation) { compile_time_hash(#name), textdup(translation)  },

    namespace {
        locale_t m_currentLocale = text("en_us");

        SortedDictionary<locale_t, const char *> m_localeProvider;

        SortedDictionary<locale_t, SortedDictionary<constexpr_hash_t, const char *>> m_locale{
    #include "translations/en_us.inc"
    #include "translations/zh_hk.inc"
        };
    }

    const char *I18NManager::GetLocale() {
        return m_currentLocale.c_str();
    }

    void I18NManager::SetLocale(const char *locale) {
        m_currentLocale = locale;
    }

    const SortedDictionary<locale_t, const char *> &I18NManager::GetTranslationProviders() {
        return m_localeProvider;
    }

    const char *I18NManager::Get(const locale_hash_t index) {
        auto &locale = m_locale[m_currentLocale];
        if (locale.find(index) != locale.end()) { // if the locale contains the translation for index
            return locale[index];  // return it
        }
        // otherwise by default, we return the translation from english locale 
        return m_locale[text("en_us")][index];
    }
}
