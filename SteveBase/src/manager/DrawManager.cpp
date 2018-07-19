#include <GlobalDefines.hpp>
#include <manager/DrawManager.hpp>

#include <manager/I18NManager.hpp>
#include <manager/PatternManager.hpp>
#include <manager/StateManager.hpp>
#include <manager/VariableManager.hpp>
#include <misc/DataStructure.hpp>
#include <misc/Macro.hpp>
#include <utility/GameUtility.hpp>
#include <utility/PowerDraw.hpp>

#include <vendor/hash/hash.h>
#include <vendor/imgui/imgui_extension.h>
#include <vendor/XorStr/XorStr.h>

#if DEBUG
#include <utility/Logger.hpp>
#endif

#include <functional>

namespace SteveBase::Manager {
    using namespace Utility;

    namespace {
        bool m_isInitalized = false;

        const char *m_dialog = "";
        std::function<void()> m_callsite;
        char m_dialogTextBuf[256] = { 0 };

        FORCEINLINE void ClearDialogTextBuf() {
            // so ghetto
            memset(m_dialogTextBuf, 0, sizeof m_dialogTextBuf);
            ImGui::CloseCurrentPopup();
        }

        int m_activeTab = 0;
#if SIMULATOR
        float fl = 0.0f;
#endif
    }


    struct Modal {
        struct Show {
            FORCEINLINE Show(std::function<void()> fn, const char *name) {
                m_callsite = fn;
                m_dialog = name;
            }
        };
    };

    using TabEntry = std::pair<LazyEvaluated<const char *>, Action<>>;

