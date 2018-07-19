#pragma once

#include <string>

#include <misc/TypeAliases.hpp>

#include <vendor/hash/hash.h>

namespace SteveBase::Manager {
    using namespace Misc;

    using locale_t = std::string;
    using locale_hash_t = constexpr_hash_t;

    class I18NManager {
    public:
        static const char *GetLocale();
        static void SetLocale(const char *locale);

        static const SortedDictionary<locale_t, const char *> &GetTranslationProviders();

        static const char *Get(locale_hash_t index);
    };

#define i18n(_text) (I18NManager::Get(compile_time_hash(#_text)))
}