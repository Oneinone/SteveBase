#pragma once

#include <Interface.hpp>
#include <source_engine/struct/CGlobalVarsBase.hpp>

namespace SteveBase::Hook {
    using namespace SourceEngine::Structure;

    class Banner {
        int position = -240;
        Tuple<float, float> time = Get<CGlobalVarsBase>()->GetRelativeTimeToReal(1 / (float)120);
    public:
        void OnPaintTraverse();
    };
}
