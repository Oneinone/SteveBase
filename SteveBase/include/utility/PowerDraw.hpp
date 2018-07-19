#pragma once

#include <misc/TypeAliases.hpp>
#include <vendor/imgui/imgui.h>

namespace SteveBase::Utility {
    using namespace Misc;

    struct PowerDraw {
        struct StyleVar {
            template<class Fn>
            constexpr FORCEINLINE StyleVar(Fn &&fn, ImGuiStyleVar idx, float val) {
                ImGui::PushStyleVar(idx, val);
                fn();
                ImGui::PopStyleVar();
            }
        };

        struct ToolTip {
            FORCEINLINE ToolTip(const char * toolTipOnHover) {
                if (ImGui::IsItemHovered()) {
                    ImGui::SetTooltip(toolTipOnHover);
                }
            }

        };

        struct TreeNode {
            template<class Fn>
            constexpr FORCEINLINE TreeNode(Fn &&fn, const char * text) {
                if (ImGui::TreeNode(text)) {
                    fn();
                    ImGui::TreePop();
                }
            }

        };

        struct Text {
            FORCEINLINE Text(const char * text) {
                ImGui::Text(text);
            }
            FORCEINLINE Text(const char * text, const char * toolTipOnHover) : Text(text) {
                ToolTip{ toolTipOnHover };
            }

        };

        struct BulletText {
            FORCEINLINE BulletText(const char * text) {
                ImGui::BulletText(text);
            }

            FORCEINLINE BulletText(const char * text, const char * toolTipOnHover) : BulletText(text) {
                ToolTip{ toolTipOnHover };
            }

        };

        struct Combo {
            template<class Fn>
            constexpr FORCEINLINE Combo(Fn &&onClick, const char * name, List<const char *> &list, int &selected) {
                const int saved = selected;
                if (ImGui::Combo(name, &selected, list.data(), list.size())) {
                    if (selected == saved) { // no change in input
                        return; // invalidate the change
                    }

                    if (!onClick(selected, list[selected])) { // if the input was invalid
                        selected = saved; // invalidate and revert the selection to the value before
                    }
                }
            }

            template<class Fn>
            constexpr FORCEINLINE Combo(Fn &&onClick, const char * name, List<const char *> &list, int &selected, const char * toolTipOnHover) : Combo(onClick, name, list, selected) {
                ToolTip{ toolTipOnHover };
            }

        };

        struct Button {
            template<class Fn>
            constexpr FORCEINLINE Button(Fn &&onClick, const char * text, ImVec2 size) {
                if (ImGui::Button(text, size)) {
                    onClick();
                }
            }
            template<class Fn>
            constexpr FORCEINLINE Button(Fn &&onClick, const char * text) : Button(onClick, text, {}) {
            }
            template<class Fn>
            constexpr FORCEINLINE Button(Fn &&onClick, const char * text, ImVec2 size, const char * toolTipOnHover) : Button(onClick, text, size) {
                ToolTip{ toolTipOnHover };
            }
        };

        struct SmallButton {
            template<class Fn>
            constexpr FORCEINLINE SmallButton(Fn &&onClick, const char * text) {
                if (ImGui::SmallButton(text)) {
                    if (onClick) {
                        onClick();
                    }
                }
            }

            template<class Fn>
            constexpr FORCEINLINE SmallButton(Fn &&onClick, const char * text, const char * toolTipOnHover) : SmallButton(onClick, text) {
                ToolTip{ toolTipOnHover };
            }
        };

        struct CheckBox {
            FORCEINLINE CheckBox(const char *text, bool &check) {
                ImGui::Checkbox(text, &check);
            }

            FORCEINLINE CheckBox(const char * text, bool &check, const char * toolTipOnHover) : CheckBox(text, check) {
                ToolTip{ toolTipOnHover };
            }
        };

