#pragma once

#include <misc/ProxiedClass.hpp>

namespace SteveBase::SourceEngine::Virtual {
    // todo
    enum class PaintMode_t {
        UIPanels = (1 << 0),
        InGamePanels = (1 << 1),
        Cursors = (1 << 2), // software cursor, if appropriate
    };

    interface IEngineVGui extends Misc::ProxiedClass {
        DefineVFunc(Paint, (PaintMode_t mode) -> void)(14)(mode);
    };
}