    // TODO: Change this to use VDOM instead
    const TabEntry tabs[] = {
        { lazy(i18n(esp.player)), []() {
            
            PowerDraw::Column { []() {
                PowerDraw::CheckBox{ i18n(esp.player.showhealth), DynamicVariable(esp.player.showhealth).Get<bool>() };
                PowerDraw::Column::Next {};
                PowerDraw::CheckBox{ i18n(esp.player.showarmor), DynamicVariable(esp.player.showarmor).Get<bool>() };
            }, 2 };

            PowerDraw::Column { []() {
                PowerDraw::CheckBox{ i18n(esp.player.showmoney), DynamicVariable(esp.player.showmoney).Get<bool>() };
                PowerDraw::Column::Next{};
                PowerDraw::CheckBox{ i18n(esp.player.showweapon), DynamicVariable(esp.player.showweapon).Get<bool>() };
            }, 2 };

            PowerDraw::Column { []() {
                PowerDraw::CheckBox{ i18n(esp.player.showclips), DynamicVariable(esp.player.showclips).Get<bool>() };
                PowerDraw::Column::Next{};
                PowerDraw::CheckBox{ i18n(esp.player.drawbox), DynamicVariable(esp.player.drawbox).Get<bool>() };
            }, 2 };
            
            PowerDraw::Column { []() {
                PowerDraw::CheckBox{ i18n(esp.player.showradarspotted), DynamicVariable(esp.player.showradarspotted).Get<bool>() };
                PowerDraw::Column::Next{};
                PowerDraw::CheckBox{ i18n(esp.player.drawglow), DynamicVariable(esp.player.drawglow).Get<bool>() };
            }, 2 };
            
        } },

        { lazy(i18n(esp.world)), []() {
            
            PowerDraw::Column { []() {
                PowerDraw::CheckBox{ text("C4 Timer"), DynamicVariable(esp.world.c4timer).Get<bool>() };
                PowerDraw::Column::Next{};
                PowerDraw::CheckBox{ text("Ground Weapons"), DynamicVariable(esp.world.groundweapons).Get<bool>() };
            }, 2 };
            
            PowerDraw::Column { []() {
                PowerDraw::CheckBox{ text("Grenades"), DynamicVariable(esp.world.grenades).Get<bool>() };
                PowerDraw::Column::Next{};
                PowerDraw::CheckBox{ text("Planted C4"), DynamicVariable(esp.world.plantedc4).Get<bool>() };
            }, 2 };
        } },

        { lazy(i18n(misc)), []() {
            PowerDraw::Column { []() {
                PowerDraw::CheckBox(text("Bunny Hop"), DynamicVariable(misc.bunnyhop).Get<bool>());
                PowerDraw::Column::Next{};
                PowerDraw::CheckBox(text("Auto Strafe"), DynamicVariable(misc.autostrafe).Get<bool>());
            }, 2 };

            PowerDraw::Column { []() {
                PowerDraw::CheckBox(text("Show Ranks"), DynamicVariable(misc.showranks).Get<bool>());
                PowerDraw::Column::Next{};
                PowerDraw::CheckBox(text("No Flash"), DynamicVariable(misc.noflash).Get<bool>());
            }, 2 };

            PowerDraw::Column { []() {
                PowerDraw::CheckBox(text("Auto Pistol"), DynamicVariable(misc.autopistol).Get<bool>());
                PowerDraw::Column::Next{};
                PowerDraw::CheckBox(text("Show Header"), DynamicVariable(misc.showheader).Get<bool>());
            }, 2 };

            PowerDraw::Column { []() {
                PowerDraw::CheckBox(text("Auto MM Accept"), DynamicVariable(misc.autommaccept).Get<bool>());
                PowerDraw::Column::Next{};
                PowerDraw::CheckBox(text("Draw Banner"), DynamicVariable(misc.drawbanner).Get<bool>());
            }, 2 };

            PowerDraw::Column{ []() {
                PowerDraw::CheckBox(text("Draw Debug Information"), DynamicVariable(misc.drawdebuginfo).Get<bool>());
            }, 2 };
        } },

#if SIMULATOR
        { []()->const char * { static const char *str = textdup("Skin Changer"); return str; }, []() {
            PowerDraw::StyleVar { []() {
            PowerDraw::Child { []() {
                static int selectedCell = -1;
                static List<const char *> l = { textdup("test"), textdup("abcd"), textdup("1234") };

                PowerDraw::ChoiceBox { [](int n, const char *item) {

                ggprint("{0}", item);
                if (item == "test" || item == "abcd") {
                    return true;
                }
                return false;
                }, l, selectedCell };
            }, "Sub2", ImVec2(150, 0), true };
            }, ImGuiStyleVar_ChildWindowRounding, 5.0f };
        } },
#endif

        { lazy(i18n(credits)), []() {
            PowerDraw::Column {[]() {
                PowerDraw::Text(text("Made by stevefan1999 @UC"));
                PowerDraw::Text(text("Special thanks: (@UC) "));
                PowerDraw::Text(text("  @MarkHC"));
                PowerDraw::Text(text("  @team_gamer_food"));
                PowerDraw::Text(text("  @gir489"));
                PowerDraw::Text(text("  @casual_hacker"));
                PowerDraw::Text(text("  @FuckFace32"));
                PowerDraw::Text(text("And you of course!"));
            }, 1 };
        } }
    };

    constexpr void MakeCloseButton(bool &ret) {
        PowerDraw::Button{ [&]() {
            // do nothing
            ret = false;
            ImGui::CloseCurrentPopup();
        }, text("Close") };
    }

