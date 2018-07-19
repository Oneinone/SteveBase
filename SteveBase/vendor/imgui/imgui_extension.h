#pragma once

#include "imgui.h"

namespace ImGui {
	IMGUI_API bool SettableButton(const char* label, bool should_activate = false, ImVec2 size_arg = ImVec2(0, 0));
}