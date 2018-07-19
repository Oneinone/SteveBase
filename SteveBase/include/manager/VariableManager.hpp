#pragma once

#include <string>
#include <limits>
#include <type_traits>

#include <misc/TemplateMetaprogramming.hpp>
#include <misc/TypeAliases.hpp>
#include <misc/IJsonSerializable.hpp>

#include <vendor/ggformat/ggformat.h>

#if RELEASE
#include <vendor/hash/hash.h>
#endif

namespace SteveBase::Manager {
    using namespace Misc;

    struct Variable : IJsonSerializable<Variable> {
        union {
            bool m_blValue;
            uint8_t m_i8Value;
            uint16_t m_i16Value;
            uint32_t m_i32Value;
            uint64_t m_i64Value;
            float_t m_fValue;
            double_t m_dbValue;
        };

    public:

        template<class T>
        constexpr T &Get() {
            static_assert(std::numeric_limits<T>::is_specialized, "T is not a numeric type");
            static_assert(!std::is_same<T, char>(), "char is not allowed");

            if constexpr (std::is_same<T, bool>()) {
                return (T &)m_blValue;
            } else if constexpr (IsEightBit<T>()) {
                return (T &)m_i8Value;
            } else if constexpr (IsSixteenBit<T>()) {
                return (T &)m_i16Value;
            } else if constexpr (IsThirtyTwoBit<T>()) {
                return (T &)m_i32Value;
            } else if constexpr (IsSixtyFourBit<T>()) {
                return (T &)m_i64Value;
            } else if constexpr (IsFloat<T>()) {
                return (T &)m_fValue;
            } else if constexpr (IsDouble<T>()) {
                return (T &)m_dbValue;
            }
        }

    public:
        void to_json(nlohmann::json& j) {
            j = ggformat_to_string(text("{x}"), m_i64Value);
        }

        void from_json(nlohmann::json& j) {
            this->Get<uint64_t>() = stoull(j.get<std::string>(), nullptr, 16);
        }
    };

#define STORE_FULL_VAR (DEBUG || SIMULATOR)

#if STORE_FULL_VAR
    using VariableMap = SortedDictionary<std::string, Variable>; // alphabetically sorted map
#else
    using VariableMap = SortedDictionary<constexpr_hash_t, Variable>; // hash map
#endif

    using VariableKey = VariableMap::key_type;

    class VariableManager {
    public:
        static void Init();

        static Variable &GetVariable(VariableKey hash);

        static VariableMap &GetCurrentSettingVariables();

        static std::string ToConfig();
        static void FromConfig(std::ifstream &stream);
        static void SaveConfig();
        static bool LoadConfig();

        static const char *GetCurrentSettingName();
        static List<std::string> GetAllSettingsName();
        static bool DidSettingExist(const char *name);

        static void NewSetting(const char *name);
        static void LoadSetting(const char *name);
        static void SaveAllSettings();

        static void RenameCurrentSettingAs(const char *name);
        static void DuplicateCurrentSettingAs(const char *name);
        static void SetDefaultSetting(const char *name);
        static const char *GetDefaultSetting();

        static void RemoveCurrentSettingAndRestoreToDefault();
    };

#if STORE_FULL_VAR
#define VarValuelize(s) text(#s)
#else
#define VarValuelize(s) compile_time_hash(#s)
#endif

#define DynamicVariable(var) (VariableManager::GetVariable(VarValuelize(var)))
}

#if STORE_FULL_VAR == 0
namespace nlohmann {
    using namespace SteveBase::Manager;

    template<>
    struct adl_serializer<VariableMap> {

        static void to_json(json& j, const VariableMap &value) {
            for (auto &it : value) {
                j[ggformat_to_string(text("{x}"), it.first)] = it.second;
            }
        }

        static void from_json(const json& j, VariableMap &value) {
            for (auto it = j.begin(); it != j.end(); ++it) {
                value[stoul(it.key(), nullptr, 16)] = it.value();
            }
        }
    };
}
#endif