    const SortedDictionary<const char *, Func<bool()>> modals{
        { textdup("New Setting"), []() {
            bool ret = true;
            PowerDraw::Text(text("Name: ")); ImGui::SameLine(); ImGui::InputText("", m_dialogTextBuf, 256);
            PowerDraw::Separator {};
            MakeCloseButton(ret);

            ImGui::SameLine();

            PowerDraw::Button { [&]() {
                if (strlen(m_dialogTextBuf) < 0 || VariableManager::DidSettingExist(m_dialogTextBuf)) {
                    // TODO: render denial modal
                } else {
                    VariableManager::NewSetting(m_dialogTextBuf);
                    ClearDialogTextBuf();
                    ret = false;
                }
            }, text("Submit") };

            return ret;
        } },
        { textdup("Rename Setting As"), []() {
            bool ret = true;
            PowerDraw::Text(text("Name: ")); ImGui::SameLine(); ImGui::InputText("", m_dialogTextBuf, 256);
            PowerDraw::Separator{};
            MakeCloseButton(ret);
            ImGui::SameLine();

            PowerDraw::Button { [&]() {
                if (strlen(m_dialogTextBuf) < 0 || VariableManager::DidSettingExist(m_dialogTextBuf)) {
                    // TODO: render denial modal
                } else {
                    VariableManager::RenameCurrentSettingAs(m_dialogTextBuf);
                    ClearDialogTextBuf();
                    ret = false;
                }
            }, text("Submit") };

            return ret;
        } },
        { textdup("Duplicate Setting As"), []() {
            bool ret = true;
            PowerDraw::Text(text("Name: ")); ImGui::SameLine(); ImGui::InputText("", m_dialogTextBuf, sizeof m_dialogTextBuf);
            PowerDraw::Separator{};
            MakeCloseButton(ret);
            ImGui::SameLine();

            PowerDraw::Button { [&]() {
                if (strlen(m_dialogTextBuf) < 0 || VariableManager::DidSettingExist(m_dialogTextBuf)) {
                    // TODO: render denial modal
                } else {
                    VariableManager::DuplicateCurrentSettingAs(m_dialogTextBuf);
                    ClearDialogTextBuf();
                    ret = false;
                }
            }, text("Submit") };

            return ret;
        } },
        { textdup("Remove Setting"), []() {
            bool ret = true;
            PowerDraw::Text { ggformat_to_string(text("Are you sure to remove {0}?"), VariableManager::GetCurrentSettingName()).c_str() };
            PowerDraw::Separator{};
            MakeCloseButton(ret);

            PowerDraw::Button { [&]() {
                // do nothing
                VariableManager::RemoveCurrentSettingAndRestoreToDefault();
                ret = false;
            }, text("Yes"), { 120, 0 } };

            ImGui::SameLine();

            return ret;
        } },
    };

    using MenuEntry = std::pair<LazyEvaluated<const char *>, Action<>>;

    const MenuEntry menuBars[] = {
        { lazy(i18n(menu.setting)), []() {
            auto currentSetting = VariableManager::GetCurrentSettingName();

            PowerDraw::Menu::Item { ggformat_to_string(i18n(menu.setting.format.current), currentSetting).c_str() };

            PowerDraw::Menu::Item { []() {
                // Modal::Show(text("New Setting"));
            }, i18n(menu.setting.new) };

            PowerDraw::Menu { [&]() {
                for (auto &&it : VariableManager::GetAllSettingsName()) {
                    PowerDraw::Menu::Item { [&]() {
                        VariableManager::LoadSetting(it.data());
                    }, it.c_str(), it == currentSetting };
                }
            }, i18n(menu.setting.load) };

            PowerDraw::Menu::Item { [&]() {
                VariableManager::SaveAllSettings();
            }, i18n(menu.setting.saveall) };

            // bug: ImGui::MenuItem won't activate modal due to not being in the same stack of the main menu

            PowerDraw::Menu::Item { [&]() {
                if (currentSetting != textpp("Default")) {
                    // Modal::Show(text("Rename Setting As"));
                }
            }, ggformat_to_string(i18n(menu.setting.format.rename), currentSetting).c_str() };

            PowerDraw::Menu::Item { []() {
                // Modal::Show(text("Duplicate Setting As"));
            }, ggformat_to_string(i18n(menu.setting.format.duplicate), currentSetting).c_str() };

            PowerDraw::Menu::Item { [&]() {
                if (currentSetting != textpp("Default")) {
                    // Modal::Show(text("Remove Setting"));
                }
            }, ggformat_to_string(i18n(menu.setting.format.remove), currentSetting).c_str() };

            PowerDraw::Menu { [&]() {
                for (auto &&it : VariableManager::GetAllSettingsName()) {
                    PowerDraw::Menu::Item { [&]() {
                        VariableManager::SetDefaultSetting(it.data());
                    }, it.c_str(), it == VariableManager::GetDefaultSetting() };
                }
            }, i18n(menu.setting.set.default) };
        } },
        { lazy(i18n(menu.language)), []() {
            for (auto &it : I18NManager::GetTranslationProviders()) {
                PowerDraw::Menu::Item { [&]() {
                    I18NManager::SetLocale(it.first.data());
                }, it.second, it.first == I18NManager::GetLocale() };
            }
        } }
    };

