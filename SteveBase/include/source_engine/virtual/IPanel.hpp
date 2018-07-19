#pragma once

#include <misc/ProxiedClass.hpp>

namespace SteveBase::SourceEngine::Virtual {
    interface IPanel extends Misc::ProxiedClass {
        DefineVFunc(GetName, (int vguiIndex) -> const char *)(36)(vguiIndex);
    };
}
