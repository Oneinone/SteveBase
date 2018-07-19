#pragma once

#include <maths/ViewMatrix.hpp>
#include <misc/ProxiedClass.hpp>

namespace SteveBase::SourceEngine::Structure {
    struct model_t;
}

namespace SteveBase::Maths {
    class EulerAngle;
    class Vector3;
}

namespace SteveBase::SourceEngine::Virtual {
    using namespace Maths;
    using namespace Structure;

    interface IClientRenderable extends Misc::ProxiedClass {
        /*
        Vector3 &GetRenderOrigin() {
            return VCALL(0, ArgsRet(Vector3 &))();
        }

        void SetRenderOrigin(Vector3 &origin) {
            VCALL(0, ArgsRet(Vector3 &))() = origin;
        }

        EulerAngle &GetRenderAngles() {
            return VCALL(1, ArgsRet(EulerAngle &))();
        }

        void SetRenderAngles(EulerAngle &angle) {
            VCALL(1, ArgsRet(EulerAngle &))() = angle;
        }
        */

        DefineVFunc(GetModel, ()->model_t *)(8)();
        DefineVFunc(SetupBones, (ViewMatrix *matrix, int maxBones, int boneMask, float curTime) -> bool)(13)(matrix, maxBones, boneMask, curTime);
        DefineVFunc(GetRenderBounds, (Vector3 &mins, Vector3 &maxs) -> void)(17)(mins, maxs);
    };
}