    void DrawManager::Init() {
        auto dir = GameUtility::GetHackDirectory();
        ImGui::GetStyle().WindowTitleAlign = ImVec2(0.5f, 0.5f);
        auto &io = ImGui::GetIO();
#if !SIMULATOR
        io.IniFilename = (dir + io.IniFilename).c_str();
        io.LogFilename = (dir + io.LogFilename).c_str();
#endif

        io.Fonts->AddFontFromFileTTF(text("c:\\Windows\\Fonts\\msyhl.ttc"), 18.0f, nullptr, io.Fonts->GetGlyphRangesChinese()); 
        // Microsoft YaHei, fuck yeah unicode font


    }

    void DrawManager::Render() {
        bool &showHeader = DynamicVariable(misc.showheader).Get<bool>();

#if !SIMULATOR
        ImGui::GetIO().MouseDrawCursor = StateManager::IsMenuActivated();
#endif

        if (showHeader) {
            PowerDraw::Begin{ []() {
              ImGui::SetWindowPos({ ImGui::GetIO().DisplaySize.x / 1.5f, 100 });
              PowerDraw::Text { text("Welcome To SteveBase") };
              PowerDraw::Text { text("Proudly Made By stevefan1999@UC") };
            }, text("SteveBase Overlay"), &showHeader, { 0, 0 }, 0.5f, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoSavedSettings };
        }

        if (StateManager::IsMenuActivated()) {
            PowerDraw::Begin{ []() {
              PowerDraw::MenuBar { []() {
                for (auto &it : menuBars) PowerDraw::Menu { it.second, it.first() };
              } };

              const size_t tabsSize = sizeof tabs / sizeof tabs[0];

              PowerDraw::Child { [&]() {
                PowerDraw::Column { [&]() {
                  for (size_t i = 0; i < tabsSize; i++) {
                    PowerDraw::Group { [&]() {
                      if (ImGui::SettableButton(tabs[i].first(), i == m_activeTab, { -1, -1 })) {
                        m_activeTab = i;
                      }
                    } };

                    PowerDraw::Column::Next {};
                  }
                }, tabsSize };
              }, text("tab menu"), ImVec2(0, ImGui::GetTextLineHeightWithSpacing() + ImGui::GetStyle().ItemSpacing.y), false, ImGuiWindowFlags_NoScrollWithMouse };

              PowerDraw::Separator{};

              tabs[m_activeTab].second();

            }, text("SteveBase"), nullptr,{ 500, 309 }, 0.25f, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_MenuBar };
        }


#if SIMULATOR
        PowerDraw::Begin{ []() {

          PowerDraw::Text {
              ggformat_to_string(text("Application average {0} ms/frame ({1} FPS)"), 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate).c_str()
          };
          PowerDraw::Text {
              text(u8"你好測試"), text(u8"你好世界")
          };

          PowerDraw::Text {
              ggformat_to_string(text("Loaded Setting: {0}"), VariableManager::GetCurrentSettingName()).c_str()
          };

          PowerDraw::BulletText{
              text("1234"), text("hello")
          };

          static int test = -1;
          static int test2 = -1;
          static List<const char *> l = { textdup("hello"), textdup("test"), textdup("abcd") };
          static List<const char *> j = { textdup("hello"), textdup("test"), textdup("abcde") };

          PowerDraw::Combo { [](int n, const char *str) {
            return false;
          }, text("test"), l, test, text("a") };

          PowerDraw::Combo { [](int n, const char *str) {
            return true;
          }, text("test2"), j, test2, text("b") };

          PowerDraw::Button([]() {
              ggprint(text("clicked\n"));
            Modal::Show([]() {
              PowerDraw::Text{ text("hello world") };

            }, text("test123"));
          }, text("test123"));

          PowerDraw::Button([]() {
              ImGui::OpenPopup("Delete ?");
          }, text("Delete..."));


          if (ImGui::BeginPopupModal("Delete ?", nullptr, ImGuiWindowFlags_AlwaysAutoResize)) {
            ImGui::Text("All those beautiful files will be deleted.\nThis operation cannot be undone!\n\n");
            ImGui::Separator();

            //static int dummy_i = 0;
            //ImGui::Combo("Combo", &dummy_i, "Delete\0Delete harder\0");

            static bool dont_ask_me_next_time = false;
            ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0, 0));
            ImGui::Checkbox("Don't ask me next time", &dont_ask_me_next_time);
            ImGui::PopStyleVar();

            if (ImGui::Button("OK", ImVec2(120, 0))) { ImGui::CloseCurrentPopup(); }
            ImGui::SameLine();
            if (ImGui::Button("Cancel", ImVec2(120, 0))) { ImGui::CloseCurrentPopup(); }

            ImGui::EndPopup();
          }

          if (ImGui::Button("Delete.."))
            ImGui::OpenPopup("Delete?");
          if (ImGui::BeginPopupModal("Delete?", nullptr, ImGuiWindowFlags_AlwaysAutoResize)) {
            ImGui::Text("All those beautiful files will be deleted.\nThis operation cannot be undone!\n\n");
            ImGui::Separator();

            //static int dummy_i = 0;
            //ImGui::Combo("Combo", &dummy_i, "Delete\0Delete harder\0");

            static bool dont_ask_me_next_time = false;
            ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0, 0));
            ImGui::Checkbox("Don't ask me next time", &dont_ask_me_next_time);
            ImGui::PopStyleVar();

