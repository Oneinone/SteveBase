#pragma once

#include <maths/Vector3.hpp>
#include <misc/ProxiedClass.hpp>

namespace SteveBase::SourceEngine::Virtual {
    using namespace Maths;

    interface IVDebugOverlay extends Misc::ProxiedClass {
        DefineVFunc(ScreenPosition, (const Vector3 &vIn, Vector3 &vOut) -> bool)(9)(vIn, vOut);
    };
}
