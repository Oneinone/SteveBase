#include <GlobalDefines.hpp>
#include <manager/VariableManager.hpp>

#include <manager/I18NManager.hpp>
#include <utility/GameUtility.hpp>
#include <utility/Logger.hpp>
#include <misc/Macro.hpp>
#include <misc/ZLib.hpp>

#include <vendor/hash/hash.h>
#include <vendor/XorStr/XorStr.h>
#include <vendor/nlohmann/json.hpp>

#include <string>
#include <fstream>

namespace SteveBase::Manager {
    using namespace Utility;

    namespace {
        SortedDictionary<std::string, VariableMap> m_vars;

        std::string m_currentSetting = text("Default");
        std::string m_defaultSetting = text("Default");
    }

    void VariableManager::Init() {
        I18NManager::SetLocale(text("en_us"));

        GameUtility::SetHackConfigLocation(GameUtility::GetHackDirectory() + textpp("config.json"));

        DynamicVariable(Show Header).Get<bool>() = true;
        try {
            LoadConfig();
            LoggerNotice("Config loaded.");
        } catch (...) {
            LoggerNotice("Config loading failed. Possibly lost, corrupted or not created.");
            SaveConfig();
        }
    }

    Variable &VariableManager::GetVariable(const VariableKey key) {
        return m_vars[m_currentSetting][key];
    }

    VariableMap &VariableManager::GetCurrentSettingVariables() {
        return m_vars[m_currentSetting];
    }

    std::string VariableManager::ToConfig() {
        nlohmann::json j {
            { text("default"), m_defaultSetting },
            { text("language"), I18NManager::GetLocale() },
            { text("settings"), m_vars }
        };

#if STORE_FULL_VAR
        return j.dump(2);
#else
        return j.dump();
#endif
    }

    void VariableManager::FromConfig(std::ifstream &stream) {
        nlohmann::json j;
        stream >> j;

        const auto _default = j[text("default")].get<std::string>();
        const auto language = j[text("language")].get<locale_t>();
        const auto settings = j[text("settings")].get<SortedDictionary<std::string, VariableMap>>();

        m_defaultSetting = m_currentSetting = _default.c_str();
        I18NManager::SetLocale(language.c_str());
        m_vars = settings;
    }

    void VariableManager::SaveConfig() {
        FILE *fp;
        fopen_s(&fp, GameUtility::GetHackConfigLocation().c_str(), "w+");

        if (fp != nullptr) {
            defer(fclose(fp));
            
            const auto out = ToConfig();
            fwrite(out.c_str(), sizeof(char), out.length(), fp);

            LoggerNotice("Config Saved");
        }
    }

    bool VariableManager::LoadConfig() {
        std::ifstream file(GameUtility::GetHackConfigLocation());

        if (file.is_open()) {
            FromConfig(file);
            return true;
        }

        return false;
    }

    const char *VariableManager::GetCurrentSettingName() {
        return m_currentSetting.c_str();
    }

    List<std::string> VariableManager::GetAllSettingsName() {
        List<std::string> list;
        for (auto &it : m_vars) {
            list.push_back(it.first);
        }
        return list;
    }

    bool VariableManager::DidSettingExist(const char *name) {
        return m_vars.find(name) != m_vars.end();
    }

    void VariableManager::NewSetting(const char *name) {
        LoadSetting(name);

        SaveAllSettings();
    }

    void VariableManager::LoadSetting(const char *name) {
        m_currentSetting = name;
    }

    void VariableManager::SaveAllSettings() {
        // TODO: current implementation is to save everything, every fucking thing
        SaveConfig();
    }

    void VariableManager::RenameCurrentSettingAs(const char *name) {
        // TODO: optimize this cancerous code below by swapping key
        m_vars[name] = m_vars[m_currentSetting]; // default copy constructor
        m_vars.erase(m_currentSetting); // delete the old setting
        LoadSetting(name); // load that new setting
        // so this is why its cancerous

        SaveAllSettings();
    }

    void VariableManager::DuplicateCurrentSettingAs(const char *name) {
        m_vars[name] = m_vars[m_currentSetting]; // default copy constructor
        LoadSetting(name); // load the duplicated setting

        SaveAllSettings();
    }

    void VariableManager::SetDefaultSetting(const char *name) {
        m_defaultSetting = name;

        SaveAllSettings();
    }

    const char *VariableManager::GetDefaultSetting() {
        return m_defaultSetting.c_str();
    }

    void VariableManager::RemoveCurrentSettingAndRestoreToDefault() {
        m_vars.erase(m_currentSetting); // delete current setting
        LoadSetting(text("Default")); // Default is never deleted so its a guarantee hit

        SaveAllSettings();
    }
}