            if (ImGui::Button("OK", ImVec2(120, 0))) { ImGui::CloseCurrentPopup(); }
            ImGui::SameLine();
            if (ImGui::Button("Cancel", ImVec2(120, 0))) { ImGui::CloseCurrentPopup(); }
            ImGui::EndPopup();
          }

          ImGui::SliderFloat("slider float", &fl, 0.0f, 1.0f, "ratio = %.3f");
        }, "Debug Menu", nullptr,{ 500, 309 } };

        PowerDraw::Begin{ []() {
          for (auto &it : VariableManager::GetCurrentSettingVariables()) {
            auto &var = it.second;

            PowerDraw::TreeNode { [&]() {
              PowerDraw::BulletText{ ggformat_to_string("uint8_t: {}", var.Get<uint8_t>()).c_str() };
              PowerDraw::BulletText{ ggformat_to_string("bool: {}", var.Get<bool>()).c_str() };
              PowerDraw::BulletText{ ggformat_to_string("uint16_t: {}", var.Get<uint16_t>()).c_str() };
              PowerDraw::BulletText{ ggformat_to_string("uint32_t: {}", var.Get<uint32_t>()).c_str() };
              PowerDraw::BulletText{ ggformat_to_string("float_t: {}", var.Get<float_t>()).c_str() };
              PowerDraw::BulletText{ ggformat_to_string("double_t: {}", var.Get<double_t>()).c_str() };
              PowerDraw::BulletText{ ggformat_to_string("uint64_t: {}", var.Get<uint64_t>()).c_str() };
            }, it.first.c_str() };
          }
        }, "Variable Debugger", nullptr, { 500, 309 }, -1, ImGuiWindowFlags_NoCollapse };
#endif
    }


    bool DrawManager::IsInitialized() {
        return m_isInitalized;
    }

    void DrawManager::SetInitialized(bool init) {
        m_isInitalized = init;
    }

    ScreenSize &DrawManager::GetScreenSize() {
#if !SIMULATOR
        static const void * addr = GetPattern("client.dll")("g_nCachedScreenSize");

        return **(ScreenSize **)addr;
#else
        static std::array<int, 2> size { -1, -1 };
        return *(ScreenSize *) &size;
#endif
    }
}