        struct ChoiceBox {
            template<class Fn>
            constexpr FORCEINLINE ChoiceBox(Fn &&onClick, List<const char *> &list, int &selected) {

                const int saved = selected;
                if (ImGui::ListBox("", &selected, list.data(), list.size())) {
                    if (selected == saved) { // no change in input
                        return; // invalidate the change
                    }

                    if (!onClick(selected, list[selected])) { // if the input was invalid
                        selected = saved; // invalidate and revert the selection to the value before
                    }
                }
            }
            template<class Fn>
            constexpr FORCEINLINE ChoiceBox(Fn &&onClick, List<const char *> &list, int &selected, const char * toolTipOnHover) : ChoiceBox(onClick, list, selected) {
                ToolTip{ toolTipOnHover };
            }
        };

        struct Line {
            struct Same {
                FORCEINLINE Same() {
                    ImGui::SameLine();
                }
            };
        };

        struct Column {
            template<class Fn>
            constexpr FORCEINLINE Column(Fn &&fn, size_t count, bool border = false) {
                ImGui::Columns(count, nullptr, border);
                fn();
                ImGui::Columns(1);
            }

            struct Next {
                FORCEINLINE Next() {
                    ImGui::NextColumn();
                }
            };
        };

        struct Separator {
            FORCEINLINE Separator() {
                ImGui::Separator();
            }
        };

        struct Begin {
            template<class Fn>
            constexpr FORCEINLINE Begin(Fn &&fn, const char * name, bool* p_open = NULL, ImGuiWindowFlags flags = 0) {
                if (ImGui::Begin(name, p_open, flags)) {
                    fn();
                    ImGui::End();
                }
            }

            template<class Fn>
            constexpr FORCEINLINE Begin(Fn &&fn, const char * name, bool* p_open, const ImVec2& size_on_first_use, float bg_alpha = -1.0f, ImGuiWindowFlags flags = 0) {
                if (ImGui::Begin(name, p_open, size_on_first_use, bg_alpha, flags)) {
                    fn();
                    ImGui::End();
                }
            }
        };

        struct Child {
            template<class Fn>
            constexpr FORCEINLINE Child(Fn &&fn, const char * str_id, const ImVec2& size = ImVec2(0, 0), bool border = false, ImGuiWindowFlags extra_flags = 0) {
                if (ImGui::BeginChild(str_id, size, border, extra_flags)) {
                    fn();
                    ImGui::EndChild();
                }
            }
        };

        struct MenuBar {

            template <class Fn>
            constexpr FORCEINLINE MenuBar(Fn &&fn) {
                if (ImGui::BeginMenuBar()) {
                    fn();
                    ImGui::EndMenuBar();
                }
            }
        };

        struct Group {
            template<class Fn>
            constexpr FORCEINLINE Group(Fn &&fn) {
                ImGui::BeginGroup();
                fn();
                ImGui::EndGroup();
            }
        };

        struct Menu {
            template<class Fn>
            constexpr FORCEINLINE Menu(Fn &&fn, const char * id) {
                if (ImGui::BeginMenu(id)) {
                    fn();
                    ImGui::EndMenu();
                }
            }

            struct Item {
                FORCEINLINE Item(const char * label, const char * shortcut, bool selected = false, bool enabled = true) {
                    ImGui::MenuItem(label, shortcut, selected, enabled);
                }

                template<class Fn>
                constexpr FORCEINLINE Item(Fn &&fn, const char * label, const char * shortcut, bool selected = false, bool enabled = true) {
                    if (ImGui::MenuItem(label, shortcut, selected, enabled)) {
                        fn();
                    }
                }

                FORCEINLINE Item(const char * label, bool selected = false, bool enabled = true) {
                    ImGui::MenuItem(label, nullptr, selected, enabled);
                }

                template<class Fn>
                constexpr FORCEINLINE Item(Fn &&fn, const char * label, bool selected = false, bool enabled = true) {
                    if (ImGui::MenuItem(label, nullptr, selected, enabled)) {
                        fn();
                    }
                }

            };
        };
    };
}